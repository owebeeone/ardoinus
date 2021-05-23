
#ifndef ARDO_COLOR_SPACE___H
#define ARDO_COLOR_SPACE___H

#include "setlx_cstdint.h"

namespace ardo {

/**
 * Convert 24 bit (888) color value to a 16 bit (565) value.
 */
inline constexpr std::uint16_t rgb_888_to_565(
  std::uint8_t red, std::uint8_t green, std::uint8_t blue) {
  return ((red & 0xf8u) << 8) | ((green & 0xfcu) << 3) | ((blue & 0xf8u) >> 3);
}

/**
 * Convert 24 bit (888) color value to a 16 bit (565) value where the input is
 * from a 3 byte array.
 */
inline constexpr std::uint16_t rgb_888_to_565(const std::uint8_t* rgb) {
  return rgb_888_to_565(rgb[0], rgb[1], rgb[2]);
}

/**
 * Convert 24 bit (888) color value to a 16 bit (565) value.
 */
inline constexpr std::uint16_t rgb_888_to_565(std::uint32_t rgb) {
  return ((rgb >> 8) & 0xf800u) | ((rgb >> 5) & 0x7e0u) | ((rgb >> 3) & 0x1fu);
}

}

#endif // ARDO_COLOR_SPACE___H