
#include "setlx_tuple.h"
#include "ardo_params_modules.h"

using namespace ardo;


struct Module1 : ModuleBase<> {
};

struct Module2 : ModuleBase<> {
};

struct ParamA {

};

struct ParamB {
  using Deps = DependentModules<Module1>;
};

struct ParamC {
  using Deps = DependentModules<Module2>;
};


struct ModuleNA : ModuleBase<Parameters<>> {
};

static_assert(std::is_same_v<ModuleNA::Deps, DependentModules<>>,
  "ModuleNA's parameters must have no dependent modules.");

struct ModuleA : ModuleBase<Parameters<ParamA>> {
};

constexpr ModuleA::Deps x{ DependentModules<>{} };

static_assert(std::is_same_v<ModuleA::Deps, DependentModules<>>,
  "ModuleA's parameters must have no dependent modules.");

struct ModuleB : ModuleBase<Parameters<ParamB>> {
};

static_assert(std::is_same_v<ModuleB::Deps, DependentModules<Module1>>,
  "ModuleB's parameters must has a Module1 dependent module.");

struct ModuleABC : ModuleBase<Parameters<ParamA, ParamB, ParamC>> {
};

static_assert(std::is_same_v<ModuleABC::Deps, DependentModules<Module1, Module2>>,
  "ModuleA's parameters have no dependent modules.");

