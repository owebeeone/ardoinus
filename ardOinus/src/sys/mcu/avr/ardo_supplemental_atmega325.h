// Generated for arch atmega325.
// This file is generated from the avr-gcc compiler with the mcu
// set to atmega325 from macros specific to avr/io.h.
// Any changes to this file will likely be lost next time this file
// is regenerated. Many any mcu_arch specific changes to 
// ardo_supplemental_atmega325_defs.h.

#ifndef ardo_supplemental_atmega325__h
#define ardo_supplemental_atmega325__h

#include "setlx_cstdint.h"
#include "setl_bit_fields.h"
#include "ardo_avr_bit_io_defs.h"

namespace ardo {
namespace sys {
namespace avr {
namespace arch_atmega325 {

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
constexpr unsigned ccADC_vect_num = 19;
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
constexpr unsigned ccANALOG_COMP_vect_num = 18;
constexpr unsigned ccAS2 = 3;
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
constexpr unsigned ccCOM0A0 = 4;
constexpr unsigned ccCOM0A1 = 5;
constexpr unsigned ccCOM1A0 = 6;
constexpr unsigned ccCOM1A1 = 7;
constexpr unsigned ccCOM1B0 = 4;
constexpr unsigned ccCOM1B1 = 5;
constexpr unsigned ccCOM2A0 = 4;
constexpr unsigned ccCOM2A1 = 5;
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
constexpr unsigned ccDDE0 = 0;
constexpr unsigned ccDDE1 = 1;
constexpr unsigned ccDDE2 = 2;
constexpr unsigned ccDDE3 = 3;
constexpr unsigned ccDDE4 = 4;
constexpr unsigned ccDDE5 = 5;
constexpr unsigned ccDDE6 = 6;
constexpr unsigned ccDDE7 = 7;
constexpr unsigned ccDDF0 = 0;
constexpr unsigned ccDDF1 = 1;
constexpr unsigned ccDDF2 = 2;
constexpr unsigned ccDDF3 = 3;
constexpr unsigned ccDDF4 = 4;
constexpr unsigned ccDDF5 = 5;
constexpr unsigned ccDDF6 = 6;
constexpr unsigned ccDDF7 = 7;
constexpr unsigned ccDDG0 = 0;
constexpr unsigned ccDDG1 = 1;
constexpr unsigned ccDDG2 = 2;
constexpr unsigned ccDDG3 = 3;
constexpr unsigned ccDDG4 = 4;
using rrDDRA = IoRegisterDef<std::uint8_t, 0x01>;
using rrDDRB = IoRegisterDef<std::uint8_t, 0x04>;
using rrDDRC = IoRegisterDef<std::uint8_t, 0x07>;
using rrDDRD = IoRegisterDef<std::uint8_t, 0x0A>;
using rrDDRE = IoRegisterDef<std::uint8_t, 0x0D>;
using rrDDRF = IoRegisterDef<std::uint8_t, 0x10>;
using rrDDRG = IoRegisterDef<std::uint8_t, 0x13>;
using rrDIDR0 = MemRegisterDef<std::uint8_t, 0x7E>;
using rrDIDR1 = MemRegisterDef<std::uint8_t, 0x7F>;
constexpr unsigned ccDOR0 = 3;
constexpr unsigned ccDORD = 5;
constexpr unsigned ccE2END = 0x3FF;
constexpr unsigned ccE2PAGESIZE = 4;
using rrEEAR = IoRegisterDef<std::uint16_t, 0x21>;
using rrEEARL = IoRegisterDef<std::uint8_t, 0x21>;
using rrEECR = IoRegisterDef<std::uint8_t, 0x1F>;
constexpr unsigned ccEEMWE = 2;
constexpr unsigned ccEERE = 0;
constexpr unsigned ccEERIE = 3;
constexpr unsigned ccEEWE = 1;
constexpr unsigned ccEE_READY_vect_num = 20;
constexpr unsigned ccEFUSE_DEFAULT = 0xFF;
using rrEICRA = MemRegisterDef<std::uint8_t, 0x69>;
using rrEIFR = IoRegisterDef<std::uint8_t, 0x1C>;
using rrEIMSK = IoRegisterDef<std::uint8_t, 0x1D>;
constexpr unsigned ccEXCLK = 4;
constexpr unsigned ccEXTRF = 1;
constexpr unsigned ccFE0 = 4;
constexpr unsigned ccFLASHEND = 0x7FFF;
constexpr unsigned ccFOC0A = 7;
constexpr unsigned ccFOC1A = 7;
constexpr unsigned ccFOC1B = 6;
constexpr unsigned ccFOC2A = 7;
using ffFUSE_BODLEVEL0 = setl::BitsRW<setl::SemanticType<setl::hash("FUSE_BODLEVEL0"), bool>, 1u<<1>;
using ffFUSE_BODLEVEL1 = setl::BitsRW<setl::SemanticType<setl::hash("FUSE_BODLEVEL1"), bool>, 1u<<2>;
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
using ffFUSE_RSTDISBL = setl::BitsRW<setl::SemanticType<setl::hash("FUSE_RSTDISBL"), bool>, 1u<<0>;
using ffFUSE_SPIEN = setl::BitsRW<setl::SemanticType<setl::hash("FUSE_SPIEN"), bool>, 1u<<5>;
using ffFUSE_SUT0 = setl::BitsRW<setl::SemanticType<setl::hash("FUSE_SUT0"), bool>, 1u<<4>;
using ffFUSE_SUT1 = setl::BitsRW<setl::SemanticType<setl::hash("FUSE_SUT1"), bool>, 1u<<5>;
using ffFUSE_WDTON = setl::BitsRW<setl::SemanticType<setl::hash("FUSE_WDTON"), bool>, 1u<<4>;
using rrGPIOR0 = IoRegisterDef<std::uint8_t, 0x1E>;
using rrGPIOR1 = IoRegisterDef<std::uint8_t, 0x2A>;
using rrGPIOR2 = IoRegisterDef<std::uint8_t, 0x2B>;
using rrGTCCR = IoRegisterDef<std::uint8_t, 0x23>;
constexpr unsigned ccICES1 = 6;
constexpr unsigned ccICF1 = 5;
constexpr unsigned ccICIE1 = 5;
constexpr unsigned ccICNC1 = 7;
using rrICR1 = MemRegisterDef<std::uint16_t, 0x86>;
using rrICR1H = MemRegisterDef<std::uint8_t, 0x87>;
using rrICR1L = MemRegisterDef<std::uint8_t, 0x86>;
constexpr unsigned ccIDRD = 7;
constexpr unsigned ccINT0 = 0;
constexpr unsigned ccINT0_vect_num = 1;
constexpr unsigned ccINTF0 = 0;
constexpr unsigned ccISC00 = 0;
constexpr unsigned ccISC01 = 1;
constexpr unsigned ccIVCE = 0;
constexpr unsigned ccIVSEL = 1;
constexpr unsigned ccJTD = 7;
constexpr unsigned ccJTRF = 4;
constexpr unsigned ccLB_MODE_1 = 0xFF;
constexpr unsigned ccLB_MODE_2 = 0xFE;
constexpr unsigned ccLB_MODE_3 = 0xFC;
constexpr unsigned ccLOCKBITS_DEFAULT = 0xFF;
using rrMCUSR = IoRegisterDef<std::uint8_t, 0x34>;
constexpr unsigned ccMPCM0 = 0;
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
constexpr unsigned ccOCF1A = 1;
constexpr unsigned ccOCF1B = 2;
constexpr unsigned ccOCF2A = 1;
constexpr unsigned ccOCIE0A = 1;
constexpr unsigned ccOCIE1A = 1;
constexpr unsigned ccOCIE1B = 2;
constexpr unsigned ccOCIE2A = 1;
using rrOCR1A = MemRegisterDef<std::uint16_t, 0x88>;
using rrOCR1AH = MemRegisterDef<std::uint8_t, 0x89>;
using rrOCR1AL = MemRegisterDef<std::uint8_t, 0x88>;
using rrOCR1B = MemRegisterDef<std::uint16_t, 0x8A>;
using rrOCR1BH = MemRegisterDef<std::uint8_t, 0x8B>;
using rrOCR1BL = MemRegisterDef<std::uint8_t, 0x8A>;
using rrOCR2A = MemRegisterDef<std::uint8_t, 0xB3>;
constexpr unsigned ccOCR2UB = 1;
using rrOSCCAL = MemRegisterDef<std::uint8_t, 0x66>;
constexpr unsigned ccPA0 = 0;
constexpr unsigned ccPA1 = 1;
constexpr unsigned ccPA2 = 2;
constexpr unsigned ccPA3 = 3;
constexpr unsigned ccPA4 = 4;
constexpr unsigned ccPA5 = 5;
constexpr unsigned ccPA6 = 6;
constexpr unsigned ccPA7 = 7;
constexpr unsigned ccPB0 = 0;
constexpr unsigned ccPB1 = 1;
constexpr unsigned ccPB2 = 2;
constexpr unsigned ccPB3 = 3;
constexpr unsigned ccPB4 = 4;
constexpr unsigned ccPB5 = 5;
constexpr unsigned ccPB6 = 6;
constexpr unsigned ccPB7 = 7;
constexpr unsigned ccPC0 = 0;
constexpr unsigned ccPC1 = 1;
constexpr unsigned ccPC2 = 2;
constexpr unsigned ccPC3 = 3;
constexpr unsigned ccPC4 = 4;
constexpr unsigned ccPC5 = 5;
constexpr unsigned ccPC6 = 6;
constexpr unsigned ccPC7 = 7;
constexpr unsigned ccPCIE0 = 4;
constexpr unsigned ccPCIE1 = 5;
constexpr unsigned ccPCIF0 = 4;
constexpr unsigned ccPCIF1 = 5;
constexpr unsigned ccPCINT0 = 0;
constexpr unsigned ccPCINT0_vect_num = 2;
constexpr unsigned ccPCINT1 = 1;
constexpr unsigned ccPCINT10 = 2;
constexpr unsigned ccPCINT11 = 3;
constexpr unsigned ccPCINT12 = 4;
constexpr unsigned ccPCINT13 = 5;
constexpr unsigned ccPCINT14 = 6;
constexpr unsigned ccPCINT15 = 7;
constexpr unsigned ccPCINT1_vect_num = 3;
constexpr unsigned ccPCINT2 = 2;
constexpr unsigned ccPCINT3 = 3;
constexpr unsigned ccPCINT4 = 4;
constexpr unsigned ccPCINT5 = 5;
constexpr unsigned ccPCINT6 = 6;
constexpr unsigned ccPCINT7 = 7;
constexpr unsigned ccPCINT8 = 0;
constexpr unsigned ccPCINT9 = 1;
using rrPCMSK0 = MemRegisterDef<std::uint8_t, 0x6B>;
using rrPCMSK1 = MemRegisterDef<std::uint8_t, 0x6C>;
constexpr unsigned ccPD0 = 0;
constexpr unsigned ccPD1 = 1;
constexpr unsigned ccPD2 = 2;
constexpr unsigned ccPD3 = 3;
constexpr unsigned ccPD4 = 4;
constexpr unsigned ccPD5 = 5;
constexpr unsigned ccPD6 = 6;
constexpr unsigned ccPD7 = 7;
constexpr unsigned ccPE0 = 0;
constexpr unsigned ccPE1 = 1;
constexpr unsigned ccPE2 = 2;
constexpr unsigned ccPE3 = 3;
constexpr unsigned ccPE4 = 4;
constexpr unsigned ccPE5 = 5;
constexpr unsigned ccPE6 = 6;
constexpr unsigned ccPE7 = 7;
constexpr unsigned ccPF0 = 0;
constexpr unsigned ccPF1 = 1;
constexpr unsigned ccPF2 = 2;
constexpr unsigned ccPF3 = 3;
constexpr unsigned ccPF4 = 4;
constexpr unsigned ccPF5 = 5;
constexpr unsigned ccPF6 = 6;
constexpr unsigned ccPF7 = 7;
constexpr unsigned ccPG0 = 0;
constexpr unsigned ccPG1 = 1;
constexpr unsigned ccPG2 = 2;
constexpr unsigned ccPG3 = 3;
constexpr unsigned ccPG4 = 4;
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
using rrPINE = IoRegisterDef<std::uint8_t, 0x0C>;
constexpr unsigned ccPINE0 = 0;
constexpr unsigned ccPINE1 = 1;
constexpr unsigned ccPINE2 = 2;
constexpr unsigned ccPINE3 = 3;
constexpr unsigned ccPINE4 = 4;
constexpr unsigned ccPINE5 = 5;
constexpr unsigned ccPINE6 = 6;
constexpr unsigned ccPINE7 = 7;
using rrPINF = IoRegisterDef<std::uint8_t, 0x0F>;
constexpr unsigned ccPINF0 = 0;
constexpr unsigned ccPINF1 = 1;
constexpr unsigned ccPINF2 = 2;
constexpr unsigned ccPINF3 = 3;
constexpr unsigned ccPINF4 = 4;
constexpr unsigned ccPINF5 = 5;
constexpr unsigned ccPINF6 = 6;
constexpr unsigned ccPINF7 = 7;
using rrPING = IoRegisterDef<std::uint8_t, 0x12>;
constexpr unsigned ccPING0 = 0;
constexpr unsigned ccPING1 = 1;
constexpr unsigned ccPING2 = 2;
constexpr unsigned ccPING3 = 3;
constexpr unsigned ccPING4 = 4;
constexpr unsigned ccPING5 = 5;
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
using rrPORTB = IoRegisterDef<std::uint8_t, 0x05>;
using rrPORTC = IoRegisterDef<std::uint8_t, 0x08>;
using rrPORTD = IoRegisterDef<std::uint8_t, 0x0B>;
using rrPORTE = IoRegisterDef<std::uint8_t, 0x0E>;
using rrPORTF = IoRegisterDef<std::uint8_t, 0x11>;
using rrPORTG = IoRegisterDef<std::uint8_t, 0x14>;
constexpr unsigned ccPRADC = 0;
using rrPRR = MemRegisterDef<std::uint8_t, 0x64>;
constexpr unsigned ccPRSPI = 2;
constexpr unsigned ccPRTIM1 = 3;
constexpr unsigned ccPRUSART0 = 1;
constexpr unsigned ccPSR10 = 0;
constexpr unsigned ccPSR2 = 1;
constexpr unsigned ccPUD = 4;
constexpr unsigned ccRAMEND = 0x8FF;
constexpr unsigned ccRAMSTART = 0x100;
constexpr unsigned ccREFS0 = 6;
constexpr unsigned ccREFS1 = 7;
constexpr unsigned ccRWWSB = 6;
constexpr unsigned ccRWWSRE = 4;
constexpr unsigned ccRXB80 = 1;
constexpr unsigned ccRXC0 = 7;
constexpr unsigned ccRXCIE0 = 7;
constexpr unsigned ccRXEN0 = 4;
constexpr unsigned ccSE = 0;
constexpr unsigned ccSIGNATURE_0 = 0x1E;
constexpr unsigned ccSIGNATURE_1 = 0x95;
constexpr unsigned ccSIGNATURE_2 = 0x05;
constexpr unsigned ccSLEEP_MODE_ADC = 0x01;
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
constexpr unsigned ccSPE = 6;
using rrSPH = IoRegisterDef<std::uint8_t, 0x3E>;
constexpr unsigned ccSPI2X = 0;
constexpr unsigned ccSPIE = 7;
constexpr unsigned ccSPIF = 7;
constexpr unsigned ccSPI_STC_vect_num = 12;
using rrSPL = IoRegisterDef<std::uint8_t, 0x3D>;
using rrSPMCSR = IoRegisterDef<std::uint8_t, 0x37>;
constexpr unsigned ccSPMEN = 0;
constexpr unsigned ccSPMIE = 7;
constexpr unsigned ccSPM_PAGESIZE = 128;
constexpr unsigned ccSPM_READY_vect_num = 21;
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
using rrTCCR1C = MemRegisterDef<std::uint8_t, 0x82>;
using rrTCCR2A = MemRegisterDef<std::uint8_t, 0xB0>;
constexpr unsigned ccTCN2UB = 2;
using rrTCNT1 = MemRegisterDef<std::uint16_t, 0x84>;
using rrTCNT1H = MemRegisterDef<std::uint8_t, 0x85>;
using rrTCNT1L = MemRegisterDef<std::uint8_t, 0x84>;
using rrTCNT2 = MemRegisterDef<std::uint8_t, 0xB2>;
constexpr unsigned ccTCR2UB = 0;
using rrTIFR0 = IoRegisterDef<std::uint8_t, 0x15>;
using rrTIFR1 = IoRegisterDef<std::uint8_t, 0x16>;
using rrTIFR2 = IoRegisterDef<std::uint8_t, 0x17>;
constexpr unsigned ccTIMER0_COMP_vect_num = 10;
constexpr unsigned ccTIMER0_OVF_vect_num = 11;
constexpr unsigned ccTIMER1_CAPT_vect_num = 6;
constexpr unsigned ccTIMER1_COMPA_vect_num = 7;
constexpr unsigned ccTIMER1_COMPB_vect_num = 8;
constexpr unsigned ccTIMER1_OVF_vect_num = 9;
constexpr unsigned ccTIMER2_COMP_vect_num = 4;
constexpr unsigned ccTIMER2_OVF_vect_num = 5;
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
constexpr unsigned ccTXB80 = 0;
constexpr unsigned ccTXC0 = 6;
constexpr unsigned ccTXCIE0 = 6;
constexpr unsigned ccTXEN0 = 3;
constexpr unsigned ccU2X0 = 1;
using rrUBRR0 = MemRegisterDef<std::uint16_t, 0xC4>;
using rrUBRR0H = MemRegisterDef<std::uint8_t, 0xC5>;
using rrUBRR0L = MemRegisterDef<std::uint8_t, 0xC4>;
constexpr unsigned ccUCPOL0 = 0;
using rrUCSR0A = MemRegisterDef<std::uint8_t, 0xC0>;
using rrUCSR0C = MemRegisterDef<std::uint8_t, 0xC2>;
constexpr unsigned ccUCSZ00 = 1;
constexpr unsigned ccUCSZ01 = 2;
constexpr unsigned ccUCSZ02 = 2;
constexpr unsigned ccUDRE0 = 5;
constexpr unsigned ccUDRIE0 = 5;
constexpr unsigned ccUMSEL0 = 6;
constexpr unsigned ccUPE0 = 2;
constexpr unsigned ccUPM00 = 4;
constexpr unsigned ccUPM01 = 5;
constexpr unsigned ccUSART0_RX_vect_num = 13;
constexpr unsigned ccUSART0_TX_vect_num = 15;
constexpr unsigned ccUSART0_UDRE_vect_num = 14;
constexpr unsigned ccUSBS0 = 3;
constexpr unsigned ccUSICLK = 1;
constexpr unsigned ccUSICNT0 = 0;
constexpr unsigned ccUSICNT1 = 1;
constexpr unsigned ccUSICNT2 = 2;
constexpr unsigned ccUSICNT3 = 3;
using rrUSICR = MemRegisterDef<std::uint8_t, 0xB8>;
constexpr unsigned ccUSICS0 = 2;
constexpr unsigned ccUSICS1 = 3;
constexpr unsigned ccUSIDC = 4;
using rrUSIDR = MemRegisterDef<std::uint8_t, 0xBA>;
constexpr unsigned ccUSIOIE = 6;
constexpr unsigned ccUSIOIF = 6;
constexpr unsigned ccUSIPF = 5;
constexpr unsigned ccUSISIE = 7;
constexpr unsigned ccUSISIF = 7;
using rrUSISR = MemRegisterDef<std::uint8_t, 0xB9>;
constexpr unsigned ccUSITC = 0;
constexpr unsigned ccUSIWM0 = 4;
constexpr unsigned ccUSIWM1 = 5;
constexpr unsigned ccUSI_OVERFLOW_vect_num = 17;
constexpr unsigned ccUSI_START_vect_num = 16;
constexpr unsigned ccWCOL = 6;
constexpr unsigned ccWDCE = 4;
constexpr unsigned ccWDE = 3;
constexpr unsigned ccWDP0 = 0;
constexpr unsigned ccWDP1 = 1;
constexpr unsigned ccWDP2 = 2;
constexpr unsigned ccWDRF = 3;
using rrWDTCR = MemRegisterDef<std::uint8_t, 0x60>;
constexpr unsigned ccWGM00 = 6;
constexpr unsigned ccWGM01 = 3;
constexpr unsigned ccWGM10 = 0;
constexpr unsigned ccWGM11 = 1;
constexpr unsigned ccWGM12 = 3;
constexpr unsigned ccWGM13 = 4;
constexpr unsigned ccWGM20 = 6;
constexpr unsigned ccWGM21 = 3;
constexpr unsigned cc_HAVE_AVR_STACK_POINTER_HI = 1;
constexpr unsigned cc_SFR_ASM_COMPAT = 0;
constexpr unsigned cc_VECTORS_SIZE = 92;
constexpr unsigned cc__EEPROM_REG_LOCATIONS__ = 1;
constexpr unsigned cc__USING_MINT8 = 0;


}  // arch_atmega325
}  // namespace avr
}  // namespace sys
}  // namespace ardo

#endif  // ardo_supplemental_atmega325__h
