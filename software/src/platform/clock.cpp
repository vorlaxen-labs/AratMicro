#include "aratmicro/platform/clock.hpp"

#if defined(ARDUINO)
#include <Arduino.h>
#else
#include <chrono>
#endif

namespace aratmicro::platform {

std::uint32_t Clock::millis() const {
#if defined(ARDUINO)
  return ::millis();
#else
  using namespace std::chrono;
  static const auto start = steady_clock::now();
  return static_cast<std::uint32_t>(
      duration_cast<milliseconds>(steady_clock::now() - start).count());
#endif
}

}  // namespace aratmicro::platform
