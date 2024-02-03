

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

#define RAND_MAX 0x7fff

int rand() {
  nfp::seed = (1103515245ll * nfp::seed + 12345);
  return int(nfp::seed) & RAND_MAX;
}

}  // namespace

#endif

#endif