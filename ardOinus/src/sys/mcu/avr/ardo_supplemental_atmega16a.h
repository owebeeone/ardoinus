// Generated for arch atmega16a.
// This file is generated from the avr-gcc compiler with the mcu
// set to atmega16a from macros specific to avr/io.h.
// Any changes to this file will likely be lost next time this file
// is regenerated. Many any mcu_arch specific changes to 
// ardo_supplemental_atmega16a_defs.h.

#ifndef ardo_supplemental_atmega16a__h
#define ardo_supplemental_atmega16a__h

#include "setlx_cstdint.h"
#include "setl_bit_fields.h"
#include "ardo_avr_bit_io_defs.h"

namespace ardo {
namespace sys {
namespace avr {
namespace arch_atmega16a {

constexpr ptrdiff_t cc__SFR_OFFSET = 0x20;

template <typename T, ptrdiff_t w_addr>
using IoRegisterDef = avr::nfp::IoRegisterDef<T, w_addr, cc__SFR_OFFSET>;
using avr::nfp::MemRegisterDef;

constexpr unsigned ccACBG = 6;
constexpr unsigned ccACD = 7;
constexpr unsigned ccACI = 4;
constexpr unsigned ccACIC = 2;
constexpr unsigned ccACIE = 3;
constexpr unsigned ccACIS0 = 0;
constexpr unsigned ccACIS1 = 1;
constexpr unsigned ccACME = 3;
constexpr unsigned ccACO = 5;
using rrACSR = IoRegisterDef<std::uint8_t, 0x08>;
constexpr unsigned ccADATE = 5;
using rrADC = IoRegisterDef<std::uint16_t, 0x04>;
constexpr unsigned ccADC0_BIT = 0;
constexpr unsigned ccADC1_BIT = 1;
constexpr unsigned ccADC2_BIT = 2;
constexpr unsigned ccADC3_BIT = 3;
constexpr unsigned ccADC4_BIT = 4;
constexpr unsigned ccADC6_BIT = 6;
constexpr unsigned ccADC7_BIT = 7;
using rrADCH = IoRegisterDef<std::uint8_t, 0x05>;
constexpr unsigned ccADCH0 = 0;
constexpr unsigned ccADCH1 = 1;
constexpr unsigned ccADCH2 = 2;
constexpr unsigned ccADCH3 = 3;
constexpr unsigned ccADCH4 = 4;
constexpr unsigned ccADCH5 = 5;
constexpr unsigned ccADCH6 = 6;
constexpr unsigned ccADCH7 = 7;
using rrADCL = IoRegisterDef<std::uint8_t, 0x04>;
constexpr unsigned ccADCL0 = 0;
constexpr unsigned ccADCL1 = 1;
constexpr unsigned ccADCL2 = 2;
constexpr unsigned ccADCL3 = 3;
constexpr unsigned ccADCL4 = 4;
constexpr unsigned ccADCL5 = 5;
constexpr unsigned ccADCL6 = 6;
constexpr unsigned ccADCL7 = 7;
using rrADCSRA = IoRegisterDef<std::uint8_t, 0x06>;
using rrADCW = IoRegisterDef<std::uint16_t, 0x04>;
constexpr unsigned ccADC_vect_num = 14;
constexpr unsigned ccADEN = 7;
constexpr unsigned ccADIE = 3;
constexpr unsigned ccADIF = 4;
constexpr unsigned ccADLAR = 5;
using rrADMUX = IoRegisterDef<std::uint8_t, 0x07>;
constexpr unsigned ccADPS0 = 0;
constexpr unsigned ccADPS1 = 1;
constexpr unsigned ccADPS2 = 2;
constexpr unsigned ccADSC = 6;
constexpr unsigned ccADTS0 = 5;
constexpr unsigned ccADTS1 = 6;
constexpr unsigned ccADTS2 = 7;
constexpr unsigned ccADc5_BIT = 5;
constexpr unsigned ccAIN0_BIT = 2;
constexpr unsigned ccAIN1_BIT = 3;
constexpr unsigned ccANA_COMP_vect_num = 16;
constexpr unsigned ccAS2 = 3;
using rrASSR = IoRegisterDef<std::uint8_t, 0x22>;
constexpr unsigned ccBLB0_MODE_1 = 0xFF;
constexpr unsigned ccBLB0_MODE_2 = 0xFB;
constexpr unsigned ccBLB0_MODE_3 = 0xF3;
constexpr unsigned ccBLB0_MODE_4 = 0xF7;
constexpr unsigned ccBLB1_MODE_1 = 0xFF;
constexpr unsigned ccBLB1_MODE_2 = 0xEF;
constexpr unsigned ccBLB1_MODE_3 = 0xCF;
constexpr unsigned ccBLB1_MODE_4 = 0xDF;
constexpr unsigned ccBLBSET = 3;
constexpr unsigned ccBORF = 2;
constexpr unsigned ccCAL0 = 0;
constexpr unsigned ccCAL1 = 1;
constexpr unsigned ccCAL2 = 2;
constexpr unsigned ccCAL3 = 3;
constexpr unsigned ccCAL4 = 4;
constexpr unsigned ccCAL5 = 5;
constexpr unsigned ccCAL6 = 6;
constexpr unsigned ccCAL7 = 7;
constexpr unsigned ccCOM00 = 4;
constexpr unsigned ccCOM01 = 5;
constexpr unsigned ccCOM1A0 = 6;
constexpr unsigned ccCOM1A1 = 7;
constexpr unsigned ccCOM1B0 = 4;
constexpr unsigned ccCOM1B1 = 5;
constexpr unsigned ccCOM20 = 4;
constexpr unsigned ccCOM21 = 5;
constexpr unsigned ccCPHA = 2;
constexpr unsigned ccCPOL = 3;
constexpr unsigned ccCS00 = 0;
constexpr unsigned ccCS01 = 1;
constexpr unsigned ccCS02 = 2;
constexpr unsigned ccCS10 = 0;
constexpr unsigned ccCS11 = 1;
constexpr unsigned ccCS12 = 2;
constexpr unsigned ccCS20 = 0;
constexpr unsigned ccCS21 = 1;
constexpr unsigned ccCS22 = 2;
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
constexpr unsigned ccDDB0 = 0;
constexpr unsigned ccDDB1 = 1;
constexpr unsigned ccDDB2 = 2;
constexpr unsigned ccDDB3 = 3;
constexpr unsigned ccDDB4 = 4;
constexpr unsigned ccDDB5 = 5;
constexpr unsigned ccDDB6 = 6;
constexpr unsigned ccDDB7 = 7;
constexpr unsigned ccDDC0 = 0;
constexpr unsigned ccDDC1 = 1;
constexpr unsigned ccDDC2 = 2;
constexpr unsigned ccDDC3 = 3;
constexpr unsigned ccDDC4 = 4;
constexpr unsigned ccDDC5 = 5;
constexpr unsigned ccDDC6 = 6;
constexpr unsigned ccDDC7 = 7;
constexpr unsigned ccDDD0 = 0;
constexpr unsigned ccDDD1 = 1;
constexpr unsigned ccDDD2 = 2;
constexpr unsigned ccDDD3 = 3;
constexpr unsigned ccDDD4 = 4;
constexpr unsigned ccDDD5 = 5;
constexpr unsigned ccDDD6 = 6;
constexpr unsigned ccDDD7 = 7;
using rrDDRA = IoRegisterDef<std::uint8_t, 0x1A>;
using rrDDRB = IoRegisterDef<std::uint8_t, 0x17>;
using rrDDRC = IoRegisterDef<std::uint8_t, 0x14>;
using rrDDRD = IoRegisterDef<std::uint8_t, 0x11>;
constexpr unsigned ccDOR = 3;
constexpr unsigned ccDORD = 5;
constexpr unsigned ccE2END = 0x1FF;
constexpr unsigned ccE2PAGESIZE = 4;
using rrEEAR = IoRegisterDef<std::uint16_t, 0x1E>;
constexpr unsigned ccEEAR0 = 0;
constexpr unsigned ccEEAR1 = 1;
constexpr unsigned ccEEAR2 = 2;
constexpr unsigned ccEEAR3 = 3;
constexpr unsigned ccEEAR4 = 4;
constexpr unsigned ccEEAR5 = 5;
constexpr unsigned ccEEAR6 = 6;
constexpr unsigned ccEEAR7 = 7;
constexpr unsigned ccEEAR8 = 0;
using rrEEARH = IoRegisterDef<std::uint8_t, 0x1F>;
using rrEEARL = IoRegisterDef<std::uint8_t, 0x1E>;
using rrEECR = IoRegisterDef<std::uint8_t, 0x1C>;
using rrEEDR = IoRegisterDef<std::uint8_t, 0x1D>;
constexpr unsigned ccEEDR0 = 0;
constexpr unsigned ccEEDR1 = 1;
constexpr unsigned ccEEDR2 = 2;
constexpr unsigned ccEEDR3 = 3;
constexpr unsigned ccEEDR4 = 4;
constexpr unsigned ccEEDR5 = 5;
constexpr unsigned ccEEDR6 = 6;
constexpr unsigned ccEEDR7 = 7;
constexpr unsigned ccEEMWE = 2;
constexpr unsigned ccEERE = 0;
constexpr unsigned ccEERIE = 3;
constexpr unsigned ccEEWE = 1;
constexpr unsigned ccEE_RDY_vect_num = 15;
constexpr unsigned ccEXTRF = 1;
constexpr unsigned ccFE = 4;
constexpr unsigned ccFLASHEND = 0x3FFF;
constexpr unsigned ccFOC0 = 7;
constexpr unsigned ccFOC1A = 3;
constexpr unsigned ccFOC1B = 2;
constexpr unsigned ccFOC2 = 7;
using ffFUSE_BODEN = setl::BitsRW<setl::SemanticType<setl::hash("FUSE_BODEN"), bool>, 1u<<6>;
using ffFUSE_BODLEVEL = setl::BitsRW<setl::SemanticType<setl::hash("FUSE_BODLEVEL"), bool>, 1u<<7>;
using ffFUSE_BOOTRST = setl::BitsRW<setl::SemanticType<setl::hash("FUSE_BOOTRST"), bool>, 1u<<0>;
using ffFUSE_BOOTSZ0 = setl::BitsRW<setl::SemanticType<setl::hash("FUSE_BOOTSZ0"), bool>, 1u<<1>;
using ffFUSE_BOOTSZ1 = setl::BitsRW<setl::SemanticType<setl::hash("FUSE_BOOTSZ1"), bool>, 1u<<2>;
using ffFUSE_CKOPT = setl::BitsRW<setl::SemanticType<setl::hash("FUSE_CKOPT"), bool>, 1u<<4>;
using ffFUSE_CKSEL0 = setl::BitsRW<setl::SemanticType<setl::hash("FUSE_CKSEL0"), bool>, 1u<<0>;
using ffFUSE_CKSEL1 = setl::BitsRW<setl::SemanticType<setl::hash("FUSE_CKSEL1"), bool>, 1u<<1>;
using ffFUSE_CKSEL2 = setl::BitsRW<setl::SemanticType<setl::hash("FUSE_CKSEL2"), bool>, 1u<<2>;
using ffFUSE_CKSEL3 = setl::BitsRW<setl::SemanticType<setl::hash("FUSE_CKSEL3"), bool>, 1u<<3>;
using ffFUSE_EESAVE = setl::BitsRW<setl::SemanticType<setl::hash("FUSE_EESAVE"), bool>, 1u<<3>;
using ffFUSE_JTAGEN = setl::BitsRW<setl::SemanticType<setl::hash("FUSE_JTAGEN"), bool>, 1u<<6>;
constexpr unsigned ccFUSE_MEMORY_SIZE = 2;
using ffFUSE_OCDEN = setl::BitsRW<setl::SemanticType<setl::hash("FUSE_OCDEN"), bool>, 1u<<7>;
using ffFUSE_SPIEN = setl::BitsRW<setl::SemanticType<setl::hash("FUSE_SPIEN"), bool>, 1u<<5>;
using ffFUSE_SUT0 = setl::BitsRW<setl::SemanticType<setl::hash("FUSE_SUT0"), bool>, 1u<<4>;
using ffFUSE_SUT1 = setl::BitsRW<setl::SemanticType<setl::hash("FUSE_SUT1"), bool>, 1u<<5>;
using rrGICR = IoRegisterDef<std::uint8_t, 0x3B>;
using rrGIFR = IoRegisterDef<std::uint8_t, 0x3A>;
constexpr unsigned ccICES1 = 6;
constexpr unsigned ccICF1 = 5;
constexpr unsigned ccICNC1 = 7;
constexpr unsigned ccICP_BIT = 6;
using rrICR1 = IoRegisterDef<std::uint16_t, 0x26>;
using rrICR1H = IoRegisterDef<std::uint8_t, 0x27>;
constexpr unsigned ccICR1H0 = 0;
constexpr unsigned ccICR1H1 = 1;
constexpr unsigned ccICR1H2 = 2;
constexpr unsigned ccICR1H3 = 3;
constexpr unsigned ccICR1H4 = 4;
constexpr unsigned ccICR1H5 = 5;
constexpr unsigned ccICR1H6 = 6;
constexpr unsigned ccICR1H7 = 7;
using rrICR1L = IoRegisterDef<std::uint8_t, 0x26>;
constexpr unsigned ccICR1L0 = 0;
constexpr unsigned ccICR1L1 = 1;
constexpr unsigned ccICR1L2 = 2;
constexpr unsigned ccICR1L3 = 3;
constexpr unsigned ccICR1L4 = 4;
constexpr unsigned ccICR1L5 = 5;
constexpr unsigned ccICR1L6 = 6;
constexpr unsigned ccICR1L7 = 7;
constexpr unsigned ccINT0 = 6;
constexpr unsigned ccINT0_BIT = 2;
constexpr unsigned ccINT0_vect_num = 1;
constexpr unsigned ccINT1 = 7;
constexpr unsigned ccINT1_BIT = 3;
constexpr unsigned ccINT1_vect_num = 2;
constexpr unsigned ccINT2 = 5;
constexpr unsigned ccINT2_vect_num = 18;
constexpr unsigned ccINTF0 = 6;
constexpr unsigned ccINTF1 = 7;
constexpr unsigned ccINTF2 = 5;
constexpr unsigned ccISC00 = 0;
constexpr unsigned ccISC01 = 1;
constexpr unsigned ccISC10 = 2;
constexpr unsigned ccISC11 = 3;
constexpr unsigned ccISC2 = 6;
constexpr unsigned ccIVCE = 0;
constexpr unsigned ccIVSEL = 1;
constexpr unsigned ccJTD = 7;
constexpr unsigned ccJTRF = 4;
constexpr unsigned ccLB_MODE_1 = 0xFF;
constexpr unsigned ccLB_MODE_2 = 0xFE;
constexpr unsigned ccLB_MODE_3 = 0xFC;
constexpr unsigned ccLOCKBITS_DEFAULT = 0xFF;
using rrMCUCR = IoRegisterDef<std::uint8_t, 0x35>;
using rrMCUCSR = IoRegisterDef<std::uint8_t, 0x34>;
constexpr unsigned ccMISO_BIT = 6;
constexpr unsigned ccMOSI_BIT = 5;
constexpr unsigned ccMPCM = 0;
constexpr unsigned ccMSTR = 4;
constexpr unsigned ccMUX0 = 0;
constexpr unsigned ccMUX1 = 1;
constexpr unsigned ccMUX2 = 2;
constexpr unsigned ccMUX3 = 3;
constexpr unsigned ccMUX4 = 4;
constexpr unsigned ccOC1A_BIT = 5;
constexpr unsigned ccOC1B_BIT = 4;
constexpr unsigned ccOC2_BIT = 7;
using rrOCDR = IoRegisterDef<std::uint8_t, 0x31>;
constexpr unsigned ccOCDR0 = 0;
constexpr unsigned ccOCDR1 = 1;
constexpr unsigned ccOCDR2 = 2;
constexpr unsigned ccOCDR3 = 3;
constexpr unsigned ccOCDR4 = 4;
constexpr unsigned ccOCDR5 = 5;
constexpr unsigned ccOCDR6 = 6;
constexpr unsigned ccOCDR7 = 7;
constexpr unsigned ccOCF0 = 1;
constexpr unsigned ccOCF1A = 4;
constexpr unsigned ccOCF1B = 3;
constexpr unsigned ccOCF2 = 7;
constexpr unsigned ccOCIE0 = 1;
constexpr unsigned ccOCIE1A = 4;
constexpr unsigned ccOCIE1B = 3;
constexpr unsigned ccOCIE2 = 7;
using rrOCR0 = IoRegisterDef<std::uint8_t, 0x3C>;
constexpr unsigned ccOCR0_0 = 0;
constexpr unsigned ccOCR0_1 = 1;
constexpr unsigned ccOCR0_2 = 2;
constexpr unsigned ccOCR0_3 = 3;
constexpr unsigned ccOCR0_4 = 4;
constexpr unsigned ccOCR0_5 = 5;
constexpr unsigned ccOCR0_6 = 6;
constexpr unsigned ccOCR0_7 = 7;
using rrOCR1A = IoRegisterDef<std::uint16_t, 0x2A>;
using rrOCR1AH = IoRegisterDef<std::uint8_t, 0x2B>;
constexpr unsigned ccOCR1AH0 = 0;
constexpr unsigned ccOCR1AH1 = 1;
constexpr unsigned ccOCR1AH2 = 2;
constexpr unsigned ccOCR1AH3 = 3;
constexpr unsigned ccOCR1AH4 = 4;
constexpr unsigned ccOCR1AH5 = 5;
constexpr unsigned ccOCR1AH6 = 6;
constexpr unsigned ccOCR1AH7 = 7;
using rrOCR1AL = IoRegisterDef<std::uint8_t, 0x2A>;
constexpr unsigned ccOCR1AL0 = 0;
constexpr unsigned ccOCR1AL1 = 1;
constexpr unsigned ccOCR1AL2 = 2;
constexpr unsigned ccOCR1AL3 = 3;
constexpr unsigned ccOCR1AL4 = 4;
constexpr unsigned ccOCR1AL5 = 5;
constexpr unsigned ccOCR1AL6 = 6;
constexpr unsigned ccOCR1AL7 = 7;
using rrOCR1B = IoRegisterDef<std::uint16_t, 0x28>;
using rrOCR1BH = IoRegisterDef<std::uint8_t, 0x29>;
constexpr unsigned ccOCR1BH0 = 0;
constexpr unsigned ccOCR1BH1 = 1;
constexpr unsigned ccOCR1BH2 = 2;
constexpr unsigned ccOCR1BH3 = 3;
constexpr unsigned ccOCR1BH4 = 4;
constexpr unsigned ccOCR1BH5 = 5;
constexpr unsigned ccOCR1BH6 = 6;
constexpr unsigned ccOCR1BH7 = 7;
using rrOCR1BL = IoRegisterDef<std::uint8_t, 0x28>;
constexpr unsigned ccOCR1BL0 = 0;
constexpr unsigned ccOCR1BL1 = 1;
constexpr unsigned ccOCR1BL2 = 2;
constexpr unsigned ccOCR1BL3 = 3;
constexpr unsigned ccOCR1BL4 = 4;
constexpr unsigned ccOCR1BL5 = 5;
constexpr unsigned ccOCR1BL6 = 6;
constexpr unsigned ccOCR1BL7 = 7;
using rrOCR2 = IoRegisterDef<std::uint8_t, 0x23>;
constexpr unsigned ccOCR2UB = 1;
constexpr unsigned ccOCR2_0 = 0;
constexpr unsigned ccOCR2_1 = 1;
constexpr unsigned ccOCR2_2 = 2;
constexpr unsigned ccOCR2_3 = 3;
constexpr unsigned ccOCR2_4 = 4;
constexpr unsigned ccOCR2_5 = 5;
constexpr unsigned ccOCR2_6 = 6;
constexpr unsigned ccOCR2_7 = 7;
using rrOSCCAL = IoRegisterDef<std::uint8_t, 0x31>;
constexpr unsigned ccPB7_SCK_BIT = 7;
constexpr unsigned ccPC3_BIT = 3;
constexpr unsigned ccPC4_BIT = 4;
constexpr unsigned ccPC5_BIT = 5;
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
using rrPINA = IoRegisterDef<std::uint8_t, 0x19>;
constexpr unsigned ccPINA0 = 0;
constexpr unsigned ccPINA1 = 1;
constexpr unsigned ccPINA2 = 2;
constexpr unsigned ccPINA3 = 3;
constexpr unsigned ccPINA4 = 4;
constexpr unsigned ccPINA5 = 5;
constexpr unsigned ccPINA6 = 6;
constexpr unsigned ccPINA7 = 7;
using rrPINB = IoRegisterDef<std::uint8_t, 0x16>;
constexpr unsigned ccPINB0 = 0;
constexpr unsigned ccPINB1 = 1;
constexpr unsigned ccPINB2 = 2;
constexpr unsigned ccPINB3 = 3;
constexpr unsigned ccPINB4 = 4;
constexpr unsigned ccPINB5 = 5;
constexpr unsigned ccPINB6 = 6;
constexpr unsigned ccPINB7 = 7;
using rrPINC = IoRegisterDef<std::uint8_t, 0x13>;
constexpr unsigned ccPINC0 = 0;
constexpr unsigned ccPINC1 = 1;
constexpr unsigned ccPINC2 = 2;
constexpr unsigned ccPINC3 = 3;
constexpr unsigned ccPINC4 = 4;
constexpr unsigned ccPINC5 = 5;
constexpr unsigned ccPINC6 = 6;
constexpr unsigned ccPINC7 = 7;
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
using rrPORTA = IoRegisterDef<std::uint8_t, 0x1B>;
constexpr unsigned ccPORTA0 = 0;
constexpr unsigned ccPORTA1 = 1;
constexpr unsigned ccPORTA2 = 2;
constexpr unsigned ccPORTA3 = 3;
constexpr unsigned ccPORTA4 = 4;
constexpr unsigned ccPORTA5 = 5;
constexpr unsigned ccPORTA6 = 6;
constexpr unsigned ccPORTA7 = 7;
using rrPORTB = IoRegisterDef<std::uint8_t, 0x18>;
constexpr unsigned ccPORTB0 = 0;
constexpr unsigned ccPORTB1 = 1;
constexpr unsigned ccPORTB2 = 2;
constexpr unsigned ccPORTB3 = 3;
constexpr unsigned ccPORTB4 = 4;
constexpr unsigned ccPORTB5 = 5;
constexpr unsigned ccPORTB6 = 6;
constexpr unsigned ccPORTB7 = 7;
using rrPORTC = IoRegisterDef<std::uint8_t, 0x15>;
constexpr unsigned ccPORTC0 = 0;
constexpr unsigned ccPORTC1 = 1;
constexpr unsigned ccPORTC2 = 2;
constexpr unsigned ccPORTC3 = 3;
constexpr unsigned ccPORTC4 = 4;
constexpr unsigned ccPORTC5 = 5;
constexpr unsigned ccPORTC6 = 6;
constexpr unsigned ccPORTC7 = 7;
using rrPORTD = IoRegisterDef<std::uint8_t, 0x12>;
constexpr unsigned ccPORTD0 = 0;
constexpr unsigned ccPORTD1 = 1;
constexpr unsigned ccPORTD2 = 2;
constexpr unsigned ccPORTD3 = 3;
constexpr unsigned ccPORTD4 = 4;
constexpr unsigned ccPORTD5 = 5;
constexpr unsigned ccPORTD6 = 6;
constexpr unsigned ccPORTD7 = 7;
constexpr unsigned ccPSR10 = 0;
constexpr unsigned ccPSR2 = 1;
constexpr unsigned ccPUD = 2;
constexpr unsigned ccRAMSIZE = 1024;
constexpr unsigned ccRAMSTART = 0x60;
constexpr unsigned ccREFS0 = 6;
constexpr unsigned ccREFS1 = 7;
constexpr unsigned ccRWWSB = 6;
constexpr unsigned ccRWWSRE = 4;
constexpr unsigned ccRXB8 = 1;
constexpr unsigned ccRXC = 7;
constexpr unsigned ccRXCIE = 7;
constexpr unsigned ccRXD_BIT = 0;
constexpr unsigned ccRXEN = 4;
constexpr unsigned ccSCL_BIT = 0;
constexpr unsigned ccSDA_BIT = 1;
constexpr unsigned ccSE = 6;
using rrSFIOR = IoRegisterDef<std::uint8_t, 0x30>;
constexpr unsigned ccSIGNATURE_0 = 0x1E;
constexpr unsigned ccSIGNATURE_1 = 0x94;
constexpr unsigned ccSIGNATURE_2 = 0x03;
constexpr unsigned ccSLEEP_MODE_ADC = 0x01;
constexpr unsigned ccSLEEP_MODE_EXT_STANDBY = 0x0B;
constexpr unsigned ccSLEEP_MODE_IDLE = 0x00;
constexpr unsigned ccSLEEP_MODE_PWR_DOWN = 0x02;
constexpr unsigned ccSLEEP_MODE_PWR_SAVE = 0x03;
constexpr unsigned ccSLEEP_MODE_STANDBY = 0x0A;
constexpr unsigned ccSM0 = 4;
constexpr unsigned ccSM1 = 5;
constexpr unsigned ccSM2 = 7;
using rrSP = IoRegisterDef<std::uint16_t, 0x3D>;
using rrSPCR = IoRegisterDef<std::uint8_t, 0x0D>;
using rrSPDR = IoRegisterDef<std::uint8_t, 0x0F>;
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
constexpr unsigned ccSPI_STC_vect_num = 10;
using rrSPL = IoRegisterDef<std::uint8_t, 0x3D>;
using rrSPMCSR = IoRegisterDef<std::uint8_t, 0x37>;
constexpr unsigned ccSPMEN = 0;
constexpr unsigned ccSPMIE = 7;
constexpr unsigned ccSPM_PAGESIZE = 128;
constexpr unsigned ccSPM_RDY_vect_num = 20;
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
constexpr unsigned ccSS_BIT = 4;
constexpr unsigned ccT0_BIT = 0;
constexpr unsigned ccT1_BIT = 1;
using rrTCCR0 = IoRegisterDef<std::uint8_t, 0x33>;
using rrTCCR1A = IoRegisterDef<std::uint8_t, 0x2F>;
using rrTCCR1B = IoRegisterDef<std::uint8_t, 0x2E>;
using rrTCCR2 = IoRegisterDef<std::uint8_t, 0x25>;
constexpr unsigned ccTCN2UB = 2;
using rrTCNT0 = IoRegisterDef<std::uint8_t, 0x32>;
constexpr unsigned ccTCNT0_0 = 0;
constexpr unsigned ccTCNT0_1 = 1;
constexpr unsigned ccTCNT0_2 = 2;
constexpr unsigned ccTCNT0_3 = 3;
constexpr unsigned ccTCNT0_4 = 4;
constexpr unsigned ccTCNT0_5 = 5;
constexpr unsigned ccTCNT0_6 = 6;
constexpr unsigned ccTCNT0_7 = 7;
using rrTCNT1 = IoRegisterDef<std::uint16_t, 0x2C>;
using rrTCNT1H = IoRegisterDef<std::uint8_t, 0x2D>;
constexpr unsigned ccTCNT1H0 = 0;
constexpr unsigned ccTCNT1H1 = 1;
constexpr unsigned ccTCNT1H2 = 2;
constexpr unsigned ccTCNT1H3 = 3;
constexpr unsigned ccTCNT1H4 = 4;
constexpr unsigned ccTCNT1H5 = 5;
constexpr unsigned ccTCNT1H6 = 6;
constexpr unsigned ccTCNT1H7 = 7;
using rrTCNT1L = IoRegisterDef<std::uint8_t, 0x2C>;
constexpr unsigned ccTCNT1L0 = 0;
constexpr unsigned ccTCNT1L1 = 1;
constexpr unsigned ccTCNT1L2 = 2;
constexpr unsigned ccTCNT1L3 = 3;
constexpr unsigned ccTCNT1L4 = 4;
constexpr unsigned ccTCNT1L5 = 5;
constexpr unsigned ccTCNT1L6 = 6;
constexpr unsigned ccTCNT1L7 = 7;
using rrTCNT2 = IoRegisterDef<std::uint8_t, 0x24>;
constexpr unsigned ccTCNT2_0 = 0;
constexpr unsigned ccTCNT2_1 = 1;
constexpr unsigned ccTCNT2_2 = 2;
constexpr unsigned ccTCNT2_3 = 3;
constexpr unsigned ccTCNT2_4 = 4;
constexpr unsigned ccTCNT2_5 = 5;
constexpr unsigned ccTCNT2_6 = 6;
constexpr unsigned ccTCNT2_7 = 7;
constexpr unsigned ccTCR2UB = 0;
constexpr unsigned ccTICIE1 = 5;
using rrTIFR = IoRegisterDef<std::uint8_t, 0x38>;
constexpr unsigned ccTIMER0_COMP_vect_num = 19;
constexpr unsigned ccTIMER0_OVF_vect_num = 9;
constexpr unsigned ccTIMER1_CAPT_vect_num = 5;
constexpr unsigned ccTIMER1_COMPA_vect_num = 6;
constexpr unsigned ccTIMER1_COMPB_vect_num = 7;
constexpr unsigned ccTIMER1_OVF_vect_num = 8;
constexpr unsigned ccTIMER2_COMP_vect_num = 3;
constexpr unsigned ccTIMER2_OVF_vect_num = 4;
using rrTIMSK = IoRegisterDef<std::uint8_t, 0x39>;
constexpr unsigned ccTOIE0 = 0;
constexpr unsigned ccTOIE1 = 2;
constexpr unsigned ccTOIE2 = 6;
constexpr unsigned ccTOV0 = 0;
constexpr unsigned ccTOV1 = 2;
constexpr unsigned ccTOV2 = 6;
constexpr unsigned ccTWA0 = 1;
constexpr unsigned ccTWA1 = 2;
constexpr unsigned ccTWA2 = 3;
constexpr unsigned ccTWA3 = 4;
constexpr unsigned ccTWA4 = 5;
constexpr unsigned ccTWA5 = 6;
constexpr unsigned ccTWA6 = 7;
using rrTWAR = IoRegisterDef<std::uint8_t, 0x02>;
using rrTWBR = IoRegisterDef<std::uint8_t, 0x00>;
constexpr unsigned ccTWBR0 = 0;
constexpr unsigned ccTWBR1 = 1;
constexpr unsigned ccTWBR2 = 2;
constexpr unsigned ccTWBR3 = 3;
constexpr unsigned ccTWBR4 = 4;
constexpr unsigned ccTWBR5 = 5;
constexpr unsigned ccTWBR6 = 6;
constexpr unsigned ccTWBR7 = 7;
using rrTWCR = IoRegisterDef<std::uint8_t, 0x36>;
constexpr unsigned ccTWD0 = 0;
constexpr unsigned ccTWD1 = 1;
constexpr unsigned ccTWD2 = 2;
constexpr unsigned ccTWD3 = 3;
constexpr unsigned ccTWD4 = 4;
constexpr unsigned ccTWD5 = 5;
constexpr unsigned ccTWD6 = 6;
constexpr unsigned ccTWD7 = 7;
using rrTWDR = IoRegisterDef<std::uint8_t, 0x03>;
constexpr unsigned ccTWEA = 6;
constexpr unsigned ccTWEN = 2;
constexpr unsigned ccTWGCE = 0;
constexpr unsigned ccTWIE = 0;
constexpr unsigned ccTWINT = 7;
constexpr unsigned ccTWI_vect_num = 17;
constexpr unsigned ccTWPS0 = 0;
constexpr unsigned ccTWPS1 = 1;
constexpr unsigned ccTWS3 = 3;
constexpr unsigned ccTWS4 = 4;
constexpr unsigned ccTWS5 = 5;
constexpr unsigned ccTWS6 = 6;
constexpr unsigned ccTWS7 = 7;
using rrTWSR = IoRegisterDef<std::uint8_t, 0x01>;
constexpr unsigned ccTWSTA = 5;
constexpr unsigned ccTWSTO = 4;
constexpr unsigned ccTWWC = 3;
constexpr unsigned ccTXB8 = 0;
constexpr unsigned ccTXC = 6;
constexpr unsigned ccTXCIE = 6;
constexpr unsigned ccTXD_BIT = 1;
constexpr unsigned ccTXEN = 3;
constexpr unsigned ccU2X = 1;
constexpr unsigned ccUBRR0 = 0;
constexpr unsigned ccUBRR1 = 1;
constexpr unsigned ccUBRR10 = 2;
constexpr unsigned ccUBRR11 = 3;
constexpr unsigned ccUBRR2 = 2;
constexpr unsigned ccUBRR3 = 3;
constexpr unsigned ccUBRR4 = 4;
constexpr unsigned ccUBRR5 = 5;
constexpr unsigned ccUBRR6 = 6;
constexpr unsigned ccUBRR7 = 7;
constexpr unsigned ccUBRR8 = 0;
constexpr unsigned ccUBRR9 = 1;
using rrUBRRH = IoRegisterDef<std::uint8_t, 0x20>;
using rrUBRRL = IoRegisterDef<std::uint8_t, 0x09>;
constexpr unsigned ccUCPOL = 0;
using rrUCSRA = IoRegisterDef<std::uint8_t, 0x0B>;
using rrUCSRB = IoRegisterDef<std::uint8_t, 0x0A>;
using rrUCSRC = IoRegisterDef<std::uint8_t, 0x20>;
constexpr unsigned ccUCSZ0 = 1;
constexpr unsigned ccUCSZ1 = 2;
constexpr unsigned ccUCSZ2 = 2;
using rrUDR = IoRegisterDef<std::uint8_t, 0x0C>;
constexpr unsigned ccUDR0 = 0;
constexpr unsigned ccUDR1 = 1;
constexpr unsigned ccUDR2 = 2;
constexpr unsigned ccUDR3 = 3;
constexpr unsigned ccUDR4 = 4;
constexpr unsigned ccUDR5 = 5;
constexpr unsigned ccUDR6 = 6;
constexpr unsigned ccUDR7 = 7;
constexpr unsigned ccUDRE = 5;
constexpr unsigned ccUDRIE = 5;
constexpr unsigned ccUMSEL = 6;
constexpr unsigned ccUPE = 2;
constexpr unsigned ccUPM0 = 4;
constexpr unsigned ccUPM1 = 5;
constexpr unsigned ccURSEL = 7;
constexpr unsigned ccUSARTRXC_vect_num = 11;
constexpr unsigned ccUSARTTXC_vect_num = 13;
constexpr unsigned ccUSARTUDRE_vect_num = 12;
constexpr unsigned ccUSART_RXC_vect_num = 11;
constexpr unsigned ccUSART_TXC_vect_num = 13;
constexpr unsigned ccUSART_UDRE_vect_num = 12;
constexpr unsigned ccUSBS = 3;
constexpr unsigned ccWCOL = 6;
constexpr unsigned ccWDE = 3;
constexpr unsigned ccWDP0 = 0;
constexpr unsigned ccWDP1 = 1;
constexpr unsigned ccWDP2 = 2;
constexpr unsigned ccWDRF = 3;
using rrWDTCR = IoRegisterDef<std::uint8_t, 0x21>;
constexpr unsigned ccWDTOE = 4;
constexpr unsigned ccWGM00 = 6;
constexpr unsigned ccWGM01 = 3;
constexpr unsigned ccWGM10 = 0;
constexpr unsigned ccWGM11 = 1;
constexpr unsigned ccWGM12 = 3;
constexpr unsigned ccWGM13 = 4;
constexpr unsigned ccWGM20 = 6;
constexpr unsigned ccWGM21 = 3;
constexpr unsigned ccXRAMSIZE = 0;
constexpr unsigned cc_HAVE_AVR_STACK_POINTER_HI = 1;
constexpr unsigned cc_SFR_ASM_COMPAT = 0;
constexpr unsigned cc_VECTORS_SIZE = 21;
constexpr unsigned cc_VECTOR_SIZE = 4;
constexpr unsigned cc__USING_MINT8 = 0;


}  // arch_atmega16a
}  // namespace avr
}  // namespace sys
}  // namespace ardo

#endif  // ardo_supplemental_atmega16a__h