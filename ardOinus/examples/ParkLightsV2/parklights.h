

#ifndef PARKLIGHTS___H
#define PARKLIGHTS___H

#include <SPI.h>
#include "WiFi.h"
#include "ardOinus.h"
#include "ArdoFastLED.h"
#include <Adafruit_GFX.h>    // Core graphics library
#include <Adafruit_ST7735.h> // Hardware-specific library for ST7735
#include <Adafruit_ST7789.h> // Hardware-specific library for ST7789
#include "AsyncUDP.h"
#include <WiFiUdp.h>
#include <ArduinoOTA.h>
#include "ardo_time_poller.h"  // A time poller class.
#include "ardo_color_space.h"
#include "setlx_array.h"
#include "ardo_packet_reassembler.h"

#include <lwip/sockets.h>
#include <lwip/netdb.h>
#include <errno.h>

#include "ssid_creds.h" // contains symbols ssid and password
/*
*** If ssid_creds.h is missing, create it with creds like so: ***
namespace {
constexpr char ssid[] = "<your wifi ssid name>";
constexpr char password[] = "<your wifi password>";
constexpr char ota_password[] = "<The OTA update password>";
}
*** ***
*/


#define PL_VERSION "V1.1"

using namespace setl::time_suffix_ops;

using SerialA = ardo::SerialIO<115200>;

/*
 * SpiPinsModule reserves the pins used for the SPI bus.
 */
template <int w_cs, int w_clk, int w_miso, int w_mosi>
struct SpiPinsModule : public ardo::ModuleBase<ardo::Parameters<
  ardo::ExternalPin<w_cs>,
  ardo::ExternalPin<w_clk>,
  ardo::ExternalPin<w_miso>,
  ardo::ExternalPin<w_mosi>>> {

  static constexpr int CS{w_cs};
  static constexpr int CLK{w_clk };
  static constexpr int MISO{w_miso};
  static constexpr int MOSI{w_mosi};
};

// The hard wired SPI interface pins for ESP32.
using Esp32VSpi = SpiPinsModule<5, 18, 19, 23>;
using Esp32HSpi = SpiPinsModule<15, 6, 12, 13>;


// The hard wired SPI interface pins for ATMEGA328P.
using AtMegaSpi = SpiPinsModule<10, 13, 12, 11>;

class Finally {
public:
  Finally(std::function<void()> func) : func(func) {}

  ~Finally() {
    if (enabled) {
      func();
    }
  }

  void disable() {
    enabled = false;
  }
private:
  bool enabled = { true };
  std::function<void()> func;
};

// Cursor position value type.
struct CursorPos {
  int16_t pos[2];
};

// Dimenstions value type.
struct Dimensions {
  uint16_t size[2];
};

Dimensions operator-(const CursorPos& lhs, const CursorPos& rhs) {
  return { {lhs.pos[0] - rhs.pos[0], lhs.pos[1] - rhs.pos[1]} };
}

/**
 * Helper class to access protected fields of Adafruit GFX classes.
 */
template <typename w_GfxType>
class GfxWithHelpers : public w_GfxType {
public:
  using Base = w_GfxType;

  template <typename... T>
  GfxWithHelpers(T... p)
    : Base(p...)
  {}

  Dimensions getTextSize() const {
    return { {this->textsize_x, this->textsize_y} };
  }

  using Base::setTextSize;

  // Set/restore text size.
  void setTextSize(const Dimensions& size) {
    this->setTextSize(size.size[0], size.size[1]);
  }

  CursorPos getCursorPos() const {
    return { {this->getCursorX(),  this->getCursorY()} };
  }

  Dimensions getDimensions() const {
    return { {this->width(),  this->height()} };
  }

  int16_t getTextHeight(int16_t textSize) {
    const Dimensions savedSize{ this->getTextSize() };
    Finally restoreSize{ [&]() { this->setTextSize(savedSize); } };
    this->setTextSize(textSize);
    CursorPos pos;
    Dimensions size;
    this->getTextBounds(
      "Pp", 20, 0, pos.pos + 0, pos.pos + 1, size.size + 0, size.size + 1);
    return size.size[1];
  }
};

template <typename w_spi_module, int w_tft_rst, int w_tft_dc>
class CentralParkTftBase : public ardo::ModuleBase<
  ardo::Parameters<ardo::ExternalPin<w_tft_rst>, ardo::ExternalPin<w_tft_dc>>,
  ardo::DependentModules<w_spi_module>> {

  // TFT parameters.
  static constexpr int TFT_DC{ w_tft_dc };
  static constexpr int TFT_RST{ w_tft_rst };

  using SpiModule = w_spi_module;

 public:
   static void runSetup() {
     instance().instanceRunSetup();
   }

   void instanceRunSetup() {
     // Use this initializer if using a 1.8" TFT screen:
     tft.initR(INITR_BLACKTAB);  // Init ST7735S chip, black tab
     tft.fillScreen(ST77XX_BLACK);
     tft.setRotation(1);
   }

   static void runLoop() {
   }

   using TftType = GfxWithHelpers<Adafruit_ST7735>;

   // Applies to 1.44" and 1.8" TFT
   TftType tft{ SpiModule::CS, TFT_DC, TFT_RST };

   static CentralParkTftBase& instance() {
     static CentralParkTftBase obj;
     return obj;
   }
};

using CentralParkTft = CentralParkTftBase<Esp32VSpi, 4, 21>;

// Configure the LED strip display size.
constexpr uint16_t LEDS_X_SIZE = 75;  // 2.5m of a 5m 30 LEDs/m strip.
constexpr uint16_t LEDS_Y_SIZE = 22;  // Number of 2.5m rows.
constexpr uint16_t LEDS_COUNT = LEDS_X_SIZE * LEDS_Y_SIZE;
constexpr float PIXEL_Y_X_SIZE_RATIO = (990.0 / 21) / (1000.0 / 30);


// Create an LEDs module.
using CentralParkLeds = ardo_fastled::LedStrip<
  LEDS_COUNT, ardo::ExternalPin<27>, WS2815, RGB, 210>;

struct RgbColor {
  CRGB convert() const {
    return *reinterpret_cast<const CRGB*>(this);
  }
  uint8_t values[3];
};

struct FrameIdent {
  uint32_t frame_number;
  uint64_t stream_id;
};

inline bool operator==(const FrameIdent& lhs, const FrameIdent& rhs) {
  return lhs.frame_number == rhs.frame_number && lhs.stream_id == rhs.stream_id;
}

inline bool operator!=(const FrameIdent& lhs, const FrameIdent& rhs) {
  return !(lhs == rhs);
}

struct RgbFrame {
  RgbColor& get(uint16_t x, uint16_t y) {
    return pixels[LEDS_X_SIZE * y + x];
  }

  void fill(const RgbColor& colour) {
    for (int i = 0; i < LEDS_COUNT; ++i) {
      pixels[i] = colour;
    }
  }

  FrameIdent frame_ident;
  RgbColor pixels[LEDS_COUNT];
};

extern const RgbFrame DEFAULT_IMAGE;

// The frame buffer...
RgbFrame rgbFrame;

class LedsUpdater : public ardo::ModuleBase<
  ardo::Parameters<>,
  ardo::DependentModules<CentralParkLeds>> {
public:

  static LedsUpdater& getInstance() {
    static LedsUpdater instance;
    return instance;
  }

  static void runLoop() {
    getInstance().updateDisplay();
  }

  void updateDisplay() {
    if (current_frame_ident != rgbFrame.frame_ident) {
      current_frame_ident = rgbFrame.frame_ident;
      frame_update_count++;

      for (uint16_t yi = 0; yi < LEDS_Y_SIZE; ++yi) {
        // Even and odd loops switch direction.
        auto offs = yi * LEDS_X_SIZE;
        if (yi & 1) {
          for (uint16_t xi = 0; xi < LEDS_X_SIZE; ++xi) {
            auto& pixel = rgbFrame.get(LEDS_X_SIZE - 1 - xi, yi);
            CentralParkLeds::set(offs + xi, pixel.convert());
          }
        }
        else {
          for (uint16_t xi = 0; xi < LEDS_X_SIZE; ++xi) {
            auto& pixel = rgbFrame.get(xi, yi);
            CentralParkLeds::set(offs + xi, pixel.convert());
          }
        }
      }
    }
  }

  std::uint32_t frame_update_count;
  FrameIdent current_frame_ident{ ~0u };
};


/**
 * The state of the WIFI connection.
 */
struct ConnectionState {
  const char* name;
  const bool is_terminal;
  const bool is_restartable;
  const bool is_connected;
};

inline bool operator==(const ConnectionState& lhs, const ConnectionState& rhs) {
  return &rhs == &lhs;
}

inline bool operator!=(const ConnectionState& lhs, const ConnectionState& rhs) {
  return &rhs != &lhs;
}

namespace wstates {
  constexpr ConnectionState UNKNOWN{ "UNKNOWN", false, false };
  constexpr ConnectionState INITIALIZING{ "INITIALIZING", false, false };
  constexpr ConnectionState IDLE{ "IDLE", true, true };
  constexpr ConnectionState SSID_NOT_FOUND{ "SSID_NOT_FOUND", false, false };
  constexpr ConnectionState CONNECTION_FAILED{ "CONNECTION_FAILED", true, true };
  constexpr ConnectionState CONNECTED{ "CONNECTED", false, true, true };
  constexpr ConnectionState CONNECTION_LOST{ "CONNECTION_LOST", false, true };
  constexpr ConnectionState DISCONNECTED{ "DISCONNECTED", true, true };
} // wstates

class Esp32Wifi : public ardo::ModuleBase<ardo::Parameters<SerialA>> {
 public:

   using Poller = ardo::TimePoller<int16_t>;
   using PeriodType = Poller::TimeType::period_type;

   static const ConnectionState& getConnectionState() {
     switch (WiFi.status()) {
       case WL_IDLE_STATUS: {
         return wstates::IDLE;
       }
       case WL_NO_SSID_AVAIL: {
         return wstates::SSID_NOT_FOUND;
       }
       case WL_SCAN_COMPLETED: {
         return wstates::INITIALIZING;
       }
       case WL_CONNECTED: {
         return wstates::CONNECTED;
       }
       case WL_CONNECT_FAILED: {
         return wstates::CONNECTION_FAILED;
       }
       case WL_CONNECTION_LOST: {
         return wstates::CONNECTION_LOST;
       }
       case WL_DISCONNECTED: {
         return wstates::DISCONNECTED;
       }
       default: {
         return wstates::UNKNOWN;
       }
     }
   }

   static void startConnection() {
     WiFi.begin(ssid, password);
     WiFi.setAutoReconnect(true);
   }

   static void runSetup() {
     WiFi.mode(WIFI_STA);
     startConnection();
   }

   static void runLoop() {
     instance.instanceRunLoop();
   }

   void instanceRunLoop() {
     const ConnectionState* current = &getConnectionState();

     if (connection_state_for_reporting != current) {
       connection_state_for_reporting = current;
       poller.setNow();
       SerialA::println("Wifi in state: ", current->name);
     }
     if (current != connection_state) {
       if (poller.poll(5_sec)) {
         poller.setNow();
         connection_state = current;
         if (connection_state->is_terminal && connection_state->is_restartable) {
           SerialA::println("Restarting wifi for state ", connection_state->name);
           WiFi.disconnect();
           startConnection();
         } else {
           SerialA::println("Entered state ", connection_state->name);
         }
       }
     }
   }

   static bool is_connected() {
     return instance.connection_state == &wstates::CONNECTED;
   }

   static Esp32Wifi instance;

   const ConnectionState* connection_state = &wstates::INITIALIZING;
   const ConnectionState* connection_state_for_reporting = &wstates::INITIALIZING;
   Poller poller;
};

Esp32Wifi Esp32Wifi::instance;

using PowerPin = ardo::OutputPin<32, ardo::CoreIF::Output>;

enum OutputCommand : uint8_t {
  NO_OPERATION = 0,
  SET_HIGH = 1,
  SET_LOW = 2
};

template <typename...Pins>
class PinsSetter {
public:
  static constexpr uint32_t PINS_COUNT = 0;

  static bool setPinOfPinsEx(int pinNo, int thisPin, OutputCommand command) {
    return false;
  }

  static bool setPinOfPins(int pinNo, OutputCommand command) {
    return false;
  }
};

template <typename Pin, typename...Pins>
class PinsSetter<Pin, Pins...> {
public:
  static constexpr uint32_t PINS_COUNT = sizeof...(Pins) + 1;

  static void setPin(OutputCommand command) {
    switch (command) {
      case NO_OPERATION: {
        break;
      }
      case SET_HIGH: {
        Pin::set(true);
        break;
      }
      case SET_LOW: {
        Pin::set(false);
        break;
      }
    }
  }

  static bool setPinOfPinsEx(int pinNo, int thisPin, OutputCommand command) {
    if (pinNo == thisPin) {
      setPin(command);
      return true;
    } else {
      return PinsSetter<Pins...>::setPinOfPinsEx(pinNo, thisPin + 1, command);
    }
  }

  static bool setPinOfPins(int pinNo, OutputCommand command) {
    return PinsSetter<Pin, Pins...>::setPinOfPinsEx(pinNo, 0, command);
  }
};

///
/// A blinker for indicating network traffic.
/// 
/// 
/// From the ArdoBlink example + mods.
template <typename Seq, typename w_LedPin>
class BlinkModule : public ardo::ModuleBase<ardo::Parameters<w_LedPin>> {
public:
  using LedPin = w_LedPin;
  using Poller = ardo::CyclicTimeSequencePoller<Seq>;

  static BlinkModule& instance() {
    static BlinkModule main_instance;  // Define an instance here.
    return main_instance;
  }

  static void runLoop() {
    instance().instanceLoop();
  }

  void instanceLoop() {
    if (runningCycle) {
      if (timeSequence.poll()) {
        LedPin::set(!(timeSequence.state() & 1));
        if (timeSequence.state() >= (Poller::Sequence::count -1)) {
          runningCycle = false;
          LedPin::set(false);
        }
      }
    }
  }

  static void start() {
    instance().instanceStart();
  }

  void instanceStart() {
    if (!runningCycle) {
      runningCycle = true;
      timeSequence.reset();
    }
  }

  bool runningCycle{ false };
  Poller timeSequence;  // State variable.
};

using NetworkBlinker = BlinkModule<
  ardo::Sequence<50, 40, 50, 40, 50, 20, 30, 20, 30>,
  ardo::OutputPin<2>>;

///
/// Some network helper classes. 
/// 

using RecieverFunc = std::function<void(
  const uint8_t* data,
  std::uint32_t length,
  IPAddress remote_addr,
  std::uint16_t remote_port
  )>;

class ParklightsUdpAsync {
public:
  bool start(uint16_t port, const RecieverFunc& func) {
    is_open = udp.listen(port);
    if (!is_open) {
      SerialA::println("Error - UDP listen failed");
      return false;
    } else {
      udp.onPacket(
        [func](AsyncUDPPacket& packet) {
          func(packet.data(),
            packet.length(), 
            packet.remoteIP(), 
            packet.remotePort());
        });
    }
    return true;
  }

  std::size_t broadcast(
    const std::uint8_t* data,
    std::size_t length,
    std::uint16_t remote_port) {
    return udp.broadcastTo(
      const_cast<std::uint8_t *>(data), length, remote_port);
  };

  std::size_t send_to(
    const uint8_t* data,
    std::size_t length,
    IPAddress remote_ip,
    std::uint16_t remote_port) {
    auto sent = udp.writeTo(data, length, remote_ip, remote_port);

    if (sent < 0) {
      // Report the error.
      SerialA::println("Could not send data: ", errno);
    }
    else {
      sent_messages++;
      sent_bytes += sent;
    }
    return sent;
  }

  void dispatch_all(std::int32_t max_dispatch) {
    // received data is dispatched in a worker thread.
  }

  bool is_connected() {
    return is_open;
  }

  bool is_open = false;
  AsyncUDP udp;
  std::uint32_t sent_messages{};
  std::uint32_t sent_bytes{};
};

class ParklightsUdp {
public:
  virtual ~ParklightsUdp() {
    stop();
  }

  bool start(uint16_t port, const RecieverFunc& func) {
    if (is_connected()) {
      stop();
    }
    local_port = port;
    receiver_func = func;
    if ((udp_server = socket(AF_INET, SOCK_DGRAM, 0)) == -1) {
      SerialA::println("could not create socket: ", errno);
      return false;
    }
    Finally close_socket{ [this]() { stop(); } };
    int yes = 1;
    if (setsockopt(udp_server, SOL_SOCKET, SO_REUSEADDR, &yes, sizeof(yes)) < 0) {
      SerialA::println("could not set socket option: ", errno);
      return 0;
    }

    sockaddr_in addr{};
    addr.sin_family = AF_INET;
    addr.sin_port = htons(local_port);
    addr.sin_addr.s_addr = htonl(INADDR_ANY);
    if (bind(udp_server, (sockaddr*) &addr, sizeof(addr)) == -1) {
      SerialA::println("could not bind socket: ", errno);
      return false;
    }
    close_socket.disable();
    fcntl(udp_server, F_SETFL, O_NONBLOCK);
    return true;
  }

  void stop() {
    if (!is_connected()) {
      return;
    }

    close(udp_server);
    udp_server = -1;
  }

  bool is_connected() {
    return udp_server >= 0;
  }

  std::size_t broadcast(
    const uint8_t* data,
    std::size_t length,
    std::uint16_t remote_port) {
    return send_to(data, length, IP4_ADDR_BROADCAST->addr, remote_port);
  }

  std::size_t send_to(
    const uint8_t* data,
    std::size_t length,
    IPAddress remote_ip,
    std::uint16_t remote_port) {

    if (length > CONFIG_TCP_MSS) {
      errno = EOVERFLOW;
      return -1;
    }
    sockaddr_in recipient{};
    recipient.sin_addr.s_addr = htonl(remote_ip);
    recipient.sin_family = AF_INET;
    recipient.sin_port = htons(remote_port);
    int sent = sendto(udp_server,
      data, 
      length, 
      0, 
      reinterpret_cast<sockaddr*>(&recipient), 
      sizeof(recipient));

    if (sent < 0) {
      // Report the error.
      SerialA::println("Could not send data: ", errno);
    } else {
      sent_messages++;
      sent_bytes += sent;
    }
    return sent;
  };

  void dispatch_all(std::int32_t max_dispatch) {
    while (dispatch_packet() && (max_dispatch-- > 0)) {}
  }

protected:

  bool dispatch_packet() {
    if (!is_connected()) {
      return false;
    }
    struct sockaddr_in si_other;
    int slen{ sizeof(si_other) };

    int len;
    if ((len = recvfrom(
        udp_server,
        buffer,
        sizeof(buffer),
        MSG_DONTWAIT,
        reinterpret_cast<sockaddr*>(&si_other),
        (socklen_t*) &slen)) == -1) {
      if (errno == EWOULDBLOCK) {
        return false;
      }
      SerialA::println("could not receive data: ", errno);
      return false;
    }

    receiver_func(
      buffer,
      len,
      IPAddress{si_other.sin_addr.s_addr},
      ntohs(si_other.sin_port));
    return true;
  }

  RecieverFunc receiver_func;
  int udp_server{ -1 };
  std::uint16_t local_port{ 0 };
  uint8_t buffer[1460];
 public:
  std::uint32_t sent_messages{};
  std::uint32_t sent_bytes{};
};

constexpr uint16_t MAGIC_SIZE = 4;
constexpr char MAGIC_INPUT[MAGIC_SIZE + 1] = "#PLI";
constexpr char MAGIC_BROADCAST[MAGIC_SIZE + 1] = "#PLB";
constexpr char MAGIC_ACK[MAGIC_SIZE + 1] = "#PLA";

class UdpServer : public ardo::ModuleBase<
  ardo::Parameters<PowerPin>,
  ardo::DependentModules<Esp32Wifi, CentralParkLeds, CentralParkTft, NetworkBlinker>> {
public:
  using Receiver = ardo::FragmentReceiver<2, 5, 1400>;
  using ReceiverFunc = Receiver::ReceiverFunc;
  using Poller = ardo::TimePoller<int16_t>;
  using PeriodType = Poller::TimeType::period_type;
  static constexpr uint16_t PORT{4159 };
  static constexpr uint16_t CLIENT_PORT{ 4169 };
  static constexpr bool SEND_ACK{ false };
  static constexpr std::int32_t MAX_DISPATCH{ 5 };

  static void runSetup() {
  }

  static void runLoop() {
    getInstance().instanceRunLoop();
  }

  void instanceRunLoop() {
    if (!listening) {
      // If we're not yet listening, see if we're connected.
      if (Esp32Wifi::instance.connection_state == &wstates::CONNECTED) {
        start_listening();
      } else {
        whenNotConnectedLoop();
      }
    } else {
      // We're listening.
      udp.dispatch_all(MAX_DISPATCH);  // Only works for sync UDP - Async UDP is async!

      // Periodically broadcast the status.
      if (broadcastPoller.poll(10_sec)) {
        broadcastStatus();
      }
    }
  }

  void start_listening() {
    listening = udp.start(PORT, [this](
        const uint8_t* data,
        std::uint32_t length,
        IPAddress remote_addr,
        std::uint16_t remote_port
      ) { recievedPacket(data, length, remote_addr, remote_port); });

    if (reportPoller.poll(3_sec)) {
      SerialA::println("udp.start result: ", listening);
    }
  }

  void restart_udp() {
    static bool do_restart = false;
    auto count = recieved_msgs - recieved_msgs_restart;
    if (count > 28) {
      recieved_msgs_restart = recieved_msgs;
      do_restart = true;
      resetPoller.reset();
    }

    if (do_restart && resetPoller.poll(20_sec)) {
      ESP.restart();
    }
  }

  void broadcastStatus() {
    String str(MAGIC_BROADCAST);
    // Write in YAML format.
    str.concat("\nPARKLIGHTS: " PL_VERSION "\nip_addr: ");
    auto ipaddr = WiFi.localIP();
    str.concat(ipaddr.toString());
    str.concat("\nsent_msgs: ");
    str.concat(udp.sent_messages);
    str.concat("\nsent_bytes: ");
    str.concat(static_cast<uint32_t>(udp.sent_bytes));
    str.concat("\nrecieved_msgs: ");
    str.concat(recieved_msgs);
    str.concat("\nrecieved_msgs_restart: ");
    str.concat(recieved_msgs_restart);
    str.concat("\nrecieved_bytes: ");
    str.concat(static_cast<uint32_t>(recieved_bytes));
    str.concat("\nrecieved_assembled_msgs: ");
    str.concat(recieved_assembled_msgs);
    str.concat("\nrecieved_assembled_bytes: ");
    str.concat(static_cast<uint32_t>(recieved_assembled_bytes));
    str.concat("\nmalformed_msgs: ");
    str.concat(malformed_msgs);
    str.concat("\npins_commands_success: ");
    str.concat(pins_commands_success);
    str.concat("\npins_commands_failed: ");
    str.concat(pins_commands_failed);
    str.concat("\naccepted_frames: ");
    str.concat(accepted_frames);
    str.concat("\ndropped_frames: ");
    str.concat(dropped_frames);
    str.concat("\nbrightness: ");
    str.concat(static_cast<unsigned>(FastLED.getBrightness()));
    str.concat("\nframe_updates: ");
    str.concat(LedsUpdater::getInstance().frame_update_count);
    str.concat("\n");
    
    size_t result = udp.broadcast(
      reinterpret_cast<const std::uint8_t*>(str.c_str()), str.length(), CLIENT_PORT);

    NetworkBlinker::start();
    SerialA::println(str);
    SerialA::println("broadcast result: ", result);
    sent_bytes += result;
    sent_msgs++;
  }

  void whenNotConnectedLoop() {
    if (poller.poll(16_msec)) {
      auto new_frame_number = 1 + rgbFrame.frame_ident.frame_number;
      rgbFrame = DEFAULT_IMAGE;
      rgbFrame.frame_ident.frame_number = new_frame_number;
    }

    if (reportPoller.poll(1_sec)) {
      SerialA::println("rgbFrame.frame_ident.frame_number = ", rgbFrame.frame_ident.frame_number);
    }
  }

  static UdpServer& getInstance() {
    static UdpServer obj;
    return obj;
  }

  enum PlCommands {
    NEXT_FRAME = 1,
    SET_BRIGHTNESS = 2,
    SET_OUTPUTS = 3,
    RESET_MCU = 0xff,
  };

  using ControlPins = PinsSetter<PowerPin>;

  void setPins(uint16_t len, const OutputCommand* commands) {
    auto count = len;
    if (count > ControlPins::PINS_COUNT) {
      pins_commands_failed += count - ControlPins::PINS_COUNT;
      count = ControlPins::PINS_COUNT;
    }
    for (int i = 0; i < count; ++i) {
      if (ControlPins::setPinOfPins(i, commands[i])) {
        pins_commands_success++;
      } else {
        pins_commands_failed++;
      }
    }
  }

  void recievedPacket(
      const uint8_t* data,
      std::uint32_t length,
      IPAddress remote_addr,
      std::uint16_t remote_port
    ) {
    NetworkBlinker::start();  // Start the indicator of network traffic.

    // This may be run in another thread. Don't call any non re-entrant functions.
    recieved_msgs++;
    recieved_bytes += length;
    resetPoller.reset();

    // Ack needed
    if (SEND_ACK) {
      udp.send_to(
        reinterpret_cast<const std::uint8_t*>(MAGIC_ACK),
        MAGIC_SIZE,
        remote_addr,
        remote_port);
    }

    assembler.receive(
      remote_addr,
      remote_port,
      data, 
      length, 
      assembled_func);
  }

  void assembled_packet(const uint8_t* data, std::uint32_t length) {
    recieved_assembled_msgs++;
    recieved_assembled_bytes += length;
    if (length <= MAGIC_SIZE) {
      malformed_msgs++;
      return;
    }
    if (memcmp(MAGIC_INPUT, data, MAGIC_SIZE) != 0) {
      malformed_msgs++;
      return;
    }

    // First byte after magic size is a command byte.
    auto len_payload = length - MAGIC_SIZE - 1;
    auto payload = data + MAGIC_SIZE + 1;
    switch (data[MAGIC_SIZE]) {
      case NEXT_FRAME: {
        if (len_payload != sizeof(RgbFrame)) {
          invalid_next_frames++;
        } else {
          const RgbFrame* next_frame = reinterpret_cast<const RgbFrame*>(payload);
          if (next_frame->frame_ident.frame_number != ~0u 
              && rgbFrame.frame_ident == next_frame->frame_ident) {
            // drop frame, assuming identical becuase frame ident is identical.
            dropped_frames++;
            break;
          }
          rgbFrame = *next_frame;
          accepted_frames++;
        }
        break;
      }
      case RESET_MCU: {
        delay(200); // Wait for Serial output.
        ESP.restart();
        break;
      }
      case SET_OUTPUTS: {
        const OutputCommand* commands = 
            reinterpret_cast<const OutputCommand*>(payload);
        setPins(len_payload, commands);
        break;
      }
      case SET_BRIGHTNESS: {
        const uint8_t brightness =
          *reinterpret_cast<const uint8_t*>(payload);
        CentralParkLeds::setBrightness(brightness);
        break;
      }
      default: {
        break;
      }
    }
  }

  ParklightsUdp udp;
  ReceiverFunc assembled_func{
    [this](const uint8_t* data, std::uint32_t length) {
      assembled_packet(data, length);
    }
  };
  Receiver assembler;
  Poller poller;
  Poller reportPoller;
  Poller broadcastPoller;
  Poller resetPoller;
  bool listening = false;
  uint32_t sent_msgs = 0;
  uint32_t sent_bytes = 0;
  uint32_t recieved_msgs = 0;
  uint32_t recieved_bytes = 0;
  uint32_t recieved_msgs_restart = 0;
  uint32_t recieved_assembled_msgs = 0;
  uint64_t recieved_assembled_bytes = 0;
  uint32_t malformed_msgs = 0;
  uint32_t malformed_commands = 0;
  uint32_t pins_commands_success = 0;
  uint32_t pins_commands_failed = 0;
  uint32_t invalid_next_frames = 0;
  uint32_t accepted_frames = 0;
  uint32_t dropped_frames = 0;
};

class NetworkStatusUpdater : public ardo::ModuleBase<
  ardo::Parameters<>,
  ardo::DependentModules<Esp32Wifi, CentralParkLeds, CentralParkTft>> {
public:

  static CentralParkTft::TftType& tft() {
    return CentralParkTft::instance().tft;
  }

  static NetworkStatusUpdater& getInstance() {
    static NetworkStatusUpdater instance;
    return instance;
  }

  static void drawtext(char* text, int16_t x, int16_t y, uint16_t color) {
    tft().setCursor(x, y);
    tft().setTextColor(color);
    tft().setTextWrap(true);
    tft().print(text);
  }

  static void runSetup() {
  }

  static void runLoop() {
    getInstance().updateNetworkState();
  }

  void updateNetworkState() {
    bool is_wifi_settled_current = Esp32Wifi::instance.connection_state_for_reporting
      == Esp32Wifi::instance.connection_state;
    if (is_wifi_settled != is_wifi_settled_current || Esp32Wifi::instance.connection_state_for_reporting != lastDisplayedState) {
      // Need to update the state.
      is_wifi_settled = is_wifi_settled_current;
      lastDisplayedState = Esp32Wifi::instance.connection_state_for_reporting;
      displayNetworkState(lastDisplayedState);
    }
  }

  void displayNetworkState(const ConnectionState* state) {
    GFXcanvas1 canvas(networkStateSize.size[0], networkStateSize.size[1]);
    if (state == &wstates::CONNECTED) {
      canvas.print("IP Addr: ");
      auto ipaddr = WiFi.localIP();
      canvas.print(ipaddr);
    } else {
      canvas.print("Net Status: ");
      canvas.print(state->name);
    }
    tft().drawBitmap(
      networkStateStartPos.pos[0], 
      networkStateStartPos.pos[1],  
      canvas.getBuffer(), 
      networkStateSize.size[0], 
      networkStateSize.size[1],
      ST77XX_YELLOW,
      is_wifi_settled ? ardo::rgb_888_to_565(0x007f00) : ardo::rgb_888_to_565(0x7f0000));
  }

  const uint16_t textHeightSmall = tft().getTextHeight(1);
  const CursorPos networkStateStartPos{ {0, tft().height() - textHeightSmall} };
  const CursorPos networkStateEndPos{ {tft().width() , tft().height() } };
  const Dimensions networkStateSize{ networkStateEndPos - networkStateStartPos };
  const ConnectionState* lastDisplayedState = &wstates::UNKNOWN;
  bool is_wifi_settled = true;
};

class LedsToTftMirror : public ardo::ModuleBase<
  ardo::Parameters<>,
  ardo::DependentModules<CentralParkLeds, CentralParkTft, UdpServer, LedsUpdater>> {
public:

  static CentralParkTft::TftType& tft() {
    return CentralParkTft::instance().tft;
  }

  static LedsToTftMirror& getInstance() {
    static LedsToTftMirror instance;
    return instance;
  }

  static void runSetup() {
    getInstance().canvas.fillScreen(ST77XX_BLACK);
    SerialA::println("LedsToTftMirror");
    SerialA::println("LEDS_X_SIZE = ", LEDS_X_SIZE);
    SerialA::println("tft().width() = ", tft().width());
    SerialA::println("tft().height() = ", tft().height());
    SerialA::println("pixelXsize = ", getInstance().pixelXsize);
    SerialA::println("pixelYsize = ", getInstance().pixelYsize);
    SerialA::println("pixelXcount = ", getInstance().pixelXcount);
    SerialA::println("pixelYcount = ", getInstance().pixelYcount);
    SerialA::println(
      "ardo::rgb_888_to_565(0xff, 0x33, 0x7f) = ", ardo::rgb_888_to_565(0xff, 0x33, 0x7f));

    SerialA::println("sizeof(RgbFrame) = ", sizeof(RgbFrame));

    SerialA::println("offsetof(RgbFrame, frame_ident) = ", offsetof(RgbFrame, frame_ident));
    SerialA::println("offsetof(RgbFrame, pixels) = ", offsetof(RgbFrame, pixels));
    SerialA::println("offsetof(FrameIdent, frame_ident) = ", offsetof(FrameIdent, frame_number));
    SerialA::println("offsetof(FrameIdent, stream_id) = ", offsetof(FrameIdent, stream_id));
    uint32_t endian = 0x0beeee01;
    SerialA::println("endian = ", int(*reinterpret_cast<unsigned char*>(&endian)));
  }

  static void runLoop() {
    getInstance().updateDisplay();
  }

  void updateDisplay() {
    auto buffer = canvas.getBuffer();
    if (current_frame_ident != rgbFrame.frame_ident) {

      for (uint16_t xi = 0; xi < LEDS_X_SIZE; ++xi) {
        for (uint16_t yi = 0; yi < LEDS_Y_SIZE; ++yi) {
          uint16_t pos = yi * pixelXcount * pixelYsize + xi * pixelXsize;
          buffer[pos] = ardo::rgb_888_to_565(rgbFrame.get(xi, yi).values);
        }
      }

      tft().drawRGBBitmap(0, 0, buffer, pixelXcount, pixelYcount);
      current_frame_ident = rgbFrame.frame_ident;
    }
  }

private:
  static uint16_t computeTftPixelYSize(uint16_t pixelXsize) {
    auto result = uint16_t(pixelXsize * PIXEL_Y_X_SIZE_RATIO + 0.5);
    return result ? result : 1;
  }

  const uint16_t pixelXsize = (tft().height() / LEDS_X_SIZE);
  const uint16_t pixelYsize = computeTftPixelYSize(pixelXsize);
  const uint16_t pixelXcount = (pixelXsize * (LEDS_X_SIZE - 1) + 1);
  const uint16_t pixelYcount = (pixelYsize * (LEDS_Y_SIZE - 1) + 1);
  const uint16_t bufferSize = pixelXcount * pixelYcount * LEDS_COUNT;
  FrameIdent current_frame_ident{ ~0u };
  GFXcanvas16 canvas{ pixelXcount, pixelYcount };
};

class Esp32OtaOld : public ardo::ModuleBase<> {
public:
  void handle_setup() {
    // Don't set up host name and onstart util we're connected.
    bool is_connected = Esp32Wifi::is_connected();
    if (is_connected == last_wifi_state_was_connected) {
      return;
    }
    last_wifi_state_was_connected = is_connected;
    if (!is_connected) {
      return;
    }
    SerialA::println("OTA Setup");
    ArduinoOTA.setHostname("parklights");
    ArduinoOTA.onStart([]() {
      String type;
      if (ArduinoOTA.getCommand() == U_FLASH) {
        type = "sketch";
      } else { // U_SPIFFS
        type = "filesystem";
      }
      // NOTE: if updating SPIFFS this would be the place to unmount SPIFFS using SPIFFS.end()
      SerialA::println("Start updating " + type);
        })
      .onEnd([]() {
          SerialA::println("\nEnd");
        })
          .onProgress([](unsigned int progress, unsigned int total) {
          Serial.printf("Progress: %u%%\r", (progress / (total / 100)));
            })
          .onError([](ota_error_t error) {
              Serial.printf("Error[%u]: ", error);
              if (error == OTA_AUTH_ERROR) SerialA::println("Auth Failed");
              else if (error == OTA_BEGIN_ERROR) SerialA::println("Begin Failed");
              else if (error == OTA_CONNECT_ERROR) SerialA::println("Connect Failed");
              else if (error == OTA_RECEIVE_ERROR) SerialA::println("Receive Failed");
              else if (error == OTA_END_ERROR) SerialA::println("End Failed");
            });
     is_initialized = true;
  }

  void instanceLoop() {
    handle_setup();
    if (is_initialized) {
      ArduinoOTA.handle();
    }
  }

  static void runLoop() {
    instance.instanceLoop();
  }

  bool last_wifi_state_was_connected = false;
  bool is_initialized = false;

  static Esp32OtaOld instance;
};

class Esp32Ota : public ardo::ModuleBase<> {
public:
  // This function will be called repeatedly from instanceLoop to manage OTA state
  void manageOtaState() {
    bool is_wifi_connected = Esp32Wifi::is_connected();

    if (is_wifi_connected) {
      // WiFi is connected
      if (!ota_service_initialized) {
        // OTA service has not been initialized yet for this WiFi session
        SerialA::println("OTA: WiFi Connected. Initializing OTA services...");

        // Set the hostname for OTA. This is how it will appear in Arduino IDE network ports.
        ArduinoOTA.setHostname("parklights"); // You can change "parklights" if needed

        // (Optional but recommended) Set a password for OTA updates
        ArduinoOTA.setPassword("UploadMe"); 
        // If you set a password, you'll be prompted for it in the Arduino IDE during upload.

        // Configure OTA event callbacks
        ArduinoOTA.onStart([]() {
          String type;
          if (ArduinoOTA.getCommand() == U_FLASH) {
            type = "sketch";
          }
          else { // U_SPIFFS
            type = "filesystem";
          }
          SerialA::println("OTA: Start updating " + type);
          // You might want to stop other critical operations here (e.g., motor control, sensor readings)
          // to ensure a smooth update process.
          });

        ArduinoOTA.onEnd([]() {
          SerialA::println("\nOTA: Update End. ESP32 will restart.");
          // The ESP32 will automatically reboot after a successful sketch update.
          });

        ArduinoOTA.onProgress([](unsigned int progress, unsigned int total) {
          // Avoid using SerialA::println here as it might be too slow or complex for an ISR-like context.
          // Stick to Serial.printf for progress if needed, or disable for faster updates.
          Serial.printf("OTA Progress: %u%%\r", (progress / (total / 100)));
          });

        ArduinoOTA.onError([](ota_error_t error) {
          Serial.printf("OTA Error[%u]: ", error);
          if (error == OTA_AUTH_ERROR) SerialA::println("Auth Failed");
          else if (error == OTA_BEGIN_ERROR) SerialA::println("Begin Failed (mDNS conflict or already running?)");
          else if (error == OTA_CONNECT_ERROR) SerialA::println("Connect Failed (IDE couldn't connect)");
          else if (error == OTA_RECEIVE_ERROR) SerialA::println("Receive Failed (network issue during transfer)");
          else if (error == OTA_END_ERROR) SerialA::println("End Failed (error finalizing update)");
          });

        // ****** CRITICAL: Start the ArduinoOTA service ******
        ArduinoOTA.begin();

        ota_service_initialized = true; // Mark OTA as initialized
        SerialA::println("OTA: Service started. Hostname: parklights. Waiting for uploads on network port.");
        SerialA::print("OTA: IP address: ");
        SerialA::println(WiFi.localIP().toString());
      }
    }
    else {
      // WiFi is not connected
      if (ota_service_initialized) {
        SerialA::println("OTA: WiFi Disconnected. OTA services are now inactive.");
        // ArduinoOTA.end(); // Optional: explicitly stop OTA. begin() should reinitialize if WiFi comes back.
        ota_service_initialized = false; // Reset the flag, so it re-initializes if WiFi reconnects
      }
    }
  }

  void instanceLoop() {
    manageOtaState(); // Manage OTA initialization and state based on WiFi connection

    // Only call ArduinoOTA.handle() if the service is initialized and WiFi is connected.
    // ArduinoOTA.handle() listens for incoming OTA requests from the IDE.
    if (ota_service_initialized && Esp32Wifi::is_connected()) {
      ArduinoOTA.handle();
    }
  }

  static void runLoop() {
    instance.instanceLoop();
  }

  // Flag to track if ArduinoOTA.begin() has been called successfully in the current WiFi session
  bool ota_service_initialized = false;

  static Esp32Ota instance; // Static instance for the module
};

Esp32Ota Esp32Ota::instance;

// Define the main app.
using mainApp = ardo::Application<NetworkStatusUpdater, LedsToTftMirror, LedsUpdater, Esp32Ota>;

#include "default_image.h"
#endif // PARKLIGHTS___H

