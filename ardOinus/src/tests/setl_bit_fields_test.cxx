
#include "setl_bit_fields.h"

namespace TestBitFields {

  
static_assert(setl::Max<5, 6, 7>::value == 7, "Max should be 7.");

using TestABS = setl::AddBitShifts<unsigned, 1, 2, setl::MaskShift<unsigned, 2, 2>>;
using TestMS = TestABS::mask_shifts;
using TestABS1 = setl::AddBitShifts<unsigned, 4, 1, setl::MaskShift<unsigned, 1, 3>>;
using TestMS1 = TestABS1::mask_shifts;

static_assert(TestMS1::count == 2, "Should have two mask shifts.");


static_assert(setl::RIndexOf<1, 5, 6, 7>::value == setl::NA, "1 is not in 5, 6, 7.");
static_assert(setl::RIndexOf<5, 5, 6, 7>::value == 2, "2 is the reverse index of 5 in 5, 6, 7.");
static_assert(setl::RIndexOf<7, 5, 6, 7>::value == 0, "0 is the reverse index of 7 in 5, 6, 7.");


using TestInverseMap = setl::InverseMap<5, 4, 3, 2, 1>::inverse_map;
static_assert(std::is_same<TestInverseMap, setl::UintList<4, 3, 2, 1, 0, setl::NA>>::value, "Invalid inverse");


using TestGMS = setl::GroupMaskShifts<unsigned short, 5, 4, 3>::group;
using TestGMSBits = setl::GroupMaskShifts<unsigned short, 5, 4, 3>::group_bits;
using TestGMSIBits = setl::GroupMaskShifts<unsigned short, 5, 4, 3>::inverse_bits;
using TestGMSIGroup = setl::GroupMaskShifts<unsigned short, 5, 4, 3>::inverse_group;
using TestGMSIIGBits = setl::GroupMaskShifts<unsigned short, 5, 4, 3>::inverse;
using TestGMSIIGBitsG = setl::GroupMaskShifts<unsigned short, 5, 4, 3>::inverse_group;

using TestGMSIIBits = setl::GroupMaskShifts<unsigned short, 5, 4, 3>::inverse::inverse_bits;
using TestGMSIII = setl::GroupMaskShifts<unsigned short, 5, 4, 3>::inverse::inverse_group;
using TestGMS2 = setl::GroupMaskShifts<unsigned short, 7, 6, setl::NA, 1, 0>::group_bits;
using TestGMS2I = setl::GroupMaskShifts<unsigned short, 7, 6, setl::NA, 1, 0>::inverse_group;
using TestGMS2IBits = setl::GroupMaskShifts<unsigned short, 7, 6, setl::NA, 1, 0>::inverse_bits;

using TestNaGMS = setl::GroupMaskShifts<unsigned short, setl::NA, 5, 4, 3>::group;
using TestNaGMSBits = setl::GroupMaskShifts<unsigned short, setl::NA, 5, 4, 3>::group_bits;
using TestNaGMSIBits = setl::GroupMaskShifts<unsigned short, setl::NA, 5, 4, 3>::inverse_bits;
using TestNaGMSIGroup = setl::GroupMaskShifts<unsigned short, setl::NA, 5, 4, 3>::inverse_group;


using TestGMS210nanana = setl::GroupMaskShifts<unsigned short, 2, 1, 0, setl::NA, setl::NA>::group;

using TestApplyMaskShift = setl::ApplyMaskShift<setl::MaskShift<unsigned, 0x1u, 4>, setl::MaskShift<unsigned, 0x30u, -4>>;
static_assert(TestApplyMaskShift::in_mask == 0x31, "Computed mask is incorrect");
static_assert(TestApplyMaskShift::out_mask == 0x13, "Computed mask is incorrect");
static_assert(TestApplyMaskShift::convert(0x21) == 0x12, "Computed converted value is incorrect");


using TAMSTestGMS = setl::GroupMaskShifts<unsigned short, 5, 4, 3>::group::apply<setl::ApplyMaskShift>;
using TAMSTestGMSG = setl::GroupMaskShifts<unsigned short, 5, 4, 3>::group;
static_assert(TAMSTestGMS::in_mask == 0x38u, "Computed mask is incorrect");
static_assert(TAMSTestGMS::out_mask == 0x7u, "Computed mask is incorrect");
constexpr unsigned short TAMSTestGMSGv = TAMSTestGMS::convert(0x21);
static_assert(TAMSTestGMS::convert(0x21) == 0x4, "Computed converted value is incorrect");

using TAMSTestAGMSI = setl::GroupMaskShifts<unsigned short, 5, 4, 3>::inverse_group::apply<setl::ApplyMaskShift>;
constexpr unsigned short TAMSTestAGMSImv = TAMSTestAGMSI::out_mask;
static_assert(TAMSTestAGMSI::in_mask == 0x7u, "Computed mask is incorrect");
static_assert(TAMSTestAGMSI::out_mask == 0x38u, "Computed mask is incorrect");
static_assert(TAMSTestAGMSI::convert(0x1) == 0x8, "Computed converted value is incorrect");
static_assert(TAMSTestAGMSI::convert(0x2) == 0x10, "Computed converted value is incorrect");
static_assert(TAMSTestAGMSI::convert(0x4) == 0x20, "Computed converted value is incorrect");
static_assert(TAMSTestAGMSI::convert(0x8) == 0x0, "Computed converted value is incorrect");

}  // namespace TestBitFields