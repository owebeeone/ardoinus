// Generated for arch ata6616c.
// This file is generated from the avr-gcc compiler with the mcu
// set to ata6616c from macros specific to avr/io.h.
// Any changes to this file will likely be lost next time this file
// is regenerated. Many any mcu_arch specific changes to 
// ardo_supplemental_ata6616c_defs.h.

#ifndef ardo_supplemental_ata6616c__h
#define ardo_supplemental_ata6616c__h

#include "setlx_cstdint.h"
#include "setl_bit_fields.h"
#include "ardo_avr_bit_io_defs.h"

namespace ardo {
namespace sys {
namespace avr {
namespace arch_ata6616c {

constexpr ptrdiff_t cc__SFR_OFFSET = 0x20;

template <typename T, ptrdiff_t w_addr>
using IoRegisterDef = avr::nfp::IoRegisterDef<T, w_addr, cc__SFR_OFFSET>;
using avr::nfp::MemRegisterDef;

constexpr unsigned ccACD = 7;
constexpr unsigned ccACI = 4;
constexpr unsigned ccACIC = 2;
constexpr unsigned ccACIE = 3;
constexpr unsigned ccACIR0 = 4;
constexpr unsigned ccACIR1 = 5;
constexpr unsigned ccACIRS = 6;
constexpr unsigned ccACIS0 = 0;
constexpr unsigned ccACIS1 = 1;
constexpr unsigned ccACME = 6;
constexpr unsigned ccACO = 5;
using rrACSR = IoRegisterDef<std::uint8_t, 0x30>;
constexpr unsigned ccADATE = 5;
using rrADC = MemRegisterDef<std::uint16_t, 0x78>;
constexpr unsigned ccADC0D = 0;
constexpr unsigned ccADC10D = 6;
constexpr unsigned ccADC1D = 1;
constexpr unsigned ccADC2D = 2;
constexpr unsigned ccADC3D = 3;
constexpr unsigned ccADC4D = 4;
constexpr unsigned ccADC5D = 5;
constexpr unsigned ccADC6D = 6;
constexpr unsigned ccADC7D = 7;
constexpr unsigned ccADC8D = 4;
constexpr unsigned ccADC9D = 5;
using rrADCH = MemRegisterDef<std::uint8_t, 0x79>;
using rrADCL = MemRegisterDef<std::uint8_t, 0x78>;
using rrADCSRA = MemRegisterDef<std::uint8_t, 0x7A>;
using rrADCSRB = MemRegisterDef<std::uint8_t, 0x7B>;
using rrADCW = MemRegisterDef<std::uint16_t, 0x78>;
constexpr unsigned ccADC_vect_num = 15;
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
using rrAMISCR = MemRegisterDef<std::uint8_t, 0x77>;
constexpr unsigned ccANA_COMP_vect_num = 17;
constexpr unsigned ccAREFEN = 2;
constexpr unsigned ccAS0 = 5;
using rrASSR = MemRegisterDef<std::uint8_t, 0xB6>;
constexpr unsigned ccBBMA = 4;
constexpr unsigned ccBBMB = 5;
constexpr unsigned ccBIN = 7;
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
constexpr unsigned ccCLKC0 = 0;
constexpr unsigned ccCLKC1 = 1;
constexpr unsigned ccCLKC2 = 2;
constexpr unsigned ccCLKC3 = 3;
constexpr unsigned ccCLKCCE = 7;
using rrCLKCSR = MemRegisterDef<std::uint8_t, 0x62>;
constexpr unsigned ccCLKPCE = 7;
using rrCLKPR = MemRegisterDef<std::uint8_t, 0x61>;
constexpr unsigned ccCLKPS0 = 0;
constexpr unsigned ccCLKPS1 = 1;
constexpr unsigned ccCLKPS2 = 2;
constexpr unsigned ccCLKPS3 = 3;
constexpr unsigned ccCLKRDY = 4;
using rrCLKSELR = MemRegisterDef<std::uint8_t, 0x63>;
constexpr unsigned ccCOM0A0 = 6;
constexpr unsigned ccCOM0A1 = 7;
constexpr unsigned ccCOM1A0 = 6;
constexpr unsigned ccCOM1A1 = 7;
constexpr unsigned ccCOM1B0 = 4;
constexpr unsigned ccCOM1B1 = 5;
constexpr unsigned ccCOUT = 6;
constexpr unsigned ccCPHA = 2;
constexpr unsigned ccCPOL = 3;
constexpr unsigned ccCS00 = 0;
constexpr unsigned ccCS01 = 1;
constexpr unsigned ccCS02 = 2;
constexpr unsigned ccCS10 = 0;
constexpr unsigned ccCS11 = 1;
constexpr unsigned ccCS12 = 2;
constexpr unsigned ccCSEL0 = 0;
constexpr unsigned ccCSEL1 = 1;
constexpr unsigned ccCSEL2 = 2;
constexpr unsigned ccCSEL3 = 3;
constexpr unsigned ccCSUT0 = 4;
constexpr unsigned ccCSUT1 = 5;
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
using rrDDRA = IoRegisterDef<std::uint8_t, 0x01>;
using rrDDRB = IoRegisterDef<std::uint8_t, 0x04>;
using rrDIDR0 = MemRegisterDef<std::uint8_t, 0x7E>;
using rrDIDR1 = MemRegisterDef<std::uint8_t, 0x7F>;
constexpr unsigned ccDORD = 5;
using rrDWDR = IoRegisterDef<std::uint8_t, 0x31>;
constexpr unsigned ccDWDR0 = 0;
constexpr unsigned ccDWDR1 = 1;
constexpr unsigned ccDWDR2 = 2;
constexpr unsigned ccDWDR3 = 3;
constexpr unsigned ccDWDR4 = 4;
constexpr unsigned ccDWDR5 = 5;
constexpr unsigned ccDWDR6 = 6;
constexpr unsigned ccDWDR7 = 7;
constexpr unsigned ccE2END = 0x01FF;
constexpr unsigned ccE2PAGESIZE = 4;
constexpr unsigned ccE2SIZE = 512;
constexpr unsigned ccE2START = 0;
using rrEEAR = IoRegisterDef<std::uint16_t, 0x21>;
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
constexpr unsigned ccEE_RDY_vect_num = 16;
constexpr unsigned ccEFUSE_DEFAULT = 0xFF;
using rrEICRA = MemRegisterDef<std::uint8_t, 0x69>;
using rrEIFR = IoRegisterDef<std::uint8_t, 0x1C>;
using rrEIMSK = IoRegisterDef<std::uint8_t, 0x1D>;
constexpr unsigned ccEXCLK = 6;
constexpr unsigned ccEXTRF = 1;
constexpr unsigned ccFLASHEND = 0x1FFF;
constexpr unsigned ccFLASHSTART = 0x0000;
constexpr unsigned ccFOC0A = 7;
constexpr unsigned ccFOC1A = 7;
constexpr unsigned ccFOC1B = 6;
using ffFUSE_BODLEVEL0 = setl::BitsRW<setl::SemanticType<setl::hash("FUSE_BODLEVEL0"), bool>, 1u<<0>;
using ffFUSE_BODLEVEL1 = setl::BitsRW<setl::SemanticType<setl::hash("FUSE_BODLEVEL1"), bool>, 1u<<1>;
using ffFUSE_BODLEVEL2 = setl::BitsRW<setl::SemanticType<setl::hash("FUSE_BODLEVEL2"), bool>, 1u<<2>;
using ffFUSE_CKDIV8 = setl::BitsRW<setl::SemanticType<setl::hash("FUSE_CKDIV8"), bool>, 1u<<7>;
using ffFUSE_CKOUT = setl::BitsRW<setl::SemanticType<setl::hash("FUSE_CKOUT"), bool>, 1u<<6>;
using ffFUSE_DWEN = setl::BitsRW<setl::SemanticType<setl::hash("FUSE_DWEN"), bool>, 1u<<6>;
using ffFUSE_EESAVE = setl::BitsRW<setl::SemanticType<setl::hash("FUSE_EESAVE"), bool>, 1u<<3>;
constexpr unsigned ccFUSE_MEMORY_SIZE = 3;
using ffFUSE_RSTDISBL = setl::BitsRW<setl::SemanticType<setl::hash("FUSE_RSTDISBL"), bool>, 1u<<7>;
using ffFUSE_SELFPRGEN = setl::BitsRW<setl::SemanticType<setl::hash("FUSE_SELFPRGEN"), bool>, 1u<<0>;
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
constexpr unsigned ccICF1 = 5;
constexpr unsigned ccICIE1 = 5;
constexpr unsigned ccICNC1 = 7;
using rrICR1 = MemRegisterDef<std::uint16_t, 0x86>;
using rrICR1H = MemRegisterDef<std::uint8_t, 0x87>;
using rrICR1L = MemRegisterDef<std::uint8_t, 0x86>;
constexpr unsigned ccINT0 = 0;
constexpr unsigned ccINT0_vect_num = 1;
constexpr unsigned ccINT1 = 1;
constexpr unsigned ccINT1_vect_num = 2;
constexpr unsigned ccINTF0 = 0;
constexpr unsigned ccINTF1 = 1;
constexpr unsigned ccISC00 = 0;
constexpr unsigned ccISC01 = 1;
constexpr unsigned ccISC10 = 2;
constexpr unsigned ccISC11 = 3;
constexpr unsigned ccISRCEN = 0;
constexpr unsigned ccLABORT = 7;
constexpr unsigned ccLAINC = 3;
constexpr unsigned ccLBERR = 0;
constexpr unsigned ccLBT0 = 0;
constexpr unsigned ccLBT1 = 1;
constexpr unsigned ccLBT2 = 2;
constexpr unsigned ccLBT3 = 3;
constexpr unsigned ccLBT4 = 4;
constexpr unsigned ccLBT5 = 5;
constexpr unsigned ccLBUSY = 4;
constexpr unsigned ccLB_MODE_1 = 0xFF;
constexpr unsigned ccLB_MODE_2 = 0xFE;
constexpr unsigned ccLB_MODE_3 = 0xFC;
constexpr unsigned ccLCERR = 1;
constexpr unsigned ccLCMD0 = 0;
constexpr unsigned ccLCMD1 = 1;
constexpr unsigned ccLCMD2 = 2;
constexpr unsigned ccLCONF0 = 4;
constexpr unsigned ccLCONF1 = 5;
constexpr unsigned ccLDATA0 = 0;
constexpr unsigned ccLDATA1 = 1;
constexpr unsigned ccLDATA2 = 2;
constexpr unsigned ccLDATA3 = 3;
constexpr unsigned ccLDATA4 = 4;
constexpr unsigned ccLDATA5 = 5;
constexpr unsigned ccLDATA6 = 6;
constexpr unsigned ccLDATA7 = 7;
constexpr unsigned ccLDISR = 7;
constexpr unsigned ccLDIV0 = 0;
constexpr unsigned ccLDIV1 = 1;
constexpr unsigned ccLDIV10 = 2;
constexpr unsigned ccLDIV11 = 3;
constexpr unsigned ccLDIV2 = 2;
constexpr unsigned ccLDIV3 = 3;
constexpr unsigned ccLDIV4 = 4;
constexpr unsigned ccLDIV5 = 5;
constexpr unsigned ccLDIV6 = 6;
constexpr unsigned ccLDIV7 = 7;
constexpr unsigned ccLDIV8 = 0;
constexpr unsigned ccLDIV9 = 1;
constexpr unsigned ccLENA = 3;
constexpr unsigned ccLENERR = 3;
constexpr unsigned ccLENIDOK = 2;
constexpr unsigned ccLENRXOK = 0;
constexpr unsigned ccLENTXOK = 1;
constexpr unsigned ccLERR = 3;
constexpr unsigned ccLFERR = 4;
constexpr unsigned ccLID0 = 0;
constexpr unsigned ccLID1 = 1;
constexpr unsigned ccLID2 = 2;
constexpr unsigned ccLID3 = 3;
constexpr unsigned ccLID4 = 4;
constexpr unsigned ccLID5 = 5;
constexpr unsigned ccLIDOK = 2;
constexpr unsigned ccLIDST0 = 5;
constexpr unsigned ccLIDST1 = 6;
constexpr unsigned ccLIDST2 = 7;
constexpr unsigned ccLIN13 = 6;
using rrLINBRR = MemRegisterDef<std::uint16_t, 0xCD>;
using rrLINBRRH = MemRegisterDef<std::uint8_t, 0xCE>;
using rrLINBRRL = MemRegisterDef<std::uint8_t, 0xCD>;
using rrLINBTR = MemRegisterDef<std::uint8_t, 0xCC>;
using rrLINCR = MemRegisterDef<std::uint8_t, 0xC8>;
using rrLINDAT = MemRegisterDef<std::uint8_t, 0xD2>;
using rrLINDLR = MemRegisterDef<std::uint8_t, 0xCF>;
constexpr unsigned ccLINDX0 = 0;
constexpr unsigned ccLINDX1 = 1;
constexpr unsigned ccLINDX2 = 2;
using rrLINENIR = MemRegisterDef<std::uint8_t, 0xCA>;
using rrLINERR = MemRegisterDef<std::uint8_t, 0xCB>;
using rrLINIDR = MemRegisterDef<std::uint8_t, 0xD0>;
using rrLINSEL = MemRegisterDef<std::uint8_t, 0xD1>;
using rrLINSIR = MemRegisterDef<std::uint8_t, 0xC9>;
constexpr unsigned ccLIN_ERR_vect_num = 13;
constexpr unsigned ccLIN_TC_vect_num = 12;
constexpr unsigned ccLOCKBITS_DEFAULT = 0xFF;
constexpr unsigned ccLOVERR = 5;
constexpr unsigned ccLP0 = 6;
constexpr unsigned ccLP1 = 7;
constexpr unsigned ccLPERR = 2;
constexpr unsigned ccLRXDL0 = 0;
constexpr unsigned ccLRXDL1 = 1;
constexpr unsigned ccLRXDL2 = 2;
constexpr unsigned ccLRXDL3 = 3;
constexpr unsigned ccLRXOK = 0;
constexpr unsigned ccLSERR = 3;
constexpr unsigned ccLSWRES = 7;
constexpr unsigned ccLTOERR = 6;
constexpr unsigned ccLTXDL0 = 4;
constexpr unsigned ccLTXDL1 = 5;
constexpr unsigned ccLTXDL2 = 6;
constexpr unsigned ccLTXDL3 = 7;
constexpr unsigned ccLTXOK = 1;
using rrMCUCR = IoRegisterDef<std::uint8_t, 0x35>;
using rrMCUSR = IoRegisterDef<std::uint8_t, 0x34>;
constexpr unsigned ccMSTR = 4;
constexpr unsigned ccMUX0 = 0;
constexpr unsigned ccMUX1 = 1;
constexpr unsigned ccMUX2 = 2;
constexpr unsigned ccMUX3 = 3;
constexpr unsigned ccMUX4 = 4;
constexpr unsigned ccOC1AU = 0;
constexpr unsigned ccOC1AV = 1;
constexpr unsigned ccOC1AW = 2;
constexpr unsigned ccOC1AX = 3;
constexpr unsigned ccOC1BU = 4;
constexpr unsigned ccOC1BV = 5;
constexpr unsigned ccOC1BW = 6;
constexpr unsigned ccOC1BX = 7;
constexpr unsigned ccOCF0A = 1;
constexpr unsigned ccOCF1A = 1;
constexpr unsigned ccOCF1B = 2;
constexpr unsigned ccOCIE0A = 1;
constexpr unsigned ccOCIE1A = 1;
constexpr unsigned ccOCIE1B = 2;
constexpr unsigned ccOCR00 = 0;
constexpr unsigned ccOCR01 = 1;
constexpr unsigned ccOCR02 = 2;
constexpr unsigned ccOCR03 = 3;
constexpr unsigned ccOCR04 = 4;
constexpr unsigned ccOCR05 = 5;
constexpr unsigned ccOCR06 = 6;
constexpr unsigned ccOCR07 = 7;
using rrOCR0A = IoRegisterDef<std::uint8_t, 0x28>;
constexpr unsigned ccOCR0AUB = 3;
using rrOCR1A = MemRegisterDef<std::uint16_t, 0x88>;
using rrOCR1AH = MemRegisterDef<std::uint8_t, 0x89>;
using rrOCR1AL = MemRegisterDef<std::uint8_t, 0x88>;
using rrOCR1B = MemRegisterDef<std::uint16_t, 0x8A>;
using rrOCR1BH = MemRegisterDef<std::uint8_t, 0x8B>;
using rrOCR1BL = MemRegisterDef<std::uint8_t, 0x8A>;
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
constexpr unsigned ccPCIF0 = 0;
constexpr unsigned ccPCIF1 = 1;
using rrPCIFR = IoRegisterDef<std::uint8_t, 0x1B>;
constexpr unsigned ccPCINT0 = 0;
constexpr unsigned ccPCINT0_vect_num = 3;
constexpr unsigned ccPCINT1 = 1;
constexpr unsigned ccPCINT10 = 2;
constexpr unsigned ccPCINT11 = 3;
constexpr unsigned ccPCINT12 = 4;
constexpr unsigned ccPCINT13 = 5;
constexpr unsigned ccPCINT14 = 6;
constexpr unsigned ccPCINT15 = 7;
constexpr unsigned ccPCINT1_vect_num = 4;
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
using rrPORTCR = IoRegisterDef<std::uint8_t, 0x12>;
constexpr unsigned ccPRADC = 0;
constexpr unsigned ccPRLIN = 5;
using rrPRR = MemRegisterDef<std::uint8_t, 0x64>;
constexpr unsigned ccPRSPI = 4;
constexpr unsigned ccPRTIM0 = 2;
constexpr unsigned ccPRTIM1 = 3;
constexpr unsigned ccPRUSI = 1;
constexpr unsigned ccPSR0 = 1;
constexpr unsigned ccPSR1 = 0;
constexpr unsigned ccPUD = 4;
constexpr unsigned ccPUDA = 0;
constexpr unsigned ccPUDB = 1;
constexpr unsigned ccRAMEND = 0x02FF;
constexpr unsigned ccRAMSIZE = 512;
constexpr unsigned ccRAMSTART = 0x0100;
constexpr unsigned ccREFS0 = 6;
constexpr unsigned ccREFS1 = 7;
constexpr unsigned ccRFLB = 3;
constexpr unsigned ccRWWSB = 6;
constexpr unsigned ccSE = 0;
constexpr unsigned ccSIGNATURE_0 = 0x1E;
constexpr unsigned ccSIGNATURE_1 = 0x93;
constexpr unsigned ccSIGNATURE_2 = 0x87;
constexpr unsigned ccSIGRD = 5;
constexpr unsigned ccSLEEP_MODE_ADC = 0x01;
constexpr unsigned ccSLEEP_MODE_IDLE = 0x00;
constexpr unsigned ccSLEEP_MODE_PWR_DOWN = 0x02;
constexpr unsigned ccSM0 = 1;
constexpr unsigned ccSM1 = 2;
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
constexpr unsigned ccSPI_STC_vect_num = 14;
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
using rrTCCR0A = IoRegisterDef<std::uint8_t, 0x25>;
using rrTCCR0B = IoRegisterDef<std::uint8_t, 0x26>;
using rrTCCR1A = MemRegisterDef<std::uint8_t, 0x80>;
using rrTCCR1B = MemRegisterDef<std::uint8_t, 0x81>;
using rrTCCR1C = MemRegisterDef<std::uint8_t, 0x82>;
using rrTCCR1D = MemRegisterDef<std::uint8_t, 0x83>;
constexpr unsigned ccTCN0UB = 4;
using rrTCNT0 = IoRegisterDef<std::uint8_t, 0x27>;
constexpr unsigned ccTCNT00 = 0;
constexpr unsigned ccTCNT01 = 1;
constexpr unsigned ccTCNT02 = 2;
constexpr unsigned ccTCNT03 = 3;
constexpr unsigned ccTCNT04 = 4;
constexpr unsigned ccTCNT05 = 5;
constexpr unsigned ccTCNT06 = 6;
constexpr unsigned ccTCNT07 = 7;
using rrTCNT1 = MemRegisterDef<std::uint16_t, 0x84>;
using rrTCNT1H = MemRegisterDef<std::uint8_t, 0x85>;
using rrTCNT1L = MemRegisterDef<std::uint8_t, 0x84>;
constexpr unsigned ccTCR0AUB = 1;
constexpr unsigned ccTCR0BUB = 0;
using rrTIFR0 = IoRegisterDef<std::uint8_t, 0x15>;
using rrTIFR1 = IoRegisterDef<std::uint8_t, 0x16>;
constexpr unsigned ccTIMER0_COMPA_vect_num = 10;
constexpr unsigned ccTIMER0_OVF_vect_num = 11;
constexpr unsigned ccTIMER1_CAPT_vect_num = 6;
constexpr unsigned ccTIMER1_COMPA_vect_num = 7;
constexpr unsigned ccTIMER1_COMPB_vect_num = 8;
constexpr unsigned ccTIMER1_OVF_vect_num = 9;
using rrTIMSK0 = MemRegisterDef<std::uint8_t, 0x6E>;
using rrTIMSK1 = MemRegisterDef<std::uint8_t, 0x6F>;
constexpr unsigned ccTOIE0 = 0;
constexpr unsigned ccTOIE1 = 0;
constexpr unsigned ccTOV0 = 0;
constexpr unsigned ccTOV1 = 0;
constexpr unsigned ccTSM = 7;
using rrUSIBR = MemRegisterDef<std::uint8_t, 0xBB>;
constexpr unsigned ccUSIBR0 = 0;
constexpr unsigned ccUSIBR1 = 1;
constexpr unsigned ccUSIBR2 = 2;
constexpr unsigned ccUSIBR3 = 3;
constexpr unsigned ccUSIBR4 = 4;
constexpr unsigned ccUSIBR5 = 5;
constexpr unsigned ccUSIBR6 = 6;
constexpr unsigned ccUSIBR7 = 7;
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
constexpr unsigned ccUSIDR0 = 0;
constexpr unsigned ccUSIDR1 = 1;
constexpr unsigned ccUSIDR2 = 2;
constexpr unsigned ccUSIDR3 = 3;
constexpr unsigned ccUSIDR4 = 4;
constexpr unsigned ccUSIDR5 = 5;
constexpr unsigned ccUSIDR6 = 6;
constexpr unsigned ccUSIDR7 = 7;
constexpr unsigned ccUSIOIE = 6;
constexpr unsigned ccUSIOIF = 6;
constexpr unsigned ccUSIPF = 5;
constexpr unsigned ccUSIPOS = 0;
using rrUSIPP = MemRegisterDef<std::uint8_t, 0xBC>;
constexpr unsigned ccUSISIE = 7;
constexpr unsigned ccUSISIF = 7;
using rrUSISR = MemRegisterDef<std::uint8_t, 0xB9>;
constexpr unsigned ccUSITC = 0;
constexpr unsigned ccUSIWM0 = 4;
constexpr unsigned ccUSIWM1 = 5;
constexpr unsigned ccUSI_OVF_vect_num = 19;
constexpr unsigned ccUSI_START_vect_num = 18;
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
using rrWDTCR = MemRegisterDef<std::uint8_t, 0x60>;
constexpr unsigned ccWDT_vect_num = 5;
constexpr unsigned ccWGM00 = 0;
constexpr unsigned ccWGM01 = 1;
constexpr unsigned ccWGM10 = 0;
constexpr unsigned ccWGM11 = 1;
constexpr unsigned ccWGM12 = 3;
constexpr unsigned ccWGM13 = 4;
constexpr unsigned ccXREFEN = 1;
constexpr unsigned cc_HAVE_AVR_STACK_POINTER_HI = 1;
constexpr unsigned cc_SFR_ASM_COMPAT = 0;
constexpr unsigned cc_VECTORS_SIZE = 40;
constexpr unsigned cc__USING_MINT8 = 0;


}  // arch_ata6616c
}  // namespace avr
}  // namespace sys
}  // namespace ardo

#endif  // ardo_supplemental_ata6616c__h
