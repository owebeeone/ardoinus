
#ifndef __ArdoFastLED_h__
#define __ArdoFastLED_h__

#include "ardoino.h"
#include "setl_time.h"

#include <FastLED.h>

namespace ardo_fastled {

// The FastLED resource.
class FastLEDParameter {
private:
  FastLEDParameter() = delete;
public:
  using Claims = ardo::ResourceClaim<decltype(FastLED)>;

  inline static void runSetup() {}
  inline static void runLoop() {}
};

template <
  unsigned w_count,
  typename w_LedPin, 
  template<uint8_t DATA_PIN, EOrder RGB_ORDER> class w_Type,
  EOrder w_colorOrder,
  uint8_t w_brightness
  >
class LedStrip : public ardo::ModuleBase<ardo::Parameters<w_LedPin, FastLEDParameter>> {
public:
  constexpr static unsigned COUNT = w_count;
  constexpr static EOrder COLOR_ORDER = w_colorOrder;
  using LedPin = w_LedPin;

  static void runSetup() {
    instance.instanceSetup();
  }

  void instanceSetup() {
    FastLED.addLeds<w_Type, LedPin::PIN, COLOR_ORDER>(leds, COUNT).setCorrection(UncorrectedColor);
    FastLED.setBrightness(w_brightness);
  }

  static void runLoop() {
    instance.instanceLoop();
  }

  void instanceLoop() {
    if (has_changed) {
      FastLED.show();
      has_changed = false;
    }
  }

  static void set(unsigned index, const CRGB& value) {
    instance.instanceSet(index, value);
  }

  static CRGB get(unsigned index) {
    instance.instanceGet(index);
  }

  void instanceSet(unsigned index, const CRGB& value) {
    auto& entry = leds[index];
    if (entry == value) {
      return; // not changed.
    }
    entry = value;
    has_changed = true;
  }

  CRGB instanceGet(unsigned index) const {
    return leds[index];
  }

private:

  bool has_changed = true;
  CRGB leds[COUNT];

public:
  static LedStrip instance;
};

template <
  unsigned w_count,
  typename w_LedPin,
  template<uint8_t DATA_PIN, EOrder RGB_ORDER> class w_Type,
  EOrder w_colorOrder,
  uint8_t w_brightness
>
LedStrip<w_count, w_LedPin, w_Type, w_colorOrder, w_brightness>
  LedStrip<w_count, w_LedPin, w_Type, w_colorOrder, w_brightness>::instance;

} // namespace

// example:
// using MyLeds = ardo_fastled::LedStrip<LEDS_COUNT, ardo::ExternalPin<LEDS_PIN>, WS2812B, RGB, 64>;

#endif // include guard

