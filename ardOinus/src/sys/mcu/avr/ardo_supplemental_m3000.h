// Generated for arch m3000.
// This file is generated from the avr-gcc compiler with the mcu
// set to m3000 from macros specific to avr/io.h.
// Any changes to this file will likely be lost next time this file
// is regenerated. Many any mcu_arch specific changes to 
// ardo_supplemental_m3000_defs.h.

#ifndef ardo_supplemental_m3000__h
#define ardo_supplemental_m3000__h

#include "setlx_cstdint.h"
#include "setl_bit_fields.h"
#include "ardo_avr_bit_io_defs.h"

namespace ardo {
namespace sys {
namespace avr {
namespace arch_m3000 {

constexpr ptrdiff_t cc__SFR_OFFSET = 0x20;

template <typename T, ptrdiff_t w_addr>
using IoRegisterDef = avr::nfp::IoRegisterDef<T, w_addr, cc__SFR_OFFSET>;
using avr::nfp::MemRegisterDef;

using rrADCSR = IoRegisterDef<std::uint8_t, 0x07>;
using rrADRSLT = IoRegisterDef<std::uint16_t, 0x05>;
using rrADRSLTH = IoRegisterDef<std::uint8_t, 0x06>;
using rrADRSLTHI = IoRegisterDef<std::uint8_t, 0x06>;
using rrADRSLTL = IoRegisterDef<std::uint8_t, 0x05>;
using rrADRSLTLO = IoRegisterDef<std::uint8_t, 0x05>;
using rrAGPDDR = IoRegisterDef<std::uint8_t, 0x1E>;
using rrAGPPIN = IoRegisterDef<std::uint8_t, 0x1D>;
using rrAGPPORT = IoRegisterDef<std::uint8_t, 0x1F>;
using rrAMUXCTL = IoRegisterDef<std::uint8_t, 0x0B>;
using rrBGPDDR = IoRegisterDef<std::uint8_t, 0x1B>;
using rrBGPPIN = IoRegisterDef<std::uint8_t, 0x1A>;
using rrBGPPORT = IoRegisterDef<std::uint8_t, 0x1C>;
using rrCBTR1 = MemRegisterDef<std::uint8_t, 0x101>;
using rrCBTR2 = MemRegisterDef<std::uint8_t, 0x102>;
using rrCBTR3 = MemRegisterDef<std::uint8_t, 0x103>;
using rrCCFLG = MemRegisterDef<std::uint8_t, 0x108>;
using rrCCISR = MemRegisterDef<std::uint8_t, 0x109>;
using rrCDIVCAN = MemRegisterDef<std::uint8_t, 0x100>;
using rrCEFR = MemRegisterDef<std::uint8_t, 0x10C>;
using rrCGPDDR = IoRegisterDef<std::uint8_t, 0x31>;
using rrCGPPIN = IoRegisterDef<std::uint8_t, 0x30>;
using rrCGPPORT = IoRegisterDef<std::uint8_t, 0x32>;
using rrCIDAC0R = MemRegisterDef<std::uint32_t, 0x110>;
using rrCIDAC1R = MemRegisterDef<std::uint32_t, 0x118>;
using rrCIDAC2R = MemRegisterDef<std::uint32_t, 0x120>;
using rrCIDAC3R = MemRegisterDef<std::uint32_t, 0x128>;
using rrCIDAC4R = MemRegisterDef<std::uint32_t, 0x130>;
using rrCIDAC5R = MemRegisterDef<std::uint32_t, 0x138>;
using rrCIDAC6R = MemRegisterDef<std::uint32_t, 0x140>;
using rrCIDAH0 = MemRegisterDef<std::uint8_t, 0x10A>;
using rrCIDAH1 = MemRegisterDef<std::uint8_t, 0x10B>;
using rrCIDM0R = MemRegisterDef<std::uint32_t, 0x114>;
using rrCIDM1R = MemRegisterDef<std::uint32_t, 0x11C>;
using rrCIDM2R = MemRegisterDef<std::uint32_t, 0x124>;
using rrCIDM3R = MemRegisterDef<std::uint32_t, 0x12C>;
using rrCIDM4R = MemRegisterDef<std::uint32_t, 0x134>;
using rrCIDM5R = MemRegisterDef<std::uint32_t, 0x13C>;
using rrCIDM6R = MemRegisterDef<std::uint32_t, 0x144>;
using rrCIER = MemRegisterDef<std::uint8_t, 0x107>;
using rrCMCR = MemRegisterDef<std::uint8_t, 0x104>;
using rrCOSDAC = MemRegisterDef<std::uint8_t, 0x282>;
using rrCOSDACH = MemRegisterDef<std::uint8_t, 0x283>;
using rrCOSDACL = MemRegisterDef<std::uint8_t, 0x282>;
using rrCRAFEN = MemRegisterDef<std::uint8_t, 0x105>;
using rrCRXERR = MemRegisterDef<std::uint8_t, 0x10D>;
using rrCTARR = MemRegisterDef<std::uint8_t, 0x106>;
using rrCTXERR = MemRegisterDef<std::uint8_t, 0x10E>;
using rrCURIRED = MemRegisterDef<std::uint8_t, 0x205>;
using rrCURIRUN = MemRegisterDef<std::uint8_t, 0x204>;
using rrCURRDLY = MemRegisterDef<std::uint16_t, 0x206>;
using rrCVER = MemRegisterDef<std::uint8_t, 0x10F>;
using rrDACCTRL = MemRegisterDef<std::uint8_t, 0x285>;
using rrDACVAL = IoRegisterDef<std::uint16_t, 0x18>;
using rrDACVALH = IoRegisterDef<std::uint8_t, 0x19>;
using rrDACVALHI = IoRegisterDef<std::uint8_t, 0x19>;
using rrDACVALL = IoRegisterDef<std::uint8_t, 0x18>;
using rrDACVALLO = IoRegisterDef<std::uint8_t, 0x18>;
constexpr unsigned ccDD0 = 0;
constexpr unsigned ccDD1 = 1;
constexpr unsigned ccDD2 = 2;
constexpr unsigned ccDD3 = 3;
constexpr unsigned ccDD4 = 4;
constexpr unsigned ccDD5 = 5;
constexpr unsigned ccDD6 = 6;
constexpr unsigned ccDD7 = 7;
constexpr unsigned ccE2END = 0x0;
constexpr unsigned ccE2PAGESIZE = 0;
using rrEXOCR1A = IoRegisterDef<std::uint16_t, 0x24>;
using rrEXOCR1AH = IoRegisterDef<std::uint8_t, 0x25>;
using rrEXOCR1AL = IoRegisterDef<std::uint8_t, 0x24>;
using rrEXOCR1B = IoRegisterDef<std::uint16_t, 0x26>;
using rrEXOCR1BH = IoRegisterDef<std::uint8_t, 0x27>;
using rrEXOCR1BL = IoRegisterDef<std::uint8_t, 0x26>;
using rrEXTCCR0 = IoRegisterDef<std::uint8_t, 0x2D>;
using rrEXTCCR1A = IoRegisterDef<std::uint8_t, 0x20>;
using rrEXTCCR1B = IoRegisterDef<std::uint8_t, 0x21>;
using rrEXTCNT = IoRegisterDef<std::uint8_t, 0x2C>;
using rrEXTCNT1 = IoRegisterDef<std::uint16_t, 0x22>;
using rrEXTCNT1H = IoRegisterDef<std::uint8_t, 0x23>;
using rrEXTCNT1L = IoRegisterDef<std::uint8_t, 0x22>;
using rrEXTIFR = IoRegisterDef<std::uint8_t, 0x2A>;
using rrEXTIMSK = IoRegisterDef<std::uint8_t, 0x2B>;
constexpr unsigned ccFLASHEND = 0xFFFF;
using rrGAINDAC = MemRegisterDef<std::uint8_t, 0x284>;
using rrGIFR = IoRegisterDef<std::uint8_t, 0x16>;
using rrGIMSK = IoRegisterDef<std::uint8_t, 0x17>;
using rrIDXCPTP = MemRegisterDef<std::uint32_t, 0x236>;
using rrIDXCTRL = MemRegisterDef<std::uint8_t, 0x234>;
using rrIDXENC = MemRegisterDef<std::uint32_t, 0x230>;
using rrIDXENT = MemRegisterDef<std::uint32_t, 0x222>;
using rrIDXIFLG = MemRegisterDef<std::uint8_t, 0x23A>;
using rrIDXIMSK = MemRegisterDef<std::uint8_t, 0x23B>;
using rrIDXMSDT = MemRegisterDef<std::uint16_t, 0x226>;
using rrIDXPOS = MemRegisterDef<std::uint32_t, 0x22C>;
using rrIDXPOT = MemRegisterDef<std::uint32_t, 0x228>;
using rrIDXSTRB = MemRegisterDef<std::uint8_t, 0x235>;
using rrIDXTRT = MemRegisterDef<std::uint32_t, 0x21E>;
using rrINOCR1A = MemRegisterDef<std::uint16_t, 0x804>;
using rrINOCR1AH = MemRegisterDef<std::uint8_t, 0x805>;
using rrINOCR1AL = MemRegisterDef<std::uint8_t, 0x804>;
using rrINOCR1B = MemRegisterDef<std::uint16_t, 0x806>;
using rrINOCR1BH = MemRegisterDef<std::uint8_t, 0x807>;
using rrINOCR1BL = MemRegisterDef<std::uint8_t, 0x806>;
using rrINTCCR0 = MemRegisterDef<std::uint8_t, 0x809>;
using rrINTCCR1A = MemRegisterDef<std::uint8_t, 0x800>;
using rrINTCCR1B = MemRegisterDef<std::uint8_t, 0x801>;
using rrINTCNT = MemRegisterDef<std::uint8_t, 0x808>;
using rrINTCNT1 = MemRegisterDef<std::uint16_t, 0x802>;
using rrINTCNT1H = MemRegisterDef<std::uint8_t, 0x803>;
using rrINTCNT1L = MemRegisterDef<std::uint8_t, 0x802>;
using rrINTIFR = MemRegisterDef<std::uint8_t, 0x80A>;
using rrINTIMSK = MemRegisterDef<std::uint8_t, 0x80B>;
using rrIOF = MemRegisterDef<std::uint8_t, 0x242>;
using rrIPA = IoRegisterDef<std::uint16_t, 0x02>;
using rrIPAH = IoRegisterDef<std::uint8_t, 0x03>;
using rrIPAL = IoRegisterDef<std::uint8_t, 0x02>;
using rrIPCR = IoRegisterDef<std::uint8_t, 0x04>;
using rrIPD = IoRegisterDef<std::uint16_t, 0x00>;
using rrIPDH = IoRegisterDef<std::uint8_t, 0x01>;
using rrIPDL = IoRegisterDef<std::uint8_t, 0x00>;
constexpr unsigned ccLOCKBITS_DEFAULT = 0xFF;
using rrMCSR = IoRegisterDef<std::uint8_t, 0x33>;
using rrMSELR = MemRegisterDef<std::uint8_t, 0x243>;
using rrMSPCR = IoRegisterDef<std::uint8_t, 0x0C>;
using rrMSPDR = IoRegisterDef<std::uint8_t, 0x0E>;
using rrMSPSR = IoRegisterDef<std::uint8_t, 0x0D>;
constexpr unsigned ccPIN0 = 0;
constexpr unsigned ccPIN1 = 1;
constexpr unsigned ccPIN2 = 2;
constexpr unsigned ccPIN3 = 3;
constexpr unsigned ccPIN4 = 4;
constexpr unsigned ccPIN5 = 5;
constexpr unsigned ccPIN6 = 6;
constexpr unsigned ccPIN7 = 7;
constexpr unsigned ccPORT0 = 0;
constexpr unsigned ccPORT1 = 1;
constexpr unsigned ccPORT2 = 2;
constexpr unsigned ccPORT3 = 3;
constexpr unsigned ccPORT4 = 4;
constexpr unsigned ccPORT5 = 5;
constexpr unsigned ccPORT6 = 6;
constexpr unsigned ccPORT7 = 7;
using rrPWMCTL = MemRegisterDef<std::uint8_t, 0x203>;
using rrPWMMSK = MemRegisterDef<std::uint8_t, 0x200>;
using rrPWMPER = MemRegisterDef<std::uint8_t, 0x201>;
using rrPWMSFRQ = MemRegisterDef<std::uint8_t, 0x202>;
constexpr unsigned ccRAMEND = 0x1FFF;
constexpr unsigned ccRAMSTART = 0x1000;
using rrSCIO = MemRegisterDef<std::uint8_t, 0x23C>;
using rrSCRF = MemRegisterDef<std::uint32_t, 0x23E>;
using rrSCSW = MemRegisterDef<std::uint8_t, 0x23D>;
using rrSINDAC = MemRegisterDef<std::uint16_t, 0x280>;
using rrSINDACH = MemRegisterDef<std::uint8_t, 0x281>;
using rrSINDACL = MemRegisterDef<std::uint8_t, 0x280>;
using rrSP = IoRegisterDef<std::uint8_t, 0x3D>;
using rrSPL = IoRegisterDef<std::uint8_t, 0x3D>;
using rrSPWMCTL = MemRegisterDef<std::uint8_t, 0x245>;
using rrSREG = IoRegisterDef<std::uint8_t, 0x3F>;
constexpr unsigned ccSREG_C = 0;
constexpr unsigned ccSREG_H = 5;
constexpr unsigned ccSREG_I = 7;
constexpr unsigned ccSREG_N = 2;
constexpr unsigned ccSREG_S = 4;
constexpr unsigned ccSREG_T = 6;
constexpr unsigned ccSREG_V = 3;
constexpr unsigned ccSREG_Z = 1;
using rrSTAT = MemRegisterDef<std::uint8_t, 0x244>;
using rrUBRR = IoRegisterDef<std::uint8_t, 0x14>;
using rrUBRRH = IoRegisterDef<std::uint8_t, 0x15>;
using rrUBRRHI = IoRegisterDef<std::uint8_t, 0x15>;
using rrUBRRL = IoRegisterDef<std::uint8_t, 0x14>;
using rrUBRRLO = IoRegisterDef<std::uint8_t, 0x14>;
using rrUCRA = IoRegisterDef<std::uint8_t, 0x12>;
using rrUCRB = IoRegisterDef<std::uint8_t, 0x13>;
using rrUSPCR = IoRegisterDef<std::uint8_t, 0x0C>;
using rrUSPDR = IoRegisterDef<std::uint8_t, 0x0E>;
using rrUSPSR = IoRegisterDef<std::uint8_t, 0x0D>;
using rrUSR = IoRegisterDef<std::uint8_t, 0x11>;
using rrVELACC1 = MemRegisterDef<std::uint8_t, 0x211>;
using rrVELACC2 = MemRegisterDef<std::uint8_t, 0x212>;
using rrVELACC3 = MemRegisterDef<std::uint8_t, 0x213>;
using rrVELCVEL = MemRegisterDef<std::uint8_t, 0x214>;
using rrVELDEC1 = MemRegisterDef<std::uint8_t, 0x20E>;
using rrVELDEC2 = MemRegisterDef<std::uint8_t, 0x20F>;
using rrVELDEC3 = MemRegisterDef<std::uint8_t, 0x210>;
using rrVELHI1 = MemRegisterDef<std::uint8_t, 0x20B>;
using rrVELHI2 = MemRegisterDef<std::uint8_t, 0x20C>;
using rrVELHI3 = MemRegisterDef<std::uint8_t, 0x20D>;
using rrVELIFLG = MemRegisterDef<std::uint8_t, 0x21C>;
using rrVELIMSK = MemRegisterDef<std::uint8_t, 0x21D>;
using rrVELLOW1 = MemRegisterDef<std::uint8_t, 0x208>;
using rrVELLOW2 = MemRegisterDef<std::uint8_t, 0x209>;
using rrVELLOW3 = MemRegisterDef<std::uint8_t, 0x20A>;
using rrVELSTB = MemRegisterDef<std::uint8_t, 0x21B>;
using rrVELTVEL = MemRegisterDef<std::uint8_t, 0x217>;
using rrVELVGCTL = MemRegisterDef<std::uint8_t, 0x21A>;
using rrWDTCR = IoRegisterDef<std::uint8_t, 0x0F>;
constexpr unsigned cc_SFR_ASM_COMPAT = 0;
constexpr unsigned cc_VECTORS_SIZE = 0;
constexpr unsigned cc__USING_MINT8 = 0;


}  // arch_m3000
}  // namespace avr
}  // namespace sys
}  // namespace ardo

#endif  // ardo_supplemental_m3000__h
