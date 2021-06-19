// Generated for arch at90s4433.
// This file is generated from the avr-gcc compiler with the mcu
// set to at90s4433 from macros specific to avr/io.h.
// Any changes to this file will likely be lost next time this file
// is regenerated. Many any mcu_arch specific changes to 
// ardo_supplemental_at90s4433_defs.h.

#ifndef ardo_supplemental_at90s4433__h
#define ardo_supplemental_at90s4433__h

#include "setlx_cstdint.h"
#include "setl_bit_fields.h"
#include "ardo_avr_bit_io_defs.h"

namespace ardo {
namespace sys {
namespace avr {
namespace arch_at90s4433 {

constexpr ptrdiff_t cc__SFR_OFFSET = 0x20;

template <typename T, ptrdiff_t w_addr>
using IoRegisterDef = avr::nfp::IoRegisterDef<T, w_addr, cc__SFR_OFFSET>;
using avr::nfp::MemRegisterDef;

constexpr unsigned ccACD = 7;
constexpr unsigned ccACDBG = 6;
constexpr unsigned ccACI = 4;
constexpr unsigned ccACIC = 2;
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
constexpr unsigned ccADC_vect_num = 11;
constexpr unsigned ccADEN = 7;
constexpr unsigned ccADFR = 5;
constexpr unsigned ccADIE = 3;
constexpr unsigned ccADIF = 4;
using rrADMUX = IoRegisterDef<std::uint8_t, 0x07>;
constexpr unsigned ccADPS0 = 0;
constexpr unsigned ccADPS1 = 1;
constexpr unsigned ccADPS2 = 2;
constexpr unsigned ccADSC = 6;
constexpr unsigned ccAINBG = 6;
constexpr unsigned ccANA_COMP_vect_num = 13;
constexpr unsigned ccBORF = 2;
constexpr unsigned ccCHR9 = 2;
constexpr unsigned ccCOM10 = 6;
constexpr unsigned ccCOM11 = 7;
constexpr unsigned ccCPHA = 2;
constexpr unsigned ccCPOL = 3;
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
constexpr unsigned ccDDC0 = 0;
constexpr unsigned ccDDC1 = 1;
constexpr unsigned ccDDC2 = 2;
constexpr unsigned ccDDC3 = 3;
constexpr unsigned ccDDC4 = 4;
constexpr unsigned ccDDC5 = 5;
constexpr unsigned ccDDD0 = 0;
constexpr unsigned ccDDD1 = 1;
constexpr unsigned ccDDD2 = 2;
constexpr unsigned ccDDD3 = 3;
constexpr unsigned ccDDD4 = 4;
constexpr unsigned ccDDD5 = 5;
constexpr unsigned ccDDD6 = 6;
constexpr unsigned ccDDD7 = 7;
using rrDDRB = IoRegisterDef<std::uint8_t, 0x17>;
using rrDDRC = IoRegisterDef<std::uint8_t, 0x14>;
using rrDDRD = IoRegisterDef<std::uint8_t, 0x11>;
constexpr unsigned ccDOR = 3;
constexpr unsigned ccDORD = 5;
constexpr unsigned ccE2END = 0xFF;
constexpr unsigned ccE2PAGESIZE = 0;
using rrEEAR = IoRegisterDef<std::uint8_t, 0x1E>;
using rrEEARL = IoRegisterDef<std::uint8_t, 0x1E>;
using rrEECR = IoRegisterDef<std::uint8_t, 0x1C>;
using rrEEDR = IoRegisterDef<std::uint8_t, 0x1D>;
constexpr unsigned ccEEMWE = 2;
constexpr unsigned ccEERE = 0;
constexpr unsigned ccEERIE = 3;
constexpr unsigned ccEEWE = 1;
constexpr unsigned ccEE_RDY_vect_num = 12;
constexpr unsigned ccEXTRF = 1;
constexpr unsigned ccFE = 4;
constexpr unsigned ccFLASHEND = 0xFFF;
using ffFUSE_BODEN = setl::BitsRW<setl::SemanticType<setl::hash("FUSE_BODEN"), bool>, 1u<<3>;
using ffFUSE_BODLEVEL = setl::BitsRW<setl::SemanticType<setl::hash("FUSE_BODLEVEL"), bool>, 1u<<4>;
using ffFUSE_CKSEL0 = setl::BitsRW<setl::SemanticType<setl::hash("FUSE_CKSEL0"), bool>, 1u<<0>;
using ffFUSE_CKSEL1 = setl::BitsRW<setl::SemanticType<setl::hash("FUSE_CKSEL1"), bool>, 1u<<1>;
using ffFUSE_CKSEL2 = setl::BitsRW<setl::SemanticType<setl::hash("FUSE_CKSEL2"), bool>, 1u<<2>;
constexpr unsigned ccFUSE_MEMORY_SIZE = 1;
using ffFUSE_SPIEN = setl::BitsRW<setl::SemanticType<setl::hash("FUSE_SPIEN"), bool>, 1u<<5>;
using rrGIFR = IoRegisterDef<std::uint8_t, 0x3A>;
using rrGIMSK = IoRegisterDef<std::uint8_t, 0x3B>;
constexpr unsigned ccICES1 = 6;
constexpr unsigned ccICF1 = 3;
constexpr unsigned ccICNC1 = 7;
using rrICR1 = IoRegisterDef<std::uint16_t, 0x26>;
using rrICR1H = IoRegisterDef<std::uint8_t, 0x27>;
using rrICR1L = IoRegisterDef<std::uint8_t, 0x26>;
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
using rrMCUSR = IoRegisterDef<std::uint8_t, 0x34>;
constexpr unsigned ccMPCM = 0;
constexpr unsigned ccMSTR = 4;
constexpr unsigned ccMUX0 = 0;
constexpr unsigned ccMUX1 = 1;
constexpr unsigned ccMUX2 = 2;
constexpr unsigned ccOCF1 = 6;
constexpr unsigned ccOCIE1 = 6;
using rrOCR1 = IoRegisterDef<std::uint16_t, 0x2A>;
using rrOCR1H = IoRegisterDef<std::uint8_t, 0x2B>;
using rrOCR1L = IoRegisterDef<std::uint8_t, 0x2A>;
constexpr unsigned ccPB0 = 0;
constexpr unsigned ccPB1 = 1;
constexpr unsigned ccPB2 = 2;
constexpr unsigned ccPB3 = 3;
constexpr unsigned ccPB4 = 4;
constexpr unsigned ccPB5 = 5;
constexpr unsigned ccPC0 = 0;
constexpr unsigned ccPC1 = 1;
constexpr unsigned ccPC2 = 2;
constexpr unsigned ccPC3 = 3;
constexpr unsigned ccPC4 = 4;
constexpr unsigned ccPC5 = 5;
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
using rrPINB = IoRegisterDef<std::uint8_t, 0x16>;
constexpr unsigned ccPINB0 = 0;
constexpr unsigned ccPINB1 = 1;
constexpr unsigned ccPINB2 = 2;
constexpr unsigned ccPINB3 = 3;
constexpr unsigned ccPINB4 = 4;
constexpr unsigned ccPINB5 = 5;
using rrPINC = IoRegisterDef<std::uint8_t, 0x13>;
constexpr unsigned ccPINC0 = 0;
constexpr unsigned ccPINC1 = 1;
constexpr unsigned ccPINC2 = 2;
constexpr unsigned ccPINC3 = 3;
constexpr unsigned ccPINC4 = 4;
constexpr unsigned ccPINC5 = 5;
using rrPIND = IoRegisterDef<std::uint8_t, 0x10>;
constexpr unsigned ccPIND0 = 0;
constexpr unsigned ccPIND1 = 1;
constexpr unsigned ccPIND2 = 2;
constexpr unsigned ccPIND3 = 3;
constexpr unsigned ccPIND4 = 4;
constexpr unsigned ccPIND5 = 5;
constexpr unsigned ccPIND6 = 6;
constexpr unsigned ccPIND7 = 7;
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
using rrPORTC = IoRegisterDef<std::uint8_t, 0x15>;
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
constexpr unsigned ccSIGNATURE_1 = 0x92;
constexpr unsigned ccSIGNATURE_2 = 0x03;
constexpr unsigned ccSLEEP_MODE_IDLE = 0;
constexpr unsigned ccSM = 4;
using rrSP = IoRegisterDef<std::uint8_t, 0x3D>;
using rrSPCR = IoRegisterDef<std::uint8_t, 0x0D>;
using rrSPDR = IoRegisterDef<std::uint8_t, 0x0F>;
constexpr unsigned ccSPE = 6;
constexpr unsigned ccSPIE = 7;
constexpr unsigned ccSPIF = 7;
constexpr unsigned ccSPI_STC_vect_num = 7;
using rrSPL = IoRegisterDef<std::uint8_t, 0x3D>;
constexpr unsigned ccSPR0 = 0;
constexpr unsigned ccSPR1 = 1;
using rrSPSR = IoRegisterDef<std::uint8_t, 0x0E>;
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
constexpr unsigned ccTICIE1 = 3;
using rrTIFR = IoRegisterDef<std::uint8_t, 0x38>;
constexpr unsigned ccTIMER0_OVF_vect_num = 6;
constexpr unsigned ccTIMER1_CAPT_vect_num = 3;
constexpr unsigned ccTIMER1_COMP_vect_num = 4;
constexpr unsigned ccTIMER1_OVF_vect_num = 5;
using rrTIMSK = IoRegisterDef<std::uint8_t, 0x39>;
constexpr unsigned ccTOIE0 = 1;
constexpr unsigned ccTOIE1 = 7;
constexpr unsigned ccTOV0 = 1;
constexpr unsigned ccTOV1 = 7;
constexpr unsigned ccTXB8 = 0;
constexpr unsigned ccTXC = 6;
constexpr unsigned ccTXCIE = 6;
constexpr unsigned ccTXEN = 3;
constexpr unsigned ccUART_RX_vect_num = 8;
constexpr unsigned ccUART_TX_vect_num = 10;
constexpr unsigned ccUART_UDRE_vect_num = 9;
using rrUBRR = IoRegisterDef<std::uint8_t, 0x09>;
using rrUBRRH = IoRegisterDef<std::uint8_t, 0x03>;
using rrUCSRA = IoRegisterDef<std::uint8_t, 0x0B>;
using rrUCSRB = IoRegisterDef<std::uint8_t, 0x0A>;
using rrUDR = IoRegisterDef<std::uint8_t, 0x0C>;
constexpr unsigned ccUDRE = 5;
constexpr unsigned ccUDRIE = 5;
constexpr unsigned ccWCOL = 6;
constexpr unsigned ccWDE = 3;
constexpr unsigned ccWDP0 = 0;
constexpr unsigned ccWDP1 = 1;
constexpr unsigned ccWDP2 = 2;
constexpr unsigned ccWDRF = 3;
using rrWDTCR = IoRegisterDef<std::uint8_t, 0x21>;
constexpr unsigned ccWDTOE = 4;
constexpr unsigned cc_SFR_ASM_COMPAT = 0;
constexpr unsigned cc_VECTORS_SIZE = 28;
constexpr unsigned cc__USING_MINT8 = 0;


}  // arch_at90s4433
}  // namespace avr
}  // namespace sys
}  // namespace ardo

#endif  // ardo_supplemental_at90s4433__h
