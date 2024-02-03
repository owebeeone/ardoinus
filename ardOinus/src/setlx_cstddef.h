#ifndef SETL_CSTDDEF__H
#define SETL_CSTDDEF__H

#include "setl_support.h"

#ifdef HAS_STD_LIB
#include <cstddef>
#else

namespace std {

using ptrdiff_t = decltype(((char *)0) - ((char *)0));
using size_t = ptrdiff_t;

}

#endif

#endif