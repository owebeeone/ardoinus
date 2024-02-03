// Generated for arch attiny15.
// This file is generated from the avr-gcc compiler with the mcu
// set to attiny15 from macros specific to avr/io.h.
// Any changes to this file will likely be lost next time this file
// is regenerated. Many any mcu_arch specific changes to 
// ardo_supplemental_attiny15_defs.h.

#ifndef ardo_supplemental_attiny15__h
#define ardo_supplemental_attiny15__h

#include "setlx_cstdint.h"
#include "setl_bit_fields.h"
#include "ardo_avr_bit_io_defs.h"

namespace ardo {
namespace sys {
namespace avr {
namespace arch_attiny15 {

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
using rrADC = IoRegisterDef<std::uint16_t, 0x04>;
using rrADCH = IoRegisterDef<std::uint8_t, 0x05>;
using rrADCL = IoRegisterDef<std::uint8_t, 0x04>;
using rrADCSR = IoRegisterDef<std::uint8_t, 0x06>;
using rrADCW = IoRegisterDef<std::uint16_t, 0x04>;
constexpr unsigned ccADC_vect_num = 8;
constexpr unsigned ccADEN = 7;
constexpr unsigned ccADFR = 5;
constexpr unsigned ccADIE = 3;
constexpr unsigned ccADIF = 4;
constexpr unsigned ccADLAR = 5;
using rrADMUX = IoRegisterDef<std::uint8_t, 0x07>;
constexpr unsigned ccADPS0 = 0;
constexpr unsigned ccADPS1 = 1;
constexpr unsigned ccADPS2 = 2;
constexpr unsigned ccADSC = 6;
constexpr unsigned ccANA_COMP_vect_num = 7;
constexpr unsigned ccBORF = 2;
constexpr unsigned ccCOM1A0 = 4;
constexpr unsigned ccCOM1A1 = 5;
constexpr unsigned ccCS00 = 0;
constexpr unsigned ccCS01 = 1;
constexpr unsigned ccCS02 = 2;
constexpr unsigned ccCS10 = 0;
constexpr unsigned ccCS11 = 1;
constexpr unsigned ccCS12 = 2;
constexpr unsigned ccCS13 = 3;
constexpr unsigned ccCTC1 = 7;
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
constexpr unsigned ccE2END = 0x3F;
constexpr unsigned ccE2PAGESIZE = 2;
using rrEEAR = IoRegisterDef<std::uint8_t, 0x1E>;
using rrEEARL = IoRegisterDef<std::uint8_t, 0x1E>;
using rrEECR = IoRegisterDef<std::uint8_t, 0x1C>;
using rrEEDR = IoRegisterDef<std::uint8_t, 0x1D>;
constexpr unsigned ccEEMWE = 2;
constexpr unsigned ccEERE = 0;
constexpr unsigned ccEERIE = 3;
constexpr unsigned ccEEWE = 1;
constexpr unsigned ccEE_RDY_vect_num = 6;
constexpr unsigned ccEXTRF = 1;
constexpr unsigned ccFLASHEND = 0x3FF;
constexpr unsigned ccFOC1A = 2;
using ffFUSE_BODEN = setl::BitsRW<setl::SemanticType<setl::hash("FUSE_BODEN"), bool>, 1u<<6>;
using ffFUSE_BODLEVEL = setl::BitsRW<setl::SemanticType<setl::hash("FUSE_BODLEVEL"), bool>, 1u<<7>;
using ffFUSE_CKSEL0 = setl::BitsRW<setl::SemanticType<setl::hash("FUSE_CKSEL0"), bool>, 1u<<0>;
using ffFUSE_CKSEL1 = setl::BitsRW<setl::SemanticType<setl::hash("FUSE_CKSEL1"), bool>, 1u<<1>;
constexpr unsigned ccFUSE_MEMORY_SIZE = 1;
using ffFUSE_RSTDISBL = setl::BitsRW<setl::SemanticType<setl::hash("FUSE_RSTDISBL"), bool>, 1u<<4>;
using ffFUSE_SPIEN = setl::BitsRW<setl::SemanticType<setl::hash("FUSE_SPIEN"), bool>, 1u<<5>;
using rrGIFR = IoRegisterDef<std::uint8_t, 0x3A>;
using rrGIMSK = IoRegisterDef<std::uint8_t, 0x3B>;
constexpr unsigned ccGREF = 6;
constexpr unsigned ccINT0 = 6;
constexpr unsigned ccINT0_vect_num = 1;
constexpr unsigned ccINTF0 = 6;
constexpr unsigned ccIO_PINS_vect_num = 2;
constexpr unsigned ccISC00 = 0;
constexpr unsigned ccISC01 = 1;
constexpr unsigned ccLB_MODE_1 = 0xFF;
constexpr unsigned ccLB_MODE_2 = 0xFE;
constexpr unsigned ccLB_MODE_3 = 0xFC;
constexpr unsigned ccLOCKBITS_DEFAULT = 0xFF;
using rrMCUCR = IoRegisterDef<std::uint8_t, 0x35>;
using rrMCUSR = IoRegisterDef<std::uint8_t, 0x34>;
constexpr unsigned ccMUX0 = 0;
constexpr unsigned ccMUX1 = 1;
constexpr unsigned ccMUX2 = 2;
constexpr unsigned ccOCF1 = 6;
constexpr unsigned ccOCIE1 = 6;
using rrOCR1A = IoRegisterDef<std::uint8_t, 0x2E>;
using rrOCR1B = IoRegisterDef<std::uint8_t, 0x2D>;
using rrOSCCAL = IoRegisterDef<std::uint8_t, 0x31>;
constexpr unsigned ccPB0 = 0;
constexpr unsigned ccPB1 = 1;
constexpr unsigned ccPB2 = 2;
constexpr unsigned ccPB3 = 3;
constexpr unsigned ccPB4 = 4;
constexpr unsigned ccPCIE = 5;
constexpr unsigned ccPCIF = 5;
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
constexpr unsigned ccPORF = 0;
constexpr unsigned ccPORT0 = 0;
constexpr unsigned ccPORT1 = 1;
constexpr unsigned ccPORT2 = 2;
constexpr unsigned ccPORT3 = 3;
constexpr unsigned ccPORT4 = 4;
constexpr unsigned ccPORT5 = 5;
constexpr unsigned ccPORT6 = 6;
constexpr unsigned ccPORT7 = 7;
using rrPORTB = IoRegisterDef<std::uint8_t, 0x18>;
constexpr unsigned ccPSR0 = 0;
constexpr unsigned ccPSR1 = 1;
constexpr unsigned ccPUD = 6;
constexpr unsigned ccPWM1 = 6;
constexpr unsigned ccRAMEND = 0x1F;
constexpr unsigned ccRAMSTART = 0x60;
constexpr unsigned ccREFS0 = 6;
constexpr unsigned ccREFS1 = 7;
constexpr unsigned ccSE = 5;
using rrSFIOR = IoRegisterDef<std::uint8_t, 0x2C>;
constexpr unsigned ccSIGNATURE_0 = 0x1E;
constexpr unsigned ccSIGNATURE_1 = 0x90;
constexpr unsigned ccSIGNATURE_2 = 0x06;
constexpr unsigned ccSLEEP_MODE_ADC = 0x01;
constexpr unsigned ccSLEEP_MODE_IDLE = 0x00;
constexpr unsigned ccSLEEP_MODE_PWR_DOWN = 0x02;
constexpr unsigned ccSM0 = 3;
constexpr unsigned ccSM1 = 4;
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
using rrTCCR1 = IoRegisterDef<std::uint8_t, 0x30>;
using rrTCNT0 = IoRegisterDef<std::uint8_t, 0x32>;
using rrTCNT1 = IoRegisterDef<std::uint8_t, 0x2F>;
using rrTIFR = IoRegisterDef<std::uint8_t, 0x38>;
constexpr unsigned ccTIMER0_OVF_vect_num = 5;
constexpr unsigned ccTIMER1_COMP_vect_num = 3;
constexpr unsigned ccTIMER1_OVF_vect_num = 4;
using rrTIMSK = IoRegisterDef<std::uint8_t, 0x39>;
constexpr unsigned ccTOIE0 = 1;
constexpr unsigned ccTOIE1 = 2;
constexpr unsigned ccTOV0 = 1;
constexpr unsigned ccTOV1 = 2;
constexpr unsigned ccWDE = 3;
constexpr unsigned ccWDP0 = 0;
constexpr unsigned ccWDP1 = 1;
constexpr unsigned ccWDP2 = 2;
constexpr unsigned ccWDRF = 3;
using rrWDTCR = IoRegisterDef<std::uint8_t, 0x21>;
constexpr unsigned ccWDTOE = 4;
constexpr unsigned ccXRAMEND = 0x0;
constexpr unsigned cc_SFR_ASM_COMPAT = 0;
constexpr unsigned cc_VECTORS_SIZE = 18;
constexpr unsigned cc__USING_MINT8 = 0;


}  // arch_attiny15
}  // namespace avr
}  // namespace sys
}  // namespace ardo

#endif  // ardo_supplemental_attiny15__h
