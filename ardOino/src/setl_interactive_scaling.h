
#ifndef SETL_INTERACTIVE_SCALING___H
#define SETL_INTERACTIVE_SCALING___H

#include "setl_time.h"

namespace setl {

/**
 * Provides scaling factor that is dependent on time.
 */
template <typename T, typename w_ScaleType = float, typename w_TimeType = Time<unsigned long>>
class RelativeInteractiveScaler {
public:
  using value_type = T;
  using TimeType = w_TimeType;
  using PeriodType = typename w_TimeType::period_type;
  using ScaleType = w_ScaleType;

  RelativeInteractiveScaler() {}

  RelativeInteractiveScaler(const ScaleType& scale)
    : scale(scale)
  {}

  RelativeInteractiveScaler(
    const ScaleType& scale, 
    const Period<ScaleType>& min_period,
    const Period<ScaleType>& max_period)
    : scale(scale)
  {}

  value_type scaleForNow(const value_type& value, const TimeType& nowTime) {
    Period<float> since = (nowTime - lastTime).to();
    lastTime = nowTime;

    // Bound the value.
    if (since <= min_period) {
      since = min_period;
    } else if (since >= max_period) {
      since = max_period - Period<ScaleType>{1};
    }

    // De-linearize the value.
    auto factor = since.get() / min_to_max_period.get();

    avgFactor = avgFactorRuningScale * factor + (1 - avgFactorRuningScale) * avgFactor;

    auto compScale = scale * (avgFactor * avgFactor * avgFactor * avgFactor);
    ScaleType unconverted_result = compScale * value + remainder;

    value_type result = value_type(unconverted_result);

    // Keep whatever fractional part.
    remainder = unconverted_result - ScaleType(result);
    return result;
  }

  void setScale(const ScaleType& scale) {
    this->scale = scale;
  }

private:
  TimeType lastTime{};
  ScaleType remainder{ 0 };
  ScaleType scale{ 1 };
  ScaleType avgFactor = 1 / scale;
  ScaleType avgFactorRuningScale = 0.2;

  const Period<ScaleType> min_period = Period<float>(4);
  const Period<ScaleType> max_period = Period<float>(100);
  const Period<ScaleType> min_to_max_period = max_period - min_period;
};


}  // namespace

#endif  // SETL_INTERACTIVE_SCALING___H