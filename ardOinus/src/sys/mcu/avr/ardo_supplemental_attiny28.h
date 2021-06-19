// Generated for arch attiny28.
// This file is generated from the avr-gcc compiler with the mcu
// set to attiny28 from macros specific to avr/io.h.
// Any changes to this file will likely be lost next time this file
// is regenerated. Many any mcu_arch specific changes to 
// ardo_supplemental_attiny28_defs.h.

#ifndef ardo_supplemental_attiny28__h
#define ardo_supplemental_attiny28__h

#include "setlx_cstdint.h"
#include "setl_bit_fields.h"
#include "ardo_avr_bit_io_defs.h"

namespace ardo {
namespace sys {
namespace avr {
namespace arch_attiny28 {

constexpr ptrdiff_t cc__SFR_OFFSET = 0x20;

template <typename T, ptrdiff_t w_addr>
using IoRegisterDef = avr::nfp::IoRegisterDef<T, w_addr, cc__SFR_OFFSET>;
using avr::nfp::MemRegisterDef;

constexpr unsigned ccACD = 7;
constexpr unsigned ccACI = 4;
constexpr unsigned ccACIE = 3;
constexpr unsigned ccACIS0 = 0;
constexpr unsigned ccACIS1 = 1;
constexpr unsigned ccACO = 5;
using rrACSR = IoRegisterDef<std::uint8_t, 0x08>;
constexpr unsigned ccANA_COMP_vect_num = 5;
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
constexpr unsigned ccDDA0 = 0;
constexpr unsigned ccDDA1 = 1;
constexpr unsigned ccDDA3 = 3;
constexpr unsigned ccDDD0 = 0;
constexpr unsigned ccDDD1 = 1;
constexpr unsigned ccDDD2 = 2;
constexpr unsigned ccDDD3 = 3;
constexpr unsigned ccDDD4 = 4;
constexpr unsigned ccDDD5 = 5;
constexpr unsigned ccDDD6 = 6;
constexpr unsigned ccDDD7 = 7;
using rrDDRD = IoRegisterDef<std::uint8_t, 0x11>;
constexpr unsigned ccE2END = 0x0;
constexpr unsigned ccE2PAGESIZE = 0;
constexpr unsigned ccEXTRF = 1;
constexpr unsigned ccFLASHEND = 0x7FF;
constexpr unsigned ccFOV0 = 7;
using ffFUSE_CKSEL0 = setl::BitsRW<setl::SemanticType<setl::hash("FUSE_CKSEL0"), bool>, 1u<<0>;
using ffFUSE_CKSEL1 = setl::BitsRW<setl::SemanticType<setl::hash("FUSE_CKSEL1"), bool>, 1u<<1>;
using ffFUSE_CKSEL2 = setl::BitsRW<setl::SemanticType<setl::hash("FUSE_CKSEL2"), bool>, 1u<<2>;
using ffFUSE_CKSEL3 = setl::BitsRW<setl::SemanticType<setl::hash("FUSE_CKSEL3"), bool>, 1u<<3>;
using ffFUSE_INTCAP = setl::BitsRW<setl::SemanticType<setl::hash("FUSE_INTCAP"), bool>, 1u<<4>;
constexpr unsigned ccFUSE_MEMORY_SIZE = 1;
using rrICR = IoRegisterDef<std::uint8_t, 0x06>;
using rrIFR = IoRegisterDef<std::uint8_t, 0x05>;
constexpr unsigned ccINT0 = 6;
constexpr unsigned ccINT0_vect_num = 1;
constexpr unsigned ccINT1 = 7;
constexpr unsigned ccINT1_vect_num = 2;
constexpr unsigned ccINTF0 = 6;
constexpr unsigned ccINTF1 = 7;
constexpr unsigned ccISC01 = 1;
constexpr unsigned ccISC10 = 2;
constexpr unsigned ccISC11 = 3;
constexpr unsigned ccLB_MODE_1 = 0xFF;
constexpr unsigned ccLB_MODE_2 = 0xFE;
constexpr unsigned ccLB_MODE_3 = 0xFC;
constexpr unsigned ccLLIE = 5;
constexpr unsigned ccLOCKBITS_DEFAULT = 0xFF;
constexpr unsigned ccLOWLEVEL_IO_PINS_vect_num = 3;
constexpr unsigned ccMCONF0 = 0;
constexpr unsigned ccMCONF1 = 1;
constexpr unsigned ccMCONF2 = 2;
using rrMCUCS = IoRegisterDef<std::uint8_t, 0x07>;
using rrMODCR = IoRegisterDef<std::uint8_t, 0x02>;
constexpr unsigned ccONTIM0 = 3;
constexpr unsigned ccONTIM1 = 4;
constexpr unsigned ccONTIM2 = 5;
constexpr unsigned ccONTIM3 = 6;
constexpr unsigned ccONTIM4 = 7;
constexpr unsigned ccOOM00 = 3;
constexpr unsigned ccOOM01 = 4;
using rrOSCCAL = IoRegisterDef<std::uint8_t, 0x00>;
constexpr unsigned ccPA0 = 0;
constexpr unsigned ccPA1 = 1;
constexpr unsigned ccPA2 = 2;
constexpr unsigned ccPA2HC = 2;
constexpr unsigned ccPA3 = 3;
using rrPACR = IoRegisterDef<std::uint8_t, 0x1A>;
constexpr unsigned ccPD0 = 0;
constexpr unsigned ccPD1 = 1;
constexpr unsigned ccPD2 = 2;
constexpr unsigned ccPD3 = 3;
constexpr unsigned ccPD4 = 4;
constexpr unsigned ccPD5 = 5;
constexpr unsigned ccPD6 = 6;
constexpr unsigned ccPD7 = 7;
constexpr unsigned ccPIN0 = 0;
constexpr unsigned ccPIN1 = 1;
constexpr unsigned ccPIN2 = 2;
constexpr unsigned ccPIN3 = 3;
constexpr unsigned ccPIN4 = 4;
constexpr unsigned ccPIN5 = 5;
constexpr unsigned ccPIN6 = 6;
constexpr unsigned ccPIN7 = 7;
using rrPINA = IoRegisterDef<std::uint8_t, 0x19>;
constexpr unsigned ccPINA0 = 0;
constexpr unsigned ccPINA1 = 1;
constexpr unsigned ccPINA3 = 3;
using rrPINB = IoRegisterDef<std::uint8_t, 0x16>;
constexpr unsigned ccPINB0 = 0;
constexpr unsigned ccPINB1 = 1;
constexpr unsigned ccPINB2 = 2;
constexpr unsigned ccPINB3 = 3;
constexpr unsigned ccPINB4 = 4;
constexpr unsigned ccPINB5 = 5;
constexpr unsigned ccPINB6 = 6;
constexpr unsigned ccPINB7 = 7;
using rrPIND = IoRegisterDef<std::uint8_t, 0x10>;
constexpr unsigned ccPIND0 = 0;
constexpr unsigned ccPIND1 = 1;
constexpr unsigned ccPIND2 = 2;
constexpr unsigned ccPIND3 = 3;
constexpr unsigned ccPIND4 = 4;
constexpr unsigned ccPIND5 = 5;
constexpr unsigned ccPIND6 = 6;
constexpr unsigned ccPIND7 = 7;
constexpr unsigned ccPLUPB = 7;
constexpr unsigned ccPORF = 0;
constexpr unsigned ccPORT0 = 0;
constexpr unsigned ccPORT1 = 1;
constexpr unsigned ccPORT2 = 2;
constexpr unsigned ccPORT3 = 3;
constexpr unsigned ccPORT4 = 4;
constexpr unsigned ccPORT5 = 5;
constexpr unsigned ccPORT6 = 6;
constexpr unsigned ccPORT7 = 7;
using rrPORTA = IoRegisterDef<std::uint8_t, 0x1B>;
using rrPORTD = IoRegisterDef<std::uint8_t, 0x12>;
constexpr unsigned ccRAMEND = 0x1F;
constexpr unsigned ccRAMSTART = 0x60;
constexpr unsigned ccSE = 5;
constexpr unsigned ccSIGNATURE_0 = 0x1E;
constexpr unsigned ccSIGNATURE_1 = 0x91;
constexpr unsigned ccSIGNATURE_2 = 0x07;
constexpr unsigned ccSLEEP_MODE_IDLE = 0x00;
constexpr unsigned ccSLEEP_MODE_PWR_DOWN = 0x01;
constexpr unsigned ccSM = 4;
using rrSREG = IoRegisterDef<std::uint8_t, 0x3F>;
constexpr unsigned ccSREG_C = 0;
constexpr unsigned ccSREG_H = 5;
constexpr unsigned ccSREG_I = 7;
constexpr unsigned ccSREG_N = 2;
constexpr unsigned ccSREG_S = 4;
constexpr unsigned ccSREG_T = 6;
constexpr unsigned ccSREG_V = 3;
constexpr unsigned ccSREG_Z = 1;
using rrTCCR0 = IoRegisterDef<std::uint8_t, 0x04>;
using rrTCNT0 = IoRegisterDef<std::uint8_t, 0x03>;
constexpr unsigned ccTIMER0_OVF_vect_num = 4;
constexpr unsigned ccTOIE0 = 4;
constexpr unsigned ccTOV0 = 4;
constexpr unsigned ccWDE = 3;
constexpr unsigned ccWDP0 = 0;
constexpr unsigned ccWDP1 = 1;
constexpr unsigned ccWDP2 = 2;
constexpr unsigned ccWDRF = 3;
using rrWDTCR = IoRegisterDef<std::uint8_t, 0x01>;
constexpr unsigned ccWDTOE = 4;
constexpr unsigned ccXRAMEND = 0x0;
constexpr unsigned cc_SFR_ASM_COMPAT = 0;
constexpr unsigned cc_VECTORS_SIZE = 12;
constexpr unsigned cc__USING_MINT8 = 0;


}  // arch_attiny28
}  // namespace avr
}  // namespace sys
}  // namespace ardo

#endif  // ardo_supplemental_attiny28__h
