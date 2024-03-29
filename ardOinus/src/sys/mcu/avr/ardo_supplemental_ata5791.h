// Generated for arch ata5791.
// This file is generated from the avr-gcc compiler with the mcu
// set to ata5791 from macros specific to avr/io.h.
// Any changes to this file will likely be lost next time this file
// is regenerated. Many any mcu_arch specific changes to 
// ardo_supplemental_ata5791_defs.h.

#ifndef ardo_supplemental_ata5791__h
#define ardo_supplemental_ata5791__h

#include "setlx_cstdint.h"
#include "setl_bit_fields.h"
#include "ardo_avr_bit_io_defs.h"

namespace ardo {
namespace sys {
namespace avr {
namespace arch_ata5791 {

constexpr ptrdiff_t cc__SFR_OFFSET = 0x20;

template <typename T, ptrdiff_t w_addr>
using IoRegisterDef = avr::nfp::IoRegisterDef<T, w_addr, cc__SFR_OFFSET>;
using avr::nfp::MemRegisterDef;

using rrAESCR = IoRegisterDef<std::uint8_t, 0x13>;
constexpr unsigned ccAESD = 3;
using rrAESDR = IoRegisterDef<std::uint8_t, 0x29>;
constexpr unsigned ccAESE = 7;
constexpr unsigned ccAESERF = 7;
constexpr unsigned ccAESIM = 2;
constexpr unsigned ccAESINT_vect_num = 22;
using rrAESKR = IoRegisterDef<std::uint8_t, 0x2A>;
constexpr unsigned ccAESKR0 = 0;
constexpr unsigned ccAESKR1 = 1;
constexpr unsigned ccAESKR2 = 2;
constexpr unsigned ccAESKR3 = 3;
constexpr unsigned ccAESKR4 = 4;
constexpr unsigned ccAESKR5 = 5;
constexpr unsigned ccAESKR6 = 6;
constexpr unsigned ccAESKR7 = 7;
constexpr unsigned ccAESRES = 5;
constexpr unsigned ccAESRF = 0;
using rrAESSR = IoRegisterDef<std::uint8_t, 0x14>;
constexpr unsigned ccAESWD = 1;
constexpr unsigned ccAESWK = 0;
constexpr unsigned ccAESXOR = 4;
constexpr unsigned ccBLB0_MODE_1 = 0xFF;
constexpr unsigned ccBLB0_MODE_2 = 0xFB;
constexpr unsigned ccBLB0_MODE_3 = 0xF3;
constexpr unsigned ccBLB0_MODE_4 = 0xF7;
constexpr unsigned ccBLB1_MODE_1 = 0xFF;
constexpr unsigned ccBLB1_MODE_2 = 0xEF;
constexpr unsigned ccBLB1_MODE_3 = 0xCF;
constexpr unsigned ccBLB1_MODE_4 = 0xDF;
constexpr unsigned ccBLBSET = 3;
constexpr unsigned ccBODLS = 7;
constexpr unsigned ccBODPD = 6;
constexpr unsigned ccBORF = 2;
constexpr unsigned ccCCS = 4;
constexpr unsigned ccCLKPCE = 7;
using rrCLKPR = IoRegisterDef<std::uint8_t, 0x3C>;
constexpr unsigned ccCLKPS0 = 0;
constexpr unsigned ccCLKPS1 = 1;
constexpr unsigned ccCLKPS2 = 2;
constexpr unsigned ccCLTPS0 = 3;
constexpr unsigned ccCLTPS1 = 4;
constexpr unsigned ccCLTPS2 = 5;
constexpr unsigned ccCMCCE = 7;
using rrCMCR = IoRegisterDef<std::uint8_t, 0x0F>;
using rrCMIMR = IoRegisterDef<std::uint8_t, 0x3B>;
constexpr unsigned ccCMM0 = 0;
constexpr unsigned ccCMM1 = 1;
constexpr unsigned ccCMONEN = 6;
using rrCMSR = IoRegisterDef<std::uint8_t, 0x10>;
constexpr unsigned ccCO32D = 3;
constexpr unsigned ccCPHA = 2;
constexpr unsigned ccCPOL = 3;
constexpr unsigned ccCRCBF = 0;
using rrCRCCR = MemRegisterDef<std::uint8_t, 0xAE>;
using rrCRCDR = MemRegisterDef<std::uint8_t, 0xAD>;
constexpr unsigned ccCRCN0 = 0;
constexpr unsigned ccCRCN1 = 1;
constexpr unsigned ccCRCN2 = 2;
using rrCRCPOL = MemRegisterDef<std::uint8_t, 0xAC>;
constexpr unsigned ccCRCRS = 7;
constexpr unsigned ccCRCSEL = 3;
using rrCRCSR = MemRegisterDef<std::uint8_t, 0xAF>;
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
constexpr unsigned ccDORD = 5;
constexpr unsigned ccE2END = 0x07FF;
constexpr unsigned ccE2PAGESIZE = 16;
constexpr unsigned ccE2SIZE = 2048;
constexpr unsigned ccE2START = 0;
constexpr unsigned ccECF = 0;
constexpr unsigned ccECIE = 0;
constexpr unsigned ccECINS = 5;
constexpr unsigned ccEEAP0 = 0;
constexpr unsigned ccEEAP1 = 1;
constexpr unsigned ccEEAP2 = 2;
constexpr unsigned ccEEAP3 = 3;
using rrEEAR = IoRegisterDef<std::uint16_t, 0x21>;
using rrEEARH = IoRegisterDef<std::uint8_t, 0x22>;
using rrEEARL = IoRegisterDef<std::uint8_t, 0x21>;
constexpr unsigned ccEEBRE = 0;
using rrEECCR = IoRegisterDef<std::uint8_t, 0x24>;
using rrEECR = IoRegisterDef<std::uint8_t, 0x1F>;
using rrEECR2 = IoRegisterDef<std::uint8_t, 0x25>;
using rrEEDR = IoRegisterDef<std::uint8_t, 0x20>;
constexpr unsigned ccEEL0 = 0;
constexpr unsigned ccEEL1 = 1;
constexpr unsigned ccEEL2 = 2;
constexpr unsigned ccEEL3 = 3;
constexpr unsigned ccEELP = 6;
constexpr unsigned ccEEMWE = 2;
constexpr unsigned ccEEPAGE = 1;
constexpr unsigned ccEEPM0 = 4;
constexpr unsigned ccEEPM1 = 5;
using rrEEPR = IoRegisterDef<std::uint8_t, 0x23>;
constexpr unsigned ccEERE = 0;
constexpr unsigned ccEEREADY_vect_num = 29;
constexpr unsigned ccEERIE = 3;
constexpr unsigned ccEEWE = 1;
using rrEICRA = MemRegisterDef<std::uint8_t, 0x69>;
using rrEIFR = IoRegisterDef<std::uint8_t, 0x1D>;
using rrEIMSK = IoRegisterDef<std::uint8_t, 0x27>;
constexpr unsigned ccEXCMINT_vect_num = 26;
constexpr unsigned ccEXTRF = 1;
constexpr unsigned ccEXXMINT_vect_num = 27;
constexpr unsigned ccFLASHEND = 0x3FFF;
constexpr unsigned ccFLASHSTART = 0x0000;
using rrFRCCAL = MemRegisterDef<std::uint8_t, 0x66>;
using ffFUSE_CKDIV8 = setl::BitsRW<setl::SemanticType<setl::hash("FUSE_CKDIV8"), bool>, 1u<<7>;
using ffFUSE_DWEN = setl::BitsRW<setl::SemanticType<setl::hash("FUSE_DWEN"), bool>, 1u<<6>;
using ffFUSE_EESAVE = setl::BitsRW<setl::SemanticType<setl::hash("FUSE_EESAVE"), bool>, 1u<<3>;
using ffFUSE_EXTCLKEN = setl::BitsRW<setl::SemanticType<setl::hash("FUSE_EXTCLKEN"), bool>, 1u<<0>;
constexpr unsigned ccFUSE_MEMORY_SIZE = 1;
using ffFUSE_Reserved = setl::BitsRW<setl::SemanticType<setl::hash("FUSE_Reserved"), bool>, 1u<<2>;
using ffFUSE_SPIEN = setl::BitsRW<setl::SemanticType<setl::hash("FUSE_SPIEN"), bool>, 1u<<5>;
using ffFUSE_WDTON = setl::BitsRW<setl::SemanticType<setl::hash("FUSE_WDTON"), bool>, 1u<<4>;
using ffFUSE__32OEN = setl::BitsRW<setl::SemanticType<setl::hash("FUSE__32OEN"), bool>, 1u<<1>;
using rrGPIOR = IoRegisterDef<std::uint8_t, 0x1E>;
constexpr unsigned ccID0E = 7;
constexpr unsigned ccID0FS0 = 0;
constexpr unsigned ccID0FS1 = 1;
constexpr unsigned ccID0FS2 = 2;
constexpr unsigned ccID0FS3 = 3;
constexpr unsigned ccID0FS4 = 4;
constexpr unsigned ccID1E = 7;
constexpr unsigned ccID1FS0 = 0;
constexpr unsigned ccID1FS1 = 1;
constexpr unsigned ccID1FS2 = 2;
constexpr unsigned ccID1FS3 = 3;
constexpr unsigned ccID1FS4 = 4;
constexpr unsigned ccINT0 = 0;
constexpr unsigned ccINT0_vect_num = 2;
constexpr unsigned ccINTF0 = 0;
constexpr unsigned ccISC00 = 0;
constexpr unsigned ccISC01 = 1;
constexpr unsigned ccIVCE = 0;
constexpr unsigned ccIVSEL = 1;
constexpr unsigned ccLB_MODE_1 = 0xFF;
constexpr unsigned ccLB_MODE_2 = 0xFE;
constexpr unsigned ccLB_MODE_3 = 0xFC;
using rrLDCR = MemRegisterDef<std::uint8_t, 0x6D>;
constexpr unsigned ccLDCS0 = 1;
constexpr unsigned ccLDCS1 = 2;
constexpr unsigned ccLDE = 0;
constexpr unsigned ccLFBRS = 3;
using rrLFCAD = MemRegisterDef<std::uint8_t, 0x83>;
constexpr unsigned ccLFCAF = 7;
using rrLFCC1 = MemRegisterDef<std::uint8_t, 0x96>;
using rrLFCC2 = MemRegisterDef<std::uint8_t, 0x97>;
using rrLFCC3 = MemRegisterDef<std::uint8_t, 0x98>;
constexpr unsigned ccLFCE1 = 0;
constexpr unsigned ccLFCE2 = 1;
constexpr unsigned ccLFCE3 = 2;
using rrLFCR0 = IoRegisterDef<std::uint8_t, 0x2F>;
using rrLFCR1 = IoRegisterDef<std::uint8_t, 0x30>;
constexpr unsigned ccLFDBF = 3;
constexpr unsigned ccLFDBIM = 3;
constexpr unsigned ccLFDBINT_vect_num = 10;
constexpr unsigned ccLFES = 0;
constexpr unsigned ccLFFEF = 2;
constexpr unsigned ccLFFEIM = 2;
constexpr unsigned ccLFFEINT_vect_num = 9;
constexpr unsigned ccLFFM0 = 2;
constexpr unsigned ccLFFM1 = 3;
using rrLFFR = IoRegisterDef<std::uint8_t, 0x18>;
using rrLFID00 = MemRegisterDef<std::uint8_t, 0x84>;
using rrLFID01 = MemRegisterDef<std::uint8_t, 0x85>;
using rrLFID02 = MemRegisterDef<std::uint8_t, 0x86>;
using rrLFID03 = MemRegisterDef<std::uint8_t, 0x87>;
constexpr unsigned ccLFID0F = 0;
constexpr unsigned ccLFID0IM = 0;
constexpr unsigned ccLFID0INT_vect_num = 7;
using rrLFID0M = MemRegisterDef<std::uint8_t, 0x90>;
using rrLFID10 = MemRegisterDef<std::uint8_t, 0x88>;
using rrLFID11 = MemRegisterDef<std::uint8_t, 0x89>;
using rrLFID12 = MemRegisterDef<std::uint8_t, 0x8A>;
using rrLFID13 = MemRegisterDef<std::uint8_t, 0x8B>;
constexpr unsigned ccLFID1F = 1;
constexpr unsigned ccLFID1IM = 1;
constexpr unsigned ccLFID1INT_vect_num = 8;
using rrLFID1M = MemRegisterDef<std::uint8_t, 0x91>;
using rrLFIMR = MemRegisterDef<std::uint8_t, 0x82>;
constexpr unsigned ccLFM0 = 0;
constexpr unsigned ccLFM1 = 1;
constexpr unsigned ccLFMDF = 6;
constexpr unsigned ccLFMDIM = 6;
constexpr unsigned ccLFMDINT_vect_num = 25;
constexpr unsigned ccLFMG = 5;
constexpr unsigned ccLFQCE = 6;
constexpr unsigned ccLFQCLL = 0;
using rrLFQCR = MemRegisterDef<std::uint8_t, 0x99>;
constexpr unsigned ccLFRBS = 4;
using rrLFRD0 = MemRegisterDef<std::uint8_t, 0x8C>;
using rrLFRD1 = MemRegisterDef<std::uint8_t, 0x8D>;
using rrLFRD2 = MemRegisterDef<std::uint8_t, 0x8E>;
using rrLFRD3 = MemRegisterDef<std::uint8_t, 0x8F>;
using rrLFRDB = IoRegisterDef<std::uint8_t, 0x32>;
using rrLFRDF = MemRegisterDef<std::uint8_t, 0x92>;
constexpr unsigned ccLFRE = 7;
constexpr unsigned ccLFRMS = 4;
constexpr unsigned ccLFRMSA = 5;
using rrLFRSD1 = MemRegisterDef<std::uint8_t, 0x93>;
using rrLFRSD2 = MemRegisterDef<std::uint8_t, 0x94>;
using rrLFRSD3 = MemRegisterDef<std::uint8_t, 0x95>;
constexpr unsigned ccLFRSF = 4;
constexpr unsigned ccLFRSIM = 4;
constexpr unsigned ccLFRSSINT_vect_num = 23;
constexpr unsigned ccLFSD = 1;
constexpr unsigned ccLFSDF = 5;
constexpr unsigned ccLFSDIM = 5;
constexpr unsigned ccLFSDINT_vect_num = 24;
using rrLFSR = IoRegisterDef<std::uint8_t, 0x36>;
constexpr unsigned ccLFVC0 = 6;
constexpr unsigned ccLFVC1 = 7;
constexpr unsigned ccLOCKBITS_DEFAULT = 0xFF;
using rrMCUCR = IoRegisterDef<std::uint8_t, 0x35>;
using rrMCUSR = IoRegisterDef<std::uint8_t, 0x34>;
constexpr unsigned ccMI1S0 = 0;
constexpr unsigned ccMI1S1 = 1;
constexpr unsigned ccMI2S0 = 2;
constexpr unsigned ccMI2S1 = 3;
constexpr unsigned ccMI4S0 = 4;
constexpr unsigned ccMI4S1 = 5;
constexpr unsigned ccMOS0 = 0;
constexpr unsigned ccMOS1 = 1;
constexpr unsigned ccMOUTC = 4;
constexpr unsigned ccMSCS0 = 2;
constexpr unsigned ccMSCS1 = 3;
constexpr unsigned ccMSTR = 4;
constexpr unsigned ccNVMBSY = 7;
using rrPCICR = IoRegisterDef<std::uint8_t, 0x26>;
constexpr unsigned ccPCIE0 = 0;
constexpr unsigned ccPCIE1 = 1;
constexpr unsigned ccPCIF0 = 0;
constexpr unsigned ccPCIF1 = 1;
using rrPCIFR = IoRegisterDef<std::uint8_t, 0x17>;
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
using rrPCMSK0 = MemRegisterDef<std::uint8_t, 0x6A>;
using rrPCMSK1 = MemRegisterDef<std::uint8_t, 0x6B>;
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
constexpr unsigned ccPRCI = 0;
constexpr unsigned ccPRCU = 5;
constexpr unsigned ccPRDS = 6;
constexpr unsigned ccPRLFR = 0;
using rrPRR0 = MemRegisterDef<std::uint8_t, 0x63>;
using rrPRR1 = MemRegisterDef<std::uint8_t, 0x64>;
constexpr unsigned ccPRSPI = 1;
constexpr unsigned ccPRT1 = 1;
constexpr unsigned ccPRT2 = 2;
constexpr unsigned ccPRT3 = 3;
constexpr unsigned ccPRTM = 4;
constexpr unsigned ccPRVM = 7;
constexpr unsigned ccPUD = 4;
constexpr unsigned ccRAMEND = 0x02FF;
constexpr unsigned ccRAMSIZE = 512;
constexpr unsigned ccRAMSTART = 0x0100;
constexpr unsigned ccRDFE = 7;
constexpr unsigned ccRDFS0 = 0;
constexpr unsigned ccRDFS1 = 1;
constexpr unsigned ccRDFS2 = 2;
constexpr unsigned ccRDFS3 = 3;
constexpr unsigned ccRDFS4 = 4;
constexpr unsigned ccREFLI = 4;
constexpr unsigned ccREFLO = 5;
using rrRTCCR = MemRegisterDef<std::uint8_t, 0x9E>;
using rrRTCDR = MemRegisterDef<std::uint8_t, 0x9F>;
constexpr unsigned ccRTCF = 2;
constexpr unsigned ccRTCIE = 2;
constexpr unsigned ccRTCINT_vect_num = 28;
constexpr unsigned ccRTCR = 0;
constexpr unsigned ccRWWSB = 6;
constexpr unsigned ccRWWSRE = 4;
constexpr unsigned ccSE = 0;
constexpr unsigned ccSIGNATURE_0 = 0x1E;
constexpr unsigned ccSIGNATURE_1 = 0x94;
constexpr unsigned ccSIGNATURE_2 = 0x62;
constexpr unsigned ccSIGRD = 5;
constexpr unsigned ccSLEEP_MODE_EXT_PWR_SAVE = 0x01;
constexpr unsigned ccSLEEP_MODE_IDLE = 0x00;
constexpr unsigned ccSLEEP_MODE_PWR_DOWN = 0x02;
constexpr unsigned ccSLEEP_MODE_PWR_SAVE = 0x03;
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
constexpr unsigned ccSPISTC_vect_num = 18;
using rrSPL = IoRegisterDef<std::uint8_t, 0x3D>;
using rrSPMCSR = IoRegisterDef<std::uint8_t, 0x37>;
constexpr unsigned ccSPMEN = 0;
constexpr unsigned ccSPMIE = 7;
constexpr unsigned ccSPMREADY_vect_num = 30;
constexpr unsigned ccSPM_PAGESIZE = 128;
constexpr unsigned ccSPR0 = 0;
constexpr unsigned ccSPR1 = 1;
using rrSPSR = IoRegisterDef<std::uint8_t, 0x2D>;
using rrSRCCAL = MemRegisterDef<std::uint8_t, 0x65>;
constexpr unsigned ccSRCD = 2;
using rrSREG = IoRegisterDef<std::uint8_t, 0x3F>;
constexpr unsigned ccSREG_C = 0;
constexpr unsigned ccSREG_H = 5;
constexpr unsigned ccSREG_I = 7;
constexpr unsigned ccSREG_N = 2;
constexpr unsigned ccSREG_S = 4;
constexpr unsigned ccSREG_T = 6;
constexpr unsigned ccSREG_V = 3;
constexpr unsigned ccSREG_Z = 1;
constexpr unsigned ccSTVAL = 6;
constexpr unsigned ccSXF = 1;
constexpr unsigned ccSXIE = 1;
using rrT0CR = IoRegisterDef<std::uint8_t, 0x39>;
constexpr unsigned ccT0F = 0;
constexpr unsigned ccT0IE = 3;
using rrT0IFR = IoRegisterDef<std::uint8_t, 0x19>;
constexpr unsigned ccT0INT_vect_num = 6;
constexpr unsigned ccT0PR = 4;
constexpr unsigned ccT0PS0 = 0;
constexpr unsigned ccT0PS1 = 1;
constexpr unsigned ccT0PS2 = 2;
using rrT1CR = IoRegisterDef<std::uint8_t, 0x38>;
constexpr unsigned ccT1CS0 = 3;
constexpr unsigned ccT1CS1 = 4;
constexpr unsigned ccT1E = 7;
constexpr unsigned ccT1F = 0;
constexpr unsigned ccT1IE = 2;
using rrT1IFR = IoRegisterDef<std::uint8_t, 0x1A>;
constexpr unsigned ccT1INT_vect_num = 17;
constexpr unsigned ccT1PS0 = 0;
constexpr unsigned ccT1PS1 = 1;
constexpr unsigned ccT2CIM = 1;
using rrT2CNT = MemRegisterDef<std::uint8_t, 0x70>;
constexpr unsigned ccT2COF = 1;
constexpr unsigned ccT2COMINT_vect_num = 15;
using rrT2COR = MemRegisterDef<std::uint8_t, 0x71>;
using rrT2CR = IoRegisterDef<std::uint8_t, 0x11>;
constexpr unsigned ccT2CRM = 2;
constexpr unsigned ccT2CS0 = 0;
constexpr unsigned ccT2CS1 = 1;
constexpr unsigned ccT2CS2 = 2;
constexpr unsigned ccT2CTM = 1;
constexpr unsigned ccT2D0 = 6;
constexpr unsigned ccT2D1 = 7;
constexpr unsigned ccT2E = 7;
constexpr unsigned ccT2GRM = 3;
using rrT2IFR = IoRegisterDef<std::uint8_t, 0x1B>;
using rrT2IMR = MemRegisterDef<std::uint8_t, 0x74>;
using rrT2MR = MemRegisterDef<std::uint8_t, 0x73>;
constexpr unsigned ccT2OFF = 0;
constexpr unsigned ccT2OIM = 0;
constexpr unsigned ccT2OTM = 0;
constexpr unsigned ccT2OVFINT_vect_num = 16;
constexpr unsigned ccT2PS0 = 3;
constexpr unsigned ccT2PS1 = 4;
constexpr unsigned ccT2PS2 = 5;
constexpr unsigned ccT2RES = 5;
constexpr unsigned ccT2TOP = 4;
constexpr unsigned ccT2TS = 6;
constexpr unsigned ccT3C2IM = 3;
constexpr unsigned ccT3C2RM = 2;
constexpr unsigned ccT3C2TM = 1;
constexpr unsigned ccT3CAPINT_vect_num = 11;
constexpr unsigned ccT3CE0 = 3;
constexpr unsigned ccT3CE1 = 4;
constexpr unsigned ccT3CIM = 1;
constexpr unsigned ccT3CNC = 5;
using rrT3CNT = MemRegisterDef<std::uint8_t, 0x76>;
constexpr unsigned ccT3CO2F = 3;
using rrT3CO2R = MemRegisterDef<std::uint8_t, 0x75>;
constexpr unsigned ccT3COF = 1;
constexpr unsigned ccT3COM2INT_vect_num = 14;
constexpr unsigned ccT3COMINT_vect_num = 12;
using rrT3COR = MemRegisterDef<std::uint8_t, 0x77>;
constexpr unsigned ccT3CPIM = 2;
constexpr unsigned ccT3CPRM = 3;
constexpr unsigned ccT3CPTM = 6;
using rrT3CR = IoRegisterDef<std::uint8_t, 0x12>;
using rrT3CR2 = IoRegisterDef<std::uint8_t, 0x0C>;
constexpr unsigned ccT3CRM = 2;
constexpr unsigned ccT3CS0 = 0;
constexpr unsigned ccT3CS1 = 1;
constexpr unsigned ccT3CTM = 1;
constexpr unsigned ccT3E = 7;
constexpr unsigned ccT3GRES = 0;
constexpr unsigned ccT3ICF = 2;
using rrT3ICR = MemRegisterDef<std::uint8_t, 0x78>;
constexpr unsigned ccT3ICS0 = 6;
constexpr unsigned ccT3ICS1 = 7;
using rrT3IFR = IoRegisterDef<std::uint8_t, 0x1C>;
using rrT3IMR = MemRegisterDef<std::uint8_t, 0x7B>;
using rrT3MRA = MemRegisterDef<std::uint8_t, 0x79>;
using rrT3MRB = MemRegisterDef<std::uint8_t, 0x7A>;
constexpr unsigned ccT3OFF = 0;
constexpr unsigned ccT3OIM = 0;
constexpr unsigned ccT3OTM = 0;
constexpr unsigned ccT3OVFINT_vect_num = 13;
constexpr unsigned ccT3PS0 = 0;
constexpr unsigned ccT3PS1 = 1;
constexpr unsigned ccT3PS2 = 2;
constexpr unsigned ccT3RES = 5;
constexpr unsigned ccT3SCE = 2;
constexpr unsigned ccT3TOP = 4;
constexpr unsigned ccTM12S = 7;
using rrTMBDR = MemRegisterDef<std::uint8_t, 0xA9>;
constexpr unsigned ccTMCPOL = 6;
using rrTMCR = MemRegisterDef<std::uint8_t, 0x7D>;
using rrTMDR = IoRegisterDef<std::uint8_t, 0x28>;
using rrTMIFR = IoRegisterDef<std::uint8_t, 0x15>;
using rrTMIMR = MemRegisterDef<std::uint8_t, 0x7F>;
using rrTMMDR = MemRegisterDef<std::uint8_t, 0xA8>;
using rrTMMR = MemRegisterDef<std::uint8_t, 0x7E>;
constexpr unsigned ccTMMS0 = 5;
constexpr unsigned ccTMMS1 = 6;
constexpr unsigned ccTMRXBINT_vect_num = 19;
constexpr unsigned ccTMRXF = 0;
constexpr unsigned ccTMRXIM = 0;
constexpr unsigned ccTMRXS = 3;
using rrTMSR = MemRegisterDef<std::uint8_t, 0xAB>;
constexpr unsigned ccTMSSIE = 7;
constexpr unsigned ccTMTCF = 2;
constexpr unsigned ccTMTCIM = 2;
using rrTMTDR = MemRegisterDef<std::uint8_t, 0xAA>;
constexpr unsigned ccTMTXBINT_vect_num = 20;
constexpr unsigned ccTMTXCINT_vect_num = 21;
constexpr unsigned ccTMTXF = 1;
constexpr unsigned ccTMTXIM = 1;
constexpr unsigned ccTMTXS = 4;
constexpr unsigned ccTPA = 1;
using rrTPCR = IoRegisterDef<std::uint8_t, 0x0D>;
constexpr unsigned ccTPD = 7;
constexpr unsigned ccTPF = 0;
using rrTPFR = IoRegisterDef<std::uint8_t, 0x0E>;
constexpr unsigned ccTPGAP = 2;
constexpr unsigned ccTPIM = 0;
using rrTPIMR = MemRegisterDef<std::uint8_t, 0x9C>;
constexpr unsigned ccTPINT_vect_num = 1;
constexpr unsigned ccTPMA = 0;
constexpr unsigned ccTPMD0 = 4;
constexpr unsigned ccTPMD1 = 5;
constexpr unsigned ccTPMOD = 1;
constexpr unsigned ccTPMS0 = 2;
constexpr unsigned ccTPMS1 = 3;
constexpr unsigned ccTPPSD = 6;
constexpr unsigned ccTPPSW = 3;
constexpr unsigned ccTPRF = 5;
using rrVMCR = IoRegisterDef<std::uint8_t, 0x2B>;
constexpr unsigned ccVMF = 0;
constexpr unsigned ccVMIM = 4;
constexpr unsigned ccVMINT_vect_num = 5;
constexpr unsigned ccVMLS0 = 0;
constexpr unsigned ccVMLS1 = 1;
constexpr unsigned ccVMLS2 = 2;
constexpr unsigned ccVMLS3 = 3;
constexpr unsigned ccVMPS = 5;
using rrVMSR = IoRegisterDef<std::uint8_t, 0x16>;
constexpr unsigned ccWCOL = 6;
constexpr unsigned ccWDCE = 4;
constexpr unsigned ccWDE = 3;
constexpr unsigned ccWDPS0 = 0;
constexpr unsigned ccWDPS1 = 1;
constexpr unsigned ccWDPS2 = 2;
constexpr unsigned ccWDRF = 3;
using rrWDTCR = MemRegisterDef<std::uint8_t, 0x60>;
constexpr unsigned cc_HAVE_AVR_STACK_POINTER_HI = 1;
constexpr unsigned cc_SFR_ASM_COMPAT = 0;
constexpr unsigned cc_VECTORS_SIZE = 124;
constexpr unsigned cc__USING_MINT8 = 0;


}  // arch_ata5791
}  // namespace avr
}  // namespace sys
}  // namespace ardo

#endif  // ardo_supplemental_ata5791__h
