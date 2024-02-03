/**
* Time polling function.
*/
#ifndef ARDO_BUTTON_EVENT__H
#define ARDO_BUTTON_EVENT__H

#include "ardOinus.h"

namespace ardo {

/**
 * Converts GPIO input from a button to events, Click, DoubleClick and LongClick
 * events.
 */
template <typename w_InPin>
class ButtonEventModule : public ardo::ModuleBase <ardo::Parameters<w_InPin>> {
 protected:
  using InPin = w_InPin;
  static ButtonEventModule instance;

  using TimeType = setl::Time<unsigned long, setl::TimeUnit::MILLIS>;
  using PeriodType = typename TimeType::period_type;

  const PeriodType LONG_PRESS_TIME = PeriodType(300);
  const PeriodType DOUBLE_CLICK_TIME = PeriodType(400);

  enum InProcessingState : char {
    Off,
    WaitForDelay,
    WaitForRelease,
    WaitForPossibleDoubleClick
  };
 public:
  enum OutEventType : char {
    None,
    Click,
    DoubleClick,
    LongClick
  };

  static void runLoop() {
    instance.instanceLoop();
  }

  void instanceLoop() {
    bool pinState = InPin::get();
    switch (inState) {
      case Off: {
        if (!pinState) {
          inState = WaitForDelay;
          last_pressed_time = ardo::CoreIF::now();
        }
        break;
      }

      case WaitForDelay: {
        if (pinState) {
          inState = WaitForPossibleDoubleClick;
          last_pressed_time = ardo::CoreIF::now();
          break;
        }

        TimeType now_pressed_time = ardo::CoreIF::now();
        if (now_pressed_time - last_pressed_time >= LONG_PRESS_TIME) {
          // This is a long press.
          outEvent = LongClick;
          inState = WaitForRelease;
        }
        break;
      }

      case WaitForPossibleDoubleClick: {

        if (!pinState) {
          outEvent = DoubleClick;
          inState = WaitForRelease;
          break;
        }

        TimeType now_pressed_time = ardo::CoreIF::now();
        if (now_pressed_time - last_pressed_time >= DOUBLE_CLICK_TIME) {
          // This is a long press.
          outEvent = Click;
          inState = WaitForRelease;
        }
        break;
      }

      case WaitForRelease: {
        if (pinState) {
          inState = Off;
          break;
        }
        break;
      }
    }
  }

  /**
   * Retrieves an event or None if no event is pending.
   */
  static OutEventType get() {
    return instance.instanceGet();
  }

 protected:
  OutEventType instanceGet() {
    OutEventType result = outEvent;
    outEvent = None;
    return result;
  }

  TimeType last_pressed_time;
  InProcessingState inState = Off;
  OutEventType outEvent = None;
};


}

#endif  // ARDO_BUTTON_EVENT__H