/**
 * ArdOino is an embedded application framework allowing composition
 * of re-usable modules targetted for embedded microcontroller applications.
 *
 * ArdOino aims to be true to the C++ philosophy that you don't pay for what
 * you don't need (at run time) and hence makes heavy use of C++ templates.
 * The extensive use of templates results in requiring the minimum version 
 * of C++14 compiler support.
 *
 * The main re-usable component is the "module". The module interface is 
 * described in the ModuleBase class template. It provides 4 static methods and
 * contains no instance state however client modules can instantiate a a module
 * object if the module requires it. Multiple modules are combinable into an
 * Applicatiion. The Application class template will combine the given modules, 
 * this can be considered akin the to "main" function in a C++ program.
 *
 * Resource collision is handled as a compile time error. Each module must 
 * define it's parameters and each parameter defines it's claim on resources.
 * Compile time detection of resource collision is higly desirable since an
 * invalid allocation does not even result in a runnable program and error 
 * messages indicate the error.
 * 
 * This library also abstracts the basic digital GPIO functions in Arduino 
 * together together with the basic time functions.
 *
 * A number of header only template libraries are provided that are suitable
 * for embedded programming, including "cyclic int", circular buffers. test
 * tools, type safe time types and conversions between them.
 */

#ifndef ARDOINO___H
#define ARDOINO___H

#include "setl_time.h"
#include "setl_utils.h"
#include "setl_templ_utils.h"

#include "setlx_cstdint.h"
#include "setlx_type_traits.h"

#if !defined(OUTPUT)  // This is provided by Arduino.h
#define INPUT 0
#define OUTPUT 1
#define INPUT_PULLUP 2
#define LOW 0
#define HIGH 1

void pinMode(unsigned pin, std::uint8_t mode);
void digitalWrite(unsigned pin, std::uint8_t mode);
int digitalRead(unsigned pin);
unsigned millis();
unsigned micros();
#endif

namespace ardo {

/** Resource designator. GPIO pins are exclusive resources. When assigning
 * input and output pins, this template is used to indicate claim of the
 * GPIO pin. If the resource is used by more than one module, the resource
 * is overcomiited and the program will fail to compile. */
template <unsigned P>
class GPIOResource {
public:
  static constexpr unsigned PIN = P;
};

/**
 * Module parameters must contain a "Claim" type which is a ResourceClaim below.
 * Any type may be a parameter to ResourceClaim which allows any library to
 * define a new claim type to manage finite resources. GPIOResource above is
 * not special but it should be used whenever a module makes use of a GPIO pin.
 * Examples of other possible resources would be timers, interrupts, network ports
 * nvram.
 */
// TODO - Currently the claim conflict is simply the existance of the type, however
// handling a range may be more desirable. For example, if multiple modules need
// nvram allocations, it would be preferable if there was a range available so each
// module is able to claim a slice of the address space.
template <typename... R>
class ResourceClaim {
public:
  template <typename Op, typename VL>
  using Scanner = setl::For<Op, VL, R...>;

  template <typename S>
  using has_resource = Scanner<setl::Operator<std::is_same, setl::OrEval>, S>;
};

/**
 * A veneer across some Android functionality.
 */
class CoreIF {
public:
  enum OutputPinMode : std::uint8_t {
    OpenDrainLowOutput = 0xffu,   // Open collector/drain low output. 
    OpenDrainHighOutput = 0xfeu,  // Open collector/drain high output. 
    Output = OUTPUT,              // Output mode.
  };

  enum InputPinMode : std::uint8_t {
    PullUp = INPUT_PULLUP,    // Input tied through pullup resistor.
    Untied = INPUT,           // Floating high impedance input.
  };

  using MillisTime = setl::Time<decltype(millis()), setl::TimeUnit::MILLIS>;
  using MicrosTime = setl::Time<decltype(micros()), setl::TimeUnit::MICROS>;

  inline static void pinMode(unsigned pin, std::uint8_t mode) {
    ::pinMode(pin, mode);
  }

  inline static void digitalWrite(unsigned pin, std::uint8_t mode) {
    ::digitalWrite(pin, mode);
  }

  inline static bool digitalRead(unsigned pin) {
    return ::digitalRead(pin) != LOW;
  }

  inline static MillisTime nowMillis() {
    return MillisTime(millis());
  }

  inline static MicrosTime nowMicros() {
    return MicrosTime(micros());
  }

  // Cast operator conversion to target time.
  struct NowTimeEvaluator {
    template <typename T>
    struct NowTime;

    template <typename T>
    operator T () const {
      return NowTime<T>::get();
    }
  };

  static NowTimeEvaluator now() {
    return NowTimeEvaluator();
  }
};

template <>
struct CoreIF::NowTimeEvaluator::NowTime<CoreIF::MillisTime> {
  static CoreIF::MillisTime get() {
    return CoreIF::nowMillis();
  }
};

template <>
struct CoreIF::NowTimeEvaluator::NowTime<CoreIF::MicrosTime> {
  static CoreIF::MicrosTime get() {
    return CoreIF::nowMicros();
  }
};

/**
 * Runner supports execution of the runSetup() and runLoop() functions across
 * a given set of classes.
 */
template <typename... T>
class Runner;

template <typename S, typename... T>
class Runner<S, T...> {
public:
  inline static void runParamsSetup() {
    S::paramsSetup();
    Runner<T...>::runParamsSetup();
  }

  inline static void runParamsLoop() {
    S::paramsLoop();
    Runner<T...>::runParamsLoop();
  }

  inline static void runSetup() {
    S::runSetup();
    Runner<T...>::runSetup();
  }

  inline static void runLoop() {
    S::runLoop();
    Runner<T...>::runLoop();
  }
};

template <>
class Runner<> {
public:
  inline static void runParamsSetup() {
  }

  inline static void runParamsLoop() {
  }

  inline static void runSetup() {
  }

  inline static void runLoop() {
  }
};

/** A base class for output pins where no base class is needed. */
class NullPinBase {};

/** A base class for output pins where a base class is needed. */
class OutputPinIF {
public:
  virtual ~OutputPinIF() {}
  virtual void setPin(bool) const = 0;
  virtual unsigned pinNo() const = 0;
};

/**
 * A digital output.
 */
template <unsigned P, 
    CoreIF::OutputPinMode M = CoreIF::Output, 
    typename Base = NullPinBase>
class OutputPin : public Base, public setl::not_copyable {
protected:
  OutputPin() {}  // Only the one instance allowed.
public:
  static constexpr unsigned PIN = P;

  // Claim resources.
  using Claims = ResourceClaim<GPIOResource<PIN>>;

  static const OutputPin pin;

  inline static void runSetup() {
    CoreIF::pinMode(PIN, M);
  }

  inline static void runLoop() {}

  static void set(bool level) {
    CoreIF::digitalWrite(PIN, level ? HIGH : LOW);
  }

  // Overrides OutputPinIF base class interface.
  void setPin(bool level) const {
    set(level);
  }

  // May override base class.
  unsigned pinNo() const {
    return PIN;
  }
};

template <unsigned P, CoreIF::OutputPinMode M, typename Base>
const OutputPin<P, M, Base> OutputPin<P, M, Base>::pin;

/**
 * A digital output for open collector/drain pulled low when active.
 */
template <unsigned P, typename Base>
class OutputPin<P, CoreIF::OpenDrainLowOutput, Base> 
    : public Base, public setl::not_copyable {
protected:
  OutputPin() {}  // Only the one instance allowed.
public:
  static constexpr unsigned PIN = P;

  // Claim resources.
  using Claims = ResourceClaim<GPIOResource<PIN>>;

  static const OutputPin pin;

  inline static void runSetup() {
    CoreIF::pinMode(PIN, CoreIF::Untied);
    CoreIF::digitalWrite(PIN, LOW);
  }

  inline static void runLoop() {}

  static void set(bool level) {
    // Switching between input (no pullup mode) and output (drive low) mode
    // emulates an open collector output.
    CoreIF::pinMode(PIN, level ? CoreIF::Untied : CoreIF::Output);
  }

  // Overrides OutputPinIF base class interface.
  void setPin(bool level) const {
    set(level);
  }

  // May override base class.
  unsigned pinNo() const {
    return PIN;
  }
};

/**
* A digital output for open collector/drain pulled high when active.
*/
template <unsigned P, typename Base>
class OutputPin<P, CoreIF::OpenDrainHighOutput, Base>
  : public Base, public setl::not_copyable {
protected:
  OutputPin() {}  // Only the one instance allowed.
public:
  static constexpr unsigned PIN = P;

  // Claim resources.
  using Claims = ResourceClaim<GPIOResource<PIN>>;

  static const OutputPin pin;

  inline static void runSetup() {
    CoreIF::pinMode(PIN, CoreIF::Untied);
    CoreIF::digitalWrite(PIN, HIGH);
  }

  inline static void runLoop() {}

  static void set(bool level) {
    // Switching between input (no pullup mode) and output (drive low) mode
    // emulates an open collector output.
    CoreIF::pinMode(PIN, level ? CoreIF::Output : CoreIF::Untied);
  }

  // Overrides OutputPinIF base class interface.
  void setPin(bool level) const {
    set(level);
  }

  // May override base class.
  unsigned pinNo() const {
    return PIN;
  }
};

template <unsigned P, typename Base>
const OutputPin<P, CoreIF::OpenDrainLowOutput, Base> 
    OutputPin<P, CoreIF::OpenDrainLowOutput, Base>::pin;

/** A base class for input pins where a base class is needed. */
class InputPinIF {
public:
  virtual ~InputPinIF() {}
  virtual bool getPin() const = 0;
  virtual unsigned pinNo() const = 0;
};

/**
 * The basic digital input pin.
 */
template <unsigned P,  // The digital/gpio pin number.
  CoreIF::InputPinMode M = CoreIF::PullUp, 
  typename Base = NullPinBase>
class InputPin : public Base, public setl::not_copyable {
protected:
  InputPin() {}  // Private constructor.
public:
  static constexpr unsigned PIN = P;

  // Claim resources.
  using Claims = ResourceClaim<GPIOResource<PIN>>;

  static const InputPin pin;

  inline static void runSetup() {
    CoreIF::pinMode(PIN, M);
  }

  inline static void runLoop() {}

  static bool get() {
    return CoreIF::digitalRead(PIN) != LOW;
  }

  // May override base class.
  bool getPin() const {
    return get();
  }

  // May override base class.
  unsigned pinNo() const {
    return PIN;
  }
};

template <unsigned P, CoreIF::InputPinMode M, typename Base>
const InputPin<P, M, Base> InputPin<P, M, Base>::pin;

/**
 * Debounced input type.
 */
template <unsigned long debounceTime, typename w_TimeType, typename InputPin>
class DebounceInput : public InputPin {
protected:
  DebounceInput() {}
public:
  using TimeType = w_TimeType;

  static bool get() {
    return debounceState.debounce(InputPin::get());
  }

  // May override base class.
  bool getPin() const {
    return get();
  }

  inline static void runSetup() {
    InputPin::runSetup();
    debounceState.runSetup(); // Initialize the debounce state.
  }

  static const DebounceInput pin;

private:
  // The debounce state 
  struct DebounceState {
    bool debounce(bool input) {
      const bool changedNow = input != currentLevel;
      if (isChanged) {
        if (changedNow) {
          TimeType now = CoreIF::now();
          auto elapsed = now - lastChangeTime;
          if (elapsed.get() > debounceTime) {
            currentLevel = input;
            isChanged = false;
          }
        }
      }
      else if (changedNow) {
        isChanged = true;
        lastChangeTime = CoreIF::now();
      }
      else {
        isChanged = false;
      }

      return currentLevel;
    }

    void runSetup() {
      lastChangeTime = CoreIF::now();
    }

    TimeType lastChangeTime;
    bool currentLevel = false;
    bool isChanged = false;
  };

  static DebounceState debounceState;
};

template <unsigned long debounceTime, typename w_TimeType, typename InputPin>
typename DebounceInput<debounceTime, w_TimeType, InputPin>::DebounceState 
    DebounceInput<debounceTime, w_TimeType, InputPin>::debounceState;

template <unsigned long debounceTime, typename w_TimeType, typename InputPin>
const DebounceInput<debounceTime, w_TimeType, InputPin>
    DebounceInput<debounceTime, w_TimeType, InputPin>::pin;

/**
 * Fetches a template parameter by index.
 */
template <unsigned index, typename... P>
class ParamByIndex;

template <unsigned index, typename W, typename... P>
class ParamByIndex<index, W, P...> {
public:
  using param = typename std::conditional<index == 0, W, ParamByIndex<index - 1, P...>>::type;
};

/**
 * Parameters.
 */
template <typename... P>
class Parameters {
public:
  template <typename Op, typename VL>
  using Scanner = setl::For<Op, VL, P...>;

  template <unsigned index>
  using Param = ParamByIndex<index, P...>;

  const unsigned size = Scanner <
      setl::Operator<setl::ConstIntegerAdaptor<unsigned, 1>::template Constant, 
        setl::AddEval<unsigned>>,
      void>::value;

  using ParamsRunner = ardo::Runner<P...>;
};

namespace nfp {
// Not part of the public API.
// Processing conflict checks for claims.

template <typename PL, typename PR>
struct ClaimsClaimConflictTest : PL::template has_resource<PR> {};

template <typename PL, typename PR>
struct ParamParamConflictTest {
  using value_type = bool;
  static constexpr value_type value = PL::Claims::template Scanner<
    setl::Operator<ClaimsClaimConflictTest, setl::OrEval>, typename PR::Claims>::value;
};

template <typename PSR, typename PL>
struct ParamParamsConflictTest {
  using value_type = bool;
  static constexpr value_type value = PSR::template Scanner<
    setl::Operator<ParamParamConflictTest, setl::OrEval>, PL>::value;
};

template <typename PSL, typename PSR>
struct ParamsParamsConflictTest {
  using value_type = bool;
  static constexpr value_type value = PSL::template Scanner<
    setl::Operator<ParamParamsConflictTest, setl::OrEval>, PSR>::value;
};
}  // namespace nfp.

/**
 * Module.
 */
template <typename w_Params>
class ModuleBase {
public:
  using Params = w_Params;

  static void paramsSetup() {
    Params::ParamsRunner::runSetup();
  }

  static void paramsLoop() {
    Params::ParamsRunner::runLoop();
  }

  static void runSetup() {
    // Provide an empty setup method.
  }

  static void runLoop() {
    // Provide an empty setup method.
  }
};

// The conflict test for modules is the conflict test for the embedded params.
template <typename M0, typename Mi>
struct ModuleConflictTest
  : nfp::ParamsParamsConflictTest<typename M0::Params, typename Mi::Params > {};

template <typename... Modules> 
class Application {
public:
  using ModuleRunner = ardo::Runner<Modules...>;

  template <typename Op, typename VL>
  using Scanner = setl::For<Op, VL, Modules...>;

  using AutoScanner = setl::AutoFor<Modules...>;


  static void runSetup() {
    ModuleRunner::runParamsSetup();
    ModuleRunner::runSetup();
  }

  static void runLoop() {
    ModuleRunner::runParamsLoop();
    ModuleRunner::runLoop();
  }

  // Evaluates if any module has conflicts.
  static constexpr bool has_conflict = AutoScanner::template FullScanner<
    setl::Operator<ModuleConflictTest, setl::OrEval>>::value;

  static_assert(!has_conflict, "Application has resource conflict.");
};

}  // namespace

#endif