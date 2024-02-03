// Generated for arch at90usb1287.
// This file is generated from the avr-gcc compiler with the mcu
// set to at90usb1287 from macros specific to avr/io.h.
// Any changes to this file will likely be lost next time this file
// is regenerated. Many any mcu_arch specific changes to 
// ardo_supplemental_at90usb1287_defs.h.

#ifndef ardo_supplemental_at90usb1287__h
#define ardo_supplemental_at90usb1287__h

#include "setlx_cstdint.h"
#include "setl_bit_fields.h"
#include "ardo_avr_bit_io_defs.h"

namespace ardo {
namespace sys {
namespace avr {
namespace arch_at90usb1287 {

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
constexpr unsigned ccADC_vect_num = 29;
constexpr unsigned ccADDEN = 7;
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
constexpr unsigned ccAIN0D = 0;
constexpr unsigned ccAIN1D = 1;
constexpr unsigned ccALLOC = 1;
constexpr unsigned ccANALOG_COMP_vect_num = 28;
constexpr unsigned ccAS2 = 5;
using rrASSR = MemRegisterDef<std::uint8_t, 0xB6>;
constexpr unsigned ccBCERRE = 2;
constexpr unsigned ccBCERRI = 2;
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
constexpr unsigned ccCOM2A0 = 6;
constexpr unsigned ccCOM2A1 = 7;
constexpr unsigned ccCOM2B0 = 4;
constexpr unsigned ccCOM2B1 = 5;
constexpr unsigned ccCOM3A0 = 6;
constexpr unsigned ccCOM3A1 = 7;
constexpr unsigned ccCOM3B0 = 4;
constexpr unsigned ccCOM3B1 = 5;
constexpr unsigned ccCOM3C0 = 2;
constexpr unsigned ccCOM3C1 = 3;
constexpr unsigned ccCOUNTER0 = 5;
constexpr unsigned ccCOUNTER1 = 6;
constexpr unsigned ccCPHA = 2;
constexpr unsigned ccCPOL = 3;
constexpr unsigned ccCRC16 = 4;
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
constexpr unsigned ccCTRLDIR = 2;
constexpr unsigned ccCURRBK0 = 0;
constexpr unsigned ccCURRBK1 = 1;
constexpr unsigned ccDATAPID = 1;
constexpr unsigned ccDATATGL = 0;
constexpr unsigned ccDCONNE = 0;
constexpr unsigned ccDCONNI = 0;
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
constexpr unsigned ccDDISCE = 1;
constexpr unsigned ccDDISCI = 1;
using rrDDRB = IoRegisterDef<std::uint8_t, 0x04>;
using rrDDRC = IoRegisterDef<std::uint8_t, 0x07>;
using rrDDRD = IoRegisterDef<std::uint8_t, 0x0A>;
using rrDDRE = IoRegisterDef<std::uint8_t, 0x0D>;
using rrDDRF = IoRegisterDef<std::uint8_t, 0x10>;
constexpr unsigned ccDETACH = 0;
using rrDIDR0 = MemRegisterDef<std::uint8_t, 0x7E>;
using rrDIDR1 = MemRegisterDef<std::uint8_t, 0x7F>;
constexpr unsigned ccDOR1 = 3;
constexpr unsigned ccDORD = 5;
constexpr unsigned ccDPACC = 7;
constexpr unsigned ccDTSEQ0 = 2;
constexpr unsigned ccDTSEQ1 = 3;
constexpr unsigned ccE2END = 0xFFF;
constexpr unsigned ccE2PAGESIZE = 8;
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
constexpr unsigned ccEE_READY_vect_num = 30;
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
constexpr unsigned ccEPINT5 = 5;
constexpr unsigned ccEPINT6 = 6;
constexpr unsigned ccEPRST0 = 0;
constexpr unsigned ccEPRST1 = 1;
constexpr unsigned ccEPRST2 = 2;
constexpr unsigned ccEPRST3 = 3;
constexpr unsigned ccEPRST4 = 4;
constexpr unsigned ccEPRST5 = 5;
constexpr unsigned ccEPRST6 = 6;
constexpr unsigned ccEPSIZE0 = 4;
constexpr unsigned ccEPSIZE1 = 5;
constexpr unsigned ccEPSIZE2 = 6;
constexpr unsigned ccEPTYPE0 = 6;
constexpr unsigned ccEPTYPE1 = 7;
constexpr unsigned ccEXCLK = 6;
constexpr unsigned ccEXTRF = 1;
constexpr unsigned ccFE1 = 4;
constexpr unsigned ccFIFOCON = 7;
constexpr unsigned ccFLASHEND = 0x1FFFF;
constexpr unsigned ccFLERRE = 7;
constexpr unsigned ccFNCERR = 4;
constexpr unsigned ccFOC0A = 7;
constexpr unsigned ccFOC0B = 6;
constexpr unsigned ccFOC1A = 7;
constexpr unsigned ccFOC1B = 6;
constexpr unsigned ccFOC1C = 5;
constexpr unsigned ccFOC2A = 7;
constexpr unsigned ccFOC2B = 6;
constexpr unsigned ccFOC3A = 7;
constexpr unsigned ccFOC3B = 6;
constexpr unsigned ccFOC3C = 5;
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
using ffFUSE_EESAVE = setl::BitsRW<setl::SemanticType<setl::hash("FUSE_EESAVE"), bool>, 1u<<3>;
using ffFUSE_HWBE = setl::BitsRW<setl::SemanticType<setl::hash("FUSE_HWBE"), bool>, 1u<<3>;
using ffFUSE_JTAGEN = setl::BitsRW<setl::SemanticType<setl::hash("FUSE_JTAGEN"), bool>, 1u<<6>;
constexpr unsigned ccFUSE_MEMORY_SIZE = 3;
using ffFUSE_OCDEN = setl::BitsRW<setl::SemanticType<setl::hash("FUSE_OCDEN"), bool>, 1u<<7>;
using ffFUSE_SPIEN = setl::BitsRW<setl::SemanticType<setl::hash("FUSE_SPIEN"), bool>, 1u<<5>;
using ffFUSE_SUT0 = setl::BitsRW<setl::SemanticType<setl::hash("FUSE_SUT0"), bool>, 1u<<4>;
using ffFUSE_SUT1 = setl::BitsRW<setl::SemanticType<setl::hash("FUSE_SUT1"), bool>, 1u<<5>;
using ffFUSE_WDTON = setl::BitsRW<setl::SemanticType<setl::hash("FUSE_WDTON"), bool>, 1u<<4>;
using rrGPIOR0 = IoRegisterDef<std::uint8_t, 0x1E>;
using rrGPIOR1 = IoRegisterDef<std::uint8_t, 0x2A>;
using rrGPIOR2 = IoRegisterDef<std::uint8_t, 0x2B>;
using rrGTCCR = IoRegisterDef<std::uint8_t, 0x23>;
constexpr unsigned ccHNPERRE = 4;
constexpr unsigned ccHNPERRI = 4;
constexpr unsigned ccHNPREQ = 5;
constexpr unsigned ccHOST = 6;
constexpr unsigned ccHSOFE = 5;
constexpr unsigned ccHSOFI = 5;
constexpr unsigned ccHWUPE = 6;
constexpr unsigned ccHWUPI = 6;
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
constexpr unsigned ccID = 1;
constexpr unsigned ccIDRD = 7;
constexpr unsigned ccIDTE = 1;
constexpr unsigned ccIDTI = 1;
constexpr unsigned ccINMODE = 5;
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
constexpr unsigned ccJTD = 7;
constexpr unsigned ccJTRF = 4;
constexpr unsigned ccLB_MODE_1 = 0xFF;
constexpr unsigned ccLB_MODE_2 = 0xFE;
constexpr unsigned ccLB_MODE_3 = 0xFC;
constexpr unsigned ccLOCKBITS_DEFAULT = 0xFF;
constexpr unsigned ccLSM = 2;
using rrMCUCR = IoRegisterDef<std::uint8_t, 0x35>;
using rrMCUSR = IoRegisterDef<std::uint8_t, 0x34>;
using rrMONDR = IoRegisterDef<std::uint8_t, 0x31>;
constexpr unsigned ccMPCM1 = 0;
constexpr unsigned ccMSTR = 4;
constexpr unsigned ccMUX0 = 0;
constexpr unsigned ccMUX1 = 1;
constexpr unsigned ccMUX2 = 2;
constexpr unsigned ccMUX3 = 3;
constexpr unsigned ccMUX4 = 4;
constexpr unsigned ccNAKEDE = 6;
constexpr unsigned ccNAKEDI = 6;
constexpr unsigned ccNAKINE = 6;
constexpr unsigned ccNAKINI = 6;
constexpr unsigned ccNAKOUTE = 4;
constexpr unsigned ccNAKOUTI = 4;
constexpr unsigned ccNBUSYBK0 = 0;
constexpr unsigned ccNBUSYBK1 = 1;
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
constexpr unsigned ccOCF1C = 3;
constexpr unsigned ccOCF2A = 1;
constexpr unsigned ccOCF2B = 2;
constexpr unsigned ccOCF3A = 1;
constexpr unsigned ccOCF3B = 2;
constexpr unsigned ccOCF3C = 3;
constexpr unsigned ccOCIE0A = 1;
constexpr unsigned ccOCIE0B = 2;
constexpr unsigned ccOCIE1A = 1;
constexpr unsigned ccOCIE1B = 2;
constexpr unsigned ccOCIE1C = 3;
constexpr unsigned ccOCIE2A = 1;
constexpr unsigned ccOCIE2B = 2;
constexpr unsigned ccOCIE3A = 1;
constexpr unsigned ccOCIE3B = 2;
constexpr unsigned ccOCIE3C = 3;
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
using rrOCR3C = MemRegisterDef<std::uint16_t, 0x9C>;
using rrOCR3CH = MemRegisterDef<std::uint8_t, 0x9D>;
using rrOCR3CL = MemRegisterDef<std::uint8_t, 0x9C>;
constexpr unsigned ccOPMODE2 = 5;
using rrOSCCAL = MemRegisterDef<std::uint8_t, 0x66>;
constexpr unsigned ccOTGPADE = 4;
constexpr unsigned ccOVERFI = 6;
constexpr unsigned ccPA0 = 0;
constexpr unsigned ccPA1 = 1;
constexpr unsigned ccPA2 = 2;
constexpr unsigned ccPA3 = 3;
constexpr unsigned ccPA4 = 4;
constexpr unsigned ccPA5 = 5;
constexpr unsigned ccPA6 = 6;
constexpr unsigned ccPA7 = 7;
constexpr unsigned ccPAGE0 = 5;
constexpr unsigned ccPAGE1 = 6;
constexpr unsigned ccPB0 = 0;
constexpr unsigned ccPB1 = 1;
constexpr unsigned ccPB2 = 2;
constexpr unsigned ccPB3 = 3;
constexpr unsigned ccPB4 = 4;
constexpr unsigned ccPB5 = 5;
constexpr unsigned ccPB6 = 6;
constexpr unsigned ccPB7 = 7;
constexpr unsigned ccPBK0 = 2;
constexpr unsigned ccPBK1 = 3;
constexpr unsigned ccPC0 = 0;
constexpr unsigned ccPC1 = 1;
constexpr unsigned ccPC2 = 2;
constexpr unsigned ccPC3 = 3;
constexpr unsigned ccPC4 = 4;
constexpr unsigned ccPC5 = 5;
constexpr unsigned ccPC6 = 6;
constexpr unsigned ccPC7 = 7;
using rrPCICR = MemRegisterDef<std::uint8_t, 0x68>;
constexpr unsigned ccPCIE0 = 0;
constexpr unsigned ccPCIF0 = 0;
using rrPCIFR = IoRegisterDef<std::uint8_t, 0x1B>;
constexpr unsigned ccPCINT0 = 0;
constexpr unsigned ccPCINT0_vect_num = 9;
constexpr unsigned ccPCINT1 = 1;
constexpr unsigned ccPCINT2 = 2;
constexpr unsigned ccPCINT3 = 3;
constexpr unsigned ccPCINT4 = 4;
constexpr unsigned ccPCINT5 = 5;
constexpr unsigned ccPCINT6 = 6;
constexpr unsigned ccPCINT7 = 7;
using rrPCMSK0 = MemRegisterDef<std::uint8_t, 0x6B>;
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
constexpr unsigned ccPEN = 0;
constexpr unsigned ccPEPNUM0 = 0;
constexpr unsigned ccPEPNUM1 = 1;
constexpr unsigned ccPEPNUM2 = 2;
constexpr unsigned ccPEPNUM3 = 3;
constexpr unsigned ccPERRE = 4;
constexpr unsigned ccPERRI = 4;
constexpr unsigned ccPF0 = 0;
constexpr unsigned ccPF1 = 1;
constexpr unsigned ccPF2 = 2;
constexpr unsigned ccPF3 = 3;
constexpr unsigned ccPF4 = 4;
constexpr unsigned ccPF5 = 5;
constexpr unsigned ccPF6 = 6;
constexpr unsigned ccPF7 = 7;
constexpr unsigned ccPFREEZE = 6;
constexpr unsigned ccPGERS = 1;
constexpr unsigned ccPGWRT = 2;
constexpr unsigned ccPID = 2;
constexpr unsigned ccPIN0 = 0;
constexpr unsigned ccPIN1 = 1;
constexpr unsigned ccPIN2 = 2;
constexpr unsigned ccPIN3 = 3;
constexpr unsigned ccPIN4 = 4;
constexpr unsigned ccPIN5 = 5;
constexpr unsigned ccPIN6 = 6;
constexpr unsigned ccPIN7 = 7;
constexpr unsigned ccPINA0 = 0;
constexpr unsigned ccPINA1 = 1;
constexpr unsigned ccPINA2 = 2;
constexpr unsigned ccPINA3 = 3;
constexpr unsigned ccPINA4 = 4;
constexpr unsigned ccPINA5 = 5;
constexpr unsigned ccPINA6 = 6;
constexpr unsigned ccPINA7 = 7;
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
constexpr unsigned ccPINT0 = 0;
constexpr unsigned ccPINT1 = 1;
constexpr unsigned ccPINT2 = 2;
constexpr unsigned ccPINT3 = 3;
constexpr unsigned ccPINT4 = 4;
constexpr unsigned ccPINT5 = 5;
constexpr unsigned ccPINT6 = 6;
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
using rrPORTE = IoRegisterDef<std::uint8_t, 0x0E>;
using rrPORTF = IoRegisterDef<std::uint8_t, 0x11>;
constexpr unsigned ccPRADC = 0;
using rrPRR0 = MemRegisterDef<std::uint8_t, 0x64>;
using rrPRR1 = MemRegisterDef<std::uint8_t, 0x65>;
constexpr unsigned ccPRSPI = 2;
constexpr unsigned ccPRST0 = 0;
constexpr unsigned ccPRST1 = 1;
constexpr unsigned ccPRST2 = 2;
constexpr unsigned ccPRST3 = 3;
constexpr unsigned ccPRST4 = 4;
constexpr unsigned ccPRST5 = 5;
constexpr unsigned ccPRST6 = 6;
constexpr unsigned ccPRTIM0 = 5;
constexpr unsigned ccPRTIM1 = 3;
constexpr unsigned ccPRTIM2 = 6;
constexpr unsigned ccPRTIM3 = 3;
constexpr unsigned ccPRTWI = 7;
constexpr unsigned ccPRUSART1 = 0;
constexpr unsigned ccPRUSB = 7;
constexpr unsigned ccPSIZE0 = 4;
constexpr unsigned ccPSIZE1 = 5;
constexpr unsigned ccPSIZE2 = 6;
constexpr unsigned ccPSRASY = 1;
constexpr unsigned ccPSRSYNC = 0;
constexpr unsigned ccPTOKEN0 = 4;
constexpr unsigned ccPTOKEN1 = 5;
constexpr unsigned ccPTYPE0 = 6;
constexpr unsigned ccPTYPE1 = 7;
constexpr unsigned ccPUD = 4;
constexpr unsigned ccRAMEND = 0x20FF;
using rrRAMPZ = IoRegisterDef<std::uint8_t, 0x3B>;
constexpr unsigned ccRAMSTART = 0x100;
constexpr unsigned ccREFS0 = 6;
constexpr unsigned ccREFS1 = 7;
constexpr unsigned ccRESET = 1;
constexpr unsigned ccRESUME = 2;
constexpr unsigned ccRMWKUP = 1;
constexpr unsigned ccROLEEXE = 3;
constexpr unsigned ccROLEEXI = 3;
constexpr unsigned ccRSMEDE = 3;
constexpr unsigned ccRSMEDI = 3;
constexpr unsigned ccRSTDT = 3;
constexpr unsigned ccRSTE = 2;
constexpr unsigned ccRSTI = 2;
constexpr unsigned ccRWAL = 5;
constexpr unsigned ccRWWSB = 6;
constexpr unsigned ccRWWSRE = 4;
constexpr unsigned ccRXB81 = 1;
constexpr unsigned ccRXC1 = 7;
constexpr unsigned ccRXCIE1 = 7;
constexpr unsigned ccRXEN1 = 4;
constexpr unsigned ccRXINE = 0;
constexpr unsigned ccRXINI = 0;
constexpr unsigned ccRXOUTE = 2;
constexpr unsigned ccRXOUTI = 2;
constexpr unsigned ccRXRSME = 4;
constexpr unsigned ccRXRSMI = 4;
constexpr unsigned ccRXSTALLE = 1;
constexpr unsigned ccRXSTALLI = 1;
constexpr unsigned ccRXSTPE = 3;
constexpr unsigned ccRXSTPI = 3;
constexpr unsigned ccSE = 0;
constexpr unsigned ccSIGNATURE_0 = 0x1E;
constexpr unsigned ccSIGNATURE_1 = 0x97;
constexpr unsigned ccSIGNATURE_2 = 0x82;
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
constexpr unsigned ccSOFE = 2;
constexpr unsigned ccSOFEN = 0;
constexpr unsigned ccSOFI = 2;
using rrSP = IoRegisterDef<std::uint16_t, 0x3D>;
using rrSPCR = IoRegisterDef<std::uint8_t, 0x2C>;
using rrSPDR = IoRegisterDef<std::uint8_t, 0x2E>;
constexpr unsigned ccSPE = 6;
constexpr unsigned ccSPEED = 3;
using rrSPH = IoRegisterDef<std::uint8_t, 0x3E>;
constexpr unsigned ccSPI2X = 0;
constexpr unsigned ccSPIE = 7;
constexpr unsigned ccSPIF = 7;
constexpr unsigned ccSPI_STC_vect_num = 24;
using rrSPL = IoRegisterDef<std::uint8_t, 0x3D>;
using rrSPMCSR = IoRegisterDef<std::uint8_t, 0x37>;
constexpr unsigned ccSPMEN = 0;
constexpr unsigned ccSPMIE = 7;
constexpr unsigned ccSPM_PAGESIZE = 256;
constexpr unsigned ccSPM_READY_vect_num = 37;
constexpr unsigned ccSPR0 = 0;
constexpr unsigned ccSPR1 = 1;
using rrSPSR = IoRegisterDef<std::uint8_t, 0x2D>;
constexpr unsigned ccSRE = 7;
using rrSREG = IoRegisterDef<std::uint8_t, 0x3F>;
constexpr unsigned ccSREG_C = 0;
constexpr unsigned ccSREG_H = 5;
constexpr unsigned ccSREG_I = 7;
constexpr unsigned ccSREG_N = 2;
constexpr unsigned ccSREG_S = 4;
constexpr unsigned ccSREG_T = 6;
constexpr unsigned ccSREG_V = 3;
constexpr unsigned ccSREG_Z = 1;
constexpr unsigned ccSRL0 = 4;
constexpr unsigned ccSRL1 = 5;
constexpr unsigned ccSRL2 = 6;
constexpr unsigned ccSRPE = 0;
constexpr unsigned ccSRPI = 0;
constexpr unsigned ccSRPREQ = 4;
constexpr unsigned ccSRPSEL = 3;
constexpr unsigned ccSRW00 = 0;
constexpr unsigned ccSRW01 = 1;
constexpr unsigned ccSRW10 = 2;
constexpr unsigned ccSRW11 = 3;
constexpr unsigned ccSTALLEDE = 1;
constexpr unsigned ccSTALLEDI = 1;
constexpr unsigned ccSTALLRQ = 5;
constexpr unsigned ccSTALLRQC = 4;
constexpr unsigned ccSTOE = 5;
constexpr unsigned ccSTOI = 5;
constexpr unsigned ccSUSPE = 0;
constexpr unsigned ccSUSPI = 0;
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
constexpr unsigned ccTIMEOUT = 3;
constexpr unsigned ccTIMER0_COMPA_vect_num = 21;
constexpr unsigned ccTIMER0_COMPB_vect_num = 22;
constexpr unsigned ccTIMER0_OVF_vect_num = 23;
constexpr unsigned ccTIMER1_CAPT_vect_num = 16;
constexpr unsigned ccTIMER1_COMPA_vect_num = 17;
constexpr unsigned ccTIMER1_COMPB_vect_num = 18;
constexpr unsigned ccTIMER1_COMPC_vect_num = 19;
constexpr unsigned ccTIMER1_OVF_vect_num = 20;
constexpr unsigned ccTIMER2_COMPA_vect_num = 13;
constexpr unsigned ccTIMER2_COMPB_vect_num = 14;
constexpr unsigned ccTIMER2_OVF_vect_num = 15;
constexpr unsigned ccTIMER3_CAPT_vect_num = 31;
constexpr unsigned ccTIMER3_COMPA_vect_num = 32;
constexpr unsigned ccTIMER3_COMPB_vect_num = 33;
constexpr unsigned ccTIMER3_COMPC_vect_num = 34;
constexpr unsigned ccTIMER3_OVF_vect_num = 35;
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
constexpr unsigned ccTSTJ = 2;
constexpr unsigned ccTSTK = 3;
constexpr unsigned ccTSTPCKT = 4;
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
constexpr unsigned ccTWI_vect_num = 36;
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
constexpr unsigned ccTXB81 = 0;
constexpr unsigned ccTXC1 = 6;
constexpr unsigned ccTXCIE1 = 6;
constexpr unsigned ccTXEN1 = 3;
constexpr unsigned ccTXINE = 0;
constexpr unsigned ccTXINI = 0;
constexpr unsigned ccTXOUTE = 2;
constexpr unsigned ccTXOUTI = 2;
constexpr unsigned ccTXSTPE = 3;
constexpr unsigned ccTXSTPI = 3;
constexpr unsigned ccU2X1 = 1;
using rrUBRR1 = MemRegisterDef<std::uint16_t, 0xCC>;
using rrUBRR1H = MemRegisterDef<std::uint8_t, 0xCD>;
using rrUBRR1L = MemRegisterDef<std::uint8_t, 0xCC>;
constexpr unsigned ccUCPOL1 = 0;
using rrUCSR1A = MemRegisterDef<std::uint8_t, 0xC8>;
using rrUCSR1C = MemRegisterDef<std::uint8_t, 0xCA>;
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
using rrUEBCHX = MemRegisterDef<std::uint8_t, 0xF3>;
using rrUEBCLX = MemRegisterDef<std::uint8_t, 0xF2>;
using rrUEBCX = MemRegisterDef<std::uint16_t, 0xF2>;
using rrUHADDR = MemRegisterDef<std::uint8_t, 0xA1>;
using rrUHCON = MemRegisterDef<std::uint8_t, 0x9E>;
using rrUHFLEN = MemRegisterDef<std::uint8_t, 0xA4>;
using rrUHFNUM = MemRegisterDef<std::uint16_t, 0xA2>;
using rrUHFNUMH = MemRegisterDef<std::uint8_t, 0xA3>;
using rrUHFNUML = MemRegisterDef<std::uint8_t, 0xA2>;
using rrUHIEN = MemRegisterDef<std::uint8_t, 0xA0>;
using rrUHINT = MemRegisterDef<std::uint8_t, 0x9F>;
constexpr unsigned ccUIDE = 6;
constexpr unsigned ccUIMOD = 7;
constexpr unsigned ccUMSEL10 = 6;
constexpr unsigned ccUMSEL11 = 7;
constexpr unsigned ccUNDERFI = 5;
using rrUPBCHX = MemRegisterDef<std::uint8_t, 0xF7>;
using rrUPBCLX = MemRegisterDef<std::uint8_t, 0xF6>;
using rrUPBCX = MemRegisterDef<std::uint16_t, 0xF6>;
using rrUPCONX = MemRegisterDef<std::uint8_t, 0xA9>;
constexpr unsigned ccUPE1 = 2;
using rrUPINRQX = MemRegisterDef<std::uint8_t, 0xA5>;
using rrUPINTX = MemRegisterDef<std::uint8_t, 0xA6>;
constexpr unsigned ccUPM10 = 4;
constexpr unsigned ccUPM11 = 5;
using rrUPNUM = MemRegisterDef<std::uint8_t, 0xA7>;
constexpr unsigned ccUPRSME = 6;
constexpr unsigned ccUPRSMI = 6;
using rrUPRST = MemRegisterDef<std::uint8_t, 0xA8>;
constexpr unsigned ccUSART1_RX_vect_num = 25;
constexpr unsigned ccUSART1_TX_vect_num = 27;
constexpr unsigned ccUSART1_UDRE_vect_num = 26;
constexpr unsigned ccUSBE = 7;
constexpr unsigned ccUSBS1 = 3;
constexpr unsigned ccUSB_COM_vect_num = 11;
constexpr unsigned ccUSB_GEN_vect_num = 10;
constexpr unsigned ccUVCONE = 4;
constexpr unsigned ccUVREGE = 0;
constexpr unsigned ccVALUE0 = 0;
constexpr unsigned ccVALUE1 = 1;
constexpr unsigned ccVBERRE = 1;
constexpr unsigned ccVBERRI = 1;
constexpr unsigned ccVBUS = 0;
constexpr unsigned ccVBUSHWC = 2;
constexpr unsigned ccVBUSREQ = 1;
constexpr unsigned ccVBUSRQC = 0;
constexpr unsigned ccVBUSTE = 0;
constexpr unsigned ccVBUSTI = 0;
constexpr unsigned ccWAKEUPE = 4;
constexpr unsigned ccWAKEUPI = 4;
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
constexpr unsigned ccWDT_vect_num = 12;
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
constexpr unsigned ccXMBK = 7;
using rrXMCRA = MemRegisterDef<std::uint8_t, 0x74>;
using rrXMCRB = MemRegisterDef<std::uint8_t, 0x75>;
constexpr unsigned ccXMM0 = 0;
constexpr unsigned ccXMM1 = 1;
constexpr unsigned ccXMM2 = 2;
constexpr unsigned ccXRAMEND = 0xFFFF;
constexpr unsigned ccZLPSEEN = 4;
constexpr unsigned cc_HAVE_AVR_STACK_POINTER_HI = 1;
constexpr unsigned cc_SFR_ASM_COMPAT = 0;
constexpr unsigned cc_VECTORS_SIZE = 152;
constexpr unsigned cc__EEPROM_REG_LOCATIONS__ = 1;
constexpr unsigned cc__USING_MINT8 = 0;


}  // arch_at90usb1287
}  // namespace avr
}  // namespace sys
}  // namespace ardo

#endif  // ardo_supplemental_at90usb1287__h
