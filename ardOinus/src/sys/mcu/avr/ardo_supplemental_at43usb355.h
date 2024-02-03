// Generated for arch at43usb355.
// This file is generated from the avr-gcc compiler with the mcu
// set to at43usb355 from macros specific to avr/io.h.
// Any changes to this file will likely be lost next time this file
// is regenerated. Many any mcu_arch specific changes to 
// ardo_supplemental_at43usb355_defs.h.

#ifndef ardo_supplemental_at43usb355__h
#define ardo_supplemental_at43usb355__h

#include "setlx_cstdint.h"
#include "setl_bit_fields.h"
#include "ardo_avr_bit_io_defs.h"

namespace ardo {
namespace sys {
namespace avr {
namespace arch_at43usb355 {

constexpr ptrdiff_t cc__SFR_OFFSET = 0x20;

template <typename T, ptrdiff_t w_addr>
using IoRegisterDef = avr::nfp::IoRegisterDef<T, w_addr, cc__SFR_OFFSET>;
using avr::nfp::MemRegisterDef;

using rrACSR = IoRegisterDef<std::uint8_t, 0x08>;
using rrADC = IoRegisterDef<std::uint16_t, 0x02>;
using rrADCH = IoRegisterDef<std::uint8_t, 0x03>;
using rrADCL = IoRegisterDef<std::uint8_t, 0x02>;
using rrADCSR = IoRegisterDef<std::uint8_t, 0x07>;
using rrADCW = IoRegisterDef<std::uint16_t, 0x02>;
constexpr unsigned ccADEN = 7;
constexpr unsigned ccADFR = 5;
constexpr unsigned ccADIE = 3;
constexpr unsigned ccADIF = 4;
using rrADMUX = IoRegisterDef<std::uint8_t, 0x08>;
constexpr unsigned ccADPS0 = 0;
constexpr unsigned ccADPS1 = 1;
constexpr unsigned ccADPS2 = 2;
constexpr unsigned ccADSC = 6;
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
constexpr unsigned ccCTC1 = 3;
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
constexpr unsigned ccDDF1 = 1;
constexpr unsigned ccDDF2 = 2;
constexpr unsigned ccDDF3 = 3;
using rrDDRA = IoRegisterDef<std::uint8_t, 0x1A>;
using rrDDRB = IoRegisterDef<std::uint8_t, 0x17>;
using rrDDRC = IoRegisterDef<std::uint8_t, 0x14>;
using rrDDRD = IoRegisterDef<std::uint8_t, 0x11>;
using rrDDRE = IoRegisterDef<std::uint8_t, 0x02>;
using rrDDRF = IoRegisterDef<std::uint8_t, 0x05>;
constexpr unsigned ccDORD = 5;
constexpr unsigned ccE2END = 0x0000;
constexpr unsigned ccFLASHEND = 0x5FFF;
using rrGIFR = IoRegisterDef<std::uint8_t, 0x3A>;
using rrGIMSK = IoRegisterDef<std::uint8_t, 0x3B>;
constexpr unsigned ccICES1 = 6;
constexpr unsigned ccICF1 = 3;
constexpr unsigned ccICNC1 = 7;
using rrICR1 = IoRegisterDef<std::uint16_t, 0x24>;
using rrICR1H = IoRegisterDef<std::uint8_t, 0x25>;
using rrICR1L = IoRegisterDef<std::uint8_t, 0x24>;
constexpr unsigned ccISC00 = 0;
constexpr unsigned ccISC01 = 1;
constexpr unsigned ccISC10 = 2;
constexpr unsigned ccISC11 = 3;
constexpr unsigned ccLOCKBITS_DEFAULT = 0xFF;
using rrMCUCR = IoRegisterDef<std::uint8_t, 0x35>;
constexpr unsigned ccMSTR = 4;
constexpr unsigned ccMUX0 = 0;
constexpr unsigned ccMUX1 = 1;
constexpr unsigned ccMUX2 = 2;
constexpr unsigned ccOCF1A = 6;
constexpr unsigned ccOCF1B = 5;
constexpr unsigned ccOCIE1A = 6;
constexpr unsigned ccOCIE1B = 5;
using rrOCR1A = IoRegisterDef<std::uint16_t, 0x2A>;
using rrOCR1AH = IoRegisterDef<std::uint8_t, 0x2B>;
using rrOCR1AL = IoRegisterDef<std::uint8_t, 0x2A>;
using rrOCR1B = IoRegisterDef<std::uint16_t, 0x28>;
using rrOCR1BH = IoRegisterDef<std::uint8_t, 0x29>;
using rrOCR1BL = IoRegisterDef<std::uint8_t, 0x28>;
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
constexpr unsigned ccPD0 = 0;
constexpr unsigned ccPD1 = 1;
constexpr unsigned ccPD2 = 2;
constexpr unsigned ccPD3 = 3;
constexpr unsigned ccPD4 = 4;
constexpr unsigned ccPD5 = 5;
constexpr unsigned ccPD6 = 6;
constexpr unsigned ccPD7 = 7;
constexpr unsigned ccPF0 = 0;
constexpr unsigned ccPF1 = 1;
constexpr unsigned ccPF2 = 2;
constexpr unsigned ccPF3 = 3;
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
using rrPINE = IoRegisterDef<std::uint8_t, 0x01>;
using rrPINF = IoRegisterDef<std::uint8_t, 0x04>;
constexpr unsigned ccPINF0 = 0;
constexpr unsigned ccPINF1 = 1;
constexpr unsigned ccPINF2 = 2;
constexpr unsigned ccPINF3 = 3;
constexpr unsigned ccPORT0 = 0;
constexpr unsigned ccPORT1 = 1;
constexpr unsigned ccPORT2 = 2;
constexpr unsigned ccPORT3 = 3;
constexpr unsigned ccPORT4 = 4;
constexpr unsigned ccPORT5 = 5;
constexpr unsigned ccPORT6 = 6;
constexpr unsigned ccPORT7 = 7;
using rrPORTA = IoRegisterDef<std::uint8_t, 0x1B>;
using rrPORTB = IoRegisterDef<std::uint8_t, 0x18>;
using rrPORTC = IoRegisterDef<std::uint8_t, 0x15>;
using rrPORTD = IoRegisterDef<std::uint8_t, 0x12>;
using rrPORTE = IoRegisterDef<std::uint8_t, 0x03>;
using rrPORTF = IoRegisterDef<std::uint8_t, 0x06>;
constexpr unsigned ccPWM10 = 0;
constexpr unsigned ccPWM11 = 1;
constexpr unsigned ccRAMEND = 0x045F;
constexpr unsigned ccRAMSTART = 0x60;
constexpr unsigned ccSE = 5;
constexpr unsigned ccSLEEP_MODE_IDLE = 0;
constexpr unsigned ccSM = 4;
using rrSP = IoRegisterDef<std::uint16_t, 0x3D>;
using rrSPCR = IoRegisterDef<std::uint8_t, 0x0D>;
using rrSPDR = IoRegisterDef<std::uint8_t, 0x0F>;
constexpr unsigned ccSPE = 6;
using rrSPH = IoRegisterDef<std::uint8_t, 0x3E>;
constexpr unsigned ccSPIE = 7;
constexpr unsigned ccSPIF = 7;
using rrSPL = IoRegisterDef<std::uint8_t, 0x3D>;
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
using rrTCCR0 = IoRegisterDef<std::uint8_t, 0x33>;
using rrTCCR1A = IoRegisterDef<std::uint8_t, 0x2F>;
using rrTCCR1B = IoRegisterDef<std::uint8_t, 0x2E>;
using rrTCNT0 = IoRegisterDef<std::uint8_t, 0x32>;
using rrTCNT1 = IoRegisterDef<std::uint16_t, 0x2C>;
using rrTCNT1H = IoRegisterDef<std::uint8_t, 0x2D>;
using rrTCNT1L = IoRegisterDef<std::uint8_t, 0x2C>;
constexpr unsigned ccTICIE1 = 3;
using rrTIFR = IoRegisterDef<std::uint8_t, 0x38>;
using rrTIMSK = IoRegisterDef<std::uint8_t, 0x39>;
constexpr unsigned ccTOIE0 = 1;
constexpr unsigned ccTOIE1 = 7;
constexpr unsigned ccTOV0 = 1;
constexpr unsigned ccTOV1 = 7;
constexpr unsigned ccWCOL = 6;
constexpr unsigned ccWDE = 3;
constexpr unsigned ccWDP0 = 0;
constexpr unsigned ccWDP1 = 1;
constexpr unsigned ccWDP2 = 2;
using rrWDTCR = IoRegisterDef<std::uint8_t, 0x21>;
constexpr unsigned ccWDTOE = 4;
constexpr unsigned cc_HAVE_AVR_STACK_POINTER_HI = 1;
constexpr unsigned cc_SFR_ASM_COMPAT = 0;
constexpr unsigned cc_VECTORS_SIZE = 52;
constexpr unsigned cc__USING_MINT8 = 0;


}  // arch_at43usb355
}  // namespace avr
}  // namespace sys
}  // namespace ardo

#endif  // ardo_supplemental_at43usb355__h
