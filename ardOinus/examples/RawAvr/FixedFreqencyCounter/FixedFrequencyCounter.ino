

#include "ardOinus.h"
#include "setlx_type_traits.h"
#include "setlx_cstdint.h"
#include "ardo_time_poller.h"  // A time poller class.
#include "ardo_timers.h"  // Hardware timers.


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
using Seq = ardo::Sequence<500, 500>;

template <int timer, std::uint32_t freq>
class FixedFreqencyExample : 
    public ardo::ModuleInstanceBase<
    FixedFreqencyExample<timer, freq>,
    ardo::Parameters<>>
{   
public:
  using AvrTimer = avrmcu::Timer1;
  using AvrTimer8 = avrmcu::Timer2;

  inline void instanceSetup() {
    
    analogWrite(5, 128);
    analogWrite(6, 128);

    analogWrite(9, 128);
    analogWrite(10, 128);
    // AvrTimer::PwmFrequencyAccurate::setupTimer();
    auto top_count = AvrTimer::PwmFrequencyAccurate::setFrequency(frequency);
    SerialA::println("top_count: ", top_count);
    
    analogWrite(3, 128);
    analogWrite(11, 128);
    AvrTimer8::BuiltInTopConf::setupTimer();
  }

  using TestTimer = AvrTimer;

  void printRegs() {
    using TimerDef = TestTimer::TimerDef;
    using WGM = TimerDef::BitsWGM_16;
    using CS = TimerDef::BitsCS;
    using Registers = TimerDef::Registers;

    WGM wgm;
    CS cs;
    
    Registers::Read(wgm, cs);

    SerialA::println("wgm: ", (int) wgm.value, ardo::ModType<BIN>{}, 
                     " cs: ", (int) cs.value, ardo::ModType<BIN>{});

  }

  inline void instanceLoop() {

    if (timeSequence.poll()) {
      switch (timeSequence.state() & 1) {
        
        case 0: {
            SerialA::print("Start ");
            printRegs();
            frequency += 1000;
            //SerialA::println("now: ", ardo::CoreIF::nowMillis().get());
            auto top_count = TestTimer::PwmFrequencyAccurate::setFrequency(frequency);
            if (top_count < 12) {
              frequency = 7000;
              top_count = AvrTimer::PwmFrequencyAccurate::setFrequency(frequency);
            }
            SerialA::println("xx = ", (int) (avrmcu::Timer1::xx()));
            auto actual_freq = TestTimer::PwmFrequencyAccurate::getFrequency<float>();
            auto actual_top_count = TestTimer::getTopCount();
            SerialA::println("requested freq:", frequency,
                             " top_count: ", top_count, 
                             " actual_freq: ", actual_freq,
                             " actual_top_count: ", actual_top_count);
            
            SerialA::print("Finished ");
            printRegs();
            break;
        }
      }
      
    }
  }
  
  std::uint32_t frequency = 7000;
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
