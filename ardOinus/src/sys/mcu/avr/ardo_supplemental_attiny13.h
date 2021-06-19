// Generated for arch attiny13.
// This file is generated from the avr-gcc compiler with the mcu
// set to attiny13 from macros specific to avr/io.h.
// Any changes to this file will likely be lost next time this file
// is regenerated. Many any mcu_arch specific changes to 
// ardo_supplemental_attiny13_defs.h.

#ifndef ardo_supplemental_attiny13__h
#define ardo_supplemental_attiny13__h

#include "setlx_cstdint.h"
#include "setl_bit_fields.h"
#include "ardo_avr_bit_io_defs.h"

namespace ardo {
namespace sys {
namespace avr {
namespace arch_attiny13 {

constexpr ptrdiff_t cc__SFR_OFFSET = 0x20;

template <typename T, ptrdiff_t w_addr>
using IoRegisterDef = avr::nfp::IoRegisterDef<T, w_addr, cc__SFR_OFFSET>;
using avr::nfp::MemRegisterDef;

constexpr unsigned ccACBG = 6;
constexpr unsigned ccACD = 7;
constexpr unsigned ccACI = 4;
constexpr unsigned ccACIE = 3;
constexpr unsigned ccACIS0 = 0;
constexpr unsigned ccACIS1 = 1;
constexpr unsigned ccACME = 6;
constexpr unsigned ccACO = 5;
using rrACSR = IoRegisterDef<std::uint8_t, 0x08>;
constexpr unsigned ccADATE = 5;
using rrADC = IoRegisterDef<std::uint16_t, 0x04>;
constexpr unsigned ccADC0D = 5;
constexpr unsigned ccADC1D = 2;
constexpr unsigned ccADC2D = 4;
constexpr unsigned ccADC3D = 3;
using rrADCH = IoRegisterDef<std::uint8_t, 0x05>;
using rrADCL = IoRegisterDef<std::uint8_t, 0x04>;
using rrADCSRA = IoRegisterDef<std::uint8_t, 0x06>;
using rrADCSRB = IoRegisterDef<std::uint8_t, 0x03>;
using rrADCW = IoRegisterDef<std::uint16_t, 0x04>;
constexpr unsigned ccADC_vect_num = 9;
constexpr unsigned ccADEN = 7;
constexpr unsigned ccADIE = 3;
constexpr unsigned ccADIF = 4;
constexpr unsigned ccADLAR = 5;
using rrADMUX = IoRegisterDef<std::uint8_t, 0x07>;
constexpr unsigned ccADPS0 = 0;
constexpr unsigned ccADPS1 = 1;
constexpr unsigned ccADPS2 = 2;
constexpr unsigned ccADSC = 6;
constexpr unsigned ccADTS0 = 0;
constexpr unsigned ccADTS1 = 1;
constexpr unsigned ccADTS2 = 2;
constexpr unsigned ccAIN0D = 0;
constexpr unsigned ccAIN1D = 1;
constexpr unsigned ccANA_COMP_vect_num = 5;
constexpr unsigned ccBORF = 2;
constexpr unsigned ccCLKPCE = 7;
using rrCLKPR = IoRegisterDef<std::uint8_t, 0x26>;
constexpr unsigned ccCLKPS0 = 0;
constexpr unsigned ccCLKPS1 = 1;
constexpr unsigned ccCLKPS2 = 2;
constexpr unsigned ccCLKPS3 = 3;
constexpr unsigned ccCOM0A0 = 6;
constexpr unsigned ccCOM0A1 = 7;
constexpr unsigned ccCOM0B0 = 4;
constexpr unsigned ccCOM0B1 = 5;
constexpr unsigned ccCS00 = 0;
constexpr unsigned ccCS01 = 1;
constexpr unsigned ccCS02 = 2;
constexpr unsigned ccCTPB = 4;
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
using rrDDRB = IoRegisterDef<std::uint8_t, 0x17>;
using rrDIDR0 = IoRegisterDef<std::uint8_t, 0x14>;
using rrDWDR = IoRegisterDef<std::uint8_t, 0x2e>;
constexpr unsigned ccE2END = 0x3F;
constexpr unsigned ccE2PAGESIZE = 4;
using rrEEAR = IoRegisterDef<std::uint8_t, 0x1E>;
using rrEEARL = IoRegisterDef<std::uint8_t, 0x1E>;
using rrEECR = IoRegisterDef<std::uint8_t, 0x1C>;
using rrEEDR = IoRegisterDef<std::uint8_t, 0x1D>;
constexpr unsigned ccEEMPE = 2;
constexpr unsigned ccEEPE = 1;
constexpr unsigned ccEEPM0 = 4;
constexpr unsigned ccEEPM1 = 5;
constexpr unsigned ccEERE = 0;
constexpr unsigned ccEERIE = 3;
constexpr unsigned ccEE_RDY_vect_num = 4;
constexpr unsigned ccEXTRF = 1;
constexpr unsigned ccFLASHEND = 0x3FF;
constexpr unsigned ccFOC0A = 7;
constexpr unsigned ccFOC0B = 6;
using ffFUSE_BODLEVEL0 = setl::BitsRW<setl::SemanticType<setl::hash("FUSE_BODLEVEL0"), bool>, 1u<<1>;
using ffFUSE_BODLEVEL1 = setl::BitsRW<setl::SemanticType<setl::hash("FUSE_BODLEVEL1"), bool>, 1u<<2>;
using ffFUSE_CKDIV8 = setl::BitsRW<setl::SemanticType<setl::hash("FUSE_CKDIV8"), bool>, 1u<<4>;
using ffFUSE_CKSEL0 = setl::BitsRW<setl::SemanticType<setl::hash("FUSE_CKSEL0"), bool>, 1u<<0>;
using ffFUSE_CKSEL1 = setl::BitsRW<setl::SemanticType<setl::hash("FUSE_CKSEL1"), bool>, 1u<<1>;
using ffFUSE_DWEN = setl::BitsRW<setl::SemanticType<setl::hash("FUSE_DWEN"), bool>, 1u<<3>;
using ffFUSE_EESAVE = setl::BitsRW<setl::SemanticType<setl::hash("FUSE_EESAVE"), bool>, 1u<<6>;
constexpr unsigned ccFUSE_MEMORY_SIZE = 2;
using ffFUSE_RSTDISBL = setl::BitsRW<setl::SemanticType<setl::hash("FUSE_RSTDISBL"), bool>, 1u<<0>;
using ffFUSE_SPIEN = setl::BitsRW<setl::SemanticType<setl::hash("FUSE_SPIEN"), bool>, 1u<<7>;
using ffFUSE_SPMEN = setl::BitsRW<setl::SemanticType<setl::hash("FUSE_SPMEN"), bool>, 1u<<4>;
using ffFUSE_SUT0 = setl::BitsRW<setl::SemanticType<setl::hash("FUSE_SUT0"), bool>, 1u<<2>;
using ffFUSE_SUT1 = setl::BitsRW<setl::SemanticType<setl::hash("FUSE_SUT1"), bool>, 1u<<3>;
using ffFUSE_WDTON = setl::BitsRW<setl::SemanticType<setl::hash("FUSE_WDTON"), bool>, 1u<<5>;
using rrGIFR = IoRegisterDef<std::uint8_t, 0x3a>;
using rrGIMSK = IoRegisterDef<std::uint8_t, 0x3b>;
using rrGTCCR = IoRegisterDef<std::uint8_t, 0x28>;
constexpr unsigned ccHFUSE_DEFAULT = 0xFF;
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
constexpr unsigned ccMUX0 = 0;
constexpr unsigned ccMUX1 = 1;
constexpr unsigned ccOCF0A = 2;
constexpr unsigned ccOCF0B = 3;
constexpr unsigned ccOCIE0A = 2;
constexpr unsigned ccOCIE0B = 3;
using rrOCR0A = IoRegisterDef<std::uint8_t, 0x36>;
using rrOCR0B = IoRegisterDef<std::uint8_t, 0x29>;
using rrOSCCAL = IoRegisterDef<std::uint8_t, 0x31>;
constexpr unsigned ccPB0 = 0;
constexpr unsigned ccPB1 = 1;
constexpr unsigned ccPB2 = 2;
constexpr unsigned ccPB3 = 3;
constexpr unsigned ccPB4 = 4;
constexpr unsigned ccPB5 = 5;
constexpr unsigned ccPCIE = 5;
constexpr unsigned ccPCIF = 5;
constexpr unsigned ccPCINT0 = 0;
constexpr unsigned ccPCINT0_vect_num = 2;
constexpr unsigned ccPCINT1 = 1;
constexpr unsigned ccPCINT2 = 2;
constexpr unsigned ccPCINT3 = 3;
constexpr unsigned ccPCINT4 = 4;
constexpr unsigned ccPCINT5 = 5;
using rrPCMSK = IoRegisterDef<std::uint8_t, 0x15>;
constexpr unsigned ccPGERS = 1;
constexpr unsigned ccPGWRT = 2;
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
constexpr unsigned ccPSR10 = 0;
constexpr unsigned ccPUD = 6;
constexpr unsigned ccRAMEND = 0x9F;
constexpr unsigned ccRAMSTART = 0x60;
constexpr unsigned ccREFS0 = 6;
constexpr unsigned ccRFLB = 3;
constexpr unsigned ccSE = 5;
constexpr unsigned ccSELFPRGEN = 0;
constexpr unsigned ccSIGNATURE_0 = 0x1E;
constexpr unsigned ccSIGNATURE_1 = 0x90;
constexpr unsigned ccSIGNATURE_2 = 0x07;
constexpr unsigned ccSLEEP_MODE_ADC = 0x01;
constexpr unsigned ccSLEEP_MODE_IDLE = 0x00;
constexpr unsigned ccSLEEP_MODE_PWR_DOWN = 0x02;
constexpr unsigned ccSM0 = 3;
constexpr unsigned ccSM1 = 4;
using rrSP = IoRegisterDef<std::uint8_t, 0x3D>;
using rrSPL = IoRegisterDef<std::uint8_t, 0x3D>;
using rrSPMCSR = IoRegisterDef<std::uint8_t, 0x37>;
constexpr unsigned ccSPMEN = 0;
constexpr unsigned ccSPM_PAGESIZE = 32;
using rrSREG = IoRegisterDef<std::uint8_t, 0x3F>;
constexpr unsigned ccSREG_C = 0;
constexpr unsigned ccSREG_H = 5;
constexpr unsigned ccSREG_I = 7;
constexpr unsigned ccSREG_N = 2;
constexpr unsigned ccSREG_S = 4;
constexpr unsigned ccSREG_T = 6;
constexpr unsigned ccSREG_V = 3;
constexpr unsigned ccSREG_Z = 1;
using rrTCCR0A = IoRegisterDef<std::uint8_t, 0x2f>;
using rrTCCR0B = IoRegisterDef<std::uint8_t, 0x33>;
using rrTCNT0 = IoRegisterDef<std::uint8_t, 0x32>;
using rrTIFR0 = IoRegisterDef<std::uint8_t, 0x38>;
constexpr unsigned ccTIM0_COMPA_vect_num = 6;
constexpr unsigned ccTIM0_COMPB_vect_num = 7;
constexpr unsigned ccTIM0_OVF_vect_num = 3;
using rrTIMSK0 = IoRegisterDef<std::uint8_t, 0x39>;
constexpr unsigned ccTOIE0 = 1;
constexpr unsigned ccTOV0 = 1;
constexpr unsigned ccTSM = 7;
constexpr unsigned ccWDCE = 4;
constexpr unsigned ccWDE = 3;
constexpr unsigned ccWDP0 = 0;
constexpr unsigned ccWDP1 = 1;
constexpr unsigned ccWDP2 = 2;
constexpr unsigned ccWDP3 = 5;
constexpr unsigned ccWDRF = 3;
using rrWDTCR = IoRegisterDef<std::uint8_t, 0x21>;
constexpr unsigned ccWDTIE = 6;
constexpr unsigned ccWDTIF = 7;
constexpr unsigned ccWDT_vect_num = 8;
constexpr unsigned ccWGM00 = 0;
constexpr unsigned ccWGM01 = 1;
constexpr unsigned ccWGM02 = 3;
constexpr unsigned cc_SFR_ASM_COMPAT = 0;
constexpr unsigned cc_VECTORS_SIZE = 20;
constexpr unsigned cc__USING_MINT8 = 0;


}  // arch_attiny13
}  // namespace avr
}  // namespace sys
}  // namespace ardo

#endif  // ardo_supplemental_attiny13__h
