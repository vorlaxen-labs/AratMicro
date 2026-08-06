#include "aratmicro/core/application.hpp"

#if defined(ARDUINO)
#include <Arduino.h>
#endif

namespace {

aratmicro::core::Application g_application;

}  // namespace

#if defined(ARDUINO)

void setup() {
  const auto result = g_application.initialize();
  (void)result;
}

void loop() {
  (void)g_application.tick();
}

#endif
