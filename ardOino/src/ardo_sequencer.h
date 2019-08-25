
/**
* Time polling function.
*/
#ifndef ARDO_SEQUENCER__H
#define ARDO_SEQUENCER__H

#include "ardoino.h"
#include "setl_cyclic_int.h"

namespace ardo {

/**
 * Provide basic time period based polling.
 *
 * @param w_StateType Incremented when a period expires.
 * @param w_TimeType A CoreIF time type. A modulo number is suggested.
 */
template <typename w_StateType, typename w_TimeType = ardo::CoreIF::MillisTime>
class TimePoller {
public:
  using StateType = w_StateType;
  using TimeType = w_TimeType;

  /** Sets the start time with now() time. */
  void setNow() {
    setFrom(ardo::CoreIF::now());
  }

  /** Sets the start time with the given time. */
  void setFrom(const TimeType& from) {
    this->from = from;
  }

  /** Polls to see if the given period passed since from.
   * NOTE: This implementation assumes that the period of time between the from
   * time and the given period is smaller than half of the timer resolution.
   * This is intended to be called in a tight loop only a relatively small
   * period between successive calls to poll.
   * Returns true when period has expired and increments the state.
   */
  bool poll(const typename TimeType::period_type& period) {
    TimeType to = ardo::CoreIF::now();

    auto passed = to - from;

    if (passed > period) {
      from += period;
      ++state;
      return true;
    }
    return false;
  }

  const StateType& getState() const {
    return state;
  }

private:
  StateType state = {};
  TimeType from = ardo::CoreIF::now();
};

/**
 * Provides a sequencing periods for a specific set of times.
 */
template <ardo::CoreIF::MillisTime::type... Seq>
class Sequence;

template <ardo::CoreIF::MillisTime::type SN, ardo::CoreIF::MillisTime::type... R>
class Sequence<SN, R...> {
public:
  using type = ardo::CoreIF::MillisTime::type;
  static const unsigned count = 1 + Sequence<R...>::count;

  inline static type get(unsigned index) {
    if (index == 0) {
      return SN;
    }
    return Sequence<R...>::get(index - 1);
  }
};

template <ardo::CoreIF::MillisTime::type L>
class Sequence<L> {
public:
  using type = ardo::CoreIF::MillisTime::type;
  static const unsigned count = 1;

  inline static type get(unsigned) {
    return L;
  }
};

/**
 * Provides a poller that will sequence throgh the given periods.
 */
template <typename w_Seq, typename w_TimeType = ardo::CoreIF::MillisTime>
class TimeSequencePoller {
public:
  using Sequence = w_Seq;
  using TimeType = w_TimeType;

  void init() {
    poller.setNow();
  }

  bool poll() {
    return poller.poll(sequence.get(state()));
  }

  unsigned state() {
    return poller.getState().get();
  }
  
  Sequence sequence;
  TimePoller<setl::CyclicInt<Sequence::count>, TimeType> poller;
};

}  // namespace

#endif