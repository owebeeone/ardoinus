


#if !defined(ARDO_STEPPER___A)
#define ARDO_STEPPER___A

#include "ardoino.h"
#include "setl_cyclic_int.h"

namespace step {

/** The time types used. */
using TimeType = ardo::CoreIF::MillisTime;
using PeriodType = TimeType::period_type;

/**
 * Provides access to the specified pins.
 */
template <typename... pins>
class PinSpecifier;

template <>
class PinSpecifier<> {
public:
  static const unsigned COUNT = 0;

  inline static void set(unsigned levelsMask) {}
  inline static void setLow() {}
};

template <typename pin, typename... pins>
class PinSpecifier<pin, pins...> {
public:
  using NextClass = PinSpecifier<pins...>;
  static constexpr unsigned COUNT = 1 + NextClass::COUNT;

  inline static void set(unsigned levelsMask) {
    pin::set(levelsMask & (1 << (COUNT - 1)) ? true : false);
    NextClass::set(levelsMask);
  }

  inline static void setLow() {
    pin::set(false);
    NextClass::setLow();
  }

};

template <typename... pins>
class Sequencer {
public:
  using Specifier = PinSpecifier<pins...>;
  static const unsigned COUNT_PIN = Specifier::COUNT;

  template <unsigned N>
  Sequencer(const unsigned char(&sequence)[N])
    : size(N), sequence(sequence)
  {}

  void set(unsigned row) {
    Specifier::set(sequence[row]);
  }

  void setLow() {
    Specifier::setLow();
  }

private:
  const unsigned size;
  const unsigned char * const sequence;
};

/**
  * Maintains state for the current position and wait times and determines the next events.
  */
class StepperStateMachine {
public:
  /**
    * ScalingType scales the periods making movement slower.
    */
  using ScalingType = float;

  enum class Action : int
  {
    NoAction = 0,  /// No Action required.
    SequenceForward = 1,  /// Step forward.
    SequenceBack = -1,  /// Step backward.
    TurnOffCoils = 2   /// Turn off coils.
  };

  /**
    * stepPeriodUnits - period between stepper motor steps.
    * coilOnPeriodUnits - -1 indicates keep coils on, otherwise,
    *  period to keep coils on after last step.
    */
  StepperStateMachine(
    const PeriodType& minStepPeriodUnits, const PeriodType& coilOnPeriodUnits)
    : minStepPeriodUnits(minStepPeriodUnits), coilOnPeriodUnits(coilOnPeriodUnits)
  {}

  /** Determine the next action to take. */
  Action nextAction() {
    bool timedCoils = coilOnPeriodUnits > PeriodType(0);

    auto nowUnits = currentTime();
    auto elapsed = nowUnits - timeOfLastChange;

    // Check to see if coils need switching off.
    if (coilsOn && timedCoils) {
      if (elapsed > coilOnPeriodUnits) {
        coilsOn = false;
        return Action::TurnOffCoils;
      }
    }

    if (remainingSteps == 0) {
      return Action::NoAction;
    }

    const auto stepPeriodUnits = getStepPeriod();
    if (elapsed > stepPeriodUnits) {
      Action result = remainingSteps > 0 ? Action::SequenceForward : Action::SequenceBack;
      timeOfLastChange = nowUnits;
      remainingSteps -= static_cast<long>(result);
      currentPosition += static_cast<long>(result);
      coilsOn = true;
      return result;
    }
    // Not enough time passed.
    return Action::NoAction;
  }

  /**
    * Returns the number of remaining steps.
    */
  long getRemainingSteps() {
    return remainingSteps;
  }

  /**
    * Returns the target position.
    */
  long getTargetPosition() {
    return remainingSteps + currentPosition;
  }

  /**
    * Returns the current position.
    */
  long getCurrentPosition() {
    return currentPosition;
  }

  /**
    * Sets the new target position.
    */
  void setTargetPosition(long position) {
    remainingSteps = position - currentPosition;
  }

  /**
    * Sets the new target by moving incrementally.
    */
  void incrementPosition(long increment) {
    remainingSteps += increment;
  }

  /**
    * Sets the scale of wait periods (inverse of speed). Must not be less than 1.
    */
  void setTimeScale(const ScalingType& scale) {
    this->scale = scale;
  }

  /**
    * Returns the time scale.
    */
  ScalingType getTimeScale() {
    return scale;
  }

  /**
    * Returns the time to elapse before the next action needs to be taken.
    * 0 means there is an action now, ~0 indicates no future action is currently scheduled.
    */
  PeriodType nextActionPeriodUnits() {
    if (remainingSteps == 0 && !coilsOn) {
      // Not enough time passed.
      return PeriodType(~PeriodType::type(0));
    }
    auto nowUnits = currentTime();

    // Check to see if coils need switching off.
    if (coilsOn && coilOnPeriodUnits > PeriodType(0)) {
      if (nowUnits - timeOfLastChange > coilOnPeriodUnits) {
        return PeriodType(0);
      }
    }

    const auto stepPeriodUnits = getStepPeriod();
    if (nowUnits - timeOfLastChange > stepPeriodUnits) {
      return PeriodType(0);
    }

    auto stepTime = timeOfLastChange + stepPeriodUnits - nowUnits;
    if (coilsOn) {
      auto coilTime = timeOfLastChange + coilOnPeriodUnits - nowUnits;
      return stepTime < coilTime ? stepTime : coilTime;
    }
    return stepTime;
  }

  step::PeriodType getStepPeriod() {
    auto result = scale * minStepPeriodUnits;
    return result;
  }

  static ardo::CoreIF::MillisTime currentTime() {
    return ardo::CoreIF::now();
  }

private:
  ScalingType scale = ScalingType(1U);
  TimeType timeOfLastChange = currentTime();
  long remainingSteps = 0;
  long currentPosition = 0;
  bool coilsOn = false;
  const PeriodType minStepPeriodUnits;
  const PeriodType coilOnPeriodUnits;
};

/**
 * The stepper interface. It is primarity driven through this base class.
 */
class StepperBase {
public:
  using ScalingType = StepperStateMachine::ScalingType;

  StepperBase(unsigned sequenceCount,
    unsigned phases,
    const PeriodType& minStepPeriodUnits,
    const PeriodType& coilOnPeriodUnits)
    : sequenceCount(sequenceCount),
      phases(phases),
      stateMachine(minStepPeriodUnits, coilOnPeriodUnits)
  {}

  virtual ~StepperBase() = default;

  /**
   * Call this method when an action needs to be taken. Polling will also work.
   */
  virtual void iterate() {
    StepperStateMachine::Action action = stateMachine.nextAction();
    switch (action) {
      case StepperStateMachine::Action::NoAction: { break; }
      case StepperStateMachine::Action::SequenceBack: {
        if (currentStepperRow <= 0) {
          currentStepperRow = sequenceCount - 1;
        } else {
          --currentStepperRow;
        }
        setCurrentStep();
        break;
      }
      case StepperStateMachine::Action::SequenceForward: {
        ++currentStepperRow;
        if (currentStepperRow >= sequenceCount) {
          currentStepperRow = 0;
        }
        setCurrentStep();
        break;
      }
      case StepperStateMachine::Action::TurnOffCoils: {
        setLow();
        break;
      }
    }
  }

  /**
  * Returns the number of remaining steps.
  */
  virtual long getRemainingSteps() {
    return stateMachine.getRemainingSteps();
  }

  /**
  * Returns the target position.
  */
  virtual long getTargetPosition() {
    return stateMachine.getTargetPosition();
  }

  /**
  * Returns the current position.
  */
  virtual long getCurrentPosition() {
    return stateMachine.getCurrentPosition();
  }

  /**
  * Sets the new target position.
  */
  virtual void setTargetPosition(long position) {
    stateMachine.setTargetPosition(position);
  }

  /**
  * Sets the new target by moving incrementally.
  */
  virtual void incrementPosition(long increment) {
    stateMachine.incrementPosition(increment);
  }

  /**
  * Sets the scale of wait periods (inverse of speed). Must not be less than 1.
  */
  void setTimeScale(const ScalingType& scale) {
    stateMachine.setTimeScale(scale);
  }

  /**
  * Returns the time scale.
  */
  ScalingType getTimeScale() {
    return stateMachine.getTimeScale();
  }

protected:

  virtual void set(unsigned row) = 0;
  virtual void setLow() = 0;

  void setCurrentStep() {
    set(currentStepperRow);
  }

  unsigned currentStepperRow = 0;
  const unsigned sequenceCount;
  const unsigned phases;
  StepperStateMachine stateMachine;
};

template <unsigned... phaseCount>
class Sequences;

template <>
class Sequences<5> {
public:
  inline static auto basicSequence() -> const unsigned char(&)[10]{
    static const unsigned char sequence[] =
  {
    0b11010,
    0b10010,
    0b10110,
    0b10100,
    0b10101,
    0b00101,
    0b01101,
    0b01001,
    0b01011,
    0b01010,
  };

  return sequence;
  }
};

template <>
class Sequences<4> {
public:
  inline static auto basicSequence() -> const unsigned char(&)[4]{
    static const unsigned char sequence[] = { 0b1100, 0b0110, 0b0011, 0b1001 };
  return sequence;
  }

    inline static auto alternateSequence() -> const unsigned char(&)[8]{
    static const unsigned char sequence[] =
  { 0b1100, 0b0100, 0b0110, 0b0001, 0b0011, 0b0001, 0b1001, 0b1000 };
  return sequence;
  }
};

template <>
class Sequences<3> {
public:
  inline static auto basicSequence() -> const unsigned char(&)[6]{
    static const unsigned char sequence[] = { 0b100, 0b110, 0b010, 0b011, 0b001, 0b101 };
  return sequence;
  }

    inline static auto alternateSequence() -> const unsigned char(&)[3]{
    static const unsigned char sequence[] = { 0b100, 0b010, 0b001 };
  return sequence;
  }
};

template <>
class Sequences<2> {
public:
  inline static auto basicSequence() -> const unsigned char(&)[4]{
    static const unsigned char sequence[] = { 0b01, 0b11, 0b10, 0b00 };
  return sequence;
  }

};

template <unsigned N, typename T>
static constexpr unsigned lengthOf(T(&p)[N]) {
  return N;
}

/**
 * A stepper motor controlling class.
 */
template <typename... pins>
class Stepper : public StepperBase {
public:
  using SequencerType = Sequencer<pins...>;
  using DefaultSequence = Sequences<SequencerType::COUNT_PIN>;

  static_assert(
    SequencerType::COUNT_PIN <= 8 * sizeof(unsigned char),
    "Bit mask can't handle number of pins");

  Stepper(
    const PeriodType& stepPeriod,
    const PeriodType& coilOnPeriod)
    : StepperBase(lengthOf(DefaultSequence::basicSequence()),
      SequencerType::COUNT_PIN,
      stepPeriod,
      coilOnPeriod),
      sequencer(DefaultSequence::basicSequence())
  {}

  template <unsigned N>
  Stepper(long stepPeriodMillis,
    long coilOnPeriodUnits,
    const unsigned char(&sequence)[N])
    : StepperBase(N, SequencerType::COUNT_PIN, stepPeriodMillis, coilOnPeriodUnits),
      sequencer(sequence)
  {}

protected:
  virtual void set(unsigned row) {
    sequencer.set(row);
  }

  virtual void setLow() {
    sequencer.setLow();
  }

private:
  SequencerType sequencer;
};

template <
  PeriodType::type stepPeriod,
  PeriodType::type coilOnPeriod, 
  setl::TimeUnit timeUnits,
  typename... pins>
class StepperModule : public ardo::ModuleBase<ardo::Parameters<pins...>> {
public:
  static void runLoop() {
    instance.instanceLoop();
  }

  void instanceLoop() {
    stepper.iterate();
  }

  static StepperModule instance;

  Stepper<pins...> stepper{
    setl::Period<PeriodType::type, timeUnits>(stepPeriod).to(),
    setl::Period<PeriodType::type, timeUnits>(coilOnPeriod).to()};
};

template < 
  PeriodType::type stepPeriod,
  PeriodType::type coilOnPeriod,
  setl::TimeUnit timeUnits, 
  typename... pins>
StepperModule<stepPeriod, coilOnPeriod, timeUnits, pins...> 
    StepperModule<stepPeriod, coilOnPeriod, timeUnits, pins...>::instance;

} // namespace step

#endif // ARDO_STEPPER___A

