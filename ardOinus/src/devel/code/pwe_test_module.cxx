#include "ardOinus.h"
#include "pwm_serial_comms.h"

using setl::operator"" _msec;
using setl::operator"" _usec;

constexpr setl::TimeUnit UNITS = setl::TimeUnit::MICROS;
using time_type = ardo::CoreIF::MillisTime::type;
constexpr time_type settle_period = 16000;
constexpr time_type stop_period = 116000;
constexpr time_type bit_period = 15000;
using Collector = setl::PweBitCollector<8>;


using ReceiverModule = ardo::PweReceiverModule<
  ardo::InputPin<4>, 
  Collector, 
  time_type,
  settle_period, 
  stop_period, 
  bit_period, 
  false, 
  false,
  UNITS>;

using TransmitterModule = ardo::PweTransmitterModule<
  ardo::OutputPin<5>,
  Collector,
  time_type,
  settle_period,
  stop_period,
  bit_period,
  false,
  false,
  UNITS>;

// Use the arduino Serial port.
using SerialChannel = ardo::SerialIO<115200>;
using SerialModule = ardo::ModuleBase<ardo::Parameters<SerialChannel>>;


struct MainModule : public ardo::ModuleBase<ardo::Parameters<ardo::InputPin<18>>> {
  using Pin = MainModule::Params::Param<0>;

  static void runLoop() {
    if (Pin::get()) {
      return;
    }

    auto waitTime = ReceiverModule::instance.decoder.nextPollWaitTime(ardo::CoreIF::now());
    if (waitTime.get() < 3) {
      SerialChannel::println("decoder state, bit no = ",
        ReceiverModule::instance.decoder.get_bit_number());
      printDecoderStatus();
      printedStatus = true;
    } else {
      printedStatus = false;
    }

    if (TransmitterModule::instance.send(iterNo)) {
      SerialChannel::println("written value = ", iterNo);
      iterNo++;
    }
    ReceiverModule::value_type value;
    if (ReceiverModule::instance.readValue(value)) {
      SerialChannel::println("read value = ", int(value));
      if (lastReceived && (lastReceived + 1) != value) {
        SerialChannel::println("EXPECTED = ", int(lastReceived + 1));
      }
      lastReceived = value;
    }
    printDecoderStatus();
  }

  static void printDecoderStatus() {
    if (ReceiverModule::instance.decoder.isOverrun()) {
      SerialChannel::println("decoder is overrun, bit no = ", 
          ReceiverModule::instance.decoder.get_bit_number());
      ReceiverModule::instance.decoder.clearOverrun();
    }
    if (ReceiverModule::instance.decoder.hasSignalError()) {
      SerialChannel::println("decoder has signal error, bit no =",
        ReceiverModule::instance.decoder.get_bit_number());
      ReceiverModule::instance.decoder.clearSignalError();
    }
  }

  static int iterNo;
  static ReceiverModule::value_type lastReceived;
  static bool printedStatus;
};
int MainModule::iterNo = 0;
ReceiverModule::value_type MainModule::lastReceived = 0;
bool MainModule::printedStatus;


// Define the main app with the serial module and a timer module.
using mainApp = ardo::Application<
  SerialModule, ReceiverModule, TransmitterModule, MainModule>;

void setupPweTest() {
  mainApp::runSetup();
}

void loopPweTest() {
  mainApp::runLoop();
}




