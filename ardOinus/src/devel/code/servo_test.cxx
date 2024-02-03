// See the LED's lab for instructions on installing ardOinus on the last 3 slides.
// https://docs.google.com/presentation/d/1Zu5ESF0ldCMxa6P-oUoWVaH5-HQhfSc1SEMyQjI8T94/edit#slide=id.p
//

#include "ardOinus.h"

#include "setl_time.h"

#include "ArdoQuadEncoder.h"

// Define the QuadEncoder to use.
using QEncoder = quad::QuadEncoder<
  ardo::DebounceInput<ardo::InputPin<7>>,  // Use Pin 7 and pin 8 and debounce the input.
  ardo::DebounceInput<ardo::InputPin<8>>>;

// Make an ardo::Module from the encoder.
using QModule = quad::QuadEncoderModule<QEncoder>;

// Use the arduino Serial port.
using SerialA = ardo::SerialIO<115200>;
using SerialModule = ardo::ModuleBase<ardo::Parameters<SerialA>>;

// Resetter.
using RotaryEncoderPushButton = ardo::DebounceInput<ardo::InputPin<10>>;

template <typename w_InPin>
class ButtonEventDecoderModule : public ardo::ModuleBase <ardo::Parameters<w_InPin>> {
public:
  using InPin = w_InPin;
  static ButtonEventDecoderModule instance;

  enum InProcessingState {
    Off,
    OnWaitForDelay,
    OnWaitForRelease
  };

  enum OutEventType {
    None,
    Click,
    LongClick
  };

  using TimeType = setl::Time<unsigned long, setl::TimeUnit::MILLIS>;
  using PeriodType = typename TimeType::period_type;

  static void runLoop() {
    instance.instanceLoop();
  }

  void instanceLoop() {
    bool pinState = InPin::get();
    switch (inState) {
      case Off: {
        if (!pinState) {
          inState = OnWaitForDelay;
          last_pressed_time = ardo::CoreIF::now();
          SerialA::println("Pressed");
        }
        break;
      }

      case OnWaitForDelay: {
        if (pinState) {
          outEvent = Click;
          inState = Off;
          SerialA::println("Click");
          break;
        }

        TimeType now_pressed_time = ardo::CoreIF::now();
        if (now_pressed_time - last_pressed_time >= LONG_PRESS_TIME) {
          // This is a long press.
          outEvent = LongClick;
          inState = OnWaitForRelease;
          SerialA::println("LongClick");
        }
        break;
      }

      case OnWaitForRelease: {
        if (pinState) {
          inState = Off;
          break;
        }
        break;
      }
    }
  }


  static OutEventType get() {
    return instance.instanceGet();
  }

  OutEventType instanceGet() {
    OutEventType result = outEvent;
    outEvent = None;
    return result;
  }

  InProcessingState inState = Off;
  OutEventType outEvent = None;

  const PeriodType LONG_PRESS_TIME = PeriodType(300);
  TimeType last_pressed_time;
};

template <typename w_InPin>
ButtonEventDecoderModule<w_InPin> ButtonEventDecoderModule<w_InPin>::instance;

/**
 * Handles an Esc output signal on the given output pin.
 */
template <
  typename w_OutPin,
  typename w_DialInputModule,
  typename w_ResetButton>
class EscHandlerModule : public ardo::ModuleBase<
    ardo::Parameters<w_OutPin>, 
    ardo::DependentModules<w_DialInputModule, w_ResetButton>> {
  public:
    using OutPin = w_OutPin;
    using DialInputModule = w_DialInputModule;
    using ResetButton = w_ResetButton;

    using TimeType = setl::Time<unsigned long, setl::TimeUnit::MICROS>;
    using PeriodType = typename TimeType::period_type;

    static constexpr long MIN_MICROS = 1050;
    static constexpr long MAX_MICROS = 1950;
    static constexpr long OFF_MICROS = 1500;
    static constexpr long CYCLE_FREQ = 60;

    static EscHandlerModule instance;

    static void runLoop() {
      instance.instanceLoop();
    }

    void instanceLoop() {
      TimeType now = ardo::CoreIF::now();
      auto elapsedTime = now - lastCycleTime;

      if (elapsedTime >= signalCycle) {
        lastCycleTime = now;
        elapsedTime = PeriodType{ 0 };
      }

      if (elapsedTime < signalPeriod) {
        OutPin::set(true);
      } else {
        OutPin::set(false);
        readSpeed();

        if (ResetButton::get() != ResetButton::Off) {
          signalPeriod = offPeriod;
          DialInputModule::quadEncoder.setCurrentPosition(0);
          SerialA::println("signalPeriod set to ", signalPeriod.get());
        }
      }

    }

    void readSpeed() {
      long currPos = DialInputModule::quadEncoder.getCurrentPosition();
      if (currPos != lastPos) {
        if (lastPos > encoderFullScale) {
          DialInputModule::quadEncoder.setCurrentPosition(encoderFullScale);
          SerialA::println("limit reached ", encoderFullScale);
          lastPos = encoderFullScale;
        } else if (lastPos < -encoderFullScale) {
          DialInputModule::quadEncoder.setCurrentPosition(-encoderFullScale);
          SerialA::println("limit reached ", -encoderFullScale);
          lastPos = -encoderFullScale;
        }
        lastPos = currPos;
        long newPeriod = OFF_MICROS + (MAX_MICROS - OFF_MICROS) * lastPos / encoderFullScale;
        signalPeriod = PeriodType(newPeriod);
        SerialA::println("lastPos = ", currPos, ", signalPeriod = ", signalPeriod.get());
      }
    }

    const PeriodType minPeriod = PeriodType{ MIN_MICROS };
    const PeriodType maxPeriod = PeriodType{ MAX_MICROS };
    const PeriodType offPeriod = PeriodType{ OFF_MICROS };
    const PeriodType signalCycle = PeriodType(setl::ConvertTime<
        setl::TimeUnit::SECOND, setl::TimeUnit::MICROS>::convert(1ul) / CYCLE_FREQ);
    const long encoderFullScale = 80;

    TimeType lastCycleTime;
    PeriodType signalPeriod = offPeriod;
    long lastPos{};
};

template <
  typename w_OutPin,
  typename w_DialInputModule,
  typename w_ResetButton>
  EscHandlerModule<w_OutPin, w_DialInputModule, w_ResetButton> 
    EscHandlerModule<w_OutPin, w_DialInputModule, w_ResetButton>::instance;

using ResetButton = ButtonEventDecoderModule<RotaryEncoderPushButton>;

using EscModule = EscHandlerModule<
  ardo::OutputPin<9>,
  QModule,
  ResetButton>;

// Put all the modules into the "Application".
using App = ardo::Application<EscModule, SerialModule>;

void setup() {
  App::runSetup();
}

void loop() {
  App::runLoop();
}

