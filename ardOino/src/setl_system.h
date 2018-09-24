#ifndef SETL_SYSTEM___H
#define SETL_SYSTEM___H

#include "setl_utils.h"

namespace setl {

// The memory barrier you have when you're not having a memory barrier.
struct NopMemoryBarrier {};

#if defined(_WIN32) || defined(__CYGWIN__) || defined(__AVR__) || defined(__XTENSA__)


class System : not_instantiable {
public:
  static void readBarrier() {
  }

  static void writeBarrier() {
  }

  struct MemoryBarrier : public not_copyable {
    MemoryBarrier() {
      readBarrier();
    }

    ~MemoryBarrier() {
      writeBarrier();
    }
  };

  /** Send an error message. */
  static void logDebugFatal(const char* message);
};

#endif // WIN32


}

#endif