
#include "setl_bit_fields.h"
#include "ardOinus.h"

#include "setl_test_framework.h"
#include <bitset>

namespace TestBitFields {

using TestUnsignedType = setl::UnsignedType<char, short, signed char, unsigned char, char>::type;

constexpr bool TestHasType = setl::has_type<int, std::tuple<bool, char>>::value;
constexpr bool TestHasTypeT = setl::has_type<int, std::tuple<bool, char, int>>::value;

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


using TestTypesOfBits1 = setl::TypesOfBits<setl::BitsRW<signed char, 1>, setl::BitsRW<bool, 2>>::type;
using TestTypesOfBits1T = setl::UnsignedType<TestTypesOfBits1>::type;



constexpr unsigned debug_mode = 1;

template <unsigned mode>
struct RegisterSelector;

template <>
struct RegisterSelector<0> {
  template <typename T, ptrdiff_t w_addrx>
  using IoAccessor = setl::McuRegister<T, w_addrx>;
};

constexpr unsigned mcu_io_memory_size = 4096;
unsigned char mcu_io_memory[mcu_io_memory_size];
unsigned char* const mcu_io_memory_ptr{ mcu_io_memory };

template <>
struct RegisterSelector<1> {
  template <typename T, ptrdiff_t w_addrx>
  using IoAccessor = setl::DebugMcuRegister<T, w_addrx, mcu_io_memory_size, mcu_io_memory_ptr>;
};

template <typename w_BitfieldType,
  typename w_Register,
  template <typename T, ptrdiff_t u_addrx> typename RegisterType = RegisterSelector<debug_mode>::IoAccessor>
using Register = setl::IoRegister<w_BitfieldType, w_Register, RegisterType>;

#define ADDR_MMIO_BYTE(mem_addr) ((ptrdiff_t) (mem_addr))
#define ADDR_MMIO_WORD(mem_addr) ((ptrdiff_t) (mem_addr))
#define ADDR_MMIO_DWORD(mem_addr) ((ptrdiff_t) (mem_addr))
#define ADDR_SFR_MEM8(mem_addr) ADDR_MMIO_BYTE(mem_addr)
#define ADDR_SFR_MEM16(mem_addr) ADDR_MMIO_WORD(mem_addr)
#define ADDR_SFR_MEM32(mem_addr) ADDR_MMIO_DWORD(mem_addr)
#define ADDR_SFR_IO8(io_addr) ADDR_MMIO_BYTE((io_addr) + __SFR_OFFSET)
#define ADDR_SFR_IO16(io_addr) ADDR_MMIO_WORD((io_addr) + __SFR_OFFSET)

#define SIZE_SFR_MEM8(mem_addr) (1)
#define SIZE_SFR_MEM16(mem_addr) (2)
#define SIZE_SFR_MEM32(mem_addr) (4)
#define SIZE_SFR_IO8(io_addr) (1)
#define SIZE_SFR_IO16(io_addr) (2)

using ardo::sys::avr::mcu::EnumCOMn;

inline constexpr const char* EnumToStr(EnumCOMn value) {
  switch (value) {
  case EnumCOMn::disconnect: return "disconnect";
  case EnumCOMn::toggle: return "toggle";
  case EnumCOMn::clear: return "clear";
  case EnumCOMn::set: return "set";
  default: return "";
  }
}

//template <typename E,
//  template <typename T, unsigned...ubits> typename B,
//  unsigned...bits>
//  inline std::ostream& operator<<(std::ostream& ostr, const B<E, bits...>& value) {
//  return ostr << value.value;
//}

using namespace ardo::sys::avr::mcu;

enum class TypeWGM1 : unsigned char {
  normal = 0b0000,
  pwm_phase_correct_8bit = 0b0001,
  pwm_phase_correct_9bit = 0b0010,
  pwm_phase_correct_10bit = 0b0011,
  ctc_ocr1a = 0b0100,
  fast_pwm_8bit = 0b0101,
  fast_pwm_9bit = 0b0110,
  fast_pwm_10bit = 0b0111,
  pwm_phase_freq_correct_icr1 = 0b1000,
  pwm_phase_freq_correct_ocr1a = 0b1001,
  pwm_phase_correct_icr1 = 0b1010,
  pwm_phase_correct_ocr1a = 0b1011,
  ctc_icr1 = 0b1100,
  reserved_d = 0b1101,
  fast_pwm_icr1 = 0b1110,
  fast_pwm_ocr1a = 0b1111,
};




using setl::NA;

using BitsWGM1_10 = setl::BitsRW<TypeWGM1, NA, NA, ccWGM11, ccWGM10>;
using BitsWGM1_32 = setl::BitsRW<TypeWGM1, ccWGM13, ccWGM12, NA, NA>;

template <typename T, ptrdiff_t w_addr>
struct MemRegisterDef {
  static constexpr ptrdiff_t addr = w_addr;
  using type = T;
};

template <typename T, ptrdiff_t w_addr>
struct IoRegisterDef {
  static constexpr ptrdiff_t uu__SFR_OFFSET = 0x20;
  static constexpr ptrdiff_t addr = w_addr + uu__SFR_OFFSET;
  using type = T;
};

using rrTCCR1A = MemRegisterDef<std::uint8_t, 0x80>;  // See TCCR1A

using FieldsTCCR1A = setl::BitFields<BitsCOM1A, BitsCOM1B, BitsWGM1_10>;
using RegisterTCCR1A = Register<FieldsTCCR1A, rrTCCR1A>;

using TestBW = setl::BitTypesTraits<RegisterTCCR1A::FormatType, BitsCOM1A, BitsWGM1_10>;
using TestBitTypesTraits = TestBW::traits;
constexpr bool TestBitTypesTraits_all_contained = TestBitTypesTraits::all_contained;
constexpr unsigned TestBitTypesTraits_in_mask = TestBitTypesTraits::in_mask;
constexpr unsigned TestBitTypesTraits_collision_mask = TestBitTypesTraits::collision_mask;

constexpr bool TestContains1 = RegisterTCCR1A::FormatType::contains<BitsCOM1A>;
constexpr bool TestContains2 = RegisterTCCR1A::FormatType::contains<BitsWGM1_32>;

enum class TypeCS1 : unsigned char {
  no_clk = 0b000,
  clk1 = 0b001,
  clk8 = 0b010,
  clk64 = 0b011,
  clk256 = 0b100,
  clk1024 = 0b101,
  ext_clk_falling = 0b110,
  ext_clk_rising = 0b111,
};

using BitsICNC1 = setl::BitsRW<bool, ccICNC1>;
using BitsICES1 = setl::BitsRW<bool, ccICES1>;

using BitsCS11 = setl::BitsRW<TypeCS1, ccCS12, ccCS11, ccCS10>;

using FieldsTCCR1B = setl::BitFields<BitsWGM1_32, BitsCS11, BitsICES1, BitsICNC1>;

using rrTCCR1B = MemRegisterDef<std::uint8_t, 0x81>;
using RegisterTCCR1B = Register<FieldsTCCR1B, rrTCCR1B>;

}  // namespace TestBitFields

#include <iostream>

template <typename E,
  template <typename T, unsigned...ubits> typename B,
  E enable = static_cast<E>(sizeof(EnumToStr(static_cast<E>(0)))),
  unsigned...bits>
inline std::ostream& operator<<(std::ostream& ostr, const B<E, bits...>& value) {
  return ostr << TestBitFields::EnumToStr(value.value);
}

inline std::ostream& operator<<(std::ostream& ostr, TestBitFields::TypeWGM1 value) {
  return ostr << "TypeWGM1(" << static_cast<unsigned>(value) << ")";
}

template <typename T, unsigned...bits>
inline std::ostream& operator<<(std::ostream& ostr, const setl::BitsRW<T, bits...>& value) {
  return ostr << typeid(value).name() << "(" << static_cast<unsigned>(value.value) << ")";
}


namespace TestBitFields {
  

using bbTest2 = setl::BitsRW<bool, 2>;
using bbTest1 = setl::BitsRW<bool, 1>;
using FieffTestldsTCCR1B = setl::BitFields<bbTest1, bbTest2>;
using rrTestA = MemRegisterDef<std::uint8_t, 0x89>;  // a test

using RegSelectorTCCR1 = setl::RegisterSelector<std::tuple<RegisterTCCR1B, RegisterTCCR1A>>;


inline void testRegSelector() {
  RegSelectorTCCR1::ReadModifyWrite(BitsCOM1A{EnumCOMn::disconnect}, BitsICNC1{false});
  BitsCOM1A a0 = RegisterTCCR1A::Read();
  BitsICNC1 b0 = RegisterTCCR1B::Read();
  RegSelectorTCCR1::ReadModifyWrite(BitsCOM1A{EnumCOMn::set}, BitsICNC1{true});
  BitsCOM1A a;
  BitsICNC1 b;
  RegSelectorTCCR1::Read(a, b);
  BitsCOM1A a1 = RegisterTCCR1A::Read();
  BitsICNC1 b1 = RegisterTCCR1B::Read();

  std::cout << "a0: " << int(a0.value) << ", b0: " << b0.value << "\n";
  std::cout << "a: " << int(a.value) << ", b: " << b.value << "\n";
  std::cout << "a1: " << int(a1.value) << ", b1: " << b1.value << "\n";
}

inline void testRegSelector2() {
  using foo = typename setl::nfp::ToBitFields<
    setl::ApplierValue<BitsCOM1A, EnumCOMn::disconnect>,
    setl::ApplierValue<BitsICNC1, false>>::type;

  using AVE = setl::ApplierValues<>;
  AVE::apply<RegSelectorTCCR1>();

  using AVNE = setl::ApplierValues<
      setl::ApplierValue<BitsCOM1A, EnumCOMn::disconnect>,
      setl::ApplierValue<BitsCOM1B, EnumCOMn::disconnect>,
      setl::ApplierValue<BitsICNC1, false>>;

  AVNE::apply<RegSelectorTCCR1>();
  BitsCOM1A a0;
  BitsCOM1B b0;
  BitsICNC1 c0;
  RegSelectorTCCR1::Read(a0, b0, c0);

  using AVNE2 = setl::ApplierValues<
    setl::ApplierValue<BitsCOM1A, EnumCOMn::set>,
    setl::ApplierValue<BitsCOM1B, EnumCOMn::toggle>,
    setl::ApplierValue<BitsICNC1, true>>;
  AVNE2::apply<RegSelectorTCCR1>();

  BitsCOM1A a;
  BitsCOM1B b;
  BitsICNC1 c;
  RegSelectorTCCR1::Read(a, b, c);

  std::cout << "a0: " << int(a0.value) << ", b0: " << int(b0.value) << ", c0: " << (c0.value) << "\n";
  std::cout << "a: " << int(a.value) << ", b: " << int(b.value) << " , c: " << (c.value) << "\n";
}

TypeWGM1 getTypeWGM1() {
  BitsCOM1A com1a;
  BitsCOM1B com1b;

  BitsWGM1_10 wgm1_10;
  BitsWGM1_32 wgm1_32;
  std::cout << "N test1\n";
  Assign(wgm1_10, com1a, com1b) = RegisterTCCR1A::Read();
  std::cout << "com1a: " << com1a << ", com1b: " << com1b << ", wgm1_10: " << wgm1_10 << "\n";
  RegisterTCCR1A::ioregister::set(0xff);
  Assign(wgm1_10, com1a, com1b) = RegisterTCCR1A::Read();
  std::cout << "com1a: " << com1a << ", com1b: " << com1b << ", wgm1_10: " << wgm1_10 << "\n";

  std::cout << "N test2a\n";
  Assign(com1a, com1b) = RegisterTCCR1A::Read(0xff);
  std::cout << "test2b\n";
  std::cout << "com1a: " << com1a << "\n";
  com1a = RegisterTCCR1A::Read(0x7f);
  std::cout << "com1a: " << com1a << "\n";

  return {};
}

using BTEvaltr = setl::BitTypesEvaluator<false, RegisterTCCR1A::FormatType, BitsCOM1A, BitsCOM1B>;
using BTEvaltrTraits = BTEvaltr::traits;
constexpr unsigned collision = BTEvaltr::traits::collision_mask;

TypeWGM1 rwTypeWGM1() {
  auto registerValue = RegisterTCCR1A::Read(0xff);
  BitsCOM1A com1a;
  BitsCOM1B com1b;
  BitsWGM1_10 wgm1_10;

  std::cout << "N test3\n";
  setl::Assign(com1a, com1b) = registerValue;
  com1a = registerValue;

  std::cout << "N test4\n";
  std::cout << "com1a: " << com1a << ", com1b: " << com1b << ", wgm1_10: " << wgm1_10 << "\n";
  RegisterTCCR1A::Write(registerValue, com1a, BitsCOM1B( EnumCOMn::clear ));
  std::cout << "com1a: " << com1a << ", com1b: " << com1b << ", wgm1_10: " << wgm1_10 << "\n";

  setl::Assign(wgm1_10, com1a, com1b) = RegisterTCCR1A::Read();
  std::cout << "com1a: " << com1a << ", com1b: " << com1b << ", wgm1_10: " << wgm1_10 << "\n";
  RegisterTCCR1A::ReadModifyWrite(
    BitsCOM1A{ EnumCOMn::toggle },
    BitsCOM1B{ EnumCOMn::disconnect },
    BitsWGM1_10{ TypeWGM1::pwm_phase_correct_9bit });
  std::cout << "com1a: " << com1a << ", com1b: " << com1b << ", wgm1_10: " << wgm1_10 << "\n";
  setl::Assign(wgm1_10, com1a, com1b) = RegisterTCCR1A::Read();
  std::cout << "com1a: " << com1a << ", com1b: " << com1b << ", wgm1_10: " << wgm1_10 << "\n";

  return {};
}

template <typename EnumT, typename T>
std::uint32_t localClockTimerTop(
    EnumT clock_divider,
    T selected_frequency,
    std::uint32_t timer_clock_frequency,
    bool phase_correct_mode) {
  return ardo::sys::avr::mcu::getClockTimerTop(
    clock_divider, selected_frequency, timer_clock_frequency, phase_correct_mode);
}

inline void setupTimer() {
  ardo::sys::avr::mcu::TC1<56000, false, 16000000>::setFastPwm();
}

void dividerTests() {
  using namespace ardo::sys::avr::mcu;
  std::cout << "Before RegisterTCCR1AB: " << std::bitset<16>(RegisterTCCR1AB::Read().value) << "\n";;
  std::cout << "Before RegisterIRC1: " << (RegisterIRC1::Read().value) << "\n";;
  TestBitFields::setupTimer();
  std::cout << "After RegisterTCCR1AB: " << std::bitset<16>(RegisterTCCR1AB::Read().value) << "\n";;
  std::cout << "After RegisterIRC1: " << (RegisterIRC1::Read().value) << "\n";;

  std::cout << "cs1_divider_multiple = " << findDividerMultiple(TC1<56000, false, 16000000>::cs_value) << "\n";
  std::cout << "top_count = " << TC1<56000, false, 16000000>::top_count << "\n";

  BitsCOM1A bc1a = RegisterTCCR1AB::Read();
}

inline void TestPort() {
  using namespace ardo::sys::avr::mcu;
  struct zzPB7 : GpioPort<zzPB7, GpioPortDefinition<
    BitsPORTB7, BitsPINB7, BitsDDB7, RegisterPORTB, RegisterPINB, RegisterDDB>>
  {};

  zzPB7::configure<zzPB7::ConfigureInputPullup>();
  zzPB7::configure(false, true);
  zzPB7::configure<zzPB7::ConfigureInput>();
  zzPB7::configure<zzPB7::ConfigureOutputFalse>();
  zzPB7::configure<zzPB7::ConfigureOutputTrue>();
  zzPB7::set(false);
  zzPB7::get();

  zzPB7::PinBit pin = zzPB7::PinReg::Read();

  using InPB7 = InputGpioPort<zzPB7, true>;
  InPB7::get();

  using OutPB7 = OutputGpioPort<zzPB7, true>;
  OutPB7::set(true);
  OutPB7::get();

  using BidiPB7 = BidirectionalGpioPort<zzPB7, true>;
  BidiPB7::set(true);
  BidiPB7::set(false);
  BidiPB7::get();


  ppPC6::configure<ppPC6::ConfigureInputPullup>();
  ppPD0::configure<ppPD0::ConfigureInputPullup>();

  InputGpioPort<ppPC6, true>::get();
  OutputGpioPort<ppPC6>::get();
  OutputGpioPort<ppPC6>::set(true);

  BidirectionalGpioPort<ppPC6, true>::get();
  BidirectionalGpioPort<ppPC6>::get();
  BidirectionalGpioPort<ppPC6>::set(true);
  BidirectionalGpioPort<ppPC6>::set(false);
}


void runBitfieldsTest() {
  testRegSelector();
  testRegSelector2();
  getTypeWGM1();
  rwTypeWGM1();
  dividerTests();
  TestPort();
}

} // namespace

struct BitFieldsTest : setl_test::SetlTest
{
  bool run() override {
    TestBitFields::runBitfieldsTest();
    return true;
  }
};

BitFieldsTest tBitFieldsTest;

setl_test::SetlTest& datest = tBitFieldsTest;