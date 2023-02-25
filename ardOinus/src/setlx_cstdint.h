

#ifndef SETLX_CSTDINT__H
#define SETLX_CSTDINT__H

#include "setl_support.h"

#ifdef HAS_STD_LIB
#include <cstdint>
#else

#include "setl_integers.h"
#include "setlx_type_traits.h"

namespace std {

using int8_t = setl::SignedTypes::FindSize<1>::type;
using int16_t = setl::SignedTypes::FindSize<2>::type;
using int32_t = setl::SignedTypes::FindSize<4>::type;
using int64_t = setl::SignedTypes::FindSize<8>::type;

using uint8_t = setl::UnsignedTypes::FindSize<1>::type;
using uint16_t = setl::UnsignedTypes::FindSize<2>::type;
using uint32_t = setl::UnsignedTypes::FindSize<4>::type;
using uint64_t = setl::UnsignedTypes::FindSize<8>::type;

} // namespace

#endif

#endif  // SETLX_CSTDINT__H