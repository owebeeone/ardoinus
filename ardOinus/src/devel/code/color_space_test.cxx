
#include "ardo_color_space.h"

int main() {
  static_assert(ardo::rgb_888_to_565(0xff0000u) == 0xf800u,
    "green bits don't match.");
  static_assert(ardo::rgb_888_to_565(0x00ff00u) == 0x7e0u,
    "red bits don't match.");
  static_assert(ardo::rgb_888_to_565(0x0000ffu) == 0x1fu,
    "blue bits don't match.");

  static_assert(ardo::rgb_888_to_565(0xff, 0, 0) == 0xf800u,
    "green bits don't match.");
  static_assert(ardo::rgb_888_to_565(0, 0xff, 0) == 0x7e0u,
    "red bits don't match.");
  static_assert(ardo::rgb_888_to_565(0, 0, 0xff) == 0x1fu,
    "blue bits don't match.");
}
