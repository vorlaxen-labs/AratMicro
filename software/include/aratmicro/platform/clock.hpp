#pragma once

#include <cstdint>

namespace aratmicro::platform {

/// No-op on host tests; will connect to HAL tick source on embedded target.
class Clock {
 public:
  Clock() = default;

  [[nodiscard]] std::uint32_t millis() const;
};

}  // namespace aratmicro::platform
