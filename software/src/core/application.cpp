#include "aratmicro/core/application.hpp"

namespace aratmicro::core {

Result<void> Application::initialize() {
  if (initialized_) {
    return Result<void>::fail(Status::InvalidState);
  }
  initialized_ = true;
  return Result<void>::ok();
}

Result<void> Application::tick() {
  if (!initialized_) {
    return Result<void>::fail(Status::NotInitialized);
  }
  return Result<void>::ok();
}

}  // namespace aratmicro::core
