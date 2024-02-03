
#if !defined(ArdoQuadEncoder___h)
#define ArdoQuadEncoder___h

#include "ardOinus.h"

#include "setl_time.h"
#include "setl_interactive_scaling.h"

namespace quad {

/**
 * Decodes a quadrature encoder and returns an absolute position.
 */
class QuadEncoderBase {
public:
  using State = unsigned char;

  /**
   * Iterate and return the delta position change.
   */
  long iterate() {
    long change = determineChange();
    currentPosition += scaleValue(change);
    return change;
  }

  long getCurrentPosition() {
    return currentPosition;
  }

  void setCurrentPosition(long position) {
    currentPosition = position;
  }

  virtual State getInput() = 0;

  virtual long scaleValue(long change) {
    return change;
  }

protected:

  long determineChange() {
    // Initialize to the initial values.
    if (lastState == NO_STATE) {
      lastState = getInput();
      return 0;
    }

    State input = getInput();
    if (input == lastState) {
      return 0;
    }

    State index = input | (lastState << 2);
    lastState = input;

    switch (actionTable()[index]) {
      case Action::increment: {
        lastDirection = 1;
        return lastDirection;
      }
      case Action::decrement: {
        lastDirection = -1;
        return lastDirection;
      }
      case Action::unchanged: {
        lastDirection = 0;
        return lastDirection;
      }
      case Action::indeterminate: {
        if (lastDirection) {
          return 2l * lastDirection;
        }
        break;
      }
    }

    return 0;
  }

  enum class Action : unsigned char {
    increment,
    decrement,
    unchanged,
    indeterminate
  };

  static constexpr State inputOf(State index) {
    return index & 0b11;
  }

  static constexpr State lastOf(State index) {
    return (index >> 2) & 0b11;
  }

  static constexpr State swapBits(State bits) {
    return ((bits << 1) & 2) | ((bits >> 1) & 1);
  }

  static constexpr Action decodeAction(State index) {
    return inputOf(index) == lastOf(index) ? Action::unchanged
      : (inputOf(index) ^ lastOf(index)) == 0b11 ? Action::indeterminate
      : (swapBits(inputOf(index)) ^ lastOf(index)) == 0b10 ? Action::increment
      : Action::decrement;
  }

  // The encoder truth table.
  inline static const Action (&actionTable())[16] {
    static const Action table[] = {
      decodeAction(0),
      decodeAction(1),
      decodeAction(2),
      decodeAction(3),
      decodeAction(4),
      decodeAction(5),
      decodeAction(6),
      decodeAction(7),
      decodeAction(8),
      decodeAction(9),
      decodeAction(10),
      decodeAction(11),
      decodeAction(12),
      decodeAction(13),
      decodeAction(14),
      decodeAction(15),
    };

    return table;
  }

  static constexpr State NO_STATE = ~static_cast<State>(0U);
  State lastState = NO_STATE;
  signed char lastDirection = 0;
  long currentPosition = 0;
};

/**
 * The scaler you have when you don't want a scaler.
 */
class NUllScaler {
public:
  template <typename T>
  static T scale(const T& value) {
    return value;
  }
};

/**
 * A scaler for interactivity.
 */
using NonlinerarScaler = setl::RelativeInteractiveScaler<
    long, float, ardo::CoreIF::MicrosTime>;

class InteractiveScaler : public NonlinerarScaler {
public:

  InteractiveScaler()
    : NonlinerarScaler{ 1.0f, setl::Period<float>(100), setl::Period<float>(500) }
  {}

  long scale(long value) {
    return scaleForNow(value, ardo::CoreIF::now());
  }
};

/**
 * The quadrature encoder class. This uses ardo::InputPin Creates 2 bits from 
 * two given pins.
 */
template <
  typename w_PinA, 
  typename w_PinB, 
  typename ScalerType = NUllScaler,
  typename Base = QuadEncoderBase>
class QuadEncoder : public Base {
public:
  using PinA = w_PinA;
  using PinB = w_PinB;
  using State = typename Base::State;

  /**
   * Return the input values as the first 2 bits in the return value.
   */
  State getInput() override {
    return (PinA::get() ? State(0u) : State(1u)) | (PinB::get() ? State(0u) : State(2u));
  }


  long scaleValue(long change) override {
    return scaler.scale(change);
  }

  ScalerType scaler;
};


template <typename w_QuadEncoderType>
class QuadEncoderModule : public ardo::ModuleBase<
    ardo::Parameters<typename w_QuadEncoderType::PinA, typename w_QuadEncoderType::PinB>> {
public:
  using QuadEncoderType = w_QuadEncoderType;

  static void runLoop() {
    quadEncoder.iterate();
  }

  static QuadEncoderType quadEncoder;
};

template <typename w_QuadEncoderType>
typename QuadEncoderModule<w_QuadEncoderType>::QuadEncoderType 
  QuadEncoderModule<w_QuadEncoderType>::quadEncoder;

} // namespace quad

#endif