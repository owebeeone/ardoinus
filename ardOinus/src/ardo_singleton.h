/**
 * A singleton base class. Prevents copy and assignment.
 */

#ifndef ARDO_SINGLETON___H
#define ARDO_SINGLETON___H

namespace ardo {

/**
 * Use the CRTP idiom to create an instance of the class parameter. 
 */
template <typename T>
class Singleton {
  friend T;
  Singleton() = default;
  Singleton(const Singleton&) = delete;
  Singleton(Singleton&&) = delete;
  Singleton& operator=(const Singleton&) = delete;
  Singleton& operator=(Singleton&&) = delete;

protected:
  // The statically allocated singleton instance.
  static T instance;
};

template <typename T>
T Singleton<T>::instance{};

/**
 * Provides a singleton and a framewprk to call instance setup and loop functions.
 */
template <typename T>
class ModuleInstance : public Singleton<T> {
  friend T;

  inline static void runSetup() {
    T::instance.instanceSetup();
  }

  inline static void runLoop() {
    T::instance.instanceLoop();
  }

  inline void instanceSetup() {
  }

  inline void instanceLoop() {
  }
};

} // namespace ardo

#endif // ARDO_SINGLETON___H