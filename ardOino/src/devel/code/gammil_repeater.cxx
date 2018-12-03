
#include "ardoino.h"
#include "setl_time.h"

#include <FastLED.h>

#include "ArdoQuadEncoder.h"


enum PinAllocation : unsigned {
  LEDS_PIN = 9,

  KEYPAD_SINGLE = 2,
  KEYPAD_STOP = 3,
  KEYPAD_START = 4,
  KEYPAD_CUT = 5,
  KEYPAD_OPTION = 6,
  KEYPAD_MODE = 7,

  ROTARY_ENCODER_S1 = 10,
  ROTARY_ENCODER_S2 = 11,
  ROTARY_ENCODER_BUTTON = 12,
};

using GRTimeType = ardo::CoreIF::MillisTime;
using GRPeriodType = GRTimeType::period_type;

static const GRPeriodType SETTLE_PERIOD{ 3 };  // We wait 3ms before collission detection.
static const GRPeriodType LONG_PRESS_TIME{ 1000 };  // Long press time.
static const GRPeriodType LONG_RECOVERY_TIME{ 1000 };  // Time to wait to detect stop.

const long MAX_PERIOD = 3000;
const long MIN_PERIOD = 200;
static GRPeriodType HIGH_PERIOD{ 500 };  // Repeater off time
static const GRPeriodType LOW_PERIOD{ 100 };  // Repeater on time


using SerialPort = ardo::SerialIO<115200>;
using SerialModule = ardo::ModuleBase<ardo::Parameters<SerialPort>>;

using QEncoder = quad::QuadEncoder<
  ardo::DebounceInput<ardo::InputPin<ROTARY_ENCODER_S1>>,
  ardo::DebounceInput<ardo::InputPin<ROTARY_ENCODER_S2>>>;

using QEncoderModule = quad::QuadEncoderModule<QEncoder>;

class FrequencyAdjuster : public ardo::ModuleBase<ardo::Parameters<>> {
public:

  static void runSetup() {
    QEncoderModule::quadEncoder.setCurrentPosition(HIGH_PERIOD.get());
  }

  static void runLoop() {
    auto currentPos = QEncoderModule::quadEncoder.getCurrentPosition();
    if (currentPos > MAX_PERIOD) {
      currentPos = MAX_PERIOD;
      QEncoderModule::quadEncoder.setCurrentPosition(currentPos);
    }
    if (currentPos < MIN_PERIOD) {
      currentPos = MIN_PERIOD;
      QEncoderModule::quadEncoder.setCurrentPosition(currentPos);
    }

    HIGH_PERIOD = GRPeriodType(currentPos);
  }

};

template <
  unsigned w_count,
  typename w_LedPin, 
  template<uint8_t DATA_PIN, EOrder RGB_ORDER> class w_Type,
  EOrder w_colorOrder,
  uint8_t w_brightness
  >
class LedStrip : public ardo::ModuleBase<ardo::Parameters<w_LedPin>> {
public:
  constexpr static unsigned COUNT = w_count;
  constexpr static EOrder COLOR_ORDER = w_colorOrder;
  using LedPin = w_LedPin;

  static void runSetup() {
    instance.instanceSetup();
  }

  void instanceSetup() {
    FastLED.addLeds<w_Type, LedPin::PIN, COLOR_ORDER>(leds, COUNT).setCorrection(UncorrectedColor);
    FastLED.setBrightness(w_brightness);
  }

  static void runLoop() {
    instance.instanceLoop();
  }

  void instanceLoop() {
    if (has_changed) {
      FastLED.show();
      has_changed = false;
    }
  }

  void set(unsigned index, const CRGB& value) {
    auto& entry = leds[index];
    if (entry == value) {
      return; // not changed.
    }
    entry = value;
    has_changed = true;
  }

private:

  bool has_changed = true;
  CRGB leds[COUNT];

public:
  static LedStrip instance;
};

template <
  unsigned w_count,
  typename w_LedPin,
  template<uint8_t DATA_PIN, EOrder RGB_ORDER> class w_Type,
  EOrder w_colorOrder,
  uint8_t w_brightness
>
LedStrip<w_count, w_LedPin, w_Type, w_colorOrder, w_brightness>
  LedStrip<w_count, w_LedPin, w_Type, w_colorOrder, w_brightness>::instance;

using ButtonLeds = LedStrip<6, ardo::OutputPin<LEDS_PIN>, WS2812B, RGB, 64>;

/**
 * Button pad button handler interface.
 */
class PadButton {
public:
  enum class State : uint8_t {
    UNASSISTED_LOW = 1,  // Signal is low.
    UNASSISTED_HIGH,  // Physical button is pressed.
    ASSISTED_LOW,  // Set a low signal and it's off
    ASSISTED_COLLISION,  // A high signal was set but we're reading a low.
    ASSISTED_HIGH  // The signal is set to high and we're reading high.
  };

  enum class LevelSetting : uint8_t {
    OUTPUT_LOW,   // drive the pin output low
    OUTPUT_HIGH,  // leave the pin go high - will go high if no device is driving low.
    INPUT_LEVEL   // waiting for reading
  };

  PadButton(unsigned index) 
    : index(index) {}

  virtual ~PadButton() {}

  virtual State getState() const = 0;

  virtual void setLevel(const LevelSetting level) = 0;

  const unsigned index;
};

/**
 * Button pad button handler impl.
 */
template <
  typename w_Pin,
  unsigned w_index
>
class PadButtonImpl : public PadButton, public ardo::ModuleBase<ardo::Parameters<w_Pin>> {
public:

  using Pin = w_Pin;

  PadButtonImpl() 
    : PadButton(w_index) {}

  /**
   * Returns the current pin state.
   */
  State getState() const override {
    switch (drivingState) {
      case DrivingState::UNASSISTED_WAIT: {
        if (!settleTimePassed()) {
          return State::UNASSISTED_HIGH;
        }
        drivingState = DrivingState::UNASSISTED;
        // Fall through.
      }
      case DrivingState::UNASSISTED: {
        return Pin::get() ? (State::UNASSISTED_HIGH) : (State::UNASSISTED_LOW);
      }
      case DrivingState::ASSISTED_LOW: {
        return State::ASSISTED_LOW;
      }
      case DrivingState::ASSISTED_HIGH_WAIT: {
        if (!settleTimePassed()) {
          return State::ASSISTED_HIGH;
        }
        drivingState = DrivingState::ASSISTED_HIGH;
        // Fall through.
      }
      case DrivingState::ASSISTED_HIGH: {
        return Pin::get() ? (State::ASSISTED_HIGH) : (State::ASSISTED_COLLISION);
      }
    }
  }

  /**
   * Sets the dersired level.
   */
  virtual void setLevel(const LevelSetting level) {
    if (level != this->level) {
      this->level = level;
      time_switched = ardo::CoreIF::now();
      Pin::set(level != LevelSetting::OUTPUT_LOW);

      switch (level) {
        case LevelSetting::OUTPUT_LOW: {
          drivingState = DrivingState::ASSISTED_LOW;
          break;
        }
        case LevelSetting::OUTPUT_HIGH: {
          drivingState = DrivingState::ASSISTED_HIGH_WAIT;
          break;
        }
        case LevelSetting::INPUT_LEVEL: {
          drivingState = DrivingState::UNASSISTED_WAIT;
          break;
        }
      }
    }
  }

private:
  // Returns true if the settle time has passed.
  bool settleTimePassed() {
    GRTimeType now = ardo::CoreIF::now();
    auto period = now - time_switched;

    return period > SETTLE_PERIOD;
  }

  enum class DrivingState : uint8_t {
    UNASSISTED_WAIT = 1,  // We're a passive listener.
    UNASSISTED,  // We're a passive listener.
    ASSISTED_LOW,  // We're setting it low.
    ASSISTED_HIGH_WAIT,  // We're waiting for settle time.
    ASSISTED_HIGH,  // We're setting it high but another device might set it low.
  };

  mutable DrivingState drivingState = DrivingState::UNASSISTED;
  GRTimeType time_switched = ardo::CoreIF::now();
  LevelSetting level = LevelSetting::INPUT_LEVEL;

public:
  static PadButtonImpl instance;
};

template <
  typename w_Pin,
  unsigned index
>
PadButtonImpl<w_Pin, index> PadButtonImpl<w_Pin, index>::instance;

using KeyPadSingle = PadButtonImpl<ardo::OutputPin<KEYPAD_SINGLE, ardo::CoreIF::OpenDrainLowOutput>, 0>;
using KeyPadStop = PadButtonImpl<ardo::OutputPin<KEYPAD_STOP, ardo::CoreIF::OpenDrainLowOutput>, 1>;
using KeyPadStart = PadButtonImpl<ardo::OutputPin<KEYPAD_START, ardo::CoreIF::OpenDrainLowOutput>, 2>;
using KeyPadCut = PadButtonImpl<ardo::OutputPin<KEYPAD_CUT, ardo::CoreIF::OpenDrainLowOutput>, 3>;
using KeyPadOption = PadButtonImpl<ardo::OutputPin<KEYPAD_OPTION, ardo::CoreIF::OpenDrainLowOutput>, 4>;
using KeyPadMode = PadButtonImpl<ardo::OutputPin<KEYPAD_MODE, ardo::CoreIF::OpenDrainLowOutput>, 5>;

/**
 * Long press detect.
 */
template <typename w_Button>
class LongPressDetect : public ardo::ModuleBase<ardo::Parameters<>> {
public:
  using Button = w_Button;

  static void runLoop() {
    LongPressDetect::instance.instanceLoop();
  }

  bool isLongPressed() {
    if (lastState == PadButton::State::UNASSISTED_LOW) {
      GRTimeType now = ardo::CoreIF::now();
      if ((now - timeEntered) > LONG_PRESS_TIME) {
        return true;
      }
    }
    return false;
  }

private:
  void instanceLoop() {
    auto newState = Button::instance.getState();

    if (newState != lastState) {
      SerialPort::println("changed ", Button::Pin::PIN, " to ", int(newState));
      timeEntered = ardo::CoreIF::now();
      lastState = newState;
    }
  }

  PadButton::State lastState = PadButton::State::UNASSISTED_HIGH;
  GRTimeType timeEntered = ardo::CoreIF::now();
public:
  static LongPressDetect instance;
};

template <typename w_Button>
LongPressDetect<w_Button> LongPressDetect<w_Button>::instance;

using LongPressDetectKeyPadSingle = LongPressDetect<KeyPadSingle>;
using LongPressDetectKeyPadStop = LongPressDetect<KeyPadStop>;
using LongPressDetectKeyPadStart = LongPressDetect<KeyPadStart>;
using LongPressDetectKeyPadCut = LongPressDetect<KeyPadCut>;
using LongPressDetectKeyPadOption = LongPressDetect<KeyPadOption>;
using LongPressDetectKeyPadMode = LongPressDetect<KeyPadMode>;

/**
 * Repeater
 */
template <typename w_Button, typename w_StopButton>
class Repeater : public ardo::ModuleBase<ardo::Parameters<>> {
public:
  using Button = w_Button;
  using StopButton = w_StopButton;

  static void runLoop() {
    Repeater::instance.instanceLoop();
  }

private:
  enum class RepeaterState {
    Off,
    Started,
    RunningHigh,
    RunningLow
  };

  void instanceLoop() {
    switch (repeaterState) {
      case RepeaterState::Off: {
        if (LongPressDetect<Button>::instance.isLongPressed()) {
          setState(RepeaterState::Started);
        }
        break;
      }
      case RepeaterState::Started: {
        if (!LongPressDetect<Button>::instance.isLongPressed()) {
          setState(RepeaterState::RunningHigh);
        }
        break;
      }
      case RepeaterState::RunningHigh: {
        if (StopButton::instance.getState() != StopButton::State::UNASSISTED_HIGH
          || Button::instance.getState() == Button::State::ASSISTED_COLLISION) {
          setState(RepeaterState::Off);
          break;
        }

        if (hasPassed(HIGH_PERIOD)) {
          setState(RepeaterState::RunningLow);
        }
        break;
      }
      case RepeaterState::RunningLow: {
        if (StopButton::instance.getState() != StopButton::State::UNASSISTED_HIGH) {
          setState(RepeaterState::Off);
          break;
        }

        if (hasPassed(LOW_PERIOD)) {
          setState(RepeaterState::RunningHigh);
        }
        break;
      }
    }
  }

  bool hasPassed(const GRPeriodType& period) {
    GRTimeType now = ardo::CoreIF::now();
    return (now - timeEntered) > period;
  }

  void setState(RepeaterState state) {
    repeaterState = state;
    timeEntered = ardo::CoreIF::now();
    switch (repeaterState) {
      case RepeaterState::RunningHigh: {
        Button::instance.setLevel(Button::LevelSetting::OUTPUT_HIGH);
        break;
      }
      case RepeaterState::RunningLow: {
        Button::instance.setLevel(Button::LevelSetting::OUTPUT_LOW);
        break;
      }
      default: {
        Button::instance.setLevel(Button::LevelSetting::INPUT_LEVEL);
        break;
      }
    }
  }

  RepeaterState repeaterState = RepeaterState::Off;
  GRTimeType timeEntered = ardo::CoreIF::now();

  static Repeater instance;
};

template <typename w_Button, typename w_StopButton>
Repeater<w_Button, w_StopButton> Repeater<w_Button, w_StopButton>::instance;

// Repeater only happens on Single.
using RepeaterKeyPadSingle = Repeater<KeyPadSingle, KeyPadStop>;

/**
 * Translate state to button colour.
 */
template <typename w_Button>
class LedTranslator : public ardo::ModuleBase<ardo::Parameters<>> {
public:
  using Button = w_Button;

  static void runLoop() {
    ButtonLeds::instance.set(Button::instance.index, colorForButton());
  }

  static CRGB colorForButton() {
    switch (Button::instance.getState()) {
      case PadButton::State::UNASSISTED_HIGH: return 0x000010;
      case PadButton::State::UNASSISTED_LOW: {
        if (LongPressDetect<Button>::instance.isLongPressed()) {
          return CRGB::Indigo;
        }
        return CRGB::SeaGreen;
      }
      case PadButton::State::ASSISTED_LOW: return CRGB::LimeGreen;
      case PadButton::State::ASSISTED_COLLISION: return CRGB::Crimson;
      case PadButton::State::ASSISTED_HIGH: return 0x101000;
    }
    return CRGB::Red;
  }
};

using LedTranslatorKeyPadSingle = LedTranslator<KeyPadSingle>;
using LedTranslatorKeyPadStop = LedTranslator<KeyPadStop>;
using LedTranslatorKeyPadStart = LedTranslator<KeyPadStart>;
using LedTranslatorKeyPadCut = LedTranslator<KeyPadCut>;
using LedTranslatorKeyPadOption = LedTranslator<KeyPadOption>;
using LedTranslatorKeyPadMode = LedTranslator<KeyPadMode>;

using mainApp = ardo::Application<
  SerialModule,
  QEncoderModule,
  FrequencyAdjuster,
  ButtonLeds, 
  KeyPadSingle, 
  KeyPadStop, 
  KeyPadStart, 
  KeyPadCut,
  KeyPadOption,
  KeyPadMode,
  LongPressDetectKeyPadSingle,
  LongPressDetectKeyPadStop,
  LongPressDetectKeyPadStart,
  LongPressDetectKeyPadCut,
  LongPressDetectKeyPadOption,
  LongPressDetectKeyPadMode,
  RepeaterKeyPadSingle,
  LedTranslatorKeyPadSingle,
  LedTranslatorKeyPadStop,
  LedTranslatorKeyPadStart,
  LedTranslatorKeyPadCut,
  LedTranslatorKeyPadOption,
  LedTranslatorKeyPadMode
>;


void setup() {
  mainApp::runSetup();
}

void loop() {
  mainApp::runLoop();
}
