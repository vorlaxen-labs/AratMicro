#pragma once

#include "aratmicro/core/types.hpp"

namespace aratmicro::core {

class Application {
 public:
  Application() = default;
  ~Application() = default;

  Application(const Application&) = delete;
  Application& operator=(const Application&) = delete;
  Application(Application&&) = delete;
  Application& operator=(Application&&) = delete;

  Result<void> initialize();
  Result<void> tick();

  [[nodiscard]] bool is_initialized() const { return initialized_; }

 private:
  bool initialized_{false};
};

}  // namespace aratmicro::core
