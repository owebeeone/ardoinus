
#if !defined(ArdoQuadEncoder___h)
#define ArdoQuadEncoder___h

#include "ardoino.h"

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
    currentPosition += change;
    return change;
  }

  long getCurrentPosition() {
    return currentPosition;
  }

  virtual State getInput() = 0;

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
 * The quadrature encoder class. This uses ardo::InputPin Creates 2 bits from 
 * two given pins.
 */
template <typename w_PinA, typename w_PinB, typename Base = QuadEncoderBase>
class QuadEncoder : public Base {
public:
  using PinA = w_PinA;
  using PinB = w_PinB;
  using State = typename Base::State;

  /**
   * Return the input values as the first 2 bits in the return value.
   */
  virtual State getInput() {
    return (PinA::get() ? State(0u) : State(1u)) | (PinB::get() ? State(0u) : State(2u));
  }
};

template <typename w_QuadEncoderType>
class QuadEncoderModule : public ardo::ModuleBase<
    ardo::Parameters<typename w_QuadEncoderType::PinA, typename w_QuadEncoderType::PinB>> {
public:
  using QuadEncoderType = w_QuadEncoderType;

  static void loop() {
    quadEncoder::iterate();
  }

  static QuadEncoderType quadEncoder;
};

template <typename w_QuadEncoderType>
typename QuadEncoderModule<w_QuadEncoderType>::QuadEncoderType 
  QuadEncoderModule<w_QuadEncoderType>::quadEncoder;

} // namespace quad

#endif