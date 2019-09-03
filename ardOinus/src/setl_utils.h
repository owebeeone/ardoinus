
#ifndef SETL_UTILS____H
#define SETL_UTILS____H

namespace setl {

// Inherit to make a class not copyable.
struct not_copyable {
public:
  not_copyable() = default;
  // Delete all ways to copy this object.
  not_copyable(const not_copyable&) = delete;
  not_copyable operator=(const not_copyable&) = delete;
  not_copyable(not_copyable&&) = delete;
  not_copyable operator=(not_copyable&&) = delete;
};

// Inherit to make a class uninstantiable.
class not_instantiable : public not_copyable {
  // Delete all ways to construct this object.
  not_instantiable() = delete;
};

}  // namespace

#endif