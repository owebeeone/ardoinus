// Generated for arch at90pwm3.
// This file is generated from the avr-gcc compiler with the mcu
// set to at90pwm3 from macros specific to avr/io.h.
// Any changes to this file will likely be lost next time this file
// is regenerated. Many any mcu_arch specific changes to 
// ardo_supplemental_at90pwm3_defs.h.

#ifndef ardo_supplemental_at90pwm3__h
#define ardo_supplemental_at90pwm3__h

#include "setlx_cstdint.h"
#include "setl_bit_fields.h"
#include "ardo_avr_bit_io_defs.h"

namespace ardo {
namespace sys {
namespace avr {
namespace arch_at90pwm3 {

constexpr ptrdiff_t cc__SFR_OFFSET = 0x20;

template <typename T, ptrdiff_t w_addr>
using IoRegisterDef = avr::nfp::IoRegisterDef<T, w_addr, cc__SFR_OFFSET>;
using avr::nfp::MemRegisterDef;

using rrAC0CON = MemRegisterDef<std::uint8_t, 0xAD>;
constexpr unsigned ccAC0EN = 7;
constexpr unsigned ccAC0IE = 6;
constexpr unsigned ccAC0IF = 4;
constexpr unsigned ccAC0IS0 = 4;
constexpr unsigned ccAC0IS1 = 5;
constexpr unsigned ccAC0M0 = 0;
constexpr unsigned ccAC0M1 = 1;
constexpr unsigned ccAC0M2 = 2;
constexpr unsigned ccAC0O = 0;
using rrAC1CON = MemRegisterDef<std::uint8_t, 0xAE>;
constexpr unsigned ccAC1EN = 7;
constexpr unsigned ccAC1ICE = 3;
constexpr unsigned ccAC1IE = 6;
constexpr unsigned ccAC1IF = 5;
constexpr unsigned ccAC1IS0 = 4;
constexpr unsigned ccAC1IS1 = 5;
constexpr unsigned ccAC1M0 = 0;
constexpr unsigned ccAC1M1 = 1;
constexpr unsigned ccAC1M2 = 2;
constexpr unsigned ccAC1O = 1;
using rrAC2CON = MemRegisterDef<std::uint8_t, 0xAF>;
constexpr unsigned ccAC2EN = 7;
constexpr unsigned ccAC2IE = 6;
constexpr unsigned ccAC2IF = 6;
constexpr unsigned ccAC2IS0 = 4;
constexpr unsigned ccAC2IS1 = 5;
constexpr unsigned ccAC2M0 = 0;
constexpr unsigned ccAC2M1 = 1;
constexpr unsigned ccAC2M2 = 2;
constexpr unsigned ccAC2O = 2;
constexpr unsigned ccACCKDIV = 7;
constexpr unsigned ccACMP0D = 5;
using rrACSR = IoRegisterDef<std::uint8_t, 0x30>;
constexpr unsigned ccADASCR = 4;
constexpr unsigned ccADATE = 5;
using rrADC = MemRegisterDef<std::uint16_t, 0x78>;
constexpr unsigned ccADC0D = 0;
constexpr unsigned ccADC10D = 2;
constexpr unsigned ccADC1D = 1;
constexpr unsigned ccADC2D = 2;
constexpr unsigned ccADC3D = 3;
constexpr unsigned ccADC4D = 4;
constexpr unsigned ccADC5D = 5;
constexpr unsigned ccADC6D = 6;
constexpr unsigned ccADC7D = 7;
constexpr unsigned ccADC8D = 0;
constexpr unsigned ccADC9D = 1;
using rrADCH = MemRegisterDef<std::uint8_t, 0x79>;
using rrADCL = MemRegisterDef<std::uint8_t, 0x78>;
using rrADCSRA = MemRegisterDef<std::uint8_t, 0x7A>;
using rrADCSRB = MemRegisterDef<std::uint8_t, 0x7B>;
using rrADCW = MemRegisterDef<std::uint16_t, 0x78>;
constexpr unsigned ccADC_vect_num = 18;
constexpr unsigned ccADEN = 7;
constexpr unsigned ccADHSM = 7;
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
constexpr unsigned ccADTS3 = 3;
using rrAMP0CSR = MemRegisterDef<std::uint8_t, 0x76>;
constexpr unsigned ccAMP0EN = 7;
constexpr unsigned ccAMP0G0 = 4;
constexpr unsigned ccAMP0G1 = 5;
constexpr unsigned ccAMP0IS = 6;
constexpr unsigned ccAMP0ND = 3;
constexpr unsigned ccAMP0PD = 4;
constexpr unsigned ccAMP0TS0 = 0;
constexpr unsigned ccAMP0TS1 = 1;
using rrAMP1CSR = MemRegisterDef<std::uint8_t, 0x77>;
constexpr unsigned ccAMP1EN = 7;
constexpr unsigned ccAMP1G0 = 4;
constexpr unsigned ccAMP1G1 = 5;
constexpr unsigned ccAMP1IS = 6;
constexpr unsigned ccAMP1TS0 = 0;
constexpr unsigned ccAMP1TS1 = 1;
constexpr unsigned ccANALOG_COMP_0_vect_num = 7;
constexpr unsigned ccANALOG_COMP_1_vect_num = 8;
constexpr unsigned ccANALOG_COMP_2_vect_num = 9;
constexpr unsigned ccBLB0_MODE_1 = 0xFF;
constexpr unsigned ccBLB0_MODE_2 = 0xFB;
constexpr unsigned ccBLB0_MODE_3 = 0xF3;
constexpr unsigned ccBLB0_MODE_4 = 0xF7;
constexpr unsigned ccBLB1_MODE_1 = 0xFF;
constexpr unsigned ccBLB1_MODE_2 = 0xEF;
constexpr unsigned ccBLB1_MODE_3 = 0xCF;
constexpr unsigned ccBLB1_MODE_4 = 0xDF;
constexpr unsigned ccBLBSET = 3;
constexpr unsigned ccBODR = 0;
constexpr unsigned ccBORF = 2;
constexpr unsigned ccCAL0 = 0;
constexpr unsigned ccCAL1 = 1;
constexpr unsigned ccCAL2 = 2;
constexpr unsigned ccCAL3 = 3;
constexpr unsigned ccCAL4 = 4;
constexpr unsigned ccCAL5 = 5;
constexpr unsigned ccCAL6 = 6;
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
constexpr unsigned ccCPHA = 2;
constexpr unsigned ccCPOL = 3;
constexpr unsigned ccCS00 = 0;
constexpr unsigned ccCS01 = 1;
constexpr unsigned ccCS02 = 2;
constexpr unsigned ccCS10 = 0;
constexpr unsigned ccCS11 = 1;
constexpr unsigned ccCS12 = 2;
constexpr unsigned ccDAATE = 7;
using rrDAC = MemRegisterDef<std::uint16_t, 0xAB>;
using rrDACH = MemRegisterDef<std::uint8_t, 0xAC>;
using rrDACL = MemRegisterDef<std::uint8_t, 0xAB>;
using rrDACON = MemRegisterDef<std::uint8_t, 0xAA>;
constexpr unsigned ccDAEN = 0;
constexpr unsigned ccDALA = 2;
constexpr unsigned ccDAOE = 1;
constexpr unsigned ccDATS0 = 4;
constexpr unsigned ccDATS1 = 5;
constexpr unsigned ccDATS2 = 6;
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
using rrDDRB = IoRegisterDef<std::uint8_t, 0x04>;
using rrDDRC = IoRegisterDef<std::uint8_t, 0x07>;
using rrDDRD = IoRegisterDef<std::uint8_t, 0x0A>;
using rrDDRE = IoRegisterDef<std::uint8_t, 0x0D>;
using rrDIDR0 = MemRegisterDef<std::uint8_t, 0x7E>;
using rrDIDR1 = MemRegisterDef<std::uint8_t, 0x7F>;
constexpr unsigned ccDOR = 3;
constexpr unsigned ccDORD = 5;
constexpr unsigned ccE2END = 0x01FF;
constexpr unsigned ccE2PAGESIZE = 4;
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
constexpr unsigned ccEEMWE = 2;
constexpr unsigned ccEERE = 0;
constexpr unsigned ccEERIE = 3;
constexpr unsigned ccEEWE = 1;
constexpr unsigned ccEE_READY_vect_num = 26;
using rrEICRA = MemRegisterDef<std::uint8_t, 0x69>;
using rrEIFR = IoRegisterDef<std::uint8_t, 0x1C>;
using rrEIMSK = IoRegisterDef<std::uint8_t, 0x1D>;
constexpr unsigned ccEMCH = 1;
using rrEUCSRA = MemRegisterDef<std::uint8_t, 0xC8>;
using rrEUCSRB = MemRegisterDef<std::uint8_t, 0xC9>;
using rrEUCSRC = MemRegisterDef<std::uint8_t, 0xCA>;
using rrEUDR = MemRegisterDef<std::uint8_t, 0xCE>;
constexpr unsigned ccEUSART = 4;
constexpr unsigned ccEUSBS = 3;
constexpr unsigned ccEXTRF = 1;
constexpr unsigned ccF1617 = 2;
constexpr unsigned ccFE = 4;
constexpr unsigned ccFEM = 3;
constexpr unsigned ccFLASHEND = 0x1FFF;
constexpr unsigned ccFOC0A = 7;
constexpr unsigned ccFOC0B = 6;
constexpr unsigned ccFOC1A = 7;
constexpr unsigned ccFOC1B = 6;
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
using ffFUSE_DWEN = setl::BitsRW<setl::SemanticType<setl::hash("FUSE_DWEN"), bool>, 1u<<6>;
using ffFUSE_EESAVE = setl::BitsRW<setl::SemanticType<setl::hash("FUSE_EESAVE"), bool>, 1u<<3>;
constexpr unsigned ccFUSE_MEMORY_SIZE = 3;
using ffFUSE_PSC0RB = setl::BitsRW<setl::SemanticType<setl::hash("FUSE_PSC0RB"), bool>, 1u<<5>;
using ffFUSE_PSC1RB = setl::BitsRW<setl::SemanticType<setl::hash("FUSE_PSC1RB"), bool>, 1u<<6>;
using ffFUSE_PSC2RB = setl::BitsRW<setl::SemanticType<setl::hash("FUSE_PSC2RB"), bool>, 1u<<7>;
using ffFUSE_PSCRV = setl::BitsRW<setl::SemanticType<setl::hash("FUSE_PSCRV"), bool>, 1u<<4>;
using ffFUSE_RSTDISBL = setl::BitsRW<setl::SemanticType<setl::hash("FUSE_RSTDISBL"), bool>, 1u<<7>;
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
using rrGPIOR1 = IoRegisterDef<std::uint8_t, 0x19>;
constexpr unsigned ccGPIOR10 = 0;
constexpr unsigned ccGPIOR11 = 1;
constexpr unsigned ccGPIOR12 = 2;
constexpr unsigned ccGPIOR13 = 3;
constexpr unsigned ccGPIOR14 = 4;
constexpr unsigned ccGPIOR15 = 5;
constexpr unsigned ccGPIOR16 = 6;
constexpr unsigned ccGPIOR17 = 7;
using rrGPIOR2 = IoRegisterDef<std::uint8_t, 0x1A>;
constexpr unsigned ccGPIOR20 = 0;
constexpr unsigned ccGPIOR21 = 1;
constexpr unsigned ccGPIOR22 = 2;
constexpr unsigned ccGPIOR23 = 3;
constexpr unsigned ccGPIOR24 = 4;
constexpr unsigned ccGPIOR25 = 5;
constexpr unsigned ccGPIOR26 = 6;
constexpr unsigned ccGPIOR27 = 7;
using rrGPIOR3 = IoRegisterDef<std::uint8_t, 0x1B>;
constexpr unsigned ccGPIOR30 = 0;
constexpr unsigned ccGPIOR31 = 1;
constexpr unsigned ccGPIOR32 = 2;
constexpr unsigned ccGPIOR33 = 3;
constexpr unsigned ccGPIOR34 = 4;
constexpr unsigned ccGPIOR35 = 5;
constexpr unsigned ccGPIOR36 = 6;
constexpr unsigned ccGPIOR37 = 7;
using rrGTCCR = IoRegisterDef<std::uint8_t, 0x23>;
constexpr unsigned ccICES1 = 6;
constexpr unsigned ccICF1 = 5;
constexpr unsigned ccICIE1 = 5;
constexpr unsigned ccICNC1 = 7;
constexpr unsigned ccICPSEL1 = 6;
using rrICR1 = MemRegisterDef<std::uint16_t, 0x86>;
constexpr unsigned ccICR10 = 0;
constexpr unsigned ccICR11 = 1;
constexpr unsigned ccICR110 = 2;
constexpr unsigned ccICR111 = 3;
constexpr unsigned ccICR112 = 4;
constexpr unsigned ccICR113 = 5;
constexpr unsigned ccICR114 = 6;
constexpr unsigned ccICR115 = 7;
constexpr unsigned ccICR12 = 2;
constexpr unsigned ccICR13 = 3;
constexpr unsigned ccICR14 = 4;
constexpr unsigned ccICR15 = 5;
constexpr unsigned ccICR16 = 6;
constexpr unsigned ccICR17 = 7;
constexpr unsigned ccICR18 = 0;
constexpr unsigned ccICR19 = 1;
using rrICR1H = MemRegisterDef<std::uint8_t, 0x87>;
using rrICR1L = MemRegisterDef<std::uint8_t, 0x86>;
constexpr unsigned ccINT0 = 0;
constexpr unsigned ccINT0_vect_num = 10;
constexpr unsigned ccINT1 = 1;
constexpr unsigned ccINT1_vect_num = 19;
constexpr unsigned ccINT2 = 2;
constexpr unsigned ccINT2_vect_num = 24;
constexpr unsigned ccINT3 = 3;
constexpr unsigned ccINT3_vect_num = 28;
constexpr unsigned ccINTF0 = 0;
constexpr unsigned ccINTF1 = 1;
constexpr unsigned ccINTF2 = 2;
constexpr unsigned ccINTF3 = 3;
constexpr unsigned ccISC00 = 0;
constexpr unsigned ccISC01 = 1;
constexpr unsigned ccISC10 = 2;
constexpr unsigned ccISC11 = 3;
constexpr unsigned ccISC20 = 4;
constexpr unsigned ccISC21 = 5;
constexpr unsigned ccISC30 = 6;
constexpr unsigned ccISC31 = 7;
constexpr unsigned ccIVCE = 0;
constexpr unsigned ccIVSEL = 1;
constexpr unsigned ccLB_MODE_1 = 0xFF;
constexpr unsigned ccLB_MODE_2 = 0xFE;
constexpr unsigned ccLB_MODE_3 = 0xFC;
constexpr unsigned ccLOCKBITS_DEFAULT = 0xFF;
using rrMCUCR = IoRegisterDef<std::uint8_t, 0x35>;
using rrMCUSR = IoRegisterDef<std::uint8_t, 0x34>;
using rrMONDR = IoRegisterDef<std::uint8_t, 0x31>;
constexpr unsigned ccMPCM = 0;
using rrMSMCR = IoRegisterDef<std::uint8_t, 0x32>;
constexpr unsigned ccMSTR = 4;
using rrMUBRR = MemRegisterDef<std::uint16_t, 0xCC>;
using rrMUBRRH = MemRegisterDef<std::uint8_t, 0xCD>;
using rrMUBRRL = MemRegisterDef<std::uint8_t, 0xCC>;
constexpr unsigned ccMUX0 = 0;
constexpr unsigned ccMUX1 = 1;
constexpr unsigned ccMUX2 = 2;
constexpr unsigned ccMUX3 = 3;
constexpr unsigned ccOCF0A = 1;
constexpr unsigned ccOCF0B = 2;
constexpr unsigned ccOCF1A = 1;
constexpr unsigned ccOCF1B = 2;
constexpr unsigned ccOCIE0A = 1;
constexpr unsigned ccOCIE0B = 2;
constexpr unsigned ccOCIE1A = 1;
constexpr unsigned ccOCIE1B = 2;
using rrOCR0A = IoRegisterDef<std::uint8_t, 0x27>;
constexpr unsigned ccOCR0A0 = 0;
constexpr unsigned ccOCR0A1 = 1;
constexpr unsigned ccOCR0A2 = 2;
constexpr unsigned ccOCR0A3 = 3;
constexpr unsigned ccOCR0A4 = 4;
constexpr unsigned ccOCR0A5 = 5;
constexpr unsigned ccOCR0A6 = 6;
constexpr unsigned ccOCR0A7 = 7;
using rrOCR0B = IoRegisterDef<std::uint8_t, 0x28>;
constexpr unsigned ccOCR0B0 = 0;
constexpr unsigned ccOCR0B1 = 1;
constexpr unsigned ccOCR0B2 = 2;
constexpr unsigned ccOCR0B3 = 3;
constexpr unsigned ccOCR0B4 = 4;
constexpr unsigned ccOCR0B5 = 5;
constexpr unsigned ccOCR0B6 = 6;
constexpr unsigned ccOCR0B7 = 7;
using rrOCR0RA = MemRegisterDef<std::uint16_t, 0xD4>;
using rrOCR0RAH = MemRegisterDef<std::uint8_t, 0xD5>;
using rrOCR0RAL = MemRegisterDef<std::uint8_t, 0xD4>;
using rrOCR0RB = MemRegisterDef<std::uint16_t, 0xD8>;
using rrOCR0RBH = MemRegisterDef<std::uint8_t, 0xD9>;
using rrOCR0RBL = MemRegisterDef<std::uint8_t, 0xD8>;
using rrOCR0SA = MemRegisterDef<std::uint16_t, 0xD2>;
using rrOCR0SAH = MemRegisterDef<std::uint8_t, 0xD3>;
using rrOCR0SAL = MemRegisterDef<std::uint8_t, 0xD2>;
using rrOCR0SB = MemRegisterDef<std::uint16_t, 0xD6>;
using rrOCR0SBH = MemRegisterDef<std::uint8_t, 0xD7>;
using rrOCR0SBL = MemRegisterDef<std::uint8_t, 0xD6>;
using rrOCR1A = MemRegisterDef<std::uint16_t, 0x88>;
constexpr unsigned ccOCR1A0 = 0;
constexpr unsigned ccOCR1A1 = 1;
constexpr unsigned ccOCR1A10 = 2;
constexpr unsigned ccOCR1A11 = 3;
constexpr unsigned ccOCR1A12 = 4;
constexpr unsigned ccOCR1A13 = 5;
constexpr unsigned ccOCR1A14 = 6;
constexpr unsigned ccOCR1A15 = 7;
constexpr unsigned ccOCR1A2 = 2;
constexpr unsigned ccOCR1A3 = 3;
constexpr unsigned ccOCR1A4 = 4;
constexpr unsigned ccOCR1A5 = 5;
constexpr unsigned ccOCR1A6 = 6;
constexpr unsigned ccOCR1A7 = 7;
constexpr unsigned ccOCR1A8 = 0;
constexpr unsigned ccOCR1A9 = 1;
using rrOCR1AH = MemRegisterDef<std::uint8_t, 0x89>;
using rrOCR1AL = MemRegisterDef<std::uint8_t, 0x88>;
using rrOCR1B = MemRegisterDef<std::uint16_t, 0x8A>;
constexpr unsigned ccOCR1B0 = 0;
constexpr unsigned ccOCR1B1 = 1;
constexpr unsigned ccOCR1B10 = 2;
constexpr unsigned ccOCR1B11 = 3;
constexpr unsigned ccOCR1B12 = 4;
constexpr unsigned ccOCR1B13 = 5;
constexpr unsigned ccOCR1B14 = 6;
constexpr unsigned ccOCR1B15 = 7;
constexpr unsigned ccOCR1B2 = 2;
constexpr unsigned ccOCR1B3 = 3;
constexpr unsigned ccOCR1B4 = 4;
constexpr unsigned ccOCR1B5 = 5;
constexpr unsigned ccOCR1B6 = 6;
constexpr unsigned ccOCR1B7 = 7;
constexpr unsigned ccOCR1B8 = 0;
constexpr unsigned ccOCR1B9 = 1;
using rrOCR1BH = MemRegisterDef<std::uint8_t, 0x8B>;
using rrOCR1BL = MemRegisterDef<std::uint8_t, 0x8A>;
using rrOCR1RA = MemRegisterDef<std::uint16_t, 0xE4>;
using rrOCR1RAH = MemRegisterDef<std::uint8_t, 0xE5>;
using rrOCR1RAL = MemRegisterDef<std::uint8_t, 0xE4>;
using rrOCR1RB = MemRegisterDef<std::uint16_t, 0xE8>;
using rrOCR1RBH = MemRegisterDef<std::uint8_t, 0xE9>;
using rrOCR1RBL = MemRegisterDef<std::uint8_t, 0xE8>;
using rrOCR1SA = MemRegisterDef<std::uint16_t, 0xE2>;
using rrOCR1SAH = MemRegisterDef<std::uint8_t, 0xE3>;
using rrOCR1SAL = MemRegisterDef<std::uint8_t, 0xE2>;
using rrOCR1SB = MemRegisterDef<std::uint16_t, 0xE6>;
using rrOCR1SBH = MemRegisterDef<std::uint8_t, 0xE7>;
using rrOCR1SBL = MemRegisterDef<std::uint8_t, 0xE6>;
using rrOCR2RA = MemRegisterDef<std::uint16_t, 0xF4>;
using rrOCR2RAH = MemRegisterDef<std::uint8_t, 0xF5>;
using rrOCR2RAL = MemRegisterDef<std::uint8_t, 0xF4>;
using rrOCR2RB = MemRegisterDef<std::uint16_t, 0xF8>;
using rrOCR2RBH = MemRegisterDef<std::uint8_t, 0xF9>;
using rrOCR2RBL = MemRegisterDef<std::uint8_t, 0xF8>;
using rrOCR2SA = MemRegisterDef<std::uint16_t, 0xF2>;
using rrOCR2SAH = MemRegisterDef<std::uint8_t, 0xF3>;
using rrOCR2SAL = MemRegisterDef<std::uint8_t, 0xF2>;
using rrOCR2SB = MemRegisterDef<std::uint16_t, 0xF6>;
using rrOCR2SBH = MemRegisterDef<std::uint8_t, 0xF7>;
using rrOCR2SBL = MemRegisterDef<std::uint8_t, 0xF6>;
using rrOSCCAL = MemRegisterDef<std::uint8_t, 0x66>;
constexpr unsigned ccPALOCK0 = 6;
constexpr unsigned ccPALOCK1 = 6;
constexpr unsigned ccPALOCK2 = 6;
constexpr unsigned ccPAOC0A = 3;
constexpr unsigned ccPAOC0B = 4;
constexpr unsigned ccPAOC1A = 3;
constexpr unsigned ccPAOC1B = 4;
constexpr unsigned ccPAOC2A = 3;
constexpr unsigned ccPAOC2B = 4;
constexpr unsigned ccPARUN0 = 2;
constexpr unsigned ccPARUN1 = 2;
constexpr unsigned ccPARUN2 = 2;
constexpr unsigned ccPB0 = 0;
constexpr unsigned ccPB1 = 1;
constexpr unsigned ccPB2 = 2;
constexpr unsigned ccPB3 = 3;
constexpr unsigned ccPB4 = 4;
constexpr unsigned ccPB5 = 5;
constexpr unsigned ccPB6 = 6;
constexpr unsigned ccPB7 = 7;
constexpr unsigned ccPBFM0 = 5;
constexpr unsigned ccPBFM1 = 5;
constexpr unsigned ccPBFM2 = 5;
constexpr unsigned ccPC0 = 0;
constexpr unsigned ccPC1 = 1;
constexpr unsigned ccPC2 = 2;
constexpr unsigned ccPC3 = 3;
constexpr unsigned ccPC4 = 4;
constexpr unsigned ccPC5 = 5;
constexpr unsigned ccPC6 = 6;
constexpr unsigned ccPC7 = 7;
constexpr unsigned ccPCAE0A = 7;
constexpr unsigned ccPCAE0B = 7;
constexpr unsigned ccPCAE1A = 7;
constexpr unsigned ccPCAE1B = 7;
constexpr unsigned ccPCAE2A = 7;
constexpr unsigned ccPCAE2B = 7;
constexpr unsigned ccPCCYC0 = 1;
constexpr unsigned ccPCCYC1 = 1;
constexpr unsigned ccPCCYC2 = 1;
constexpr unsigned ccPCKE = 2;
constexpr unsigned ccPCLKSEL0 = 1;
constexpr unsigned ccPCLKSEL1 = 1;
constexpr unsigned ccPCLKSEL2 = 1;
using rrPCNF0 = MemRegisterDef<std::uint8_t, 0xDA>;
using rrPCNF1 = MemRegisterDef<std::uint8_t, 0xEA>;
using rrPCNF2 = MemRegisterDef<std::uint8_t, 0xFA>;
constexpr unsigned ccPCST0 = 7;
constexpr unsigned ccPCST1 = 7;
constexpr unsigned ccPCST2 = 7;
using rrPCTL0 = MemRegisterDef<std::uint8_t, 0xDB>;
using rrPCTL1 = MemRegisterDef<std::uint8_t, 0xEB>;
using rrPCTL2 = MemRegisterDef<std::uint8_t, 0xFB>;
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
constexpr unsigned ccPELEV0A = 5;
constexpr unsigned ccPELEV0B = 5;
constexpr unsigned ccPELEV1A = 5;
constexpr unsigned ccPELEV1B = 5;
constexpr unsigned ccPELEV2A = 5;
constexpr unsigned ccPELEV2B = 5;
constexpr unsigned ccPEOP0 = 0;
constexpr unsigned ccPEOP1 = 0;
constexpr unsigned ccPEOP2 = 0;
constexpr unsigned ccPEOPE0 = 0;
constexpr unsigned ccPEOPE1 = 0;
constexpr unsigned ccPEOPE2 = 0;
constexpr unsigned ccPEV0A = 3;
constexpr unsigned ccPEV0B = 4;
constexpr unsigned ccPEV1A = 3;
constexpr unsigned ccPEV1B = 4;
constexpr unsigned ccPEV2A = 3;
constexpr unsigned ccPEV2B = 4;
constexpr unsigned ccPEVE0A = 3;
constexpr unsigned ccPEVE0B = 4;
constexpr unsigned ccPEVE1A = 3;
constexpr unsigned ccPEVE1B = 4;
constexpr unsigned ccPEVE2A = 3;
constexpr unsigned ccPEVE2B = 4;
constexpr unsigned ccPFIFTY0 = 7;
constexpr unsigned ccPFIFTY1 = 7;
constexpr unsigned ccPFIFTY2 = 7;
constexpr unsigned ccPFLTE0A = 4;
constexpr unsigned ccPFLTE0B = 4;
constexpr unsigned ccPFLTE1A = 4;
constexpr unsigned ccPFLTE1B = 4;
constexpr unsigned ccPFLTE2A = 4;
constexpr unsigned ccPFLTE2B = 4;
using rrPFRC0A = MemRegisterDef<std::uint8_t, 0xDC>;
using rrPFRC0B = MemRegisterDef<std::uint8_t, 0xDD>;
using rrPFRC1A = MemRegisterDef<std::uint8_t, 0xEC>;
using rrPFRC1B = MemRegisterDef<std::uint8_t, 0xED>;
using rrPFRC2A = MemRegisterDef<std::uint8_t, 0xFC>;
using rrPFRC2B = MemRegisterDef<std::uint8_t, 0xFD>;
constexpr unsigned ccPGERS = 1;
constexpr unsigned ccPGWRT = 2;
using rrPICR0 = MemRegisterDef<std::uint16_t, 0xDE>;
using rrPICR0H = MemRegisterDef<std::uint8_t, 0xDF>;
using rrPICR0L = MemRegisterDef<std::uint8_t, 0xDE>;
using rrPICR1 = MemRegisterDef<std::uint16_t, 0xEE>;
using rrPICR1H = MemRegisterDef<std::uint8_t, 0xEF>;
using rrPICR1L = MemRegisterDef<std::uint8_t, 0xEE>;
using rrPICR2 = MemRegisterDef<std::uint16_t, 0xFE>;
using rrPICR2H = MemRegisterDef<std::uint8_t, 0xFF>;
using rrPICR2L = MemRegisterDef<std::uint8_t, 0xFE>;
using rrPIFR0 = MemRegisterDef<std::uint8_t, 0xA0>;
using rrPIFR1 = MemRegisterDef<std::uint8_t, 0xA2>;
using rrPIFR2 = MemRegisterDef<std::uint8_t, 0xA4>;
using rrPIM0 = MemRegisterDef<std::uint8_t, 0xA1>;
using rrPIM1 = MemRegisterDef<std::uint8_t, 0xA3>;
using rrPIM2 = MemRegisterDef<std::uint8_t, 0xA5>;
constexpr unsigned ccPIN0 = 0;
constexpr unsigned ccPIN1 = 1;
constexpr unsigned ccPIN2 = 2;
constexpr unsigned ccPIN3 = 3;
constexpr unsigned ccPIN4 = 4;
constexpr unsigned ccPIN5 = 5;
constexpr unsigned ccPIN6 = 6;
constexpr unsigned ccPIN7 = 7;
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
constexpr unsigned ccPISEL0A = 6;
constexpr unsigned ccPISEL0B = 6;
constexpr unsigned ccPISEL1A = 6;
constexpr unsigned ccPISEL1B = 6;
constexpr unsigned ccPISEL2A = 6;
constexpr unsigned ccPISEL2B = 6;
using rrPLLCSR = IoRegisterDef<std::uint8_t, 0x29>;
constexpr unsigned ccPLLE = 1;
constexpr unsigned ccPLLF = 2;
constexpr unsigned ccPLOCK = 0;
constexpr unsigned ccPLOCK0 = 5;
constexpr unsigned ccPLOCK1 = 5;
constexpr unsigned ccPLOCK2 = 5;
constexpr unsigned ccPMODE00 = 3;
constexpr unsigned ccPMODE01 = 4;
constexpr unsigned ccPMODE10 = 3;
constexpr unsigned ccPMODE11 = 4;
constexpr unsigned ccPMODE20 = 3;
constexpr unsigned ccPMODE21 = 4;
constexpr unsigned ccPOAC0A = 6;
constexpr unsigned ccPOAC0B = 7;
constexpr unsigned ccPOAC1A = 6;
constexpr unsigned ccPOAC1B = 7;
constexpr unsigned ccPOAC2A = 6;
constexpr unsigned ccPOAC2B = 7;
constexpr unsigned ccPOEN0A = 0;
constexpr unsigned ccPOEN0B = 2;
constexpr unsigned ccPOEN1A = 0;
constexpr unsigned ccPOEN1B = 2;
constexpr unsigned ccPOEN2A = 0;
constexpr unsigned ccPOEN2B = 2;
constexpr unsigned ccPOEN2C = 1;
constexpr unsigned ccPOEN2D = 3;
using rrPOM2 = MemRegisterDef<std::uint8_t, 0xF1>;
constexpr unsigned ccPOME2 = 0;
constexpr unsigned ccPOMV2A0 = 0;
constexpr unsigned ccPOMV2A1 = 1;
constexpr unsigned ccPOMV2A2 = 2;
constexpr unsigned ccPOMV2A3 = 3;
constexpr unsigned ccPOMV2B0 = 4;
constexpr unsigned ccPOMV2B1 = 5;
constexpr unsigned ccPOMV2B2 = 6;
constexpr unsigned ccPOMV2B3 = 7;
constexpr unsigned ccPOP0 = 2;
constexpr unsigned ccPOP1 = 2;
constexpr unsigned ccPOP2 = 2;
constexpr unsigned ccPORF = 0;
constexpr unsigned ccPORT0 = 0;
constexpr unsigned ccPORT1 = 1;
constexpr unsigned ccPORT2 = 2;
constexpr unsigned ccPORT3 = 3;
constexpr unsigned ccPORT4 = 4;
constexpr unsigned ccPORT5 = 5;
constexpr unsigned ccPORT6 = 6;
constexpr unsigned ccPORT7 = 7;
using rrPORTB = IoRegisterDef<std::uint8_t, 0x05>;
using rrPORTC = IoRegisterDef<std::uint8_t, 0x08>;
using rrPORTD = IoRegisterDef<std::uint8_t, 0x0B>;
using rrPORTE = IoRegisterDef<std::uint8_t, 0x0E>;
constexpr unsigned ccPOS22 = 6;
constexpr unsigned ccPOS23 = 7;
constexpr unsigned ccPPRE00 = 6;
constexpr unsigned ccPPRE01 = 7;
constexpr unsigned ccPPRE10 = 6;
constexpr unsigned ccPPRE11 = 7;
constexpr unsigned ccPPRE20 = 6;
constexpr unsigned ccPPRE21 = 7;
constexpr unsigned ccPRADC = 0;
constexpr unsigned ccPRFM0A0 = 0;
constexpr unsigned ccPRFM0A1 = 1;
constexpr unsigned ccPRFM0A2 = 2;
constexpr unsigned ccPRFM0A3 = 3;
constexpr unsigned ccPRFM0B0 = 0;
constexpr unsigned ccPRFM0B1 = 1;
constexpr unsigned ccPRFM0B2 = 2;
constexpr unsigned ccPRFM0B3 = 3;
constexpr unsigned ccPRFM1A0 = 0;
constexpr unsigned ccPRFM1A1 = 1;
constexpr unsigned ccPRFM1A2 = 2;
constexpr unsigned ccPRFM1A3 = 3;
constexpr unsigned ccPRFM1B0 = 0;
constexpr unsigned ccPRFM1B1 = 1;
constexpr unsigned ccPRFM1B2 = 2;
constexpr unsigned ccPRFM1B3 = 3;
constexpr unsigned ccPRFM2A0 = 0;
constexpr unsigned ccPRFM2A1 = 1;
constexpr unsigned ccPRFM2A2 = 2;
constexpr unsigned ccPRFM2A3 = 3;
constexpr unsigned ccPRFM2B0 = 0;
constexpr unsigned ccPRFM2B1 = 1;
constexpr unsigned ccPRFM2B2 = 2;
constexpr unsigned ccPRFM2B3 = 3;
constexpr unsigned ccPRN00 = 1;
constexpr unsigned ccPRN01 = 2;
constexpr unsigned ccPRN10 = 1;
constexpr unsigned ccPRN11 = 2;
constexpr unsigned ccPRN20 = 1;
constexpr unsigned ccPRN21 = 2;
constexpr unsigned ccPRPSC0 = 5;
constexpr unsigned ccPRPSC1 = 6;
constexpr unsigned ccPRPSC2 = 7;
using rrPRR = MemRegisterDef<std::uint8_t, 0x64>;
constexpr unsigned ccPRSPI = 2;
constexpr unsigned ccPRTIM0 = 3;
constexpr unsigned ccPRTIM1 = 4;
constexpr unsigned ccPRUN0 = 0;
constexpr unsigned ccPRUN1 = 0;
constexpr unsigned ccPRUN2 = 0;
constexpr unsigned ccPRUSART0 = 1;
constexpr unsigned ccPSC0_CAPT_vect_num = 5;
constexpr unsigned ccPSC0_EC_vect_num = 6;
constexpr unsigned ccPSC1_CAPT_vect_num = 3;
constexpr unsigned ccPSC1_EC_vect_num = 4;
constexpr unsigned ccPSC2_CAPT_vect_num = 1;
constexpr unsigned ccPSC2_EC_vect_num = 2;
constexpr unsigned ccPSEI0 = 5;
constexpr unsigned ccPSEI1 = 5;
constexpr unsigned ccPSEI2 = 5;
constexpr unsigned ccPSEIE0 = 5;
constexpr unsigned ccPSEIE1 = 5;
constexpr unsigned ccPSEIE2 = 5;
using rrPSOC0 = MemRegisterDef<std::uint8_t, 0xD0>;
using rrPSOC1 = MemRegisterDef<std::uint8_t, 0xE0>;
using rrPSOC2 = MemRegisterDef<std::uint8_t, 0xF0>;
constexpr unsigned ccPSR10 = 0;
constexpr unsigned ccPSYNC00 = 4;
constexpr unsigned ccPSYNC01 = 5;
constexpr unsigned ccPSYNC10 = 4;
constexpr unsigned ccPSYNC11 = 5;
constexpr unsigned ccPSYNC20 = 4;
constexpr unsigned ccPSYNC21 = 5;
constexpr unsigned ccPUD = 4;
constexpr unsigned ccRAMEND = 0x02FF;
constexpr unsigned ccRAMSTART = 0x100;
constexpr unsigned ccREFS0 = 6;
constexpr unsigned ccREFS1 = 7;
constexpr unsigned ccRWWSB = 6;
constexpr unsigned ccRWWSRE = 4;
constexpr unsigned ccRXB8 = 1;
constexpr unsigned ccRXC = 7;
constexpr unsigned ccRXCIE = 7;
constexpr unsigned ccRXEN = 4;
constexpr unsigned ccSE = 0;
constexpr unsigned ccSLEEP_MODE_IDLE = 0;
constexpr unsigned ccSM0 = 1;
constexpr unsigned ccSM1 = 2;
constexpr unsigned ccSM2 = 3;
using rrSMCR = IoRegisterDef<std::uint8_t, 0x33>;
using rrSP = IoRegisterDef<std::uint16_t, 0x3D>;
using rrSPCR = IoRegisterDef<std::uint8_t, 0x2C>;
constexpr unsigned ccSPD0 = 0;
constexpr unsigned ccSPD1 = 1;
constexpr unsigned ccSPD2 = 2;
constexpr unsigned ccSPD3 = 3;
constexpr unsigned ccSPD4 = 4;
constexpr unsigned ccSPD5 = 5;
constexpr unsigned ccSPD6 = 6;
constexpr unsigned ccSPD7 = 7;
using rrSPDR = IoRegisterDef<std::uint8_t, 0x2E>;
constexpr unsigned ccSPE = 6;
using rrSPH = IoRegisterDef<std::uint8_t, 0x3E>;
constexpr unsigned ccSPI2X = 0;
constexpr unsigned ccSPIE = 7;
constexpr unsigned ccSPIF = 7;
constexpr unsigned ccSPIPS = 7;
constexpr unsigned ccSPI_STC_vect_num = 20;
using rrSPL = IoRegisterDef<std::uint8_t, 0x3D>;
using rrSPMCSR = IoRegisterDef<std::uint8_t, 0x37>;
constexpr unsigned ccSPMEN = 0;
constexpr unsigned ccSPMIE = 7;
constexpr unsigned ccSPM_PAGESIZE = 64;
constexpr unsigned ccSPM_READY_vect_num = 31;
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
constexpr unsigned ccSTP0 = 0;
constexpr unsigned ccSTP1 = 1;
using rrTCCR0A = IoRegisterDef<std::uint8_t, 0x24>;
using rrTCCR0B = IoRegisterDef<std::uint8_t, 0x25>;
using rrTCCR1A = MemRegisterDef<std::uint8_t, 0x80>;
using rrTCCR1B = MemRegisterDef<std::uint8_t, 0x81>;
using rrTCCR1C = MemRegisterDef<std::uint8_t, 0x82>;
using rrTCNT0 = IoRegisterDef<std::uint8_t, 0x26>;
constexpr unsigned ccTCNT00 = 0;
constexpr unsigned ccTCNT01 = 1;
constexpr unsigned ccTCNT02 = 2;
constexpr unsigned ccTCNT03 = 3;
constexpr unsigned ccTCNT04 = 4;
constexpr unsigned ccTCNT05 = 5;
constexpr unsigned ccTCNT06 = 6;
constexpr unsigned ccTCNT07 = 7;
using rrTCNT1 = MemRegisterDef<std::uint16_t, 0x84>;
constexpr unsigned ccTCNT10 = 0;
constexpr unsigned ccTCNT11 = 1;
constexpr unsigned ccTCNT110 = 2;
constexpr unsigned ccTCNT111 = 3;
constexpr unsigned ccTCNT112 = 4;
constexpr unsigned ccTCNT113 = 5;
constexpr unsigned ccTCNT114 = 6;
constexpr unsigned ccTCNT115 = 7;
constexpr unsigned ccTCNT12 = 2;
constexpr unsigned ccTCNT13 = 3;
constexpr unsigned ccTCNT14 = 4;
constexpr unsigned ccTCNT15 = 5;
constexpr unsigned ccTCNT16 = 6;
constexpr unsigned ccTCNT17 = 7;
constexpr unsigned ccTCNT18 = 0;
constexpr unsigned ccTCNT19 = 1;
using rrTCNT1H = MemRegisterDef<std::uint8_t, 0x85>;
using rrTCNT1L = MemRegisterDef<std::uint8_t, 0x84>;
using rrTIFR0 = IoRegisterDef<std::uint8_t, 0x15>;
using rrTIFR1 = IoRegisterDef<std::uint8_t, 0x16>;
constexpr unsigned ccTIMER0_COMPB_vect_num = 27;
constexpr unsigned ccTIMER0_COMP_A_vect_num = 16;
constexpr unsigned ccTIMER0_OVF_vect_num = 17;
constexpr unsigned ccTIMER1_CAPT_vect_num = 11;
constexpr unsigned ccTIMER1_COMPA_vect_num = 12;
constexpr unsigned ccTIMER1_COMPB_vect_num = 13;
constexpr unsigned ccTIMER1_OVF_vect_num = 15;
using rrTIMSK0 = MemRegisterDef<std::uint8_t, 0x6E>;
using rrTIMSK1 = MemRegisterDef<std::uint8_t, 0x6F>;
constexpr unsigned ccTOIE0 = 0;
constexpr unsigned ccTOIE1 = 0;
constexpr unsigned ccTOV0 = 0;
constexpr unsigned ccTOV1 = 0;
constexpr unsigned ccTSM = 7;
constexpr unsigned ccTXB8 = 0;
constexpr unsigned ccTXC = 6;
constexpr unsigned ccTXCIE = 6;
constexpr unsigned ccTXEN = 3;
constexpr unsigned ccU2X = 1;
using rrUBRR = MemRegisterDef<std::uint16_t, 0xC4>;
using rrUBRRH = MemRegisterDef<std::uint8_t, 0xC5>;
using rrUBRRL = MemRegisterDef<std::uint8_t, 0xC4>;
constexpr unsigned ccUCPOL = 0;
using rrUCSRA = MemRegisterDef<std::uint8_t, 0xC0>;
using rrUCSRB = MemRegisterDef<std::uint8_t, 0xC1>;
using rrUCSRC = MemRegisterDef<std::uint8_t, 0xC2>;
constexpr unsigned ccUCSZ0 = 1;
constexpr unsigned ccUCSZ1 = 2;
constexpr unsigned ccUCSZ2 = 2;
using rrUDR = MemRegisterDef<std::uint8_t, 0xC6>;
constexpr unsigned ccUDRE = 5;
constexpr unsigned ccUDRIE = 5;
constexpr unsigned ccUMSEL = 6;
constexpr unsigned ccUPE = 2;
constexpr unsigned ccUPM0 = 4;
constexpr unsigned ccUPM1 = 5;
constexpr unsigned ccURxS0 = 0;
constexpr unsigned ccURxS1 = 1;
constexpr unsigned ccURxS2 = 2;
constexpr unsigned ccURxS3 = 3;
constexpr unsigned ccUSART_RX_vect_num = 21;
constexpr unsigned ccUSART_TX_vect_num = 23;
constexpr unsigned ccUSART_UDRE_vect_num = 22;
constexpr unsigned ccUSBS = 3;
constexpr unsigned ccUTxS0 = 4;
constexpr unsigned ccUTxS1 = 5;
constexpr unsigned ccUTxS2 = 6;
constexpr unsigned ccUTxS3 = 7;
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
constexpr unsigned ccWDT_vect_num = 25;
constexpr unsigned ccWGM00 = 0;
constexpr unsigned ccWGM01 = 1;
constexpr unsigned ccWGM02 = 3;
constexpr unsigned ccWGM10 = 0;
constexpr unsigned ccWGM11 = 1;
constexpr unsigned ccWGM12 = 3;
constexpr unsigned ccWGM13 = 4;
constexpr unsigned cc_HAVE_AVR_STACK_POINTER_HI = 1;
constexpr unsigned cc_SFR_ASM_COMPAT = 0;
constexpr unsigned cc_VECTORS_SIZE = 64;
constexpr unsigned cc__EEPROM_REG_LOCATIONS__ = 1;
constexpr unsigned cc__USING_MINT8 = 0;


}  // arch_at90pwm3
}  // namespace avr
}  // namespace sys
}  // namespace ardo

#endif  // ardo_supplemental_at90pwm3__h
