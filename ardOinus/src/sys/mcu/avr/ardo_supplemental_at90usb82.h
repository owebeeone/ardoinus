// Generated for arch at90usb82.
// This file is generated from the avr-gcc compiler with the mcu
// set to at90usb82 from macros specific to avr/io.h.
// Any changes to this file will likely be lost next time this file
// is regenerated. Many any mcu_arch specific changes to 
// ardo_supplemental_at90usb82_defs.h.

#ifndef ardo_supplemental_at90usb82__h
#define ardo_supplemental_at90usb82__h

#include "setlx_cstdint.h"
#include "setl_bit_fields.h"
#include "ardo_avr_bit_io_defs.h"

namespace ardo {
namespace sys {
namespace avr {
namespace arch_at90usb82 {

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
constexpr unsigned ccACO = 5;
using rrACSR = IoRegisterDef<std::uint8_t, 0x30>;
constexpr unsigned ccADDEN = 7;
constexpr unsigned ccALLOC = 1;
constexpr unsigned ccANALOG_COMP_vect_num = 26;
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
constexpr unsigned ccCFGOK = 7;
constexpr unsigned ccCLKPCE = 7;
using rrCLKPR = MemRegisterDef<std::uint8_t, 0x61>;
constexpr unsigned ccCLKPS0 = 0;
constexpr unsigned ccCLKPS1 = 1;
constexpr unsigned ccCLKPS2 = 2;
constexpr unsigned ccCLKPS3 = 3;
constexpr unsigned ccCLKS = 0;
constexpr unsigned ccCOM0A0 = 6;
constexpr unsigned ccCOM0A1 = 7;
constexpr unsigned ccCOM0B0 = 4;
constexpr unsigned ccCOM0B1 = 5;
constexpr unsigned ccCOM1A0 = 6;
constexpr unsigned ccCOM1A1 = 7;
constexpr unsigned ccCOM1B0 = 4;
constexpr unsigned ccCOM1B1 = 5;
constexpr unsigned ccCOM1C0 = 2;
constexpr unsigned ccCOM1C1 = 3;
constexpr unsigned ccCPHA = 2;
constexpr unsigned ccCPOL = 3;
constexpr unsigned ccCS00 = 0;
constexpr unsigned ccCS01 = 1;
constexpr unsigned ccCS02 = 2;
constexpr unsigned ccCS10 = 0;
constexpr unsigned ccCS11 = 1;
constexpr unsigned ccCS12 = 2;
constexpr unsigned ccCTRLDIR = 2;
constexpr unsigned ccCTSEN = 1;
constexpr unsigned ccCURRBK0 = 0;
constexpr unsigned ccCURRBK1 = 1;
constexpr unsigned ccDATAI = 2;
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
using rrDDRB = IoRegisterDef<std::uint8_t, 0x04>;
using rrDDRC = IoRegisterDef<std::uint8_t, 0x07>;
using rrDDRD = IoRegisterDef<std::uint8_t, 0x0A>;
constexpr unsigned ccDETACH = 0;
constexpr unsigned ccDMI = 0;
constexpr unsigned ccDOR1 = 3;
constexpr unsigned ccDORD = 5;
constexpr unsigned ccDPACC = 7;
constexpr unsigned ccDPI = 1;
constexpr unsigned ccDTSEQ0 = 2;
constexpr unsigned ccDTSEQ1 = 3;
using rrDWDR = IoRegisterDef<std::uint8_t, 0x31>;
constexpr unsigned ccE2END = 0x1FF;
constexpr unsigned ccE2PAGESIZE = 4;
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
constexpr unsigned ccEE_READY_vect_num = 27;
using rrEICRA = MemRegisterDef<std::uint8_t, 0x69>;
using rrEICRB = MemRegisterDef<std::uint8_t, 0x6A>;
using rrEIFR = IoRegisterDef<std::uint8_t, 0x1C>;
using rrEIMSK = IoRegisterDef<std::uint8_t, 0x1D>;
constexpr unsigned ccEORSME = 5;
constexpr unsigned ccEORSMI = 5;
constexpr unsigned ccEORSTE = 3;
constexpr unsigned ccEORSTI = 3;
constexpr unsigned ccEPBK0 = 2;
constexpr unsigned ccEPBK1 = 3;
constexpr unsigned ccEPDIR = 0;
constexpr unsigned ccEPEN = 0;
constexpr unsigned ccEPINT0 = 0;
constexpr unsigned ccEPINT1 = 1;
constexpr unsigned ccEPINT2 = 2;
constexpr unsigned ccEPINT3 = 3;
constexpr unsigned ccEPINT4 = 4;
constexpr unsigned ccEPNUM0 = 0;
constexpr unsigned ccEPNUM1 = 1;
constexpr unsigned ccEPNUM2 = 2;
constexpr unsigned ccEPRST0 = 0;
constexpr unsigned ccEPRST1 = 1;
constexpr unsigned ccEPRST2 = 2;
constexpr unsigned ccEPRST3 = 3;
constexpr unsigned ccEPRST4 = 4;
constexpr unsigned ccEPSIZE0 = 4;
constexpr unsigned ccEPSIZE1 = 5;
constexpr unsigned ccEPSIZE2 = 6;
constexpr unsigned ccEPTYPE0 = 6;
constexpr unsigned ccEPTYPE1 = 7;
constexpr unsigned ccEXCKSEL0 = 0;
constexpr unsigned ccEXCKSEL1 = 1;
constexpr unsigned ccEXCKSEL2 = 2;
constexpr unsigned ccEXCKSEL3 = 3;
constexpr unsigned ccEXSUT0 = 4;
constexpr unsigned ccEXSUT1 = 5;
constexpr unsigned ccEXTE = 2;
constexpr unsigned ccEXTON = 0;
constexpr unsigned ccEXTRF = 1;
constexpr unsigned ccFE1 = 4;
constexpr unsigned ccFIFOCON = 7;
constexpr unsigned ccFLASHEND = 0x1FFF;
constexpr unsigned ccFLERRE = 7;
constexpr unsigned ccFNCERR = 4;
constexpr unsigned ccFOC0A = 7;
constexpr unsigned ccFOC0B = 6;
constexpr unsigned ccFOC1A = 7;
constexpr unsigned ccFOC1B = 6;
constexpr unsigned ccFOC1C = 5;
constexpr unsigned ccFRZCLK = 5;
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
using ffFUSE_DWEN = setl::BitsRW<setl::SemanticType<setl::hash("FUSE_DWEN"), bool>, 1u<<7>;
using ffFUSE_EESAVE = setl::BitsRW<setl::SemanticType<setl::hash("FUSE_EESAVE"), bool>, 1u<<3>;
using ffFUSE_HWBE = setl::BitsRW<setl::SemanticType<setl::hash("FUSE_HWBE"), bool>, 1u<<3>;
constexpr unsigned ccFUSE_MEMORY_SIZE = 3;
using ffFUSE_RSTDSBL = setl::BitsRW<setl::SemanticType<setl::hash("FUSE_RSTDSBL"), bool>, 1u<<6>;
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
constexpr unsigned ccINT1 = 1;
constexpr unsigned ccINT1_vect_num = 2;
constexpr unsigned ccINT2 = 2;
constexpr unsigned ccINT2_vect_num = 3;
constexpr unsigned ccINT3 = 3;
constexpr unsigned ccINT3_vect_num = 4;
constexpr unsigned ccINT4 = 4;
constexpr unsigned ccINT4_vect_num = 5;
constexpr unsigned ccINT5 = 5;
constexpr unsigned ccINT5_vect_num = 6;
constexpr unsigned ccINT6 = 6;
constexpr unsigned ccINT6_vect_num = 7;
constexpr unsigned ccINT7 = 7;
constexpr unsigned ccINT7_vect_num = 8;
constexpr unsigned ccINTF0 = 0;
constexpr unsigned ccINTF1 = 1;
constexpr unsigned ccINTF2 = 2;
constexpr unsigned ccINTF3 = 3;
constexpr unsigned ccINTF4 = 4;
constexpr unsigned ccINTF5 = 5;
constexpr unsigned ccINTF6 = 6;
constexpr unsigned ccINTF7 = 7;
constexpr unsigned ccISC00 = 0;
constexpr unsigned ccISC01 = 1;
constexpr unsigned ccISC10 = 2;
constexpr unsigned ccISC11 = 3;
constexpr unsigned ccISC20 = 4;
constexpr unsigned ccISC21 = 5;
constexpr unsigned ccISC30 = 6;
constexpr unsigned ccISC31 = 7;
constexpr unsigned ccISC40 = 0;
constexpr unsigned ccISC41 = 1;
constexpr unsigned ccISC50 = 2;
constexpr unsigned ccISC51 = 3;
constexpr unsigned ccISC60 = 4;
constexpr unsigned ccISC61 = 5;
constexpr unsigned ccISC70 = 6;
constexpr unsigned ccISC71 = 7;
constexpr unsigned ccIVCE = 0;
constexpr unsigned ccIVSEL = 1;
constexpr unsigned ccLB_MODE_1 = 0xFF;
constexpr unsigned ccLB_MODE_2 = 0xFE;
constexpr unsigned ccLB_MODE_3 = 0xFC;
constexpr unsigned ccLOCKBITS_DEFAULT = 0xFF;
using rrMCUCR = IoRegisterDef<std::uint8_t, 0x35>;
using rrMCUSR = IoRegisterDef<std::uint8_t, 0x34>;
constexpr unsigned ccMPCM1 = 0;
constexpr unsigned ccMSTR = 4;
constexpr unsigned ccNAKINE = 6;
constexpr unsigned ccNAKINI = 6;
constexpr unsigned ccNAKOUTE = 4;
constexpr unsigned ccNAKOUTI = 4;
constexpr unsigned ccNBUSYBK0 = 0;
constexpr unsigned ccNBUSYBK1 = 1;
constexpr unsigned ccOCF0A = 1;
constexpr unsigned ccOCF0B = 2;
constexpr unsigned ccOCF1A = 1;
constexpr unsigned ccOCF1B = 2;
constexpr unsigned ccOCF1C = 3;
constexpr unsigned ccOCIE0A = 1;
constexpr unsigned ccOCIE0B = 2;
constexpr unsigned ccOCIE1A = 1;
constexpr unsigned ccOCIE1B = 2;
constexpr unsigned ccOCIE1C = 3;
using rrOCR0A = IoRegisterDef<std::uint8_t, 0x27>;
using rrOCR1A = MemRegisterDef<std::uint16_t, 0x88>;
using rrOCR1AH = MemRegisterDef<std::uint8_t, 0x89>;
using rrOCR1AL = MemRegisterDef<std::uint8_t, 0x88>;
using rrOCR1B = MemRegisterDef<std::uint16_t, 0x8A>;
using rrOCR1BH = MemRegisterDef<std::uint8_t, 0x8B>;
using rrOCR1BL = MemRegisterDef<std::uint8_t, 0x8A>;
using rrOCR1C = MemRegisterDef<std::uint16_t, 0x8C>;
using rrOCR1CH = MemRegisterDef<std::uint8_t, 0x8D>;
using rrOCR1CL = MemRegisterDef<std::uint8_t, 0x8C>;
using rrOSCCAL = MemRegisterDef<std::uint8_t, 0x66>;
constexpr unsigned ccOVERFI = 6;
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
constexpr unsigned ccPC4 = 4;
constexpr unsigned ccPC5 = 5;
constexpr unsigned ccPC6 = 6;
constexpr unsigned ccPC7 = 7;
using rrPCICR = MemRegisterDef<std::uint8_t, 0x68>;
constexpr unsigned ccPCIE0 = 0;
constexpr unsigned ccPCIE1 = 1;
constexpr unsigned ccPCIF0 = 0;
constexpr unsigned ccPCIF1 = 1;
using rrPCIFR = IoRegisterDef<std::uint8_t, 0x1B>;
constexpr unsigned ccPCINT0 = 0;
constexpr unsigned ccPCINT0_vect_num = 9;
constexpr unsigned ccPCINT1 = 1;
constexpr unsigned ccPCINT10 = 2;
constexpr unsigned ccPCINT11 = 3;
constexpr unsigned ccPCINT12 = 4;
constexpr unsigned ccPCINT1_vect_num = 10;
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
using rrPLLCSR = IoRegisterDef<std::uint8_t, 0x29>;
constexpr unsigned ccPLLE = 1;
constexpr unsigned ccPLLP0 = 2;
constexpr unsigned ccPLLP1 = 3;
constexpr unsigned ccPLLP2 = 4;
constexpr unsigned ccPLOCK = 0;
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
using rrPRR0 = MemRegisterDef<std::uint8_t, 0x64>;
using rrPRR1 = MemRegisterDef<std::uint8_t, 0x65>;
constexpr unsigned ccPRSPI = 2;
constexpr unsigned ccPRTIM0 = 5;
constexpr unsigned ccPRTIM1 = 3;
constexpr unsigned ccPRUSART1 = 0;
constexpr unsigned ccPRUSB = 7;
constexpr unsigned ccPS2EN = 0;
constexpr unsigned ccPSRASY = 1;
constexpr unsigned ccPSRSYNC = 0;
constexpr unsigned ccPUD = 4;
constexpr unsigned ccRAMEND = 0x2FF;
constexpr unsigned ccRAMSTART = 0x100;
constexpr unsigned ccRCCKSEL0 = 4;
constexpr unsigned ccRCCKSEL1 = 5;
constexpr unsigned ccRCCKSEL2 = 6;
constexpr unsigned ccRCCKSEL3 = 7;
constexpr unsigned ccRCE = 3;
constexpr unsigned ccRCON = 1;
constexpr unsigned ccRCSUT0 = 6;
constexpr unsigned ccRCSUT1 = 7;
using rrREGCR = MemRegisterDef<std::uint8_t, 0x63>;
constexpr unsigned ccREGDIS = 0;
constexpr unsigned ccRMWKUP = 1;
constexpr unsigned ccRSTCPU = 2;
constexpr unsigned ccRSTDT = 3;
constexpr unsigned ccRTSEN = 0;
constexpr unsigned ccRWAL = 5;
constexpr unsigned ccRWWSB = 6;
constexpr unsigned ccRWWSRE = 4;
constexpr unsigned ccRXB81 = 1;
constexpr unsigned ccRXC1 = 7;
constexpr unsigned ccRXCIE1 = 7;
constexpr unsigned ccRXEN1 = 4;
constexpr unsigned ccRXOUTE = 2;
constexpr unsigned ccRXOUTI = 2;
constexpr unsigned ccRXSTPE = 3;
constexpr unsigned ccRXSTPI = 3;
constexpr unsigned ccSCKI = 3;
constexpr unsigned ccSE = 0;
constexpr unsigned ccSIGRD = 5;
constexpr unsigned ccSLEEP_MODE_EXT_STANDBY = 0x07;
constexpr unsigned ccSLEEP_MODE_IDLE = 0x00;
constexpr unsigned ccSLEEP_MODE_PWR_DOWN = 0x02;
constexpr unsigned ccSLEEP_MODE_PWR_SAVE = 0x03;
constexpr unsigned ccSLEEP_MODE_STANDBY = 0x06;
constexpr unsigned ccSM0 = 1;
constexpr unsigned ccSM1 = 2;
constexpr unsigned ccSM2 = 3;
using rrSMCR = IoRegisterDef<std::uint8_t, 0x33>;
constexpr unsigned ccSOFE = 2;
constexpr unsigned ccSOFI = 2;
using rrSP = IoRegisterDef<std::uint16_t, 0x3D>;
using rrSPCR = IoRegisterDef<std::uint8_t, 0x2C>;
using rrSPDR = IoRegisterDef<std::uint8_t, 0x2E>;
constexpr unsigned ccSPE = 6;
using rrSPH = IoRegisterDef<std::uint8_t, 0x3E>;
constexpr unsigned ccSPI2X = 0;
constexpr unsigned ccSPIE = 7;
constexpr unsigned ccSPIF = 7;
constexpr unsigned ccSPI_STC_vect_num = 22;
using rrSPL = IoRegisterDef<std::uint8_t, 0x3D>;
using rrSPMCSR = IoRegisterDef<std::uint8_t, 0x37>;
constexpr unsigned ccSPMEN = 0;
constexpr unsigned ccSPMIE = 7;
constexpr unsigned ccSPM_PAGESIZE = 128;
constexpr unsigned ccSPM_READY_vect_num = 28;
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
constexpr unsigned ccSTALLEDE = 1;
constexpr unsigned ccSTALLEDI = 1;
constexpr unsigned ccSTALLRQ = 5;
constexpr unsigned ccSTALLRQC = 4;
constexpr unsigned ccSUSPE = 0;
constexpr unsigned ccSUSPI = 0;
using rrTCCR0A = IoRegisterDef<std::uint8_t, 0x24>;
using rrTCCR0B = IoRegisterDef<std::uint8_t, 0x25>;
using rrTCCR1A = MemRegisterDef<std::uint8_t, 0x80>;
using rrTCCR1B = MemRegisterDef<std::uint8_t, 0x81>;
using rrTCCR1C = MemRegisterDef<std::uint8_t, 0x82>;
using rrTCNT1 = MemRegisterDef<std::uint16_t, 0x84>;
using rrTCNT1H = MemRegisterDef<std::uint8_t, 0x85>;
using rrTCNT1L = MemRegisterDef<std::uint8_t, 0x84>;
using rrTIFR0 = IoRegisterDef<std::uint8_t, 0x15>;
using rrTIFR1 = IoRegisterDef<std::uint8_t, 0x16>;
constexpr unsigned ccTIMER0_COMPA_vect_num = 19;
constexpr unsigned ccTIMER0_COMPB_vect_num = 20;
constexpr unsigned ccTIMER0_OVF_vect_num = 21;
constexpr unsigned ccTIMER1_CAPT_vect_num = 14;
constexpr unsigned ccTIMER1_COMPA_vect_num = 15;
constexpr unsigned ccTIMER1_COMPB_vect_num = 16;
constexpr unsigned ccTIMER1_COMPC_vect_num = 17;
constexpr unsigned ccTIMER1_OVF_vect_num = 18;
using rrTIMSK0 = MemRegisterDef<std::uint8_t, 0x6E>;
using rrTIMSK1 = MemRegisterDef<std::uint8_t, 0x6F>;
constexpr unsigned ccTOIE0 = 0;
constexpr unsigned ccTOIE1 = 0;
constexpr unsigned ccTOV0 = 0;
constexpr unsigned ccTOV1 = 0;
constexpr unsigned ccTSM = 7;
constexpr unsigned ccTXB81 = 0;
constexpr unsigned ccTXC1 = 6;
constexpr unsigned ccTXCIE1 = 6;
constexpr unsigned ccTXEN1 = 3;
constexpr unsigned ccTXINE = 0;
constexpr unsigned ccTXINI = 0;
constexpr unsigned ccU2X1 = 1;
using rrUBRR1 = MemRegisterDef<std::uint16_t, 0xCC>;
using rrUBRR1H = MemRegisterDef<std::uint8_t, 0xCD>;
using rrUBRR1L = MemRegisterDef<std::uint8_t, 0xCC>;
constexpr unsigned ccUCPOL1 = 0;
using rrUCSR1A = MemRegisterDef<std::uint8_t, 0xC8>;
using rrUCSR1C = MemRegisterDef<std::uint8_t, 0xCA>;
using rrUCSR1D = MemRegisterDef<std::uint8_t, 0xCB>;
constexpr unsigned ccUCSZ10 = 1;
constexpr unsigned ccUCSZ11 = 2;
constexpr unsigned ccUCSZ12 = 2;
using rrUDFNUM = MemRegisterDef<std::uint16_t, 0xE4>;
using rrUDFNUMH = MemRegisterDef<std::uint8_t, 0xE5>;
using rrUDFNUML = MemRegisterDef<std::uint8_t, 0xE4>;
using rrUDPADD = MemRegisterDef<std::uint16_t, 0xDB>;
using rrUDPADDH = MemRegisterDef<std::uint8_t, 0xDC>;
using rrUDPADDL = MemRegisterDef<std::uint8_t, 0xDB>;
constexpr unsigned ccUDRE1 = 5;
constexpr unsigned ccUDRIE1 = 5;
using rrUEBCLX = MemRegisterDef<std::uint8_t, 0xF2>;
constexpr unsigned ccUMSEL10 = 6;
constexpr unsigned ccUMSEL11 = 7;
constexpr unsigned ccUNDERFI = 5;
constexpr unsigned ccUPDRV0 = 4;
constexpr unsigned ccUPDRV1 = 5;
constexpr unsigned ccUPE1 = 2;
constexpr unsigned ccUPM10 = 4;
constexpr unsigned ccUPM11 = 5;
constexpr unsigned ccUPRSME = 6;
constexpr unsigned ccUPRSMI = 6;
constexpr unsigned ccUPWE0 = 6;
constexpr unsigned ccUPWE1 = 7;
constexpr unsigned ccUSART1_RX_vect_num = 23;
constexpr unsigned ccUSART1_TX_vect_num = 25;
constexpr unsigned ccUSART1_UDRE_vect_num = 24;
constexpr unsigned ccUSBE = 7;
constexpr unsigned ccUSBRF = 5;
constexpr unsigned ccUSBS1 = 3;
constexpr unsigned ccUSB_COM_vect_num = 12;
constexpr unsigned ccUSB_GEN_vect_num = 11;
constexpr unsigned ccWAKEUPE = 4;
constexpr unsigned ccWAKEUPI = 4;
constexpr unsigned ccWCLKD0 = 0;
constexpr unsigned ccWCLKD1 = 1;
constexpr unsigned ccWCOL = 6;
constexpr unsigned ccWDCE = 4;
constexpr unsigned ccWDE = 3;
constexpr unsigned ccWDEWIE = 2;
constexpr unsigned ccWDEWIF = 3;
constexpr unsigned ccWDIE = 6;
constexpr unsigned ccWDIF = 7;
constexpr unsigned ccWDP0 = 0;
constexpr unsigned ccWDP1 = 1;
constexpr unsigned ccWDP2 = 2;
constexpr unsigned ccWDP3 = 5;
constexpr unsigned ccWDRF = 3;
using rrWDTCKD = MemRegisterDef<std::uint8_t, 0x62>;
using rrWDTCSR = MemRegisterDef<std::uint8_t, 0x60>;
constexpr unsigned ccWDT_vect_num = 13;
constexpr unsigned ccWGM00 = 0;
constexpr unsigned ccWGM01 = 1;
constexpr unsigned ccWGM02 = 3;
constexpr unsigned ccWGM10 = 0;
constexpr unsigned ccWGM11 = 1;
constexpr unsigned ccWGM12 = 3;
constexpr unsigned ccWGM13 = 4;
constexpr unsigned cc_HAVE_AVR_STACK_POINTER_HI = 1;
constexpr unsigned cc_SFR_ASM_COMPAT = 0;
constexpr unsigned cc_VECTORS_SIZE = 116;
constexpr unsigned cc__EEPROM_REG_LOCATIONS__ = 1;
constexpr unsigned cc__USING_MINT8 = 0;


}  // arch_at90usb82
}  // namespace avr
}  // namespace sys
}  // namespace ardo

#endif  // ardo_supplemental_at90usb82__h
