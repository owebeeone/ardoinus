

#ifndef SETL_CSTDLIB__H
#define SETL_CSTDLIB__H

#include "setl_support.h"

#ifdef HAS_STD_LIB
#include <cstdlib>
#else

namespace std {

namespace nfp {
  
long long seed = 123456789;

}

int rand() {
  nfp::seed = (1103515245 * nfp::seed + 12345);
  return int(nfp::seed);
}

}  // namespace

#endif

#endif