/**
 * A singleton base class. Prevents copy and assignment.
 */

#ifndef ARDO_SINGLETON___H
#define ARDO_SINGLETON___H

namespace ardo {

/**
 * Use the CRTP idiom to create an instance of the class parameter. 
 */
template <typename w_Module>
class Singleton {
  friend w_Module;
  Singleton(const Singleton&) = delete;
  Singleton(Singleton&&) = delete;
  Singleton& operator=(const Singleton&) = delete;
  Singleton& operator=(Singleton&&) = delete;
public:
  Singleton() = default;
  using Module = w_Module;
protected:
  // The statically allocated singleton instance.
  static Module instance;
};

template <typename T>
T Singleton<T>::instance{};


} // namespace ardo

#endif // ARDO_SINGLETON___H