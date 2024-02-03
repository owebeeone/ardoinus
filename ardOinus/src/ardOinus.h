/**
 * ArdOinus is an embedded application framework allowing composition
 * of re-usable modules targetted for embedded microcontroller applications.
 *
 * ArdOinus aims to be true to the C++ philosophy that you don't pay for what
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

#ifndef ARDOINUS___H
#define ARDOINUS___H

#include "ardo_resources.h"
#include "ardo_sys_defs.h"
#include "ardo_params_modules.h"

#include "setl_time.h"
#include "setl_utils.h"
#include "setl_templ_utils.h"

#include "setlx_cstdint.h"
#include "setlx_type_traits.h"

namespace ardo {

/** A base class for output pins where a base class is needed. */
class OutputPinIF {
public:
  virtual ~OutputPinIF() {}
  virtual void setPin(bool) const = 0;
  virtual unsigned pinNo() const = 0;
};

/** A base class for input pins where a base class is needed. */
class InputPinIF {
public:
  virtual ~InputPinIF() {}
  virtual bool getPin() const = 0;
  virtual unsigned pinNo() const = 0;
};

/** A base class for pins that support both input and output where a 
 * base class is needed.
 * @deprecated - use OutputPinIF, InputPinIF as Base
 */
class InputOutputPinIF : public OutputPinIF, public InputPinIF {
};

/**
 * An externally managed pin. This only provides resource claims. It expects that
 * an external library will manage the pin setup. No access to the GPIO functions
 * are provided.
 */
template <unsigned P>
class ExternalPin : public setl::not_copyable {
  private:
    ExternalPin() = delete;  // No instance provided.
  public:
    static constexpr unsigned PIN = P;

    // Claim resources.
    using Claims = ResourceClaim<GPIOResource<PIN>>;

    inline static void runSetup() {}

    inline static void runLoop() {}
};

/**
 * A digital output.
 */
template <unsigned P, 
    CoreIF::OutputPinMode M = CoreIF::Output, 
    typename... Base>
class OutputPin : public Base..., public setl::not_copyable {
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

template <unsigned P, CoreIF::OutputPinMode M, typename... Base>
const OutputPin<P, M, Base...> OutputPin<P, M, Base...>::pin;

/**
 * A digital output for open collector/drain pulled low when active.
 */
template <unsigned P, typename... Base>
class OutputPin<P, CoreIF::OpenDrainLowOutput, Base...> 
    : public Base..., public setl::not_copyable {
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

  // Open drain can be read as well.
  static bool get() {
    return CoreIF::digitalRead(PIN);
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

template <unsigned P, typename... Base>
const OutputPin<P, CoreIF::OpenDrainLowOutput, Base...>
OutputPin<P, CoreIF::OpenDrainLowOutput, Base...>::pin;

/**
 * A digital output for open collector/drain pulled high when active.
 */
template <unsigned P, typename... Base>
class OutputPin<P, CoreIF::OpenDrainHighOutput, Base...>
  : public Base..., public setl::not_copyable {
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
    CoreIF::pinMode(PIN, level ? CoreIF::Output: CoreIF::Untied);
  }

  // Overrides OutputPinIF base class interface.
  void setPin(bool level) const {
    set(level);
  }

  // Open drain can be read as well.
  static bool get() {
    return CoreIF::digitalRead(PIN);
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

template <unsigned P, typename... Base>
const OutputPin<P, CoreIF::OpenDrainHighOutput, Base...>
    OutputPin<P, CoreIF::OpenDrainHighOutput, Base...>::pin;

/**
 * The basic digital input pin.
 */
template <unsigned P,  // The digital/gpio pin number.
  CoreIF::InputPinMode M = CoreIF::PullUp, 
  typename... Base>
class InputPin : public Base..., public setl::not_copyable {
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
    return CoreIF::digitalRead(PIN);
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

template <unsigned P, CoreIF::InputPinMode M, typename... Base>
const InputPin<P, M, Base...> InputPin<P, M, Base...>::pin;

/**
 * Debounced input type.
 */
template <typename InputPin, 
  unsigned long debounceTime = 300, 
  typename w_TimeType= ardo::CoreIF::MicrosTime>
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

template <typename InputPin, unsigned long debounceTime, typename w_TimeType>
typename DebounceInput<InputPin, debounceTime, w_TimeType>::DebounceState
    DebounceInput<InputPin, debounceTime, w_TimeType>::debounceState;

template <typename InputPin, unsigned long debounceTime, typename w_TimeType>
const DebounceInput<InputPin, debounceTime, w_TimeType>
    DebounceInput<InputPin, debounceTime, w_TimeType>::pin;


namespace nfp {
// Not part of the public API.
// Processing conflict checks for claims.

// Tests a list of resources for conflict within the list itself.
template <typename... Res>
struct SelfParamsConflictTest;

template <>
struct SelfParamsConflictTest<> {
  using value_type = bool;
  constexpr static bool value = false;
};

template <typename Res>
struct SelfParamsConflictTest<Res> {
  using value_type = bool;
  constexpr static value_type value = false;
};

template <typename Res1, typename Res2, typename... Ress>
struct SelfParamsConflictTest<Res1, Res2, Ress...> {
  using value_type = bool;
  static constexpr value_type res1_res2_conflict = has_conflict<Res1, Res2>::value;
  static constexpr value_type value =
    res1_res2_conflict
    || SelfParamsConflictTest<Res1, Ress...>::value
    || SelfParamsConflictTest<Res2, Ress...>::value;

  static_assert(!res1_res2_conflict, "Found resource conflict in same claim.");
};

template <typename PL, typename PR>
struct ClaimsClaimConflictTest : PL::template has_resource<PR> {};

template <typename PL, typename PR>
struct ParamParamConflictTest {
  using value_type = bool;
  static constexpr value_type value = PL::Claims::template Scanner<
    setl::Operator<ClaimsClaimConflictTest, setl::OrEval>, typename PR::Claims>::value
    || PL::Claims::Resources::template eval<nfp::SelfParamsConflictTest>::value
    || PR::Claims::Resources::template eval<nfp::SelfParamsConflictTest>::value;
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

  static_assert(!value, "Application has resource conflict.");
};

}  // namespace nfp.

template <typename...w_Ms>
using ModuleClosure = typename nfp::ModuleClosureVa<setl::TypeArgs<>, w_Ms...>::type;

namespace nfp {
// Helper for testing module parameters self conflict.
template <typename... Params>
struct SelfModuleParamsConflictTest;

template <>
struct SelfModuleParamsConflictTest<> {
  using value_type = bool;
  constexpr static bool value = false;
};

template <typename Param>
struct SelfModuleParamsConflictTest<Param> {
  using value_type = bool;
  constexpr static value_type value = false;
};

template <typename Param1, typename Param2, typename... Params>
struct SelfModuleParamsConflictTest<Param1, Param2, Params...> {
  using value_type = bool;
  static constexpr value_type value =
    ParamParamConflictTest<Param1, Param2>::value
    || SelfModuleParamsConflictTest<Param1, Params...>::value
    || SelfModuleParamsConflictTest<Param2, Params...>::value;

  static_assert(!value, "Application has resource conflict within same module.");
};
}  // namespace nfp

// Resource conflict test for modules. Test all embedded params against each other.
template <typename M0, typename Mi>
struct ModuleConflictTest {
  using value_type = bool;
  static constexpr value_type value =
    nfp::ParamsParamsConflictTest<typename M0::Params, typename Mi::Params>::value;
};

// Each module also needs not to have a conflicting set of params.
template <typename... Ms>
struct SelfModuleConflictTest;

template <>
struct SelfModuleConflictTest<> {
  using value_type = bool;
  static constexpr value_type value = false;
};

template <typename M, typename... Ms>
struct SelfModuleConflictTest<M, Ms...> {
  using value_type = bool;
  static constexpr value_type value =
    M::Params::Params::template eval<nfp::SelfModuleParamsConflictTest>::value
    || SelfModuleConflictTest<Ms...>::value;

  static_assert(!value, "Application has resource conflict.");
};

template <typename... Modules> 
class Application {
public:
  // Find the closure of all dependent modules.
  using AllModules = ModuleClosure<Modules...>;

  using ModuleRunner = typename AllModules::template eval<Runner>;

  template <typename Op, typename VL>
  using Scanner = typename AllModules::template eval_arg2<Op, VL, setl::For>;

  using AutoScanner = typename AllModules::template eval<setl::AutoFor>;

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
    setl::Operator<ModuleConflictTest, setl::OrEval>>::value
    || AllModules::template eval<SelfModuleConflictTest>::value;

  static_assert(!has_conflict, "Application has resource conflict.");
};

}  // namespace ardo

#define ARDOINUS___H_DONE
#endif
