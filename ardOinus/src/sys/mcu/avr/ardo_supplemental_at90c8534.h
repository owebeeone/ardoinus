// Generated for arch at90c8534.
// This file is generated from the avr-gcc compiler with the mcu
// set to at90c8534 from macros specific to avr/io.h.
// Any changes to this file will likely be lost next time this file
// is regenerated. Many any mcu_arch specific changes to 
// ardo_supplemental_at90c8534_defs.h.

#ifndef ardo_supplemental_at90c8534__h
#define ardo_supplemental_at90c8534__h

#include "setlx_cstdint.h"
#include "setl_bit_fields.h"
#include "ardo_avr_bit_io_defs.h"

namespace ardo {
namespace sys {
namespace avr {
namespace arch_at90c8534 {

constexpr ptrdiff_t cc__SFR_OFFSET = 0x20;

template <typename T, ptrdiff_t w_addr>
using IoRegisterDef = avr::nfp::IoRegisterDef<T, w_addr, cc__SFR_OFFSET>;
using avr::nfp::MemRegisterDef;

using rrADC = IoRegisterDef<std::uint16_t, 0x04>;
using rrADCH = IoRegisterDef<std::uint8_t, 0x05>;
using rrADCL = IoRegisterDef<std::uint8_t, 0x04>;
using rrADCSR = IoRegisterDef<std::uint8_t, 0x06>;
using rrADCW = IoRegisterDef<std::uint16_t, 0x04>;
using rrADMUX = IoRegisterDef<std::uint8_t, 0x07>;
constexpr unsigned ccCS00 = 0;
constexpr unsigned ccCS01 = 1;
constexpr unsigned ccCS02 = 2;
constexpr unsigned ccCS10 = 0;
constexpr unsigned ccCS11 = 1;
constexpr unsigned ccCS12 = 2;
constexpr unsigned ccDD0 = 0;
constexpr unsigned ccDD1 = 1;
constexpr unsigned ccDD2 = 2;
constexpr unsigned ccDD3 = 3;
constexpr unsigned ccDD4 = 4;
constexpr unsigned ccDD5 = 5;
constexpr unsigned ccDD6 = 6;
constexpr unsigned ccDD7 = 7;
constexpr unsigned ccDDA0 = 0;
constexpr unsigned ccDDA1 = 1;
constexpr unsigned ccDDA2 = 2;
constexpr unsigned ccDDA3 = 3;
constexpr unsigned ccDDA4 = 4;
constexpr unsigned ccDDA5 = 5;
constexpr unsigned ccDDA6 = 6;
constexpr unsigned ccDDA7 = 7;
using rrDDRA = IoRegisterDef<std::uint8_t, 0x1A>;
constexpr unsigned ccE2END = 0x1FF;
using rrEEAR = IoRegisterDef<std::uint16_t, 0x1E>;
using rrEEARH = IoRegisterDef<std::uint8_t, 0x1F>;
using rrEEARL = IoRegisterDef<std::uint8_t, 0x1E>;
using rrEECR = IoRegisterDef<std::uint8_t, 0x1C>;
using rrEEDR = IoRegisterDef<std::uint8_t, 0x1D>;
constexpr unsigned ccEEMWE = 2;
constexpr unsigned ccEERE = 0;
constexpr unsigned ccEERIE = 3;
constexpr unsigned ccEEWE = 1;
constexpr unsigned ccFLASHEND = 0x1FFF;
using rrGIFR = IoRegisterDef<std::uint8_t, 0x3A>;
using rrGIMSK = IoRegisterDef<std::uint8_t, 0x3B>;
using rrGIPR = IoRegisterDef<std::uint8_t, 0x10>;
constexpr unsigned ccINT0 = 6;
constexpr unsigned ccINT1 = 7;
constexpr unsigned ccINTF0 = 6;
constexpr unsigned ccINTF1 = 7;
constexpr unsigned ccIPIN0 = 2;
constexpr unsigned ccIPIN1 = 3;
constexpr unsigned ccISC0 = 0;
constexpr unsigned ccISC1 = 2;
constexpr unsigned ccLOCKBITS_DEFAULT = 0xFF;
using rrMCUCR = IoRegisterDef<std::uint8_t, 0x35>;
constexpr unsigned ccPA0 = 0;
constexpr unsigned ccPA1 = 1;
constexpr unsigned ccPA2 = 2;
constexpr unsigned ccPA3 = 3;
constexpr unsigned ccPA4 = 4;
constexpr unsigned ccPA5 = 5;
constexpr unsigned ccPA6 = 6;
constexpr unsigned ccPA7 = 7;
constexpr unsigned ccPIN0 = 0;
constexpr unsigned ccPIN1 = 1;
constexpr unsigned ccPIN2 = 2;
constexpr unsigned ccPIN3 = 3;
constexpr unsigned ccPIN4 = 4;
constexpr unsigned ccPIN5 = 5;
constexpr unsigned ccPIN6 = 6;
constexpr unsigned ccPIN7 = 7;
constexpr unsigned ccPORT0 = 0;
constexpr unsigned ccPORT1 = 1;
constexpr unsigned ccPORT2 = 2;
constexpr unsigned ccPORT3 = 3;
constexpr unsigned ccPORT4 = 4;
constexpr unsigned ccPORT5 = 5;
constexpr unsigned ccPORT6 = 6;
constexpr unsigned ccPORT7 = 7;
using rrPORTA = IoRegisterDef<std::uint8_t, 0x1B>;
constexpr unsigned ccRAMEND = 0x15F;
constexpr unsigned ccRAMSTART = 0x60;
constexpr unsigned ccSE = 6;
constexpr unsigned ccSM = 5;
using rrSP = IoRegisterDef<std::uint16_t, 0x3D>;
using rrSPH = IoRegisterDef<std::uint8_t, 0x3E>;
using rrSPL = IoRegisterDef<std::uint8_t, 0x3D>;
using rrSREG = IoRegisterDef<std::uint8_t, 0x3F>;
constexpr unsigned ccSREG_C = 0;
constexpr unsigned ccSREG_H = 5;
constexpr unsigned ccSREG_I = 7;
constexpr unsigned ccSREG_N = 2;
constexpr unsigned ccSREG_S = 4;
constexpr unsigned ccSREG_T = 6;
constexpr unsigned ccSREG_V = 3;
constexpr unsigned ccSREG_Z = 1;
using rrTCCR0 = IoRegisterDef<std::uint8_t, 0x33>;
using rrTCCR1 = IoRegisterDef<std::uint8_t, 0x2E>;
using rrTCNT0 = IoRegisterDef<std::uint8_t, 0x32>;
using rrTCNT1 = IoRegisterDef<std::uint16_t, 0x2C>;
using rrTCNT1H = IoRegisterDef<std::uint8_t, 0x2D>;
using rrTCNT1L = IoRegisterDef<std::uint8_t, 0x2C>;
using rrTIFR = IoRegisterDef<std::uint8_t, 0x38>;
using rrTIMSK = IoRegisterDef<std::uint8_t, 0x39>;
constexpr unsigned ccTOIE0 = 0;
constexpr unsigned ccTOIE1 = 2;
constexpr unsigned ccTOV0 = 0;
constexpr unsigned ccTOV1 = 2;
constexpr unsigned cc_AVR_IO8534_ = 1;
constexpr unsigned cc_HAVE_AVR_STACK_POINTER_HI = 1;
constexpr unsigned cc_SFR_ASM_COMPAT = 0;
constexpr unsigned cc_VECTORS_SIZE = 14;
constexpr unsigned cc__USING_MINT8 = 0;


}  // arch_at90c8534
}  // namespace avr
}  // namespace sys
}  // namespace ardo

#endif  // ardo_supplemental_at90c8534__h
