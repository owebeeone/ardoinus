// Generated for arch atmega1284.
// This file is generated from the avr-gcc compiler with the mcu
// set to atmega1284 from macros specific to avr/io.h.
// Any changes to this file will likely be lost next time this file
// is regenerated. Many any mcu_arch specific changes to 
// ardo_supplemental_atmega1284_defs.h.

#ifndef ardo_supplemental_atmega1284__h
#define ardo_supplemental_atmega1284__h

#include "setlx_cstdint.h"
#include "setl_bit_fields.h"
#include "ardo_avr_bit_io_defs.h"

namespace ardo {
namespace sys {
namespace avr {
namespace arch_atmega1284 {

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
constexpr unsigned ccADC1D = 1;
constexpr unsigned ccADC2D = 2;
constexpr unsigned ccADC3D = 3;
constexpr unsigned ccADC4D = 4;
constexpr unsigned ccADC5D = 5;
constexpr unsigned ccADC6D = 6;
constexpr unsigned ccADC7D = 7;
using rrADCH = MemRegisterDef<std::uint8_t, 0x79>;
using rrADCL = MemRegisterDef<std::uint8_t, 0x78>;
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
constexpr unsigned ccAIN1D = 1;
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
constexpr unsigned ccBORF = 2;
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
constexpr unsigned ccCOM3A0 = 6;
constexpr unsigned ccCOM3A1 = 7;
constexpr unsigned ccCOM3B0 = 4;
constexpr unsigned ccCOM3B1 = 5;
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
constexpr unsigned ccCS30 = 0;
constexpr unsigned ccCS31 = 1;
constexpr unsigned ccCS32 = 2;
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
constexpr unsigned ccDDRA0 = 0;
constexpr unsigned ccDDRA1 = 1;
constexpr unsigned ccDDRA2 = 2;
constexpr unsigned ccDDRA3 = 3;
constexpr unsigned ccDDRA4 = 4;
constexpr unsigned ccDDRA5 = 5;
constexpr unsigned ccDDRA6 = 6;
constexpr unsigned ccDDRA7 = 7;
using rrDDRB = IoRegisterDef<std::uint8_t, 0x04>;
constexpr unsigned ccDDRB0 = 0;
constexpr unsigned ccDDRB1 = 1;
constexpr unsigned ccDDRB2 = 2;
constexpr unsigned ccDDRB3 = 3;
constexpr unsigned ccDDRB4 = 4;
constexpr unsigned ccDDRB5 = 5;
constexpr unsigned ccDDRB6 = 6;
constexpr unsigned ccDDRB7 = 7;
using rrDDRC = IoRegisterDef<std::uint8_t, 0x07>;
constexpr unsigned ccDDRC0 = 0;
constexpr unsigned ccDDRC1 = 1;
constexpr unsigned ccDDRC2 = 2;
constexpr unsigned ccDDRC3 = 3;
constexpr unsigned ccDDRC4 = 4;
constexpr unsigned ccDDRC5 = 5;
constexpr unsigned ccDDRC6 = 6;
constexpr unsigned ccDDRC7 = 7;
using rrDDRD = IoRegisterDef<std::uint8_t, 0x0A>;
constexpr unsigned ccDDRD0 = 0;
constexpr unsigned ccDDRD1 = 1;
constexpr unsigned ccDDRD2 = 2;
constexpr unsigned ccDDRD3 = 3;
constexpr unsigned ccDDRD4 = 4;
constexpr unsigned ccDDRD5 = 5;
constexpr unsigned ccDDRD6 = 6;
constexpr unsigned ccDDRD7 = 7;
using rrDIDR0 = MemRegisterDef<std::uint8_t, 0x7E>;
using rrDIDR1 = MemRegisterDef<std::uint8_t, 0x7F>;
constexpr unsigned ccDOR0 = 3;
constexpr unsigned ccDOR1 = 3;
constexpr unsigned ccDORD = 5;
constexpr unsigned ccE2END = 0x0FFF;
constexpr unsigned ccE2PAGESIZE = 8;
constexpr unsigned ccE2SIZE = 4096;
constexpr unsigned ccE2START = 0;
using rrEEAR = IoRegisterDef<std::uint16_t, 0x21>;
using rrEEARH = IoRegisterDef<std::uint8_t, 0x22>;
using rrEEARL = IoRegisterDef<std::uint8_t, 0x21>;
using rrEECR = IoRegisterDef<std::uint8_t, 0x1F>;
using rrEEDR = IoRegisterDef<std::uint8_t, 0x20>;
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
constexpr unsigned ccFLASHEND = 0x1FFFF;
constexpr unsigned ccFLASHSTART = 0x0000;
constexpr unsigned ccFOC0A = 7;
constexpr unsigned ccFOC0B = 6;
constexpr unsigned ccFOC1A = 7;
constexpr unsigned ccFOC1B = 6;
constexpr unsigned ccFOC2A = 7;
constexpr unsigned ccFOC2B = 6;
constexpr unsigned ccFOC3A = 7;
constexpr unsigned ccFOC3B = 6;
using ffFUSE_BODLEVEL0 = setl::BitsRW<setl::SemanticType<setl::hash("FUSE_BODLEVEL0"), bool>, 1u<<0>;
using ffFUSE_BODLEVEL1 = setl::BitsRW<setl::SemanticType<setl::hash("FUSE_BODLEVEL1"), bool>, 1u<<1>;
using ffFUSE_BODLEVEL2 = setl::BitsRW<setl::SemanticType<setl::hash("FUSE_BODLEVEL2"), bool>, 1u<<2>;
using ffFUSE_BOOTRST = setl::BitsRW<setl::SemanticType<setl::hash("FUSE_BOOTRST"), bool>, 1u<<0>;
using ffFUSE_BOOTSZ0 = setl::BitsRW<setl::SemanticType<setl::hash("FUSE_BOOTSZ0"), bool>, 1u<<1>;
using ffFUSE_BOOTSZ1 = setl::BitsRW<setl::SemanticType<setl::hash("FUSE_BOOTSZ1"), bool>, 1u<<2>;
using ffFUSE_CKDIV8 = setl::BitsRW<setl::SemanticType<setl::hash("FUSE_CKDIV8"), bool>, 1u<<7>;
using ffFUSE_CKOUT = setl::BitsRW<setl::SemanticType<setl::hash("FUSE_CKOUT"), bool>, 1u<<6>;
using ffFUSE_EESAVE = setl::BitsRW<setl::SemanticType<setl::hash("FUSE_EESAVE"), bool>, 1u<<3>;
using ffFUSE_JTAGEN = setl::BitsRW<setl::SemanticType<setl::hash("FUSE_JTAGEN"), bool>, 1u<<6>;
constexpr unsigned ccFUSE_MEMORY_SIZE = 3;
using ffFUSE_OCDEN = setl::BitsRW<setl::SemanticType<setl::hash("FUSE_OCDEN"), bool>, 1u<<7>;
using ffFUSE_SPIEN = setl::BitsRW<setl::SemanticType<setl::hash("FUSE_SPIEN"), bool>, 1u<<5>;
using ffFUSE_SUT_CKSEL0 = setl::BitsRW<setl::SemanticType<setl::hash("FUSE_SUT_CKSEL0"), bool>, 1u<<0>;
using ffFUSE_SUT_CKSEL1 = setl::BitsRW<setl::SemanticType<setl::hash("FUSE_SUT_CKSEL1"), bool>, 1u<<1>;
using ffFUSE_SUT_CKSEL2 = setl::BitsRW<setl::SemanticType<setl::hash("FUSE_SUT_CKSEL2"), bool>, 1u<<2>;
using ffFUSE_SUT_CKSEL3 = setl::BitsRW<setl::SemanticType<setl::hash("FUSE_SUT_CKSEL3"), bool>, 1u<<3>;
using ffFUSE_SUT_CKSEL4 = setl::BitsRW<setl::SemanticType<setl::hash("FUSE_SUT_CKSEL4"), bool>, 1u<<4>;
using ffFUSE_SUT_CKSEL5 = setl::BitsRW<setl::SemanticType<setl::hash("FUSE_SUT_CKSEL5"), bool>, 1u<<5>;
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
constexpr unsigned ccICES3 = 6;
constexpr unsigned ccICF1 = 5;
constexpr unsigned ccICF3 = 5;
constexpr unsigned ccICIE1 = 5;
constexpr unsigned ccICIE3 = 5;
constexpr unsigned ccICNC1 = 7;
constexpr unsigned ccICNC3 = 7;
using rrICR1 = MemRegisterDef<std::uint16_t, 0x86>;
using rrICR1H = MemRegisterDef<std::uint8_t, 0x87>;
using rrICR1L = MemRegisterDef<std::uint8_t, 0x86>;
using rrICR3 = MemRegisterDef<std::uint16_t, 0x96>;
using rrICR3H = MemRegisterDef<std::uint8_t, 0x97>;
using rrICR3L = MemRegisterDef<std::uint8_t, 0x96>;
constexpr unsigned ccINT0 = 0;
constexpr unsigned ccINT0_vect_num = 1;
constexpr unsigned ccINT1 = 1;
constexpr unsigned ccINT1_vect_num = 2;
constexpr unsigned ccINT2 = 2;
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
constexpr unsigned ccMPCM0 = 0;
constexpr unsigned ccMPCM1 = 0;
constexpr unsigned ccMSTR = 4;
constexpr unsigned ccMUX0 = 0;
constexpr unsigned ccMUX1 = 1;
constexpr unsigned ccMUX2 = 2;
constexpr unsigned ccMUX3 = 3;
constexpr unsigned ccMUX4 = 4;
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
constexpr unsigned ccOCF3A = 1;
constexpr unsigned ccOCF3B = 2;
constexpr unsigned ccOCIE0A = 1;
constexpr unsigned ccOCIE0B = 2;
constexpr unsigned ccOCIE1A = 1;
constexpr unsigned ccOCIE1B = 2;
constexpr unsigned ccOCIE2A = 1;
constexpr unsigned ccOCIE2B = 2;
constexpr unsigned ccOCIE3A = 1;
constexpr unsigned ccOCIE3B = 2;
using rrOCR0A = IoRegisterDef<std::uint8_t, 0x27>;
using rrOCR0B = IoRegisterDef<std::uint8_t, 0x28>;
using rrOCR1A = MemRegisterDef<std::uint16_t, 0x88>;
using rrOCR1AH = MemRegisterDef<std::uint8_t, 0x89>;
using rrOCR1AL = MemRegisterDef<std::uint8_t, 0x88>;
using rrOCR1B = MemRegisterDef<std::uint16_t, 0x8A>;
using rrOCR1BH = MemRegisterDef<std::uint8_t, 0x8B>;
using rrOCR1BL = MemRegisterDef<std::uint8_t, 0x8A>;
using rrOCR2A = MemRegisterDef<std::uint8_t, 0xB3>;
constexpr unsigned ccOCR2AUB = 3;
using rrOCR2B = MemRegisterDef<std::uint8_t, 0xB4>;
constexpr unsigned ccOCR2BUB = 2;
using rrOCR3A = MemRegisterDef<std::uint16_t, 0x98>;
using rrOCR3AH = MemRegisterDef<std::uint8_t, 0x99>;
using rrOCR3AL = MemRegisterDef<std::uint8_t, 0x98>;
using rrOCR3B = MemRegisterDef<std::uint16_t, 0x9A>;
using rrOCR3BH = MemRegisterDef<std::uint8_t, 0x9B>;
using rrOCR3BL = MemRegisterDef<std::uint8_t, 0x9A>;
using rrOSCCAL = MemRegisterDef<std::uint8_t, 0x66>;
constexpr unsigned ccOSCCAL0 = 0;
constexpr unsigned ccOSCCAL1 = 1;
constexpr unsigned ccOSCCAL2 = 2;
constexpr unsigned ccOSCCAL3 = 3;
constexpr unsigned ccOSCCAL4 = 4;
constexpr unsigned ccOSCCAL5 = 5;
constexpr unsigned ccOSCCAL6 = 6;
constexpr unsigned ccOSCCAL7 = 7;
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
constexpr unsigned ccPCINT0_vect_num = 4;
constexpr unsigned ccPCINT1 = 1;
constexpr unsigned ccPCINT10 = 2;
constexpr unsigned ccPCINT11 = 3;
constexpr unsigned ccPCINT12 = 4;
constexpr unsigned ccPCINT13 = 5;
constexpr unsigned ccPCINT14 = 6;
constexpr unsigned ccPCINT15 = 7;
constexpr unsigned ccPCINT16 = 0;
constexpr unsigned ccPCINT17 = 1;
constexpr unsigned ccPCINT18 = 2;
constexpr unsigned ccPCINT19 = 3;
constexpr unsigned ccPCINT1_vect_num = 5;
constexpr unsigned ccPCINT2 = 2;
constexpr unsigned ccPCINT20 = 4;
constexpr unsigned ccPCINT21 = 5;
constexpr unsigned ccPCINT22 = 6;
constexpr unsigned ccPCINT23 = 7;
constexpr unsigned ccPCINT24 = 0;
constexpr unsigned ccPCINT25 = 1;
constexpr unsigned ccPCINT26 = 2;
constexpr unsigned ccPCINT27 = 3;
constexpr unsigned ccPCINT28 = 4;
constexpr unsigned ccPCINT29 = 5;
constexpr unsigned ccPCINT2_vect_num = 6;
constexpr unsigned ccPCINT3 = 3;
constexpr unsigned ccPCINT30 = 6;
constexpr unsigned ccPCINT31 = 7;
constexpr unsigned ccPCINT3_vect_num = 7;
constexpr unsigned ccPCINT4 = 4;
constexpr unsigned ccPCINT5 = 5;
constexpr unsigned ccPCINT6 = 6;
constexpr unsigned ccPCINT7 = 7;
constexpr unsigned ccPCINT8 = 0;
constexpr unsigned ccPCINT9 = 1;
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
using rrPRR1 = MemRegisterDef<std::uint8_t, 0x65>;
constexpr unsigned ccPRSPI = 2;
constexpr unsigned ccPRTIM0 = 5;
constexpr unsigned ccPRTIM1 = 3;
constexpr unsigned ccPRTIM2 = 6;
constexpr unsigned ccPRTIM3 = 0;
constexpr unsigned ccPRTWI = 7;
constexpr unsigned ccPRUSART0 = 1;
constexpr unsigned ccPRUSART1 = 4;
constexpr unsigned ccPSRASY = 1;
constexpr unsigned ccPSRSYNC = 0;
constexpr unsigned ccPUD = 4;
constexpr unsigned ccRAMEND = 0x40FF;
using rrRAMPZ = IoRegisterDef<std::uint8_t, 0x3B>;
constexpr unsigned ccRAMSIZE = 16384;
constexpr unsigned ccRAMSTART = 0x0100;
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
constexpr unsigned ccRXEN0 = 4;
constexpr unsigned ccRXEN1 = 4;
constexpr unsigned ccSE = 0;
constexpr unsigned ccSIGNATURE_0 = 0x1E;
constexpr unsigned ccSIGNATURE_1 = 0x97;
constexpr unsigned ccSIGNATURE_2 = 0x06;
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
using rrTCCR0A = IoRegisterDef<std::uint8_t, 0x24>;
using rrTCCR0B = IoRegisterDef<std::uint8_t, 0x25>;
using rrTCCR1A = MemRegisterDef<std::uint8_t, 0x80>;
using rrTCCR1B = MemRegisterDef<std::uint8_t, 0x81>;
using rrTCCR1C = MemRegisterDef<std::uint8_t, 0x82>;
using rrTCCR2A = MemRegisterDef<std::uint8_t, 0xB0>;
using rrTCCR2B = MemRegisterDef<std::uint8_t, 0xB1>;
using rrTCCR3A = MemRegisterDef<std::uint8_t, 0x90>;
using rrTCCR3B = MemRegisterDef<std::uint8_t, 0x91>;
using rrTCCR3C = MemRegisterDef<std::uint8_t, 0x92>;
constexpr unsigned ccTCN2UB = 4;
using rrTCNT0 = IoRegisterDef<std::uint8_t, 0x26>;
using rrTCNT1 = MemRegisterDef<std::uint16_t, 0x84>;
using rrTCNT1H = MemRegisterDef<std::uint8_t, 0x85>;
using rrTCNT1L = MemRegisterDef<std::uint8_t, 0x84>;
using rrTCNT2 = MemRegisterDef<std::uint8_t, 0xB2>;
using rrTCNT3 = MemRegisterDef<std::uint16_t, 0x94>;
using rrTCNT3H = MemRegisterDef<std::uint8_t, 0x95>;
using rrTCNT3L = MemRegisterDef<std::uint8_t, 0x94>;
constexpr unsigned ccTCR2AUB = 1;
constexpr unsigned ccTCR2BUB = 0;
using rrTIFR0 = IoRegisterDef<std::uint8_t, 0x15>;
using rrTIFR1 = IoRegisterDef<std::uint8_t, 0x16>;
using rrTIFR2 = IoRegisterDef<std::uint8_t, 0x17>;
using rrTIFR3 = IoRegisterDef<std::uint8_t, 0x18>;
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
constexpr unsigned ccTIMER3_CAPT_vect_num = 31;
constexpr unsigned ccTIMER3_COMPA_vect_num = 32;
constexpr unsigned ccTIMER3_COMPB_vect_num = 33;
constexpr unsigned ccTIMER3_OVF_vect_num = 34;
using rrTIMSK0 = MemRegisterDef<std::uint8_t, 0x6E>;
using rrTIMSK1 = MemRegisterDef<std::uint8_t, 0x6F>;
using rrTIMSK2 = MemRegisterDef<std::uint8_t, 0x70>;
using rrTIMSK3 = MemRegisterDef<std::uint8_t, 0x71>;
constexpr unsigned ccTOIE0 = 0;
constexpr unsigned ccTOIE1 = 0;
constexpr unsigned ccTOIE2 = 0;
constexpr unsigned ccTOIE3 = 0;
constexpr unsigned ccTOV0 = 0;
constexpr unsigned ccTOV1 = 0;
constexpr unsigned ccTOV2 = 0;
constexpr unsigned ccTOV3 = 0;
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
using rrTWCR = MemRegisterDef<std::uint8_t, 0xBC>;
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
constexpr unsigned ccTXEN0 = 3;
constexpr unsigned ccTXEN1 = 3;
constexpr unsigned ccU2X0 = 1;
constexpr unsigned ccU2X1 = 1;
using rrUBRR0 = MemRegisterDef<std::uint16_t, 0xC4>;
using rrUBRR0H = MemRegisterDef<std::uint8_t, 0xC5>;
using rrUBRR0L = MemRegisterDef<std::uint8_t, 0xC4>;
using rrUBRR1 = MemRegisterDef<std::uint16_t, 0xCC>;
using rrUBRR1H = MemRegisterDef<std::uint8_t, 0xCD>;
using rrUBRR1L = MemRegisterDef<std::uint8_t, 0xCC>;
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
using rrUDR1 = MemRegisterDef<std::uint8_t, 0xCE>;
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
constexpr unsigned ccWGM30 = 0;
constexpr unsigned ccWGM31 = 1;
constexpr unsigned ccWGM32 = 3;
constexpr unsigned ccWGM33 = 4;
constexpr unsigned cc_HAVE_AVR_STACK_POINTER_HI = 1;
constexpr unsigned cc_SFR_ASM_COMPAT = 0;
constexpr unsigned cc_VECTORS_SIZE = 140;
constexpr unsigned cc__AVR_HAVE_PRR1 = 1;
constexpr unsigned cc__USING_MINT8 = 0;


}  // arch_atmega1284
}  // namespace avr
}  // namespace sys
}  // namespace ardo

#endif  // ardo_supplemental_atmega1284__h
