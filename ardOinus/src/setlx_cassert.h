
#ifndef SETL_CASSERT__H
#define SETL_CASSERT__H

#include "setl_support.h"

#ifdef HAS_STD_LIB
#include <cassert>
#else

namespace std {

#define assert(V)

} // namespace

#endif
#endif