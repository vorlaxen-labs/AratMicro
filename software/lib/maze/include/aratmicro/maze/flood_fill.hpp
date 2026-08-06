#pragma once

#include "aratmicro/maze/types.hpp"

#include <array>
#include <cstdint>

namespace aratmicro::maze {

class FloodFillSolver {
 public:
  FloodFillSolver();

  void reset(std::uint8_t start_x, std::uint8_t start_y, Direction heading,
             std::uint8_t goal_x, std::uint8_t goal_y);

  [[nodiscard]] std::uint8_t x() const { return x_; }
  [[nodiscard]] std::uint8_t y() const { return y_; }
  [[nodiscard]] Direction heading() const { return heading_; }

  [[nodiscard]] const Cell& cell(std::uint8_t x, std::uint8_t y) const { return maze_[y][x]; }

  void set_wall(std::uint8_t x, std::uint8_t y, Wall wall, bool present);
  void update_walls_from_sensors(const WallSensors& sensors);

  void flood_fill();

  /// Best heading to reduce distance toward the goal; nullopt if trapped.
  [[nodiscard]] bool has_escape_route() const;
  [[nodiscard]] Direction preferred_heading() const;

  /// Move one cell in `heading`; caller must ensure the path is open.
  void move(Direction heading);

 private:
  [[nodiscard]] bool is_open(std::uint8_t x, std::uint8_t y, Direction direction) const;
  [[nodiscard]] bool neighbor(std::uint8_t x, std::uint8_t y, Direction direction,
                              std::uint8_t& nx, std::uint8_t& ny) const;
  void set_wall_internal(std::uint8_t x, std::uint8_t y, Wall wall, bool present);

  std::array<std::array<Cell, kMazeSize>, kMazeSize> maze_{};
  std::uint8_t x_{0};
  std::uint8_t y_{0};
  Direction heading_{Direction::North};
  std::uint8_t goal_x_{0};
  std::uint8_t goal_y_{0};
};

}  // namespace aratmicro::maze
