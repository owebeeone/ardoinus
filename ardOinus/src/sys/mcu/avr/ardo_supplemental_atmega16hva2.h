// Generated for arch atmega16hva2.
// This file is generated from the avr-gcc compiler with the mcu
// set to atmega16hva2 from macros specific to avr/io.h.
// Any changes to this file will likely be lost next time this file
// is regenerated. Many any mcu_arch specific changes to 
// ardo_supplemental_atmega16hva2_defs.h.

#ifndef ardo_supplemental_atmega16hva2__h
#define ardo_supplemental_atmega16hva2__h

#include "setlx_cstdint.h"
#include "setl_bit_fields.h"
#include "ardo_avr_bit_io_defs.h"

namespace ardo {
namespace sys {
namespace avr {
namespace arch_atmega16hva2 {

constexpr ptrdiff_t cc__SFR_OFFSET = 0x20;

template <typename T, ptrdiff_t w_addr>
using IoRegisterDef = avr::nfp::IoRegisterDef<T, w_addr, cc__SFR_OFFSET>;
using avr::nfp::MemRegisterDef;

constexpr unsigned ccBGCC0 = 0;
constexpr unsigned ccBGCC1 = 1;
constexpr unsigned ccBGCC2 = 2;
constexpr unsigned ccBGCC3 = 3;
constexpr unsigned ccBGCC4 = 4;
constexpr unsigned ccBGCC5 = 5;
using rrBGCCR = MemRegisterDef<std::uint8_t, 0xD0>;
constexpr unsigned ccBGCR0 = 0;
constexpr unsigned ccBGCR1 = 1;
constexpr unsigned ccBGCR2 = 2;
constexpr unsigned ccBGCR3 = 3;
constexpr unsigned ccBGCR4 = 4;
constexpr unsigned ccBGCR5 = 5;
constexpr unsigned ccBGCR6 = 6;
constexpr unsigned ccBGCR7 = 7;
using rrBGCRR = MemRegisterDef<std::uint8_t, 0xD1>;
constexpr unsigned ccBGD = 7;
constexpr unsigned ccBODRF = 2;
using rrBPCHCD = MemRegisterDef<std::uint8_t, 0xF9>;
using rrBPCOCD = MemRegisterDef<std::uint8_t, 0xF7>;
using rrBPCR = MemRegisterDef<std::uint8_t, 0xFD>;
using rrBPDHCD = MemRegisterDef<std::uint8_t, 0xF8>;
using rrBPDOCD = MemRegisterDef<std::uint8_t, 0xF6>;
using rrBPHCTR = MemRegisterDef<std::uint8_t, 0xFC>;
using rrBPIFR = MemRegisterDef<std::uint8_t, 0xF3>;
using rrBPIMSK = MemRegisterDef<std::uint8_t, 0xF2>;
constexpr unsigned ccBPINT_vect_num = 1;
using rrBPOCTR = MemRegisterDef<std::uint8_t, 0xFB>;
constexpr unsigned ccBPPL = 0;
constexpr unsigned ccBPPLE = 1;
using rrBPPLR = MemRegisterDef<std::uint8_t, 0xFE>;
using rrBPSCD = MemRegisterDef<std::uint8_t, 0xF5>;
using rrBPSCTR = MemRegisterDef<std::uint8_t, 0xFA>;
using rrCADAC0 = MemRegisterDef<std::uint8_t, 0xE0>;
constexpr unsigned ccCADAC00 = 0;
constexpr unsigned ccCADAC01 = 1;
constexpr unsigned ccCADAC02 = 2;
constexpr unsigned ccCADAC03 = 3;
constexpr unsigned ccCADAC04 = 4;
constexpr unsigned ccCADAC05 = 5;
constexpr unsigned ccCADAC06 = 6;
constexpr unsigned ccCADAC07 = 7;
constexpr unsigned ccCADAC08 = 0;
constexpr unsigned ccCADAC09 = 1;
using rrCADAC1 = MemRegisterDef<std::uint8_t, 0xE1>;
constexpr unsigned ccCADAC10 = 2;
constexpr unsigned ccCADAC11 = 3;
constexpr unsigned ccCADAC12 = 4;
constexpr unsigned ccCADAC13 = 5;
constexpr unsigned ccCADAC14 = 6;
constexpr unsigned ccCADAC15 = 7;
constexpr unsigned ccCADAC16 = 0;
constexpr unsigned ccCADAC17 = 1;
constexpr unsigned ccCADAC18 = 2;
constexpr unsigned ccCADAC19 = 3;
using rrCADAC2 = MemRegisterDef<std::uint8_t, 0xE2>;
constexpr unsigned ccCADAC20 = 4;
constexpr unsigned ccCADAC21 = 5;
constexpr unsigned ccCADAC22 = 6;
constexpr unsigned ccCADAC23 = 7;
constexpr unsigned ccCADAC24 = 0;
constexpr unsigned ccCADAC25 = 1;
constexpr unsigned ccCADAC26 = 2;
constexpr unsigned ccCADAC27 = 3;
constexpr unsigned ccCADAC28 = 4;
constexpr unsigned ccCADAC29 = 5;
using rrCADAC3 = MemRegisterDef<std::uint8_t, 0xE3>;
constexpr unsigned ccCADAC30 = 6;
constexpr unsigned ccCADAC31 = 7;
constexpr unsigned ccCADACIE = 6;
constexpr unsigned ccCADACIF = 2;
constexpr unsigned ccCADAS0 = 3;
constexpr unsigned ccCADAS1 = 4;
using rrCADCSRA = MemRegisterDef<std::uint8_t, 0xE4>;
using rrCADCSRB = MemRegisterDef<std::uint8_t, 0xE5>;
constexpr unsigned ccCADEN = 7;
using rrCADIC = MemRegisterDef<std::uint16_t, 0xE8>;
using rrCADICH = MemRegisterDef<std::uint8_t, 0xE9>;
constexpr unsigned ccCADICH0 = 0;
constexpr unsigned ccCADICH1 = 1;
constexpr unsigned ccCADICH2 = 2;
constexpr unsigned ccCADICH3 = 3;
constexpr unsigned ccCADICH4 = 4;
constexpr unsigned ccCADICH5 = 5;
constexpr unsigned ccCADICH6 = 6;
constexpr unsigned ccCADICH7 = 7;
constexpr unsigned ccCADICIE = 4;
constexpr unsigned ccCADICIF = 0;
using rrCADICL = MemRegisterDef<std::uint8_t, 0xE8>;
constexpr unsigned ccCADICL0 = 0;
constexpr unsigned ccCADICL1 = 1;
constexpr unsigned ccCADICL2 = 2;
constexpr unsigned ccCADICL3 = 3;
constexpr unsigned ccCADICL4 = 4;
constexpr unsigned ccCADICL5 = 5;
constexpr unsigned ccCADICL6 = 6;
constexpr unsigned ccCADICL7 = 7;
constexpr unsigned ccCADPOL = 6;
using rrCADRC = MemRegisterDef<std::uint8_t, 0xE6>;
constexpr unsigned ccCADRC0 = 0;
constexpr unsigned ccCADRC1 = 1;
constexpr unsigned ccCADRC2 = 2;
constexpr unsigned ccCADRC3 = 3;
constexpr unsigned ccCADRC4 = 4;
constexpr unsigned ccCADRC5 = 5;
constexpr unsigned ccCADRC6 = 6;
constexpr unsigned ccCADRC7 = 7;
constexpr unsigned ccCADRCIE = 5;
constexpr unsigned ccCADRCIF = 1;
constexpr unsigned ccCADSE = 0;
constexpr unsigned ccCADSI0 = 1;
constexpr unsigned ccCADSI1 = 2;
constexpr unsigned ccCADUB = 5;
constexpr unsigned ccCCADC_ACC_vect_num = 20;
constexpr unsigned ccCCADC_CONV_vect_num = 18;
constexpr unsigned ccCCADC_REG_CUR_vect_num = 19;
constexpr unsigned ccCFE = 0;
constexpr unsigned ccCHCD = 0;
constexpr unsigned ccCHCDL0 = 0;
constexpr unsigned ccCHCDL1 = 1;
constexpr unsigned ccCHCDL2 = 2;
constexpr unsigned ccCHCDL3 = 3;
constexpr unsigned ccCHCDL4 = 4;
constexpr unsigned ccCHCDL5 = 5;
constexpr unsigned ccCHCDL6 = 6;
constexpr unsigned ccCHCDL7 = 7;
constexpr unsigned ccCHCIE = 0;
constexpr unsigned ccCHCIF = 0;
constexpr unsigned ccCKOE = 5;
constexpr unsigned ccCLKPCE = 7;
using rrCLKPR = MemRegisterDef<std::uint8_t, 0x61>;
constexpr unsigned ccCLKPS0 = 0;
constexpr unsigned ccCLKPS1 = 1;
constexpr unsigned ccCOCD = 2;
constexpr unsigned ccCOCDL0 = 0;
constexpr unsigned ccCOCDL1 = 1;
constexpr unsigned ccCOCDL2 = 2;
constexpr unsigned ccCOCDL3 = 3;
constexpr unsigned ccCOCDL4 = 4;
constexpr unsigned ccCOCDL5 = 5;
constexpr unsigned ccCOCDL6 = 6;
constexpr unsigned ccCOCDL7 = 7;
constexpr unsigned ccCOCIE = 2;
constexpr unsigned ccCOCIF = 2;
constexpr unsigned ccCPHA = 2;
constexpr unsigned ccCPOL = 3;
constexpr unsigned ccCPS = 2;
constexpr unsigned ccCS00 = 0;
constexpr unsigned ccCS01 = 1;
constexpr unsigned ccCS02 = 2;
constexpr unsigned ccCS10 = 0;
constexpr unsigned ccCS11 = 1;
constexpr unsigned ccCS12 = 2;
constexpr unsigned ccCTPB = 4;
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
constexpr unsigned ccDDB0 = 0;
constexpr unsigned ccDDB1 = 1;
constexpr unsigned ccDDB2 = 2;
constexpr unsigned ccDDB3 = 3;
using rrDDRA = IoRegisterDef<std::uint8_t, 0x01>;
using rrDDRB = IoRegisterDef<std::uint8_t, 0x04>;
constexpr unsigned ccDFE = 1;
constexpr unsigned ccDHCD = 1;
constexpr unsigned ccDHCDL0 = 0;
constexpr unsigned ccDHCDL1 = 1;
constexpr unsigned ccDHCDL2 = 2;
constexpr unsigned ccDHCDL3 = 3;
constexpr unsigned ccDHCDL4 = 4;
constexpr unsigned ccDHCDL5 = 5;
constexpr unsigned ccDHCDL6 = 6;
constexpr unsigned ccDHCDL7 = 7;
constexpr unsigned ccDHCIE = 1;
constexpr unsigned ccDHCIF = 1;
using rrDIDR0 = MemRegisterDef<std::uint8_t, 0x7E>;
constexpr unsigned ccDOCD = 3;
constexpr unsigned ccDOCDL0 = 0;
constexpr unsigned ccDOCDL1 = 1;
constexpr unsigned ccDOCDL2 = 2;
constexpr unsigned ccDOCDL3 = 3;
constexpr unsigned ccDOCDL4 = 4;
constexpr unsigned ccDOCDL5 = 5;
constexpr unsigned ccDOCDL6 = 6;
constexpr unsigned ccDOCDL7 = 7;
constexpr unsigned ccDOCIE = 3;
constexpr unsigned ccDOCIF = 3;
constexpr unsigned ccDORD = 5;
constexpr unsigned ccDUVRD = 3;
using rrDWDR = IoRegisterDef<std::uint8_t, 0x31>;
constexpr unsigned ccE2END = 0xFF;
constexpr unsigned ccE2PAGESIZE = 4;
using rrEEAR = IoRegisterDef<std::uint8_t, 0x21>;
constexpr unsigned ccEEAR0 = 0;
constexpr unsigned ccEEAR1 = 1;
constexpr unsigned ccEEAR2 = 2;
constexpr unsigned ccEEAR3 = 3;
constexpr unsigned ccEEAR4 = 4;
constexpr unsigned ccEEAR5 = 5;
constexpr unsigned ccEEAR6 = 6;
constexpr unsigned ccEEAR7 = 7;
using rrEECR = IoRegisterDef<std::uint8_t, 0x1F>;
using rrEEDR = IoRegisterDef<std::uint8_t, 0x20>;
constexpr unsigned ccEEDR0 = 0;
constexpr unsigned ccEEDR1 = 1;
constexpr unsigned ccEEDR2 = 2;
constexpr unsigned ccEEDR3 = 3;
constexpr unsigned ccEEDR4 = 4;
constexpr unsigned ccEEDR5 = 5;
constexpr unsigned ccEEDR6 = 6;
constexpr unsigned ccEEDR7 = 7;
constexpr unsigned ccEEMPE = 2;
constexpr unsigned ccEEPE = 1;
constexpr unsigned ccEEPM0 = 4;
constexpr unsigned ccEEPM1 = 5;
constexpr unsigned ccEERE = 0;
constexpr unsigned ccEERIE = 3;
constexpr unsigned ccEE_READY_vect_num = 21;
using rrEICRA = MemRegisterDef<std::uint8_t, 0x69>;
using rrEIFR = IoRegisterDef<std::uint8_t, 0x1C>;
using rrEIMSK = IoRegisterDef<std::uint8_t, 0x1D>;
constexpr unsigned ccEXTRF = 1;
constexpr unsigned ccFCAL0 = 0;
constexpr unsigned ccFCAL1 = 1;
constexpr unsigned ccFCAL2 = 2;
constexpr unsigned ccFCAL3 = 3;
constexpr unsigned ccFCAL4 = 4;
constexpr unsigned ccFCAL5 = 5;
constexpr unsigned ccFCAL6 = 6;
constexpr unsigned ccFCAL7 = 7;
using rrFCSR = MemRegisterDef<std::uint8_t, 0xF0>;
constexpr unsigned ccFLASHEND = 0x3FFF;
using rrFOSCCAL = MemRegisterDef<std::uint8_t, 0x66>;
using ffFUSE_COMPMODE = setl::BitsRW<setl::SemanticType<setl::hash("FUSE_COMPMODE"), bool>, 1u<<2>;
using ffFUSE_DWEN = setl::BitsRW<setl::SemanticType<setl::hash("FUSE_DWEN"), bool>, 1u<<4>;
using ffFUSE_EESAVE = setl::BitsRW<setl::SemanticType<setl::hash("FUSE_EESAVE"), bool>, 1u<<6>;
constexpr unsigned ccFUSE_MEMORY_SIZE = 2;
using ffFUSE_OSCSEL0 = setl::BitsRW<setl::SemanticType<setl::hash("FUSE_OSCSEL0"), bool>, 1u<<0>;
using ffFUSE_OSCSEL1 = setl::BitsRW<setl::SemanticType<setl::hash("FUSE_OSCSEL1"), bool>, 1u<<1>;
using ffFUSE_SELFPRGEN = setl::BitsRW<setl::SemanticType<setl::hash("FUSE_SELFPRGEN"), bool>, 1u<<3>;
using ffFUSE_SPIEN = setl::BitsRW<setl::SemanticType<setl::hash("FUSE_SPIEN"), bool>, 1u<<5>;
using ffFUSE_SUT0 = setl::BitsRW<setl::SemanticType<setl::hash("FUSE_SUT0"), bool>, 1u<<0>;
using ffFUSE_SUT1 = setl::BitsRW<setl::SemanticType<setl::hash("FUSE_SUT1"), bool>, 1u<<1>;
using ffFUSE_SUT2 = setl::BitsRW<setl::SemanticType<setl::hash("FUSE_SUT2"), bool>, 1u<<2>;
using ffFUSE_WDTON = setl::BitsRW<setl::SemanticType<setl::hash("FUSE_WDTON"), bool>, 1u<<7>;
using rrGPIOR0 = IoRegisterDef<std::uint8_t, 0x1E>;
constexpr unsigned ccGPIOR00 = 0;
constexpr unsigned ccGPIOR01 = 1;
constexpr unsigned ccGPIOR02 = 2;
constexpr unsigned ccGPIOR03 = 3;
constexpr unsigned ccGPIOR04 = 4;
constexpr unsigned ccGPIOR05 = 5;
constexpr unsigned ccGPIOR06 = 6;
constexpr unsigned ccGPIOR07 = 7;
using rrGPIOR1 = IoRegisterDef<std::uint8_t, 0x2A>;
constexpr unsigned ccGPIOR10 = 0;
constexpr unsigned ccGPIOR11 = 1;
constexpr unsigned ccGPIOR12 = 2;
constexpr unsigned ccGPIOR13 = 3;
constexpr unsigned ccGPIOR14 = 4;
constexpr unsigned ccGPIOR15 = 5;
constexpr unsigned ccGPIOR16 = 6;
constexpr unsigned ccGPIOR17 = 7;
using rrGPIOR2 = IoRegisterDef<std::uint8_t, 0x2B>;
constexpr unsigned ccGPIOR20 = 0;
constexpr unsigned ccGPIOR21 = 1;
constexpr unsigned ccGPIOR22 = 2;
constexpr unsigned ccGPIOR23 = 3;
constexpr unsigned ccGPIOR24 = 4;
constexpr unsigned ccGPIOR25 = 5;
constexpr unsigned ccGPIOR26 = 6;
constexpr unsigned ccGPIOR27 = 7;
using rrGTCCR = IoRegisterDef<std::uint8_t, 0x23>;
constexpr unsigned ccHCPT0 = 0;
constexpr unsigned ccHCPT1 = 1;
constexpr unsigned ccHCPT2 = 2;
constexpr unsigned ccHCPT3 = 3;
constexpr unsigned ccHCPT4 = 4;
constexpr unsigned ccHCPT5 = 5;
constexpr unsigned ccICEN0 = 6;
constexpr unsigned ccICEN1 = 6;
constexpr unsigned ccICES0 = 4;
constexpr unsigned ccICES1 = 4;
constexpr unsigned ccICF0 = 3;
constexpr unsigned ccICF1 = 3;
constexpr unsigned ccICIE0 = 3;
constexpr unsigned ccICIE1 = 3;
constexpr unsigned ccICNC0 = 5;
constexpr unsigned ccICNC1 = 5;
constexpr unsigned ccICS0 = 3;
constexpr unsigned ccICS1 = 3;
constexpr unsigned ccINT0 = 0;
constexpr unsigned ccINT0_vect_num = 3;
constexpr unsigned ccINT1 = 1;
constexpr unsigned ccINT1_vect_num = 4;
constexpr unsigned ccINT2 = 2;
constexpr unsigned ccINT2_vect_num = 5;
constexpr unsigned ccINTF0 = 0;
constexpr unsigned ccINTF1 = 1;
constexpr unsigned ccINTF2 = 2;
constexpr unsigned ccISC00 = 0;
constexpr unsigned ccISC01 = 1;
constexpr unsigned ccISC10 = 2;
constexpr unsigned ccISC11 = 3;
constexpr unsigned ccISC20 = 4;
constexpr unsigned ccISC21 = 5;
constexpr unsigned ccLB_MODE_1 = 0xFF;
constexpr unsigned ccLB_MODE_2 = 0xFE;
constexpr unsigned ccLB_MODE_3 = 0xFC;
constexpr unsigned ccLOCKBITS_DEFAULT = 0xFF;
using rrMCUCR = IoRegisterDef<std::uint8_t, 0x35>;
using rrMCUSR = IoRegisterDef<std::uint8_t, 0x34>;
constexpr unsigned ccMSTR = 4;
constexpr unsigned ccOCDRF = 4;
constexpr unsigned ccOCF0A = 1;
constexpr unsigned ccOCF0B = 2;
constexpr unsigned ccOCF1A = 1;
constexpr unsigned ccOCF1B = 2;
constexpr unsigned ccOCIE0A = 1;
constexpr unsigned ccOCIE0B = 2;
constexpr unsigned ccOCIE1A = 1;
constexpr unsigned ccOCIE1B = 2;
constexpr unsigned ccOCPT0 = 0;
constexpr unsigned ccOCPT1 = 1;
constexpr unsigned ccOCPT2 = 2;
constexpr unsigned ccOCPT3 = 3;
constexpr unsigned ccOCPT4 = 4;
constexpr unsigned ccOCPT5 = 5;
using rrOCR0A = IoRegisterDef<std::uint8_t, 0x28>;
constexpr unsigned ccOCR0A0 = 0;
constexpr unsigned ccOCR0A1 = 1;
constexpr unsigned ccOCR0A2 = 2;
constexpr unsigned ccOCR0A3 = 3;
constexpr unsigned ccOCR0A4 = 4;
constexpr unsigned ccOCR0A5 = 5;
constexpr unsigned ccOCR0A6 = 6;
constexpr unsigned ccOCR0A7 = 7;
using rrOCR0B = IoRegisterDef<std::uint8_t, 0x29>;
constexpr unsigned ccOCR0B0 = 0;
constexpr unsigned ccOCR0B1 = 1;
constexpr unsigned ccOCR0B2 = 2;
constexpr unsigned ccOCR0B3 = 3;
constexpr unsigned ccOCR0B4 = 4;
constexpr unsigned ccOCR0B5 = 5;
constexpr unsigned ccOCR0B6 = 6;
constexpr unsigned ccOCR0B7 = 7;
using rrOCR1A = MemRegisterDef<std::uint8_t, 0x88>;
constexpr unsigned ccOCR1A0 = 0;
constexpr unsigned ccOCR1A1 = 1;
constexpr unsigned ccOCR1A2 = 2;
constexpr unsigned ccOCR1A3 = 3;
constexpr unsigned ccOCR1A4 = 4;
constexpr unsigned ccOCR1A5 = 5;
constexpr unsigned ccOCR1A6 = 6;
constexpr unsigned ccOCR1A7 = 7;
using rrOCR1B = MemRegisterDef<std::uint8_t, 0x89>;
constexpr unsigned ccOCR1B0 = 0;
constexpr unsigned ccOCR1B1 = 1;
constexpr unsigned ccOCR1B2 = 2;
constexpr unsigned ccOCR1B3 = 3;
constexpr unsigned ccOCR1B4 = 4;
constexpr unsigned ccOCR1B5 = 5;
constexpr unsigned ccOCR1B6 = 6;
constexpr unsigned ccOCR1B7 = 7;
using rrOSICSR = IoRegisterDef<std::uint8_t, 0x17>;
constexpr unsigned ccOSIEN = 0;
constexpr unsigned ccOSISEL0 = 4;
constexpr unsigned ccOSIST = 1;
constexpr unsigned ccPA0DID = 0;
constexpr unsigned ccPA0_BIT = 0;
constexpr unsigned ccPA1DID = 1;
constexpr unsigned ccPA1_BIT = 1;
constexpr unsigned ccPA2_BIT = 2;
constexpr unsigned ccPB0_BIT = 0;
constexpr unsigned ccPB1_BIT = 1;
constexpr unsigned ccPB2_BIT = 2;
constexpr unsigned ccPB3_BIT = 3;
constexpr unsigned ccPC0_BIT = 0;
using rrPCICR = MemRegisterDef<std::uint8_t, 0x68>;
constexpr unsigned ccPCIE0 = 0;
constexpr unsigned ccPCIF0 = 0;
using rrPCIFR = IoRegisterDef<std::uint8_t, 0x1B>;
constexpr unsigned ccPCINT0 = 0;
constexpr unsigned ccPCINT0_vect_num = 6;
constexpr unsigned ccPCINT1 = 1;
constexpr unsigned ccPCINT2 = 2;
constexpr unsigned ccPCINT3 = 3;
using rrPCMSK0 = MemRegisterDef<std::uint8_t, 0x6B>;
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
using rrPINA = IoRegisterDef<std::uint8_t, 0x00>;
constexpr unsigned ccPINA0 = 0;
constexpr unsigned ccPINA1 = 1;
using rrPINB = IoRegisterDef<std::uint8_t, 0x03>;
constexpr unsigned ccPINB0 = 0;
constexpr unsigned ccPINB1 = 1;
constexpr unsigned ccPINB2 = 2;
constexpr unsigned ccPINB3 = 3;
using rrPINC = IoRegisterDef<std::uint8_t, 0x06>;
constexpr unsigned ccPINC0 = 0;
constexpr unsigned ccPORF = 0;
constexpr unsigned ccPORT0 = 0;
constexpr unsigned ccPORT1 = 1;
constexpr unsigned ccPORT2 = 2;
constexpr unsigned ccPORT3 = 3;
constexpr unsigned ccPORT4 = 4;
constexpr unsigned ccPORT5 = 5;
constexpr unsigned ccPORT6 = 6;
constexpr unsigned ccPORT7 = 7;
using rrPORTA = IoRegisterDef<std::uint8_t, 0x02>;
constexpr unsigned ccPORTA0 = 0;
constexpr unsigned ccPORTA1 = 1;
using rrPORTB = IoRegisterDef<std::uint8_t, 0x05>;
constexpr unsigned ccPORTB0 = 0;
constexpr unsigned ccPORTB1 = 1;
constexpr unsigned ccPORTB2 = 2;
constexpr unsigned ccPORTB3 = 3;
using rrPORTC = IoRegisterDef<std::uint8_t, 0x08>;
constexpr unsigned ccPORTC0 = 0;
constexpr unsigned ccPRMD = 7;
using rrPRR0 = MemRegisterDef<std::uint8_t, 0x64>;
constexpr unsigned ccPRSPI = 3;
constexpr unsigned ccPRTIM0 = 1;
constexpr unsigned ccPRTIM1 = 2;
constexpr unsigned ccPRVADC = 0;
constexpr unsigned ccPRVRM = 5;
constexpr unsigned ccPSRSYNC = 0;
constexpr unsigned ccPUD = 4;
constexpr unsigned ccPV1_BIT = 1;
constexpr unsigned ccPV2_BIT = 2;
constexpr unsigned ccRAMSIZE = 1024;
constexpr unsigned ccRAMSTART = 0x100;
constexpr unsigned ccRFLB = 3;
using rrROCR = MemRegisterDef<std::uint8_t, 0xC8>;
constexpr unsigned ccROCS = 7;
constexpr unsigned ccROCWIE = 0;
constexpr unsigned ccROCWIF = 1;
constexpr unsigned ccSCD = 4;
constexpr unsigned ccSCDL0 = 0;
constexpr unsigned ccSCDL1 = 1;
constexpr unsigned ccSCDL2 = 2;
constexpr unsigned ccSCDL3 = 3;
constexpr unsigned ccSCDL4 = 4;
constexpr unsigned ccSCDL5 = 5;
constexpr unsigned ccSCDL6 = 6;
constexpr unsigned ccSCDL7 = 7;
constexpr unsigned ccSCIE = 4;
constexpr unsigned ccSCIF = 4;
constexpr unsigned ccSCPT0 = 0;
constexpr unsigned ccSCPT1 = 1;
constexpr unsigned ccSCPT2 = 2;
constexpr unsigned ccSCPT3 = 3;
constexpr unsigned ccSCPT4 = 4;
constexpr unsigned ccSCPT5 = 5;
constexpr unsigned ccSCPT6 = 6;
constexpr unsigned ccSE = 0;
constexpr unsigned ccSIGNATURE_0 = 0x1E;
constexpr unsigned ccSIGNATURE_1 = 0x94;
constexpr unsigned ccSIGNATURE_2 = 0x0E;
constexpr unsigned ccSIGRD = 5;
constexpr unsigned ccSLEEP_MODE_ADC = 0x01;
constexpr unsigned ccSLEEP_MODE_IDLE = 0x00;
constexpr unsigned ccSLEEP_MODE_PWR_OFF = 0x04;
constexpr unsigned ccSLEEP_MODE_PWR_SAVE = 0x03;
constexpr unsigned ccSM0 = 1;
constexpr unsigned ccSM1 = 2;
constexpr unsigned ccSM2 = 3;
using rrSMCR = IoRegisterDef<std::uint8_t, 0x33>;
using rrSP = IoRegisterDef<std::uint16_t, 0x3D>;
using rrSPCR = IoRegisterDef<std::uint8_t, 0x2C>;
using rrSPDR = IoRegisterDef<std::uint8_t, 0x2E>;
constexpr unsigned ccSPDR0 = 0;
constexpr unsigned ccSPDR1 = 1;
constexpr unsigned ccSPDR2 = 2;
constexpr unsigned ccSPDR3 = 3;
constexpr unsigned ccSPDR4 = 4;
constexpr unsigned ccSPDR5 = 5;
constexpr unsigned ccSPDR6 = 6;
constexpr unsigned ccSPDR7 = 7;
constexpr unsigned ccSPE = 6;
using rrSPH = IoRegisterDef<std::uint8_t, 0x3E>;
constexpr unsigned ccSPI2X = 0;
constexpr unsigned ccSPIE = 7;
constexpr unsigned ccSPIF = 7;
constexpr unsigned ccSPI_STC_vect_num = 16;
using rrSPL = IoRegisterDef<std::uint8_t, 0x3D>;
using rrSPMCSR = IoRegisterDef<std::uint8_t, 0x37>;
constexpr unsigned ccSPMEN = 0;
constexpr unsigned ccSPM_PAGESIZE = 128;
constexpr unsigned ccSPR0 = 0;
constexpr unsigned ccSPR1 = 1;
using rrSPSR = IoRegisterDef<std::uint8_t, 0x2D>;
using rrSREG = IoRegisterDef<std::uint8_t, 0x3F>;
constexpr unsigned ccSREG_C = 0;
constexpr unsigned ccSREG_H = 5;
constexpr unsigned ccSREG_I = 7;
constexpr unsigned ccSREG_N = 2;
constexpr unsigned ccSREG_S = 4;
constexpr unsigned ccSREG_T = 6;
constexpr unsigned ccSREG_V = 3;
constexpr unsigned ccSREG_Z = 1;
using rrTCCR0A = IoRegisterDef<std::uint8_t, 0x24>;
using rrTCCR0B = IoRegisterDef<std::uint8_t, 0x25>;
using rrTCCR1A = MemRegisterDef<std::uint8_t, 0x80>;
using rrTCCR1B = MemRegisterDef<std::uint8_t, 0x81>;
using rrTCNT0 = IoRegisterDef<std::uint16_t, 0x26>;
using rrTCNT0H = IoRegisterDef<std::uint8_t, 0x27>;
constexpr unsigned ccTCNT0H0 = 0;
constexpr unsigned ccTCNT0H1 = 1;
constexpr unsigned ccTCNT0H2 = 2;
constexpr unsigned ccTCNT0H3 = 3;
constexpr unsigned ccTCNT0H4 = 4;
constexpr unsigned ccTCNT0H5 = 5;
constexpr unsigned ccTCNT0H6 = 6;
constexpr unsigned ccTCNT0H7 = 7;
using rrTCNT0L = IoRegisterDef<std::uint8_t, 0x26>;
constexpr unsigned ccTCNT0L0 = 0;
constexpr unsigned ccTCNT0L1 = 1;
constexpr unsigned ccTCNT0L2 = 2;
constexpr unsigned ccTCNT0L3 = 3;
constexpr unsigned ccTCNT0L4 = 4;
constexpr unsigned ccTCNT0L5 = 5;
constexpr unsigned ccTCNT0L6 = 6;
constexpr unsigned ccTCNT0L7 = 7;
using rrTCNT1 = MemRegisterDef<std::uint16_t, 0x84>;
using rrTCNT1H = MemRegisterDef<std::uint8_t, 0x85>;
constexpr unsigned ccTCNT1H0 = 0;
constexpr unsigned ccTCNT1H1 = 1;
constexpr unsigned ccTCNT1H2 = 2;
constexpr unsigned ccTCNT1H3 = 3;
constexpr unsigned ccTCNT1H4 = 4;
constexpr unsigned ccTCNT1H5 = 5;
constexpr unsigned ccTCNT1H6 = 6;
constexpr unsigned ccTCNT1H7 = 7;
using rrTCNT1L = MemRegisterDef<std::uint8_t, 0x84>;
constexpr unsigned ccTCNT1L0 = 0;
constexpr unsigned ccTCNT1L1 = 1;
constexpr unsigned ccTCNT1L2 = 2;
constexpr unsigned ccTCNT1L3 = 3;
constexpr unsigned ccTCNT1L4 = 4;
constexpr unsigned ccTCNT1L5 = 5;
constexpr unsigned ccTCNT1L6 = 6;
constexpr unsigned ccTCNT1L7 = 7;
constexpr unsigned ccTCW0 = 7;
constexpr unsigned ccTCW1 = 7;
using rrTIFR0 = IoRegisterDef<std::uint8_t, 0x15>;
using rrTIFR1 = IoRegisterDef<std::uint8_t, 0x16>;
constexpr unsigned ccTIMER0_COMPA_vect_num = 13;
constexpr unsigned ccTIMER0_COMPB_vect_num = 14;
constexpr unsigned ccTIMER0_IC_vect_num = 12;
constexpr unsigned ccTIMER0_OVF_vect_num = 15;
constexpr unsigned ccTIMER1_COMPA_vect_num = 9;
constexpr unsigned ccTIMER1_COMPB_vect_num = 10;
constexpr unsigned ccTIMER1_IC_vect_num = 8;
constexpr unsigned ccTIMER1_OVF_vect_num = 11;
using rrTIMSK0 = MemRegisterDef<std::uint8_t, 0x6E>;
using rrTIMSK1 = MemRegisterDef<std::uint8_t, 0x6F>;
constexpr unsigned ccTOIE0 = 0;
constexpr unsigned ccTOIE1 = 0;
constexpr unsigned ccTOV0 = 0;
constexpr unsigned ccTOV1 = 0;
constexpr unsigned ccTSM = 7;
using rrVADC = MemRegisterDef<std::uint16_t, 0x78>;
constexpr unsigned ccVADC0 = 0;
constexpr unsigned ccVADC1 = 1;
constexpr unsigned ccVADC10 = 2;
constexpr unsigned ccVADC11 = 3;
constexpr unsigned ccVADC2 = 2;
constexpr unsigned ccVADC3 = 3;
constexpr unsigned ccVADC4 = 4;
constexpr unsigned ccVADC5 = 5;
constexpr unsigned ccVADC6 = 6;
constexpr unsigned ccVADC7 = 7;
constexpr unsigned ccVADC8 = 0;
constexpr unsigned ccVADC9 = 1;
constexpr unsigned ccVADCCIE = 0;
constexpr unsigned ccVADCCIF = 1;
using rrVADCH = MemRegisterDef<std::uint8_t, 0x79>;
using rrVADCL = MemRegisterDef<std::uint8_t, 0x78>;
using rrVADCSR = MemRegisterDef<std::uint8_t, 0x7A>;
constexpr unsigned ccVADC_vect_num = 17;
constexpr unsigned ccVADEN = 3;
using rrVADMUX = MemRegisterDef<std::uint8_t, 0x7C>;
constexpr unsigned ccVADMUX0 = 0;
constexpr unsigned ccVADMUX1 = 1;
constexpr unsigned ccVADMUX2 = 2;
constexpr unsigned ccVADMUX3 = 3;
constexpr unsigned ccVADSC = 2;
constexpr unsigned ccVREGMON_vect_num = 2;
constexpr unsigned ccWCOL = 6;
constexpr unsigned ccWDCE = 4;
constexpr unsigned ccWDE = 3;
constexpr unsigned ccWDIE = 6;
constexpr unsigned ccWDIF = 7;
constexpr unsigned ccWDP0 = 0;
constexpr unsigned ccWDP1 = 1;
constexpr unsigned ccWDP2 = 2;
constexpr unsigned ccWDP3 = 5;
constexpr unsigned ccWDRF = 3;
using rrWDTCSR = MemRegisterDef<std::uint8_t, 0x60>;
constexpr unsigned ccWDT_vect_num = 7;
constexpr unsigned ccWGM00 = 0;
constexpr unsigned ccWGM10 = 0;
constexpr unsigned cc_HAVE_AVR_STACK_POINTER_HI = 1;
constexpr unsigned cc_SFR_ASM_COMPAT = 0;
constexpr unsigned cc_VECTORS_SIZE = 22;
constexpr unsigned cc_VECTOR_SIZE = 4;
constexpr unsigned cc__USING_MINT8 = 0;


}  // arch_atmega16hva2
}  // namespace avr
}  // namespace sys
}  // namespace ardo

#endif  // ardo_supplemental_atmega16hva2__h
