
#ifndef ARDO_PARAMS_MODULES___H
#define ARDO_PARAMS_MODULES___H

#include "ardo_singleton.h"

#include "setlx_cstdint.h"
#include "setlx_type_traits.h"
#include "setl_templ_utils.h"

namespace ardo {

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
    Runner<T...>::runParamsSetup();
    S::paramsSetup();
  }

  inline static void runParamsLoop() {
    Runner<T...>::runParamsLoop();
    S::paramsLoop();
  }

  inline static void runSetup() {
    Runner<T...>::runSetup();
    S::runSetup();
  }

  inline static void runLoop() {
    Runner<T...>::runLoop();
    S::runLoop();
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
 * Parameters captures a set of module parameters.
 */
template <typename... P>
class Parameters {
public:
  using Params = setl::TypeArgs<P...>;

  template <typename Op, typename VL>
  using Scanner = setl::For<Op, VL, P...>;

  template <unsigned index>
  using Param = typename ParamByIndex<index, P...>::param;

  const unsigned size = Scanner<
      setl::Operator<setl::ConstIntegerAdaptor<unsigned, 1>::template Constant, 
        setl::AddEval<unsigned>>,
      void>::value;

  using ParamsRunner = ardo::Runner<P...>;
};

/**
 * Container for dependent modules.
 */
template <typename... T>
using DependentModules = setl::TypeArgs<T...>;

/**
 * Evaluate the closure of the module dependency graph. The result is
 * a setl::TypeArgs that contains all the closure modules. Any repeated nodes
 * in the given
 */
namespace nfp {
// Helper templates for module closure computation.
// Not part of official API.
template <typename Contained, typename...w_Ms>
struct ModuleClosureVa;

template <typename Contained, typename...w_Ms>
using ModuleClosureVaTemplate = ModuleClosureVa<Contained, w_Ms...>;

template <typename Contained>
struct ModuleClosureVa<Contained> {
  using type = Contained;
};

template <typename Contained, typename T, typename...w_Ms>
class ModuleClosureVa<Contained, T, w_Ms...> {
  using new_contained = typename Contained::template cat<T>;
  using catenated_deps = typename T::Deps::template cat<w_Ms...>;
  using rest = setl::RemoveAll<catenated_deps, new_contained>;
public:
  using type = 
    typename rest::template eval_arg1<new_contained, ModuleClosureVaTemplate>::type;
};

// Extract dependent modules from parameters. This can be used by parameters
// that have shared resources and the setup() function should only be called
// once. An example is timer resources where the timer setup should only happen
// once but it's used by multiple PWM outputs.
template <typename T>
struct GetDepsFromParams;

template <>
struct GetDepsFromParams<Parameters<>> {
  using Deps = DependentModules<>;
};

struct EmptyDeps {
  using Deps = DependentModules<>;
};

template <typename T, typename...Ts>
struct GetDepsFromParams<Parameters<T, Ts...>> {
  using DepsRest = typename GetDepsFromParams<Parameters<Ts...>>::Deps;

  template <typename V>
  static std::true_type hasDeps(const typename V::Deps*);

  template <typename V>
  static std::false_type hasDeps(...);

  template <typename V>
  using DepsOf = typename std::conditional_t<
    decltype(hasDeps<V>(nullptr))::value,
    T,
    EmptyDeps>::Deps;

  using Deps = typename DepsRest::template catr_type_arg<DepsOf<T>>;
};

template <typename Params>
using DepsFromParams = typename GetDepsFromParams<Params>::Deps;

} // namespace nfp


/**
 * Module base class. Use this type of base class if no instance is required.
 * Otherwise use the ModuleInstanceBase class to create a singleton instance.
 */
template <
  typename w_Params = Parameters<>,
  typename w_Deps = DependentModules<>>
class ModuleBase {
public:
  // Dependent modules will automatically be added to the application modules
  // if not already in the application modules. Modules added here will not 
  // conflict with other modules adding modules.
  using ImplicitDeps = w_Deps;
  using Deps = typename ImplicitDeps::template cat_type_arg<nfp::DepsFromParams<w_Params>>;
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

/**
 * Provides an instance of the module. The provided module's instance functions
 * instanceLoop() and instanceSetup() are called from the provided static functions.
 */
template <
  typename w_Module,
  typename w_Params = Parameters<>,
  typename w_Deps = DependentModules<>>
class ModuleInstanceBase :
    public ModuleBase<w_Params, w_Deps>,
    public Singleton<w_Module> {
public:
  inline static void runSetup() {
    w_Module::instance.instanceSetup();
  }

  inline static void runLoop() {
    w_Module::instance.instanceLoop();
  }

  inline void instanceSetup() {
  }

  inline void instanceLoop() {
  }
};

}  // namespace ardo

#endif // ARDO_PARAMS_MODULES___H