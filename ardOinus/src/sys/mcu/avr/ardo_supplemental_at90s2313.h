// Generated for arch at90s2313.
// This file is generated from the avr-gcc compiler with the mcu
// set to at90s2313 from macros specific to avr/io.h.
// Any changes to this file will likely be lost next time this file
// is regenerated. Many any mcu_arch specific changes to 
// ardo_supplemental_at90s2313_defs.h.

#ifndef ardo_supplemental_at90s2313__h
#define ardo_supplemental_at90s2313__h

#include "setlx_cstdint.h"
#include "setl_bit_fields.h"
#include "ardo_avr_bit_io_defs.h"

namespace ardo {
namespace sys {
namespace avr {
namespace arch_at90s2313 {

constexpr ptrdiff_t cc__SFR_OFFSET = 0x20;

template <typename T, ptrdiff_t w_addr>
using IoRegisterDef = avr::nfp::IoRegisterDef<T, w_addr, cc__SFR_OFFSET>;
using avr::nfp::MemRegisterDef;

constexpr unsigned ccACD = 7;
constexpr unsigned ccACI = 4;
constexpr unsigned ccACIC = 2;
constexpr unsigned ccACIE = 3;
constexpr unsigned ccACIS0 = 0;
constexpr unsigned ccACIS1 = 1;
constexpr unsigned ccACO = 5;
using rrACSR = IoRegisterDef<std::uint8_t, 0x08>;
constexpr unsigned ccANA_COMP_vect_num = 10;
constexpr unsigned ccCHR9 = 2;
constexpr unsigned ccCOM1A0 = 6;
constexpr unsigned ccCOM1A1 = 7;
constexpr unsigned ccCS00 = 0;
constexpr unsigned ccCS01 = 1;
constexpr unsigned ccCS02 = 2;
constexpr unsigned ccCS10 = 0;
constexpr unsigned ccCS11 = 1;
constexpr unsigned ccCS12 = 2;
constexpr unsigned ccCTC1 = 3;
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
constexpr unsigned ccDDB5 = 5;
constexpr unsigned ccDDB6 = 6;
constexpr unsigned ccDDB7 = 7;
constexpr unsigned ccDDD0 = 0;
constexpr unsigned ccDDD1 = 1;
constexpr unsigned ccDDD2 = 2;
constexpr unsigned ccDDD3 = 3;
constexpr unsigned ccDDD4 = 4;
constexpr unsigned ccDDD5 = 5;
constexpr unsigned ccDDD6 = 6;
using rrDDRB = IoRegisterDef<std::uint8_t, 0x17>;
using rrDDRD = IoRegisterDef<std::uint8_t, 0x11>;
constexpr unsigned ccDOR = 3;
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
constexpr unsigned ccFE = 4;
constexpr unsigned ccFLASHEND = 0x07FF;
using ffFUSE_FSTRT = setl::BitsRW<setl::SemanticType<setl::hash("FUSE_FSTRT"), bool>, 1u<<0>;
constexpr unsigned ccFUSE_MEMORY_SIZE = 1;
using ffFUSE_SPIEN = setl::BitsRW<setl::SemanticType<setl::hash("FUSE_SPIEN"), bool>, 1u<<5>;
using rrGIFR = IoRegisterDef<std::uint8_t, 0x3A>;
using rrGIMSK = IoRegisterDef<std::uint8_t, 0x3B>;
constexpr unsigned ccICES1 = 6;
constexpr unsigned ccICF1 = 3;
constexpr unsigned ccICNC1 = 7;
using rrICR1 = IoRegisterDef<std::uint16_t, 0x24>;
using rrICR1H = IoRegisterDef<std::uint8_t, 0x25>;
using rrICR1L = IoRegisterDef<std::uint8_t, 0x24>;
constexpr unsigned ccINT0 = 6;
constexpr unsigned ccINT0_vect_num = 1;
constexpr unsigned ccINT1 = 7;
constexpr unsigned ccINT1_vect_num = 2;
constexpr unsigned ccINTF0 = 6;
constexpr unsigned ccINTF1 = 7;
constexpr unsigned ccISC00 = 0;
constexpr unsigned ccISC01 = 1;
constexpr unsigned ccISC10 = 2;
constexpr unsigned ccISC11 = 3;
constexpr unsigned ccLB_MODE_1 = 0xFF;
constexpr unsigned ccLB_MODE_2 = 0xFE;
constexpr unsigned ccLB_MODE_3 = 0xFC;
constexpr unsigned ccLFUSE_DEFAULT = 0xFF;
constexpr unsigned ccLOCKBITS_DEFAULT = 0xFF;
using rrMCUCR = IoRegisterDef<std::uint8_t, 0x35>;
constexpr unsigned ccOCF1A = 6;
constexpr unsigned ccOCIE1A = 6;
using rrOCR1 = IoRegisterDef<std::uint16_t, 0x2A>;
using rrOCR1A = IoRegisterDef<std::uint16_t, 0x2A>;
using rrOCR1AH = IoRegisterDef<std::uint8_t, 0x2B>;
using rrOCR1AL = IoRegisterDef<std::uint8_t, 0x2A>;
using rrOCR1H = IoRegisterDef<std::uint8_t, 0x2B>;
using rrOCR1L = IoRegisterDef<std::uint8_t, 0x2A>;
constexpr unsigned ccPB0 = 0;
constexpr unsigned ccPB1 = 1;
constexpr unsigned ccPB2 = 2;
constexpr unsigned ccPB3 = 3;
constexpr unsigned ccPB4 = 4;
constexpr unsigned ccPB5 = 5;
constexpr unsigned ccPB6 = 6;
constexpr unsigned ccPB7 = 7;
constexpr unsigned ccPD0 = 0;
constexpr unsigned ccPD1 = 1;
constexpr unsigned ccPD2 = 2;
constexpr unsigned ccPD3 = 3;
constexpr unsigned ccPD4 = 4;
constexpr unsigned ccPD5 = 5;
constexpr unsigned ccPD6 = 6;
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
constexpr unsigned ccPORT0 = 0;
constexpr unsigned ccPORT1 = 1;
constexpr unsigned ccPORT2 = 2;
constexpr unsigned ccPORT3 = 3;
constexpr unsigned ccPORT4 = 4;
constexpr unsigned ccPORT5 = 5;
constexpr unsigned ccPORT6 = 6;
constexpr unsigned ccPORT7 = 7;
using rrPORTB = IoRegisterDef<std::uint8_t, 0x18>;
using rrPORTD = IoRegisterDef<std::uint8_t, 0x12>;
constexpr unsigned ccPWM10 = 0;
constexpr unsigned ccPWM11 = 1;
constexpr unsigned ccRAMEND = 0xDF;
constexpr unsigned ccRAMSTART = 0x60;
constexpr unsigned ccRXB8 = 1;
constexpr unsigned ccRXC = 7;
constexpr unsigned ccRXCIE = 7;
constexpr unsigned ccRXEN = 4;
constexpr unsigned ccSE = 5;
constexpr unsigned ccSIGNATURE_0 = 0x1E;
constexpr unsigned ccSIGNATURE_1 = 0x91;
constexpr unsigned ccSIGNATURE_2 = 0x01;
constexpr unsigned ccSLEEP_MODE_IDLE = 0;
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
using rrTCCR1A = IoRegisterDef<std::uint8_t, 0x2F>;
using rrTCCR1B = IoRegisterDef<std::uint8_t, 0x2E>;
using rrTCNT0 = IoRegisterDef<std::uint8_t, 0x32>;
using rrTCNT1 = IoRegisterDef<std::uint16_t, 0x2C>;
using rrTCNT1H = IoRegisterDef<std::uint8_t, 0x2D>;
using rrTCNT1L = IoRegisterDef<std::uint8_t, 0x2C>;
constexpr unsigned ccTICIE = 3;
constexpr unsigned ccTICIE1 = 3;
using rrTIFR = IoRegisterDef<std::uint8_t, 0x38>;
constexpr unsigned ccTIMER0_OVF0_vect_num = 6;
constexpr unsigned ccTIMER1_CAPT1_vect_num = 3;
constexpr unsigned ccTIMER1_COMP1_vect_num = 4;
constexpr unsigned ccTIMER1_OVF1_vect_num = 5;
using rrTIMSK = IoRegisterDef<std::uint8_t, 0x39>;
constexpr unsigned ccTOIE0 = 1;
constexpr unsigned ccTOIE1 = 7;
constexpr unsigned ccTOV0 = 1;
constexpr unsigned ccTOV1 = 7;
constexpr unsigned ccTXB8 = 0;
constexpr unsigned ccTXC = 6;
constexpr unsigned ccTXCIE = 6;
constexpr unsigned ccTXEN = 3;
constexpr unsigned ccUART_RX_vect_num = 7;
constexpr unsigned ccUART_TX_vect_num = 9;
constexpr unsigned ccUART_UDRE_vect_num = 8;
using rrUBRR = IoRegisterDef<std::uint8_t, 0x09>;
using rrUCR = IoRegisterDef<std::uint8_t, 0x0A>;
using rrUDR = IoRegisterDef<std::uint8_t, 0x0C>;
constexpr unsigned ccUDRE = 5;
constexpr unsigned ccUDRIE = 5;
using rrUSR = IoRegisterDef<std::uint8_t, 0x0B>;
constexpr unsigned ccWDE = 3;
constexpr unsigned ccWDP0 = 0;
constexpr unsigned ccWDP1 = 1;
constexpr unsigned ccWDP2 = 2;
using rrWDTCR = IoRegisterDef<std::uint8_t, 0x21>;
constexpr unsigned ccWDTOE = 4;
constexpr unsigned cc_SFR_ASM_COMPAT = 0;
constexpr unsigned cc_VECTORS_SIZE = 22;
constexpr unsigned cc__USING_MINT8 = 0;


}  // arch_at90s2313
}  // namespace avr
}  // namespace sys
}  // namespace ardo

#endif  // ardo_supplemental_at90s2313__h
