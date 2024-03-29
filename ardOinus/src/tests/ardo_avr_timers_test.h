#pragma once

#include "ardOinus.h"
#include "setlx_type_traits.h"
#include "setlx_cstdint.h"
#include "ardo_time_poller.h"  // A time poller class.
#include "ardo_timers.h"  // Hardware timers.

#include "setl_test_framework.h"

#define ARDUINO_AVR_NANO 1
#define __AVR_ATmega328p 1
#define F_CPU 16000000L
#include "arduino_boards.h"

#define AS_TEST 1

#if AS_TEST
namespace avr_timers_tests {
#endif

using PwmTimerConfigX = ardo::timers::TimerConfig<
  ardo::timers::VariableFrequency<10000>,  // 10 kHz.
  ardo::timers::Resolution<16>,    // 16 bit timer.
  ardo::timers::PwmPin<6>,  // Use pin 6 for PWM output.
  ardo::timers::avr::PhaseCorrectMode,  // Phase correct mode.
  ardo::timers::avr::TopCount<ardo::timers::avr::TopCountMode::icr>
>;

using PwmTimerConfigY = ardo::timers::TimerConfig<
  ardo::timers::Frequency<10000>,  // 10 kHz.
  ardo::timers::PwmPin<11>,  // Use pin 11 for PWM output.
  ardo::timers::avr::PhaseCorrectMode,  // Phase correct mode.
  ardo::timers::avr::TopCount<ardo::timers::avr::TopCountMode::icr>
>;

using AppTimerSelector = ardo::timers::TimerSelector<PwmTimerConfigX, PwmTimerConfigY>;

using AppTimers = AppTimerSelector::Select<PwmTimerConfigX, PwmTimerConfigY>;

using TimerX = AppTimers::Resolve<PwmTimerConfigX>;


//#include "sys/mcu/avr/ardo_sys_avr_mcu_defs.h"

namespace avrmcu = ardo::sys::avr::mcu;

// Use the arduino Serial port.
using SerialA = ardo::SerialIO<115200>;
using SerialM = ardo::ModuleBase<ardo::Parameters<SerialA>>;
using Seq = ardo::Sequence<2000, 2000>;

template <int timer, std::uint32_t freq>
class FixedFreqencyExample : 
    public ardo::ModuleInstanceBase<
    FixedFreqencyExample<timer, freq>,
    ardo::Parameters<>>
{   
public:
  using AvrTimer = avrmcu::Timer1;
  using AvrTimer8 = avrmcu::Timer2;

  template <typename TimerConf>
  void printTimerRegs(const char* timerName) {

#if AS_TEST
    TimerConf::setupTimer();
#endif

    using TimerDef = typename TimerConf::TimerDef;
    using WGM = typename TimerDef::BitsWGM_16;
    using CS = typename TimerDef::BitsCS;
    using Registers = typename TimerDef::Registers;
    using ComA = typename TimerDef::template OcrType<avrmcu::OcrEnum::OcrA>::COM;
    using ComB = typename TimerDef::template OcrType<avrmcu::OcrEnum::OcrB>::COM;
    using OcrA = typename TimerDef::template OcrType<avrmcu::OcrEnum::OcrA>::OCR;
    using OcrB = typename TimerDef::template OcrType<avrmcu::OcrEnum::OcrB>::OCR;

    WGM wgm;
    CS cs;
    ComA comA;
    ComB comB;
    OcrA ocrA;
    OcrB ocrB;

    using OcrEnum = ardo::sys::avr::mcu::OcrEnum;

    Registers::Read(wgm, cs, comA, comB, ocrA, ocrB);
    //Registers::Read(wgm, cs, comA, comB);
    //Registers::Read(ocrA, ocrB);

    // Registers::Read(wgm, cs);
    // Registers::Read(comA, comB);


    SerialA::println(timerName, " vvvvvvvvvvvvvvvvvvvvvvvv ");
    SerialA::println("wgm: ", (int)wgm.value, ardo::ModType<BIN>{},
      " cs: ", (int)cs.value, ardo::ModType<BIN>{},
      " comA: ", (int)comA.value, ardo::ModType<BIN>{},
      " comA: ", (int)comB.value, ardo::ModType<BIN>{},
      " ocrA: ", (int)ocrA.value,
      " ocrB: ", (int)ocrB.value);
    SerialA::println("Frequency: ", TimerConf::template getFrequency<float>());
    SerialA::println("top count: ", TimerConf::get_top_count());

    SerialA::println(timerName, " ^^^^^^^^^^^^^^^^^^^^^^ ");
  }

  inline void instanceSetup() {

    printTimerRegs<avrmcu::Timer0::BuiltInTop<
      1000, 16000000, avrmcu::TimerMode::pwm, avrmcu::TimerPwmMode::fast, 8>>("Timer0");

    printTimerRegs<avrmcu::Timer1::BuiltInTop<
      1000, 16000000, avrmcu::TimerMode::pwm, avrmcu::TimerPwmMode::phase_correct, 8>>("Timer1");

    printTimerRegs<avrmcu::Timer2::BuiltInTop<
      500, 16000000, avrmcu::TimerMode::pwm, avrmcu::TimerPwmMode::phase_correct, 8>>("Timer2");

    //analogWrite(5, 128);
    //analogWrite(6, 128);

    //analogWrite(9, 128);
    //analogWrite(10, 128);
    // AvrTimer::PwmFrequencyAccurate::setupTimer();
    //auto top_count = AvrTimer::PwmFrequencyAccurate::setFrequency(frequency);

    AvrTimer::FaConfig::setup();
    auto top_count = AvrTimer::FaConfig::setFrequency(frequency);

    SerialA::println("top_count: ", top_count);
    
    analogWrite(3, 128);
    analogWrite(11, 128);
    AvrTimer8::BuiltInTopConf::setupTimer();
  }

  using TestTimer = AvrTimer;
  //using TestTimerConf = TestTimer::BuiltInTopConf;

  //using TestTimer = AvrTimer8;
  using TestTimerConf = TestTimer::FaConfig;
  using TestTimerConf2 = TestTimer::PwmFrequencyAccurate;

  void printRegs() {
    using TimerDef = TestTimer::TimerDef;
    using WGM = TimerDef::BitsWGM_16;
    using CS = TimerDef::BitsCS;
    using Registers = TimerDef::Registers;
    using ComA = TimerDef::OcrType<avrmcu::OcrEnum::OcrA>::COM;
    using ComB = TimerDef::OcrType<avrmcu::OcrEnum::OcrB>::COM;
    using OcrA = TimerDef::OcrType<avrmcu::OcrEnum::OcrA>::OCR;
    using OcrB = TimerDef::OcrType<avrmcu::OcrEnum::OcrB>::OCR;

    WGM wgm;
    CS cs;
    ComA comA;
    ComB comB;
    OcrA ocrA;
    OcrB ocrB;

    using OcrEnum = ardo::sys::avr::mcu::OcrEnum;

    Registers::Read(wgm, cs, comA, comB, ocrA, ocrB);

    // Registers::Read(wgm, cs);
    // Registers::Read(comA, comB);

    SerialA::println("wgm: ", (int) wgm.value, ardo::ModType<BIN>{}, 
                     " cs: ", (int) cs.value, ardo::ModType<BIN>{},
                     " comA: ", (int)comA.value, ardo::ModType<BIN>{},
                     " comA: ", (int)comB.value, ardo::ModType<BIN>{},
                     " ocrA: ", (int)ocrA.value,
                     " ocrB: ", (int)ocrB.value);


    auto modeA = AvrTimer::FaConfig::PwmPinByOcrReg<OcrEnum::OcrA>::COM_MODE;
    auto modeB = AvrTimer::FaConfig::PwmPinByOcrReg<OcrEnum::OcrB>::COM_MODE;


    SerialA::println(" modeA: ", (int)modeA, ardo::ModType<BIN>{},
      " modeB: ", (int)modeB, ardo::ModType<BIN>{});
  }

  inline void instanceLoop() {

#if !AS_TEST
    if (timeSequence.poll()) {
      switch (timeSequence.state() & 1) {
        
        case 0: {
#endif
            SerialA::print("Start ");
            printRegs();
            frequency *= 1.5;
            //SerialA::println("now: ", ardo::CoreIF::nowMillis().get());
            auto top_count = TestTimerConf::setFrequency(frequency);
            if (top_count < 12) {
              frequency = 0.5;
              top_count = TestTimerConf::setFrequency(frequency);
              AvrTimer::FaConfig::PwmPinByArgN<0>::pwmWrite(top_count / 2, top_count);
              AvrTimer::FaConfig::PwmPinByArgN<1>::pwmWrite(top_count / 3, top_count);
            }
            auto actual_freq = TestTimerConf::getFrequency<float>();
            auto actual_top_count = TestTimer::getTopCount();

            //AvrTimer::FaConfig::PwmPinByArgN<0>::pwmWrite(top_count / 2, top_count);
            //AvrTimer::FaConfig::PwmPinByArgN<1>::pwmWrite(top_count / 2, top_count);

            SerialA::println("requested freq:", frequency,
                             " top_count: ", top_count, 
                             " actual_freq: ", actual_freq,
                             " actual_top_count: ", actual_top_count);
            
            SerialA::print("Finished ");
            printRegs();

#if !AS_TEST
            break;
        }
      }
    }
#endif
  }
  
  float frequency = 81.0;
  ardo::CyclicTimeSequencePoller<Seq> timeSequence;  // State variable.
};


using FixedFreqencyExampleA = FixedFreqencyExample<0, 1000000>;

// Define the main application with 2 blinker modules.
using mainApp = ardo::Application<FixedFreqencyExampleA, SerialM>;

// Provides the Arduino setup and loop functions. Nothing else should go
// into these functions. If there is a need to call a third party library
// just create a module class and add it to the Application or make a 
// dependent module.
void setup() {
  mainApp::runSetup();
}

void loop() {
  mainApp::runLoop();
}

/*
Timer0 vvvvvvvvvvvvvvvvvvvvvvvv
wgm: 11 cs: 11 comA: 0 comA: 0 ocrA: 0 ocrB: 0
Frequency: 980.39
top count: 255
Timer0 ^^^^^^^^^^^^^^^^^^^^^^
Timer1 vvvvvvvvvvvvvvvvvvvvvvvv
wgm: 1 cs: 11 comA: 0 comA: 0 ocrA: 0 ocrB: 0
Frequency: 490.20
top count: 255
Timer1 ^^^^^^^^^^^^^^^^^^^^^^
Timer2 vvvvvvvvvvvvvvvvvvvvvvvv
wgm: 1 cs: 100 comA: 0 comA: 0 ocrA: 0 ocrB: 0
Frequency: 490.20
top count: 255
Timer2 ^^^^^^^^^^^^^^^^^^^^^^
top_count: 24691
*/

#if AS_TEST
class TestAvr : setl_test::SetlTest {

  bool run() override {
    std::cout << "AVR Timers test...\n";

    setup();

    for (auto i = 0; i < 400; ++i) {
      loop();
    }

    return true;
  }

} TestAvrInstance;

}
#endif