#pragma once

#include <cstdint>

namespace aratmicro::maze {

inline constexpr std::uint8_t kMazeSize = 16;
inline constexpr std::uint8_t kUnreachable = 255;

enum class Direction : std::uint8_t { North = 0, East = 1, South = 2, West = 3 };

enum class Wall : std::uint8_t { North = 0, East = 1, South = 2, West = 3 };

struct Cell {
  std::uint8_t distance{kUnreachable};
  bool walls[4]{false, false, false, false};
  bool walls_known[4]{false, false, false, false};
};

/// Four IR receivers paired with four IR emitters (front-left, front-right, left, right).
struct WallSensors {
  bool front_left{false};
  bool front_right{false};
  bool left{false};
  bool right{false};
};

[[nodiscard]] constexpr Direction turn_left(Direction heading) {
  return static_cast<Direction>((static_cast<std::uint8_t>(heading) + 3) % 4);
}

[[nodiscard]] constexpr Direction turn_right(Direction heading) {
  return static_cast<Direction>((static_cast<std::uint8_t>(heading) + 1) % 4);
}

[[nodiscard]] constexpr Direction turn_around(Direction heading) {
  return static_cast<Direction>((static_cast<std::uint8_t>(heading) + 2) % 4);
}

[[nodiscard]] constexpr Wall direction_to_wall(Direction direction) {
  return static_cast<Wall>(static_cast<std::uint8_t>(direction));
}

[[nodiscard]] constexpr Direction wall_to_direction(Wall wall) {
  return static_cast<Direction>(static_cast<std::uint8_t>(wall));
}

}  // namespace aratmicro::maze
