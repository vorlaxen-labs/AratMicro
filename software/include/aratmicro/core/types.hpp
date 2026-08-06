#pragma once

#include <cstdint>

namespace aratmicro::core {

enum class Status : std::uint8_t {
  Ok = 0,
  InvalidState,
  NotInitialized,
  HardwareError,
};

template <typename T>
class Result {
 public:
  static Result ok(T value) { return Result{Status::Ok, value}; }

  static Result fail(Status status) { return Result{status, T{}}; }

  [[nodiscard]] bool is_ok() const { return status_ == Status::Ok; }

  [[nodiscard]] Status status() const { return status_; }

  [[nodiscard]] const T& value() const { return value_; }

  [[nodiscard]] T& value() { return value_; }

 private:
  Result(Status status, T value) : status_{status}, value_{value} {}

  Status status_;
  T value_;
};

template <>
class Result<void> {
 public:
  static Result ok() { return Result{Status::Ok}; }

  static Result fail(Status status) { return Result{status}; }

  [[nodiscard]] bool is_ok() const { return status_ == Status::Ok; }

  [[nodiscard]] Status status() const { return status_; }

 private:
  explicit Result(Status status) : status_{status} {}

  Status status_;
};

}  // namespace aratmicro::core
