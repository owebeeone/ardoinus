// Generated for arch atmega644pa.
// This file is generated from the avr-gcc compiler with the mcu
// set to atmega644pa from macros specific to avr/io.h.
// Any changes to this file will likely be lost next time this file
// is regenerated. Many any mcu_arch specific changes to 
// ardo_supplemental_atmega644pa_defs.h.

#ifndef ardo_supplemental_atmega644pa__h
#define ardo_supplemental_atmega644pa__h

#include "setlx_cstdint.h"
#include "setl_bit_fields.h"
#include "ardo_avr_bit_io_defs.h"

namespace ardo {
namespace sys {
namespace avr {
namespace arch_atmega644pa {

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
constexpr unsigned ccACME = 6;
constexpr unsigned ccACO = 5;
using rrACSR = IoRegisterDef<std::uint8_t, 0x30>;
constexpr unsigned ccADATE = 5;
using rrADC = MemRegisterDef<std::uint16_t, 0x78>;
constexpr unsigned ccADC0D = 0;
constexpr unsigned ccADC0_BIT = 0;
constexpr unsigned ccADC1D = 1;
constexpr unsigned ccADC1_BIT = 1;
constexpr unsigned ccADC2D = 2;
constexpr unsigned ccADC2_BIT = 2;
constexpr unsigned ccADC3D = 3;
constexpr unsigned ccADC3_BIT = 3;
constexpr unsigned ccADC4D = 4;
constexpr unsigned ccADC4_BIT = 4;
constexpr unsigned ccADC5D = 5;
constexpr unsigned ccADC5_BIT = 5;
constexpr unsigned ccADC6D = 6;
constexpr unsigned ccADC6_BIT = 6;
constexpr unsigned ccADC7D = 7;
constexpr unsigned ccADC7_BIT = 7;
using rrADCH = MemRegisterDef<std::uint8_t, 0x79>;
constexpr unsigned ccADCH0 = 0;
constexpr unsigned ccADCH1 = 1;
constexpr unsigned ccADCH2 = 2;
constexpr unsigned ccADCH3 = 3;
constexpr unsigned ccADCH4 = 4;
constexpr unsigned ccADCH5 = 5;
constexpr unsigned ccADCH6 = 6;
constexpr unsigned ccADCH7 = 7;
using rrADCL = MemRegisterDef<std::uint8_t, 0x78>;
constexpr unsigned ccADCL0 = 0;
constexpr unsigned ccADCL1 = 1;
constexpr unsigned ccADCL2 = 2;
constexpr unsigned ccADCL3 = 3;
constexpr unsigned ccADCL4 = 4;
constexpr unsigned ccADCL5 = 5;
constexpr unsigned ccADCL6 = 6;
constexpr unsigned ccADCL7 = 7;
using rrADCSRA = MemRegisterDef<std::uint8_t, 0x7A>;
using rrADCSRB = MemRegisterDef<std::uint8_t, 0x7B>;
using rrADCW = MemRegisterDef<std::uint16_t, 0x78>;
constexpr unsigned ccADC_vect_num = 24;
constexpr unsigned ccADEN = 7;
constexpr unsigned ccADIE = 3;
constexpr unsigned ccADIF = 4;
constexpr unsigned ccADLAR = 5;
using rrADMUX = MemRegisterDef<std::uint8_t, 0x7C>;
constexpr unsigned ccADPS0 = 0;
constexpr unsigned ccADPS1 = 1;
constexpr unsigned ccADPS2 = 2;
constexpr unsigned ccADSC = 6;
constexpr unsigned ccADTS0 = 0;
constexpr unsigned ccADTS1 = 1;
constexpr unsigned ccADTS2 = 2;
constexpr unsigned ccAIN0D = 0;
constexpr unsigned ccAIN0_BIT = 2;
constexpr unsigned ccAIN1D = 1;
constexpr unsigned ccAIN1_BIT = 3;
constexpr unsigned ccANALOG_COMP_vect_num = 23;
constexpr unsigned ccAS2 = 5;
using rrASSR = MemRegisterDef<std::uint8_t, 0xB6>;
constexpr unsigned ccBLB0_MODE_1 = 0xFF;
constexpr unsigned ccBLB0_MODE_2 = 0xFB;
constexpr unsigned ccBLB0_MODE_3 = 0xF3;
constexpr unsigned ccBLB0_MODE_4 = 0xF7;
constexpr unsigned ccBLB1_MODE_1 = 0xFF;
constexpr unsigned ccBLB1_MODE_2 = 0xEF;
constexpr unsigned ccBLB1_MODE_3 = 0xCF;
constexpr unsigned ccBLB1_MODE_4 = 0xDF;
constexpr unsigned ccBLBSET = 3;
constexpr unsigned ccBODS = 6;
constexpr unsigned ccBODSE = 5;
constexpr unsigned ccBORF = 2;
constexpr unsigned ccCAL0 = 0;
constexpr unsigned ccCAL1 = 1;
constexpr unsigned ccCAL2 = 2;
constexpr unsigned ccCAL3 = 3;
constexpr unsigned ccCAL4 = 4;
constexpr unsigned ccCAL5 = 5;
constexpr unsigned ccCAL6 = 6;
constexpr unsigned ccCAL7 = 7;
constexpr unsigned ccCLKO_BIT = 1;
constexpr unsigned ccCLKPCE = 7;
using rrCLKPR = MemRegisterDef<std::uint8_t, 0x61>;
constexpr unsigned ccCLKPS0 = 0;
constexpr unsigned ccCLKPS1 = 1;
constexpr unsigned ccCLKPS2 = 2;
constexpr unsigned ccCLKPS3 = 3;
constexpr unsigned ccCOM0A0 = 6;
constexpr unsigned ccCOM0A1 = 7;
constexpr unsigned ccCOM0B0 = 4;
constexpr unsigned ccCOM0B1 = 5;
constexpr unsigned ccCOM1A0 = 6;
constexpr unsigned ccCOM1A1 = 7;
constexpr unsigned ccCOM1B0 = 4;
constexpr unsigned ccCOM1B1 = 5;
constexpr unsigned ccCOM2A0 = 6;
constexpr unsigned ccCOM2A1 = 7;
constexpr unsigned ccCOM2B0 = 4;
constexpr unsigned ccCOM2B1 = 5;
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
using rrDDRA = IoRegisterDef<std::uint8_t, 0x01>;
using rrDDRB = IoRegisterDef<std::uint8_t, 0x04>;
using rrDDRC = IoRegisterDef<std::uint8_t, 0x07>;
using rrDDRD = IoRegisterDef<std::uint8_t, 0x0A>;
using rrDIDR0 = MemRegisterDef<std::uint8_t, 0x7E>;
using rrDIDR1 = MemRegisterDef<std::uint8_t, 0x7F>;
constexpr unsigned ccDOR0 = 3;
constexpr unsigned ccDOR1 = 3;
constexpr unsigned ccDORD = 5;
constexpr unsigned ccE2END = 0x7FF;
constexpr unsigned ccE2PAGESIZE = 8;
using rrEEAR = IoRegisterDef<std::uint16_t, 0x21>;
constexpr unsigned ccEEAR0 = 0;
constexpr unsigned ccEEAR1 = 1;
constexpr unsigned ccEEAR10 = 2;
constexpr unsigned ccEEAR11 = 3;
constexpr unsigned ccEEAR2 = 2;
constexpr unsigned ccEEAR3 = 3;
constexpr unsigned ccEEAR4 = 4;
constexpr unsigned ccEEAR5 = 5;
constexpr unsigned ccEEAR6 = 6;
constexpr unsigned ccEEAR7 = 7;
constexpr unsigned ccEEAR8 = 0;
constexpr unsigned ccEEAR9 = 1;
using rrEEARH = IoRegisterDef<std::uint8_t, 0x22>;
using rrEEARL = IoRegisterDef<std::uint8_t, 0x21>;
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
constexpr unsigned ccEE_READY_vect_num = 25;
constexpr unsigned ccEFUSE_DEFAULT = 0xFF;
using rrEICRA = MemRegisterDef<std::uint8_t, 0x69>;
using rrEIFR = IoRegisterDef<std::uint8_t, 0x1C>;
using rrEIMSK = IoRegisterDef<std::uint8_t, 0x1D>;
constexpr unsigned ccEXCLK = 6;
constexpr unsigned ccEXTRF = 1;
constexpr unsigned ccFE0 = 4;
constexpr unsigned ccFE1 = 4;
constexpr unsigned ccFLASHEND = 0xFFFF;
constexpr unsigned ccFOC0A = 7;
constexpr unsigned ccFOC0B = 6;
constexpr unsigned ccFOC1A = 7;
constexpr unsigned ccFOC1B = 6;
constexpr unsigned ccFOC2A = 7;
constexpr unsigned ccFOC2B = 6;
using ffFUSE_BODLEVEL0 = setl::BitsRW<setl::SemanticType<setl::hash("FUSE_BODLEVEL0"), bool>, 1u<<0>;
using ffFUSE_BODLEVEL1 = setl::BitsRW<setl::SemanticType<setl::hash("FUSE_BODLEVEL1"), bool>, 1u<<1>;
using ffFUSE_BODLEVEL2 = setl::BitsRW<setl::SemanticType<setl::hash("FUSE_BODLEVEL2"), bool>, 1u<<2>;
using ffFUSE_BOOTRST = setl::BitsRW<setl::SemanticType<setl::hash("FUSE_BOOTRST"), bool>, 1u<<0>;
using ffFUSE_BOOTSZ0 = setl::BitsRW<setl::SemanticType<setl::hash("FUSE_BOOTSZ0"), bool>, 1u<<1>;
using ffFUSE_BOOTSZ1 = setl::BitsRW<setl::SemanticType<setl::hash("FUSE_BOOTSZ1"), bool>, 1u<<2>;
using ffFUSE_CKDIV8 = setl::BitsRW<setl::SemanticType<setl::hash("FUSE_CKDIV8"), bool>, 1u<<7>;
using ffFUSE_CKOUT = setl::BitsRW<setl::SemanticType<setl::hash("FUSE_CKOUT"), bool>, 1u<<6>;
using ffFUSE_CKSEL0 = setl::BitsRW<setl::SemanticType<setl::hash("FUSE_CKSEL0"), bool>, 1u<<0>;
using ffFUSE_CKSEL1 = setl::BitsRW<setl::SemanticType<setl::hash("FUSE_CKSEL1"), bool>, 1u<<1>;
using ffFUSE_CKSEL2 = setl::BitsRW<setl::SemanticType<setl::hash("FUSE_CKSEL2"), bool>, 1u<<2>;
using ffFUSE_CKSEL3 = setl::BitsRW<setl::SemanticType<setl::hash("FUSE_CKSEL3"), bool>, 1u<<3>;
using ffFUSE_EESAVE = setl::BitsRW<setl::SemanticType<setl::hash("FUSE_EESAVE"), bool>, 1u<<3>;
using ffFUSE_JTAGEN = setl::BitsRW<setl::SemanticType<setl::hash("FUSE_JTAGEN"), bool>, 1u<<6>;
constexpr unsigned ccFUSE_MEMORY_SIZE = 3;
using ffFUSE_OCDEN = setl::BitsRW<setl::SemanticType<setl::hash("FUSE_OCDEN"), bool>, 1u<<7>;
using ffFUSE_SPIEN = setl::BitsRW<setl::SemanticType<setl::hash("FUSE_SPIEN"), bool>, 1u<<5>;
using ffFUSE_SUT0 = setl::BitsRW<setl::SemanticType<setl::hash("FUSE_SUT0"), bool>, 1u<<4>;
using ffFUSE_SUT1 = setl::BitsRW<setl::SemanticType<setl::hash("FUSE_SUT1"), bool>, 1u<<5>;
using ffFUSE_WDTON = setl::BitsRW<setl::SemanticType<setl::hash("FUSE_WDTON"), bool>, 1u<<4>;
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
constexpr unsigned ccICES1 = 6;
constexpr unsigned ccICF1 = 5;
constexpr unsigned ccICIE1 = 5;
constexpr unsigned ccICNC1 = 7;
constexpr unsigned ccICP_BIT = 6;
using rrICR1 = MemRegisterDef<std::uint16_t, 0x86>;
using rrICR1H = MemRegisterDef<std::uint8_t, 0x87>;
constexpr unsigned ccICR1H0 = 0;
constexpr unsigned ccICR1H1 = 1;
constexpr unsigned ccICR1H2 = 2;
constexpr unsigned ccICR1H3 = 3;
constexpr unsigned ccICR1H4 = 4;
constexpr unsigned ccICR1H5 = 5;
constexpr unsigned ccICR1H6 = 6;
constexpr unsigned ccICR1H7 = 7;
using rrICR1L = MemRegisterDef<std::uint8_t, 0x86>;
constexpr unsigned ccICR1L0 = 0;
constexpr unsigned ccICR1L1 = 1;
constexpr unsigned ccICR1L2 = 2;
constexpr unsigned ccICR1L3 = 3;
constexpr unsigned ccICR1L4 = 4;
constexpr unsigned ccICR1L5 = 5;
constexpr unsigned ccICR1L6 = 6;
constexpr unsigned ccICR1L7 = 7;
constexpr unsigned ccINT0 = 0;
constexpr unsigned ccINT0_BIT = 2;
constexpr unsigned ccINT0_vect_num = 1;
constexpr unsigned ccINT1 = 1;
constexpr unsigned ccINT1_BIT = 3;
constexpr unsigned ccINT1_vect_num = 2;
constexpr unsigned ccINT2 = 2;
constexpr unsigned ccINT2_BIT = 2;
constexpr unsigned ccINT2_vect_num = 3;
constexpr unsigned ccINTF0 = 0;
constexpr unsigned ccINTF1 = 1;
constexpr unsigned ccINTF2 = 2;
constexpr unsigned ccISC00 = 0;
constexpr unsigned ccISC01 = 1;
constexpr unsigned ccISC10 = 2;
constexpr unsigned ccISC11 = 3;
constexpr unsigned ccISC20 = 4;
constexpr unsigned ccISC21 = 5;
constexpr unsigned ccIVCE = 0;
constexpr unsigned ccIVSEL = 1;
constexpr unsigned ccJTD = 7;
constexpr unsigned ccJTRF = 4;
constexpr unsigned ccLB_MODE_1 = 0xFF;
constexpr unsigned ccLB_MODE_2 = 0xFE;
constexpr unsigned ccLB_MODE_3 = 0xFC;
constexpr unsigned ccLOCKBITS_DEFAULT = 0xFF;
using rrMCUCR = IoRegisterDef<std::uint8_t, 0x35>;
using rrMCUSR = IoRegisterDef<std::uint8_t, 0x34>;
constexpr unsigned ccMISO_BIT = 6;
constexpr unsigned ccMOSI_BIT = 5;
constexpr unsigned ccMPCM0 = 0;
constexpr unsigned ccMPCM1 = 0;
constexpr unsigned ccMSTR = 4;
constexpr unsigned ccMUX0 = 0;
constexpr unsigned ccMUX1 = 1;
constexpr unsigned ccMUX2 = 2;
constexpr unsigned ccMUX3 = 3;
constexpr unsigned ccMUX4 = 4;
constexpr unsigned ccOC0A_BIT = 3;
constexpr unsigned ccOC0B_BIT = 4;
constexpr unsigned ccOC1A_BIT = 5;
constexpr unsigned ccOC1B_BIT = 4;
constexpr unsigned ccOC2A_BIT = 7;
constexpr unsigned ccOC2B_BIT = 6;
using rrOCDR = IoRegisterDef<std::uint8_t, 0x31>;
constexpr unsigned ccOCDR0 = 0;
constexpr unsigned ccOCDR1 = 1;
constexpr unsigned ccOCDR2 = 2;
constexpr unsigned ccOCDR3 = 3;
constexpr unsigned ccOCDR4 = 4;
constexpr unsigned ccOCDR5 = 5;
constexpr unsigned ccOCDR6 = 6;
constexpr unsigned ccOCDR7 = 7;
constexpr unsigned ccOCF0A = 1;
constexpr unsigned ccOCF0B = 2;
constexpr unsigned ccOCF1A = 1;
constexpr unsigned ccOCF1B = 2;
constexpr unsigned ccOCF2A = 1;
constexpr unsigned ccOCF2B = 2;
constexpr unsigned ccOCIE0A = 1;
constexpr unsigned ccOCIE0B = 2;
constexpr unsigned ccOCIE1A = 1;
constexpr unsigned ccOCIE1B = 2;
constexpr unsigned ccOCIE2A = 1;
constexpr unsigned ccOCIE2B = 2;
using rrOCR0A = IoRegisterDef<std::uint8_t, 0x27>;
constexpr unsigned ccOCR0A_0 = 0;
constexpr unsigned ccOCR0A_1 = 1;
constexpr unsigned ccOCR0A_2 = 2;
constexpr unsigned ccOCR0A_3 = 3;
constexpr unsigned ccOCR0A_4 = 4;
constexpr unsigned ccOCR0A_5 = 5;
constexpr unsigned ccOCR0A_6 = 6;
constexpr unsigned ccOCR0A_7 = 7;
using rrOCR0B = IoRegisterDef<std::uint8_t, 0x28>;
constexpr unsigned ccOCR0B_0 = 0;
constexpr unsigned ccOCR0B_1 = 1;
constexpr unsigned ccOCR0B_2 = 2;
constexpr unsigned ccOCR0B_3 = 3;
constexpr unsigned ccOCR0B_4 = 4;
constexpr unsigned ccOCR0B_5 = 5;
constexpr unsigned ccOCR0B_6 = 6;
constexpr unsigned ccOCR0B_7 = 7;
using rrOCR1A = MemRegisterDef<std::uint16_t, 0x88>;
using rrOCR1AH = MemRegisterDef<std::uint8_t, 0x89>;
constexpr unsigned ccOCR1AH0 = 0;
constexpr unsigned ccOCR1AH1 = 1;
constexpr unsigned ccOCR1AH2 = 2;
constexpr unsigned ccOCR1AH3 = 3;
constexpr unsigned ccOCR1AH4 = 4;
constexpr unsigned ccOCR1AH5 = 5;
constexpr unsigned ccOCR1AH6 = 6;
constexpr unsigned ccOCR1AH7 = 7;
using rrOCR1AL = MemRegisterDef<std::uint8_t, 0x88>;
constexpr unsigned ccOCR1AL0 = 0;
constexpr unsigned ccOCR1AL1 = 1;
constexpr unsigned ccOCR1AL2 = 2;
constexpr unsigned ccOCR1AL3 = 3;
constexpr unsigned ccOCR1AL4 = 4;
constexpr unsigned ccOCR1AL5 = 5;
constexpr unsigned ccOCR1AL6 = 6;
constexpr unsigned ccOCR1AL7 = 7;
using rrOCR1B = MemRegisterDef<std::uint16_t, 0x8A>;
using rrOCR1BH = MemRegisterDef<std::uint8_t, 0x8B>;
constexpr unsigned ccOCR1BH0 = 0;
constexpr unsigned ccOCR1BH1 = 1;
constexpr unsigned ccOCR1BH2 = 2;
constexpr unsigned ccOCR1BH3 = 3;
constexpr unsigned ccOCR1BH4 = 4;
constexpr unsigned ccOCR1BH5 = 5;
constexpr unsigned ccOCR1BH6 = 6;
constexpr unsigned ccOCR1BH7 = 7;
using rrOCR1BL = MemRegisterDef<std::uint8_t, 0x8A>;
constexpr unsigned ccOCR1BL0 = 0;
constexpr unsigned ccOCR1BL1 = 1;
constexpr unsigned ccOCR1BL2 = 2;
constexpr unsigned ccOCR1BL3 = 3;
constexpr unsigned ccOCR1BL4 = 4;
constexpr unsigned ccOCR1BL5 = 5;
constexpr unsigned ccOCR1BL6 = 6;
constexpr unsigned ccOCR1BL7 = 7;
using rrOCR2A = MemRegisterDef<std::uint8_t, 0xB3>;
constexpr unsigned ccOCR2AUB = 3;
constexpr unsigned ccOCR2A_0 = 0;
constexpr unsigned ccOCR2A_1 = 1;
constexpr unsigned ccOCR2A_2 = 2;
constexpr unsigned ccOCR2A_3 = 3;
constexpr unsigned ccOCR2A_4 = 4;
constexpr unsigned ccOCR2A_5 = 5;
constexpr unsigned ccOCR2A_6 = 6;
constexpr unsigned ccOCR2A_7 = 7;
using rrOCR2B = MemRegisterDef<std::uint8_t, 0xB4>;
constexpr unsigned ccOCR2BUB = 2;
constexpr unsigned ccOCR2B_0 = 0;
constexpr unsigned ccOCR2B_1 = 1;
constexpr unsigned ccOCR2B_2 = 2;
constexpr unsigned ccOCR2B_3 = 3;
constexpr unsigned ccOCR2B_4 = 4;
constexpr unsigned ccOCR2B_5 = 5;
constexpr unsigned ccOCR2B_6 = 6;
constexpr unsigned ccOCR2B_7 = 7;
using rrOSCCAL = MemRegisterDef<std::uint8_t, 0x66>;
using rrPCICR = MemRegisterDef<std::uint8_t, 0x68>;
constexpr unsigned ccPCIE0 = 0;
constexpr unsigned ccPCIE1 = 1;
constexpr unsigned ccPCIE2 = 2;
constexpr unsigned ccPCIE3 = 3;
constexpr unsigned ccPCIF0 = 0;
constexpr unsigned ccPCIF1 = 1;
constexpr unsigned ccPCIF2 = 2;
constexpr unsigned ccPCIF3 = 3;
using rrPCIFR = IoRegisterDef<std::uint8_t, 0x1B>;
constexpr unsigned ccPCINT0 = 0;
constexpr unsigned ccPCINT0_BIT = 0;
constexpr unsigned ccPCINT0_vect_num = 4;
constexpr unsigned ccPCINT1 = 1;
constexpr unsigned ccPCINT10 = 2;
constexpr unsigned ccPCINT10_BIT = 2;
constexpr unsigned ccPCINT11 = 3;
constexpr unsigned ccPCINT11_BIT = 3;
constexpr unsigned ccPCINT12 = 4;
constexpr unsigned ccPCINT12_BIT = 4;
constexpr unsigned ccPCINT13 = 5;
constexpr unsigned ccPCINT13_BIT = 5;
constexpr unsigned ccPCINT14 = 6;
constexpr unsigned ccPCINT14_BIT = 6;
constexpr unsigned ccPCINT15 = 7;
constexpr unsigned ccPCINT15_BIT = 7;
constexpr unsigned ccPCINT16 = 0;
constexpr unsigned ccPCINT16_BIT = 0;
constexpr unsigned ccPCINT17 = 1;
constexpr unsigned ccPCINT17_BIT = 1;
constexpr unsigned ccPCINT18 = 2;
constexpr unsigned ccPCINT18_BIT = 2;
constexpr unsigned ccPCINT19 = 3;
constexpr unsigned ccPCINT19_BIT = 3;
constexpr unsigned ccPCINT1_BIT = 1;
constexpr unsigned ccPCINT1_vect_num = 5;
constexpr unsigned ccPCINT2 = 2;
constexpr unsigned ccPCINT20 = 4;
constexpr unsigned ccPCINT20_BIT = 4;
constexpr unsigned ccPCINT21 = 5;
constexpr unsigned ccPCINT21_BIT = 5;
constexpr unsigned ccPCINT22 = 6;
constexpr unsigned ccPCINT22_BIT = 6;
constexpr unsigned ccPCINT23 = 7;
constexpr unsigned ccPCINT23_BIT = 7;
constexpr unsigned ccPCINT24 = 0;
constexpr unsigned ccPCINT24_BIT = 0;
constexpr unsigned ccPCINT25 = 1;
constexpr unsigned ccPCINT25_BIT = 1;
constexpr unsigned ccPCINT26 = 2;
constexpr unsigned ccPCINT26_BIT = 2;
constexpr unsigned ccPCINT27 = 3;
constexpr unsigned ccPCINT27_BIT = 3;
constexpr unsigned ccPCINT28 = 4;
constexpr unsigned ccPCINT28_BIT = 4;
constexpr unsigned ccPCINT29 = 5;
constexpr unsigned ccPCINT29_BIT = 5;
constexpr unsigned ccPCINT2_BIT = 2;
constexpr unsigned ccPCINT2_vect_num = 6;
constexpr unsigned ccPCINT3 = 3;
constexpr unsigned ccPCINT30 = 6;
constexpr unsigned ccPCINT30_BIT = 6;
constexpr unsigned ccPCINT31 = 7;
constexpr unsigned ccPCINT31_BIT = 7;
constexpr unsigned ccPCINT3_BIT = 3;
constexpr unsigned ccPCINT3_vect_num = 7;
constexpr unsigned ccPCINT4 = 4;
constexpr unsigned ccPCINT4_BIT = 4;
constexpr unsigned ccPCINT5 = 5;
constexpr unsigned ccPCINT5_BIT = 5;
constexpr unsigned ccPCINT6 = 6;
constexpr unsigned ccPCINT6_BIT = 6;
constexpr unsigned ccPCINT7 = 7;
constexpr unsigned ccPCINT7_BIT = 7;
constexpr unsigned ccPCINT8 = 0;
constexpr unsigned ccPCINT8_BIT = 0;
constexpr unsigned ccPCINT9 = 1;
constexpr unsigned ccPCINT9_BIT = 1;
using rrPCMSK0 = MemRegisterDef<std::uint8_t, 0x6B>;
using rrPCMSK1 = MemRegisterDef<std::uint8_t, 0x6C>;
using rrPCMSK2 = MemRegisterDef<std::uint8_t, 0x6D>;
using rrPCMSK3 = MemRegisterDef<std::uint8_t, 0x73>;
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
constexpr unsigned ccPINA2 = 2;
constexpr unsigned ccPINA3 = 3;
constexpr unsigned ccPINA4 = 4;
constexpr unsigned ccPINA5 = 5;
constexpr unsigned ccPINA6 = 6;
constexpr unsigned ccPINA7 = 7;
using rrPINB = IoRegisterDef<std::uint8_t, 0x03>;
constexpr unsigned ccPINB0 = 0;
constexpr unsigned ccPINB1 = 1;
constexpr unsigned ccPINB2 = 2;
constexpr unsigned ccPINB3 = 3;
constexpr unsigned ccPINB4 = 4;
constexpr unsigned ccPINB5 = 5;
constexpr unsigned ccPINB6 = 6;
constexpr unsigned ccPINB7 = 7;
using rrPINC = IoRegisterDef<std::uint8_t, 0x06>;
constexpr unsigned ccPINC0 = 0;
constexpr unsigned ccPINC1 = 1;
constexpr unsigned ccPINC2 = 2;
constexpr unsigned ccPINC3 = 3;
constexpr unsigned ccPINC4 = 4;
constexpr unsigned ccPINC5 = 5;
constexpr unsigned ccPINC6 = 6;
constexpr unsigned ccPINC7 = 7;
using rrPIND = IoRegisterDef<std::uint8_t, 0x09>;
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
using rrPORTA = IoRegisterDef<std::uint8_t, 0x02>;
constexpr unsigned ccPORTA0 = 0;
constexpr unsigned ccPORTA1 = 1;
constexpr unsigned ccPORTA2 = 2;
constexpr unsigned ccPORTA3 = 3;
constexpr unsigned ccPORTA4 = 4;
constexpr unsigned ccPORTA5 = 5;
constexpr unsigned ccPORTA6 = 6;
constexpr unsigned ccPORTA7 = 7;
using rrPORTB = IoRegisterDef<std::uint8_t, 0x05>;
constexpr unsigned ccPORTB0 = 0;
constexpr unsigned ccPORTB1 = 1;
constexpr unsigned ccPORTB2 = 2;
constexpr unsigned ccPORTB3 = 3;
constexpr unsigned ccPORTB4 = 4;
constexpr unsigned ccPORTB5 = 5;
constexpr unsigned ccPORTB6 = 6;
constexpr unsigned ccPORTB7 = 7;
using rrPORTC = IoRegisterDef<std::uint8_t, 0x08>;
constexpr unsigned ccPORTC0 = 0;
constexpr unsigned ccPORTC1 = 1;
constexpr unsigned ccPORTC2 = 2;
constexpr unsigned ccPORTC3 = 3;
constexpr unsigned ccPORTC4 = 4;
constexpr unsigned ccPORTC5 = 5;
constexpr unsigned ccPORTC6 = 6;
constexpr unsigned ccPORTC7 = 7;
using rrPORTD = IoRegisterDef<std::uint8_t, 0x0B>;
constexpr unsigned ccPORTD0 = 0;
constexpr unsigned ccPORTD1 = 1;
constexpr unsigned ccPORTD2 = 2;
constexpr unsigned ccPORTD3 = 3;
constexpr unsigned ccPORTD4 = 4;
constexpr unsigned ccPORTD5 = 5;
constexpr unsigned ccPORTD6 = 6;
constexpr unsigned ccPORTD7 = 7;
constexpr unsigned ccPRADC = 0;
using rrPRR0 = MemRegisterDef<std::uint8_t, 0x64>;
constexpr unsigned ccPRSPI = 2;
constexpr unsigned ccPRTIM0 = 5;
constexpr unsigned ccPRTIM1 = 3;
constexpr unsigned ccPRTIM2 = 6;
constexpr unsigned ccPRTWI = 7;
constexpr unsigned ccPRUSART0 = 1;
constexpr unsigned ccPRUSART1 = 4;
constexpr unsigned ccPSRASY = 1;
constexpr unsigned ccPSRSYNC = 0;
constexpr unsigned ccPUD = 4;
constexpr unsigned ccRAMSIZE = 4096;
constexpr unsigned ccRAMSTART = 0x100;
constexpr unsigned ccRDX1_BIT = 2;
constexpr unsigned ccREFS0 = 6;
constexpr unsigned ccREFS1 = 7;
constexpr unsigned ccRWWSB = 6;
constexpr unsigned ccRWWSRE = 4;
constexpr unsigned ccRXB80 = 1;
constexpr unsigned ccRXB81 = 1;
constexpr unsigned ccRXC0 = 7;
constexpr unsigned ccRXC1 = 7;
constexpr unsigned ccRXCIE0 = 7;
constexpr unsigned ccRXCIE1 = 7;
constexpr unsigned ccRXD_BIT = 0;
constexpr unsigned ccRXEN0 = 4;
constexpr unsigned ccRXEN1 = 4;
constexpr unsigned ccSCK_BIT = 7;
constexpr unsigned ccSCL_BIT = 0;
constexpr unsigned ccSDA_BIT = 1;
constexpr unsigned ccSE = 0;
constexpr unsigned ccSIGNATURE_0 = 0x1E;
constexpr unsigned ccSIGNATURE_1 = 0x96;
constexpr unsigned ccSIGNATURE_2 = 0x0A;
constexpr unsigned ccSIGRD = 5;
constexpr unsigned ccSLEEP_MODE_ADC = 0x01;
constexpr unsigned ccSLEEP_MODE_EXT_STANDBY = 0x07;
constexpr unsigned ccSLEEP_MODE_IDLE = 0x00;
constexpr unsigned ccSLEEP_MODE_PWR_DOWN = 0x02;
constexpr unsigned ccSLEEP_MODE_PWR_SAVE = 0x03;
constexpr unsigned ccSLEEP_MODE_STANDBY = 0x06;
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
constexpr unsigned ccSPI_STC_vect_num = 19;
using rrSPL = IoRegisterDef<std::uint8_t, 0x3D>;
using rrSPMCSR = IoRegisterDef<std::uint8_t, 0x37>;
constexpr unsigned ccSPMEN = 0;
constexpr unsigned ccSPMIE = 7;
constexpr unsigned ccSPM_PAGESIZE = 256;
constexpr unsigned ccSPM_READY_vect_num = 27;
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
constexpr unsigned ccSS_BIT = 4;
constexpr unsigned ccT0_BIT = 0;
constexpr unsigned ccT1_BIT = 1;
using rrTCCR0A = IoRegisterDef<std::uint8_t, 0x24>;
using rrTCCR0B = IoRegisterDef<std::uint8_t, 0x25>;
using rrTCCR1A = MemRegisterDef<std::uint8_t, 0x80>;
using rrTCCR1B = MemRegisterDef<std::uint8_t, 0x81>;
using rrTCCR1C = MemRegisterDef<std::uint8_t, 0x82>;
using rrTCCR2A = MemRegisterDef<std::uint8_t, 0xB0>;
using rrTCCR2B = MemRegisterDef<std::uint8_t, 0xB1>;
constexpr unsigned ccTCN2UB = 4;
using rrTCNT0 = IoRegisterDef<std::uint8_t, 0x26>;
constexpr unsigned ccTCNT0_0 = 0;
constexpr unsigned ccTCNT0_1 = 1;
constexpr unsigned ccTCNT0_2 = 2;
constexpr unsigned ccTCNT0_3 = 3;
constexpr unsigned ccTCNT0_4 = 4;
constexpr unsigned ccTCNT0_5 = 5;
constexpr unsigned ccTCNT0_6 = 6;
constexpr unsigned ccTCNT0_7 = 7;
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
using rrTCNT2 = MemRegisterDef<std::uint8_t, 0xB2>;
constexpr unsigned ccTCNT2_0 = 0;
constexpr unsigned ccTCNT2_1 = 1;
constexpr unsigned ccTCNT2_2 = 2;
constexpr unsigned ccTCNT2_3 = 3;
constexpr unsigned ccTCNT2_4 = 4;
constexpr unsigned ccTCNT2_5 = 5;
constexpr unsigned ccTCNT2_6 = 6;
constexpr unsigned ccTCNT2_7 = 7;
constexpr unsigned ccTCR2AUB = 1;
constexpr unsigned ccTCR2BUB = 0;
using rrTIFR0 = IoRegisterDef<std::uint8_t, 0x15>;
using rrTIFR1 = IoRegisterDef<std::uint8_t, 0x16>;
using rrTIFR2 = IoRegisterDef<std::uint8_t, 0x17>;
constexpr unsigned ccTIMER0_COMPA_vect_num = 16;
constexpr unsigned ccTIMER0_COMPB_vect_num = 17;
constexpr unsigned ccTIMER0_OVF_vect_num = 18;
constexpr unsigned ccTIMER1_CAPT_vect_num = 12;
constexpr unsigned ccTIMER1_COMPA_vect_num = 13;
constexpr unsigned ccTIMER1_COMPB_vect_num = 14;
constexpr unsigned ccTIMER1_OVF_vect_num = 15;
constexpr unsigned ccTIMER2_COMPA_vect_num = 9;
constexpr unsigned ccTIMER2_COMPB_vect_num = 10;
constexpr unsigned ccTIMER2_OVF_vect_num = 11;
using rrTIMSK0 = MemRegisterDef<std::uint8_t, 0x6E>;
using rrTIMSK1 = MemRegisterDef<std::uint8_t, 0x6F>;
using rrTIMSK2 = MemRegisterDef<std::uint8_t, 0x70>;
constexpr unsigned ccTOIE0 = 0;
constexpr unsigned ccTOIE1 = 0;
constexpr unsigned ccTOIE2 = 0;
constexpr unsigned ccTOV0 = 0;
constexpr unsigned ccTOV1 = 0;
constexpr unsigned ccTOV2 = 0;
constexpr unsigned ccTSM = 7;
constexpr unsigned ccTWA0 = 1;
constexpr unsigned ccTWA1 = 2;
constexpr unsigned ccTWA2 = 3;
constexpr unsigned ccTWA3 = 4;
constexpr unsigned ccTWA4 = 5;
constexpr unsigned ccTWA5 = 6;
constexpr unsigned ccTWA6 = 7;
constexpr unsigned ccTWAM0 = 1;
constexpr unsigned ccTWAM1 = 2;
constexpr unsigned ccTWAM2 = 3;
constexpr unsigned ccTWAM3 = 4;
constexpr unsigned ccTWAM4 = 5;
constexpr unsigned ccTWAM5 = 6;
constexpr unsigned ccTWAM6 = 7;
using rrTWAMR = MemRegisterDef<std::uint8_t, 0xBD>;
using rrTWAR = MemRegisterDef<std::uint8_t, 0xBA>;
using rrTWBR = MemRegisterDef<std::uint8_t, 0xB8>;
constexpr unsigned ccTWBR0 = 0;
constexpr unsigned ccTWBR1 = 1;
constexpr unsigned ccTWBR2 = 2;
constexpr unsigned ccTWBR3 = 3;
constexpr unsigned ccTWBR4 = 4;
constexpr unsigned ccTWBR5 = 5;
constexpr unsigned ccTWBR6 = 6;
constexpr unsigned ccTWBR7 = 7;
using rrTWCR = MemRegisterDef<std::uint8_t, 0xBC>;
constexpr unsigned ccTWD0 = 0;
constexpr unsigned ccTWD1 = 1;
constexpr unsigned ccTWD2 = 2;
constexpr unsigned ccTWD3 = 3;
constexpr unsigned ccTWD4 = 4;
constexpr unsigned ccTWD5 = 5;
constexpr unsigned ccTWD6 = 6;
constexpr unsigned ccTWD7 = 7;
using rrTWDR = MemRegisterDef<std::uint8_t, 0xBB>;
constexpr unsigned ccTWEA = 6;
constexpr unsigned ccTWEN = 2;
constexpr unsigned ccTWGCE = 0;
constexpr unsigned ccTWIE = 0;
constexpr unsigned ccTWINT = 7;
constexpr unsigned ccTWI_vect_num = 26;
constexpr unsigned ccTWPS0 = 0;
constexpr unsigned ccTWPS1 = 1;
constexpr unsigned ccTWS3 = 3;
constexpr unsigned ccTWS4 = 4;
constexpr unsigned ccTWS5 = 5;
constexpr unsigned ccTWS6 = 6;
constexpr unsigned ccTWS7 = 7;
using rrTWSR = MemRegisterDef<std::uint8_t, 0xB9>;
constexpr unsigned ccTWSTA = 5;
constexpr unsigned ccTWSTO = 4;
constexpr unsigned ccTWWC = 3;
constexpr unsigned ccTXB80 = 0;
constexpr unsigned ccTXB81 = 0;
constexpr unsigned ccTXC0 = 6;
constexpr unsigned ccTXC1 = 6;
constexpr unsigned ccTXCIE0 = 6;
constexpr unsigned ccTXCIE1 = 6;
constexpr unsigned ccTXD1_BIT = 3;
constexpr unsigned ccTXD_BIT = 1;
constexpr unsigned ccTXEN0 = 3;
constexpr unsigned ccTXEN1 = 3;
constexpr unsigned ccU2X0 = 1;
constexpr unsigned ccU2X1 = 1;
using rrUBRR0 = MemRegisterDef<std::uint16_t, 0xC4>;
using rrUBRR0H = MemRegisterDef<std::uint8_t, 0xC5>;
using rrUBRR0L = MemRegisterDef<std::uint8_t, 0xC4>;
using rrUBRR1 = MemRegisterDef<std::uint16_t, 0xCC>;
constexpr unsigned ccUBRR10 = 2;
constexpr unsigned ccUBRR11 = 3;
using rrUBRR1H = MemRegisterDef<std::uint8_t, 0xCD>;
using rrUBRR1L = MemRegisterDef<std::uint8_t, 0xCC>;
constexpr unsigned ccUBRR2 = 2;
constexpr unsigned ccUBRR3 = 3;
constexpr unsigned ccUBRR4 = 4;
constexpr unsigned ccUBRR5 = 5;
constexpr unsigned ccUBRR6 = 6;
constexpr unsigned ccUBRR7 = 7;
constexpr unsigned ccUBRR8 = 0;
constexpr unsigned ccUBRR9 = 1;
constexpr unsigned ccUBRR_0 = 0;
constexpr unsigned ccUBRR_1 = 1;
constexpr unsigned ccUBRR_10 = 2;
constexpr unsigned ccUBRR_11 = 3;
constexpr unsigned ccUBRR_2 = 2;
constexpr unsigned ccUBRR_3 = 3;
constexpr unsigned ccUBRR_4 = 4;
constexpr unsigned ccUBRR_5 = 5;
constexpr unsigned ccUBRR_6 = 6;
constexpr unsigned ccUBRR_7 = 7;
constexpr unsigned ccUBRR_8 = 0;
constexpr unsigned ccUBRR_9 = 1;
constexpr unsigned ccUCPOL0 = 0;
constexpr unsigned ccUCPOL1 = 0;
using rrUCSR0A = MemRegisterDef<std::uint8_t, 0xC0>;
using rrUCSR0B = MemRegisterDef<std::uint8_t, 0xC1>;
using rrUCSR0C = MemRegisterDef<std::uint8_t, 0xC2>;
using rrUCSR1A = MemRegisterDef<std::uint8_t, 0xC8>;
using rrUCSR1B = MemRegisterDef<std::uint8_t, 0xC9>;
using rrUCSR1C = MemRegisterDef<std::uint8_t, 0xCA>;
constexpr unsigned ccUCSZ00 = 1;
constexpr unsigned ccUCSZ01 = 2;
constexpr unsigned ccUCSZ02 = 2;
constexpr unsigned ccUCSZ10 = 1;
constexpr unsigned ccUCSZ11 = 2;
constexpr unsigned ccUCSZ12 = 2;
using rrUDR0 = MemRegisterDef<std::uint8_t, 0xC6>;
constexpr unsigned ccUDR0_0 = 0;
constexpr unsigned ccUDR0_1 = 1;
constexpr unsigned ccUDR0_2 = 2;
constexpr unsigned ccUDR0_3 = 3;
constexpr unsigned ccUDR0_4 = 4;
constexpr unsigned ccUDR0_5 = 5;
constexpr unsigned ccUDR0_6 = 6;
constexpr unsigned ccUDR0_7 = 7;
using rrUDR1 = MemRegisterDef<std::uint8_t, 0xCE>;
constexpr unsigned ccUDR1_0 = 0;
constexpr unsigned ccUDR1_1 = 1;
constexpr unsigned ccUDR1_2 = 2;
constexpr unsigned ccUDR1_3 = 3;
constexpr unsigned ccUDR1_4 = 4;
constexpr unsigned ccUDR1_5 = 5;
constexpr unsigned ccUDR1_6 = 6;
constexpr unsigned ccUDR1_7 = 7;
constexpr unsigned ccUDRE0 = 5;
constexpr unsigned ccUDRE1 = 5;
constexpr unsigned ccUDRIE0 = 5;
constexpr unsigned ccUDRIE1 = 5;
constexpr unsigned ccUMSEL00 = 6;
constexpr unsigned ccUMSEL01 = 7;
constexpr unsigned ccUMSEL10 = 6;
constexpr unsigned ccUMSEL11 = 7;
constexpr unsigned ccUPE0 = 2;
constexpr unsigned ccUPE1 = 2;
constexpr unsigned ccUPM00 = 4;
constexpr unsigned ccUPM01 = 5;
constexpr unsigned ccUPM10 = 4;
constexpr unsigned ccUPM11 = 5;
constexpr unsigned ccUSART0_RX_vect_num = 20;
constexpr unsigned ccUSART0_TX_vect_num = 22;
constexpr unsigned ccUSART0_UDRE_vect_num = 21;
constexpr unsigned ccUSART1_RX_vect_num = 28;
constexpr unsigned ccUSART1_TX_vect_num = 30;
constexpr unsigned ccUSART1_UDRE_vect_num = 29;
constexpr unsigned ccUSBS0 = 3;
constexpr unsigned ccUSBS1 = 3;
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
constexpr unsigned ccWDT_vect_num = 8;
constexpr unsigned ccWGM00 = 0;
constexpr unsigned ccWGM01 = 1;
constexpr unsigned ccWGM02 = 3;
constexpr unsigned ccWGM10 = 0;
constexpr unsigned ccWGM11 = 1;
constexpr unsigned ccWGM12 = 3;
constexpr unsigned ccWGM13 = 4;
constexpr unsigned ccWGM20 = 0;
constexpr unsigned ccWGM21 = 1;
constexpr unsigned ccWGM22 = 3;
constexpr unsigned ccXCK1_BIT = 4;
constexpr unsigned ccXCK_BIT = 0;
constexpr unsigned ccXRAMSIZE = 0;
constexpr unsigned ccXRAMSTART = 0x0;
constexpr unsigned cc_HAVE_AVR_STACK_POINTER_HI = 1;
constexpr unsigned cc_SFR_ASM_COMPAT = 0;
constexpr unsigned cc_UBRR0 = 0;
constexpr unsigned cc_UBRR1 = 1;
constexpr unsigned cc_VECTORS_SIZE = 31;
constexpr unsigned cc_VECTOR_SIZE = 4;
constexpr unsigned cc__USING_MINT8 = 0;


}  // arch_atmega644pa
}  // namespace avr
}  // namespace sys
}  // namespace ardo

#endif  // ardo_supplemental_atmega644pa__h
