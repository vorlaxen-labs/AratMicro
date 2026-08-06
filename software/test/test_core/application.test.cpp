#include <unity.h>

#include "aratmicro/core/application.hpp"

using aratmicro::core::Application;
using aratmicro::core::Status;

void test_application_initialize_succeeds() {
  Application app;
  const auto result = app.initialize();
  TEST_ASSERT_TRUE(result.is_ok());
  TEST_ASSERT_TRUE(app.is_initialized());
}

void test_application_initialize_twice_fails() {
  Application app;
  TEST_ASSERT_TRUE(app.initialize().is_ok());
  const auto second = app.initialize();
  TEST_ASSERT_FALSE(second.is_ok());
  TEST_ASSERT_EQUAL_UINT8(static_cast<std::uint8_t>(Status::InvalidState),
                          static_cast<std::uint8_t>(second.status()));
}

void test_application_tick_requires_initialize() {
  Application app;
  const auto tick = app.tick();
  TEST_ASSERT_FALSE(tick.is_ok());
  TEST_ASSERT_EQUAL_UINT8(static_cast<std::uint8_t>(Status::NotInitialized),
                          static_cast<std::uint8_t>(tick.status()));
}

void test_application_tick_after_initialize_succeeds() {
  Application app;
  TEST_ASSERT_TRUE(app.initialize().is_ok());
  TEST_ASSERT_TRUE(app.tick().is_ok());
}

int main(int argc, char** argv) {
  (void)argc;
  (void)argv;
  UNITY_BEGIN();
  RUN_TEST(test_application_initialize_succeeds);
  RUN_TEST(test_application_initialize_twice_fails);
  RUN_TEST(test_application_tick_requires_initialize);
  RUN_TEST(test_application_tick_after_initialize_succeeds);
  return UNITY_END();
}
