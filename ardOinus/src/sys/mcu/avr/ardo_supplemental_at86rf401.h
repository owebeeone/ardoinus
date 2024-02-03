// Generated for arch at86rf401.
// This file is generated from the avr-gcc compiler with the mcu
// set to at86rf401 from macros specific to avr/io.h.
// Any changes to this file will likely be lost next time this file
// is regenerated. Many any mcu_arch specific changes to 
// ardo_supplemental_at86rf401_defs.h.

#ifndef ardo_supplemental_at86rf401__h
#define ardo_supplemental_at86rf401__h

#include "setlx_cstdint.h"
#include "setl_bit_fields.h"
#include "ardo_avr_bit_io_defs.h"

namespace ardo {
namespace sys {
namespace avr {
namespace arch_at86rf401 {

constexpr ptrdiff_t cc__SFR_OFFSET = 0x20;

template <typename T, ptrdiff_t w_addr>
using IoRegisterDef = avr::nfp::IoRegisterDef<T, w_addr, cc__SFR_OFFSET>;
using avr::nfp::MemRegisterDef;

constexpr unsigned ccACS0 = 5;
constexpr unsigned ccACS1 = 6;
using rrAVR_CONFIG = IoRegisterDef<std::uint8_t, 0x33>;
constexpr unsigned ccBA0 = 0;
constexpr unsigned ccBA1 = 1;
constexpr unsigned ccBA2 = 2;
constexpr unsigned ccBBM = 0;
constexpr unsigned ccBD = 3;
constexpr unsigned ccBD0 = 0;
constexpr unsigned ccBD1 = 1;
constexpr unsigned ccBD2 = 2;
constexpr unsigned ccBD3 = 3;
constexpr unsigned ccBD4 = 4;
constexpr unsigned ccBD5 = 5;
constexpr unsigned ccBL = 7;
constexpr unsigned ccBL0 = 0;
constexpr unsigned ccBL1 = 1;
constexpr unsigned ccBL2 = 2;
constexpr unsigned ccBL3 = 3;
constexpr unsigned ccBL4 = 4;
constexpr unsigned ccBL5 = 5;
constexpr unsigned ccBLI = 2;
constexpr unsigned ccBLV = 6;
using rrBL_CONFIG = IoRegisterDef<std::uint8_t, 0x35>;
constexpr unsigned ccBOD = 2;
constexpr unsigned ccBOHYST = 6;
constexpr unsigned ccBSY = 3;
using rrBTCNT = IoRegisterDef<std::uint8_t, 0x20>;
using rrBTCR = IoRegisterDef<std::uint8_t, 0x21>;
using rrB_DET = IoRegisterDef<std::uint8_t, 0x34>;
constexpr unsigned ccC0 = 0;
constexpr unsigned ccC1 = 1;
constexpr unsigned ccC2 = 2;
constexpr unsigned ccC3 = 3;
constexpr unsigned ccC4 = 4;
constexpr unsigned ccC5 = 5;
constexpr unsigned ccC6 = 6;
constexpr unsigned ccC7 = 7;
constexpr unsigned ccC8 = 6;
constexpr unsigned ccC9 = 7;
constexpr unsigned ccCS0 = 0;
constexpr unsigned ccCS1 = 1;
constexpr unsigned ccDATA = 1;
constexpr unsigned ccDD0 = 0;
constexpr unsigned ccDD1 = 1;
constexpr unsigned ccDD2 = 2;
constexpr unsigned ccDD3 = 3;
constexpr unsigned ccDD4 = 4;
constexpr unsigned ccDD5 = 5;
constexpr unsigned ccDD6 = 6;
constexpr unsigned ccDD7 = 7;
using rrDEEAR = IoRegisterDef<std::uint8_t, 0x1E>;
using rrDEEARL = IoRegisterDef<std::uint8_t, 0x1E>;
using rrDEECR = IoRegisterDef<std::uint8_t, 0x1C>;
using rrDEEDR = IoRegisterDef<std::uint8_t, 0x1D>;
constexpr unsigned ccE2END = 0x7F;
constexpr unsigned ccE2PAGESIZE = 0;
constexpr unsigned ccED0 = 0;
constexpr unsigned ccED1 = 1;
constexpr unsigned ccED2 = 2;
constexpr unsigned ccED3 = 3;
constexpr unsigned ccED4 = 4;
constexpr unsigned ccED5 = 5;
constexpr unsigned ccED6 = 6;
constexpr unsigned ccED7 = 7;
constexpr unsigned ccEEL = 1;
constexpr unsigned ccEER = 0;
constexpr unsigned ccEEU = 2;
constexpr unsigned ccENKO = 3;
constexpr unsigned ccEUD = 7;
constexpr unsigned ccF0 = 0;
constexpr unsigned ccF2 = 2;
constexpr unsigned ccFLASHEND = 0x07FF;
constexpr unsigned ccFUSE_MEMORY_SIZE = 0;
constexpr unsigned ccIE = 3;
constexpr unsigned ccIOE0 = 0;
constexpr unsigned ccIOE1 = 1;
constexpr unsigned ccIOE2 = 2;
constexpr unsigned ccIOE3 = 3;
constexpr unsigned ccIOE4 = 4;
constexpr unsigned ccIOE5 = 5;
constexpr unsigned ccIOI0 = 0;
constexpr unsigned ccIOI1 = 1;
constexpr unsigned ccIOI2 = 2;
constexpr unsigned ccIOI3 = 3;
constexpr unsigned ccIOI4 = 4;
constexpr unsigned ccIOI5 = 5;
constexpr unsigned ccIOO0 = 0;
constexpr unsigned ccIOO1 = 1;
constexpr unsigned ccIOO2 = 2;
constexpr unsigned ccIOO3 = 3;
constexpr unsigned ccIOO4 = 4;
constexpr unsigned ccIOO5 = 5;
using rrIO_DATIN = IoRegisterDef<std::uint8_t, 0x32>;
using rrIO_DATOUT = IoRegisterDef<std::uint8_t, 0x31>;
using rrIO_ENAB = IoRegisterDef<std::uint8_t, 0x30>;
constexpr unsigned ccLAT = 6;
constexpr unsigned ccLB_MODE_1 = 0xFF;
constexpr unsigned ccLB_MODE_2 = 0xFE;
constexpr unsigned ccLB_MODE_3 = 0xFC;
constexpr unsigned ccLC0 = 0;
constexpr unsigned ccLC1 = 1;
constexpr unsigned ccLC2 = 2;
constexpr unsigned ccLOC = 2;
constexpr unsigned ccLOCKBITS_DEFAULT = 0xFF;
using rrLOCKDET1 = IoRegisterDef<std::uint8_t, 0x10>;
using rrLOCKDET2 = IoRegisterDef<std::uint8_t, 0x17>;
constexpr unsigned ccM0 = 4;
constexpr unsigned ccM1 = 5;
constexpr unsigned ccPA3 = 3;
constexpr unsigned ccPA4 = 4;
constexpr unsigned ccPA5 = 5;
constexpr unsigned ccPA6 = 6;
constexpr unsigned ccPCC0 = 3;
constexpr unsigned ccPCC1 = 4;
constexpr unsigned ccPCC2 = 5;
constexpr unsigned ccPCF0 = 0;
constexpr unsigned ccPCF1 = 1;
constexpr unsigned ccPCF2 = 2;
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
using rrPWR_ATTEN = IoRegisterDef<std::uint8_t, 0x14>;
constexpr unsigned ccRAMEND = 0xDF;
constexpr unsigned ccRAMSTART = 0x60;
constexpr unsigned ccSIGNATURE_0 = 0x1E;
constexpr unsigned ccSIGNATURE_1 = 0x91;
constexpr unsigned ccSIGNATURE_2 = 0x81;
constexpr unsigned ccSLEEP = 1;
using rrSP = IoRegisterDef<std::uint16_t, 0x3D>;
using rrSPH = IoRegisterDef<std::uint8_t, 0x3E>;
using rrSPL = IoRegisterDef<std::uint8_t, 0x3D>;
using rrSREG = IoRegisterDef<std::uint8_t, 0x3F>;
constexpr unsigned ccSREG_C = 0;
constexpr unsigned ccSREG_H = 5;
constexpr unsigned ccSREG_I = 7;
constexpr unsigned ccSREG_N = 2;
constexpr unsigned ccSREG_S = 4;
constexpr unsigned ccSREG_T = 6;
constexpr unsigned ccSREG_V = 3;
constexpr unsigned ccSREG_Z = 1;
constexpr unsigned ccTM = 4;
constexpr unsigned ccTXDONE_vect_num = 1;
constexpr unsigned ccTXE = 5;
constexpr unsigned ccTXEMPTY_vect_num = 2;
constexpr unsigned ccTXK = 4;
using rrTX_CNTL = IoRegisterDef<std::uint8_t, 0x12>;
constexpr unsigned ccULC0 = 3;
constexpr unsigned ccULC1 = 4;
constexpr unsigned ccULC2 = 5;
constexpr unsigned ccUPOK = 4;
using rrVCOTUNE = IoRegisterDef<std::uint8_t, 0x16>;
constexpr unsigned ccVCOTUNE0 = 0;
constexpr unsigned ccVCOTUNE1 = 1;
constexpr unsigned ccVCOTUNE2 = 2;
constexpr unsigned ccVCOTUNE3 = 3;
constexpr unsigned ccVCOTUNE4 = 4;
constexpr unsigned ccVCOVDET0 = 6;
constexpr unsigned ccVCOVDET1 = 7;
constexpr unsigned ccWDE = 3;
constexpr unsigned ccWDP0 = 0;
constexpr unsigned ccWDP1 = 1;
constexpr unsigned ccWDP2 = 2;
using rrWDTCR = IoRegisterDef<std::uint8_t, 0x22>;
constexpr unsigned ccWDTOE = 4;
constexpr unsigned cc_HAVE_AVR_STACK_POINTER_HI = 1;
constexpr unsigned cc_SFR_ASM_COMPAT = 0;
constexpr unsigned cc_VECTORS_SIZE = 12;
constexpr unsigned cc__USING_MINT8 = 0;


}  // arch_at86rf401
}  // namespace avr
}  // namespace sys
}  // namespace ardo

#endif  // ardo_supplemental_at86rf401__h
