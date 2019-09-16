/**
 * ArdOinus resource claims provide the framework for compile time
 * resource conflict detection.
 */

#ifndef ARDO_RESOURCES__H
#define ARDO_RESOURCES__H

#include "setl_templ_utils.h"

namespace ardo {

/** Resource designator. GPIO pins are exclusive resources. When assigning
 * input and output pins, this template is used to indicate claim of the
 * GPIO pin. If the resource is used by more than one module, the resource
 * is overcomiited and the program will fail to compile. */
template <unsigned P>
class GPIOResource {
public:
  static constexpr unsigned PIN = P;
};

/**
 * For serial port resource claims. 
 */
template <unsigned PortN>
class SerialResource {};

/**
 * For hardware timer resource claims.
 */
template <unsigned N>
class HardwareTimer {};

/**
 * Module parameters must contain a "Claim" type which is a ResourceClaim below.
 * Any type may be a parameter to ResourceClaim which allows any library to
 * define a new claim type to manage finite resources. GPIOResource above is
 * not special but it should be used whenever a module makes use of a GPIO pin.
 * Examples of other possible resources would be timers, interrupts, network ports
 * nvram.
 *
 * Range claims allow the use of a resource claim than spans a continuous
 * range of integers. An example where this is particularly useful for claiming 
 * ranges of EEPROM addresses. End is not inclusive, i.e. End = Begin + size.
 *
 * The base type of a range claim is considered in conflict if the range claim
 * with the type and the type itself is considered claimed. This can be useful
 * with cases such as hardware timers where the claim for using a PWM timer
 * can be shared with multiple GPIO pins in this case the GPIO pins can claim
 * a "slot" for the timer and not be in conflict. However, if one uses the timer
 * independently it would be in conflict with any GPIO pin using the same
 * timer for PWM support.
 */

template <typename T, int Begin, int End = Begin + 1>
struct range_claim {
  static constexpr bool is_good = End > Begin;
  static_assert(is_good, "Incorrect range, End must be strictly after Begin.");
};

template<typename T, typename U>
struct has_conflict : std::false_type {};

template<typename T>
struct has_conflict<T, T> : std::true_type {};

template<typename T, int Begin1, int End1, int Begin2, int End2>
struct has_conflict<range_claim<T, Begin1, End1>, range_claim<T, Begin2, End2>> {
  static constexpr bool value = (End1 > Begin2) && (End2 > Begin1)
    || !range_claim<T, Begin1, End1>::is_good
    || !range_claim<T, Begin2, End2>::is_good;
};

template<typename T, int Begin, int End>
struct has_conflict<range_claim<T, Begin, End>, T> : std::true_type {};

template<typename T, int Begin, int End>
struct has_conflict<T, range_claim<T, Begin, End>> : std::true_type {};


// R is the set of resourced claimed. A resource may be any type or for a range 
// of resources can be a range_claim.
template <typename... R>
class ResourceClaim {
public:
  using Resources = setl::TypeArgs<R...>;

  template <typename Op, typename VL>
  using Scanner = setl::For<Op, VL, R...>;

  template <typename S>
  using has_resource = Scanner<setl::Operator<has_conflict, setl::OrEval>, S>;
};

}

#endif
