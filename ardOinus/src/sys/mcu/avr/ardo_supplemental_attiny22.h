// Generated for arch attiny22.
// This file is generated from the avr-gcc compiler with the mcu
// set to attiny22 from macros specific to avr/io.h.
// Any changes to this file will likely be lost next time this file
// is regenerated. Many any mcu_arch specific changes to 
// ardo_supplemental_attiny22_defs.h.

#ifndef ardo_supplemental_attiny22__h
#define ardo_supplemental_attiny22__h

#include "setlx_cstdint.h"
#include "setl_bit_fields.h"
#include "ardo_avr_bit_io_defs.h"

namespace ardo {
namespace sys {
namespace avr {
namespace arch_attiny22 {

constexpr ptrdiff_t cc__SFR_OFFSET = 0x20;

template <typename T, ptrdiff_t w_addr>
using IoRegisterDef = avr::nfp::IoRegisterDef<T, w_addr, cc__SFR_OFFSET>;
using avr::nfp::MemRegisterDef;

constexpr unsigned ccCS00 = 0;
constexpr unsigned ccCS01 = 1;
constexpr unsigned ccCS02 = 2;
constexpr unsigned ccDD0 = 0;
constexpr unsigned ccDD1 = 1;
constexpr unsigned ccDD2 = 2;
constexpr unsigned ccDD3 = 3;
constexpr unsigned ccDD4 = 4;
constexpr unsigned ccDD5 = 5;
constexpr unsigned ccDD6 = 6;
constexpr unsigned ccDD7 = 7;
constexpr unsigned ccDDB0 = 0;
constexpr unsigned ccDDB1 = 1;
constexpr unsigned ccDDB2 = 2;
constexpr unsigned ccDDB3 = 3;
constexpr unsigned ccDDB4 = 4;
using rrDDRB = IoRegisterDef<std::uint8_t, 0x17>;
constexpr unsigned ccE2END = 0x7F;
constexpr unsigned ccE2PAGESIZE = 0;
using rrEEAR = IoRegisterDef<std::uint8_t, 0x1E>;
using rrEEARL = IoRegisterDef<std::uint8_t, 0x1E>;
using rrEECR = IoRegisterDef<std::uint8_t, 0x1C>;
using rrEEDR = IoRegisterDef<std::uint8_t, 0x1D>;
constexpr unsigned ccEEMWE = 2;
constexpr unsigned ccEERE = 0;
constexpr unsigned ccEERIE = 3;
constexpr unsigned ccEEWE = 1;
constexpr unsigned ccFLASHEND = 0x07FF;
using ffFUSE_CKSEL = setl::BitsRW<setl::SemanticType<setl::hash("FUSE_CKSEL"), bool>, 1u<<0>;
constexpr unsigned ccFUSE_MEMORY_SIZE = 1;
using ffFUSE_SPIEN = setl::BitsRW<setl::SemanticType<setl::hash("FUSE_SPIEN"), bool>, 1u<<5>;
using rrGIFR = IoRegisterDef<std::uint8_t, 0x3A>;
using rrGIMSK = IoRegisterDef<std::uint8_t, 0x3B>;
constexpr unsigned ccINT0 = 6;
constexpr unsigned ccINT0_vect_num = 1;
constexpr unsigned ccINTF0 = 6;
constexpr unsigned ccISC00 = 0;
constexpr unsigned ccISC01 = 1;
constexpr unsigned ccLB_MODE_1 = 0xFF;
constexpr unsigned ccLB_MODE_2 = 0xFE;
constexpr unsigned ccLB_MODE_3 = 0xFC;
constexpr unsigned ccLOCKBITS_DEFAULT = 0xFF;
using rrMCUCR = IoRegisterDef<std::uint8_t, 0x35>;
using rrMCUSR = IoRegisterDef<std::uint8_t, 0x34>;
constexpr unsigned ccPB0 = 0;
constexpr unsigned ccPB1 = 1;
constexpr unsigned ccPB2 = 2;
constexpr unsigned ccPB3 = 3;
constexpr unsigned ccPB4 = 4;
constexpr unsigned ccPIN0 = 0;
constexpr unsigned ccPIN1 = 1;
constexpr unsigned ccPIN2 = 2;
constexpr unsigned ccPIN3 = 3;
constexpr unsigned ccPIN4 = 4;
constexpr unsigned ccPIN5 = 5;
constexpr unsigned ccPIN6 = 6;
constexpr unsigned ccPIN7 = 7;
using rrPINB = IoRegisterDef<std::uint8_t, 0x16>;
constexpr unsigned ccPINB0 = 0;
constexpr unsigned ccPINB1 = 1;
constexpr unsigned ccPINB2 = 2;
constexpr unsigned ccPINB3 = 3;
constexpr unsigned ccPINB4 = 4;
constexpr unsigned ccPORT0 = 0;
constexpr unsigned ccPORT1 = 1;
constexpr unsigned ccPORT2 = 2;
constexpr unsigned ccPORT3 = 3;
constexpr unsigned ccPORT4 = 4;
constexpr unsigned ccPORT5 = 5;
constexpr unsigned ccPORT6 = 6;
constexpr unsigned ccPORT7 = 7;
using rrPORTB = IoRegisterDef<std::uint8_t, 0x18>;
constexpr unsigned ccRAMEND = 0xDF;
constexpr unsigned ccRAMSTART = 0x60;
constexpr unsigned ccSE = 5;
constexpr unsigned ccSIGNATURE_0 = 0x1E;
constexpr unsigned ccSIGNATURE_1 = 0x91;
constexpr unsigned ccSIGNATURE_2 = 0x06;
constexpr unsigned ccSLEEP_MODE_IDLE = 0x00;
constexpr unsigned ccSLEEP_MODE_PWR_DOWN = 0x01;
constexpr unsigned ccSM = 4;
using rrSP = IoRegisterDef<std::uint8_t, 0x3D>;
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
using rrTCNT0 = IoRegisterDef<std::uint8_t, 0x32>;
using rrTIFR = IoRegisterDef<std::uint8_t, 0x38>;
constexpr unsigned ccTIMER0_OVF0_vect_num = 2;
using rrTIMSK = IoRegisterDef<std::uint8_t, 0x39>;
constexpr unsigned ccTOIE0 = 1;
constexpr unsigned ccTOV0 = 1;
constexpr unsigned ccWDE = 3;
constexpr unsigned ccWDP0 = 0;
constexpr unsigned ccWDP1 = 1;
constexpr unsigned ccWDP2 = 2;
using rrWDTCR = IoRegisterDef<std::uint8_t, 0x21>;
constexpr unsigned ccWDTOE = 4;
constexpr unsigned cc_SFR_ASM_COMPAT = 0;
constexpr unsigned cc_VECTORS_SIZE = 6;
constexpr unsigned cc__USING_MINT8 = 0;


}  // arch_attiny22
}  // namespace avr
}  // namespace sys
}  // namespace ardo

#endif  // ardo_supplemental_attiny22__h
