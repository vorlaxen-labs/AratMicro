#include "aratmicro/maze/flood_fill.hpp"

#include <array>
#include <cstddef>

namespace aratmicro::maze {

namespace {

struct QueueEntry {
  std::uint8_t x;
  std::uint8_t y;
};

}  // namespace

FloodFillSolver::FloodFillSolver() = default;

void FloodFillSolver::reset(std::uint8_t start_x, std::uint8_t start_y, Direction heading,
                              std::uint8_t goal_x, std::uint8_t goal_y) {
  for (auto& row : maze_) {
    for (auto& cell : row) {
      cell = Cell{};
    }
  }

  x_ = start_x;
  y_ = start_y;
  heading_ = heading;
  goal_x_ = goal_x;
  goal_y_ = goal_y;

  flood_fill();
}

void FloodFillSolver::set_wall_internal(std::uint8_t x, std::uint8_t y, Wall wall,
                                        bool present) {
  const auto index = static_cast<std::uint8_t>(wall);
  maze_[y][x].walls[index] = present;
  maze_[y][x].walls_known[index] = true;

  const auto opposite = static_cast<Wall>((index + 2) % 4);
  std::uint8_t nx = x;
  std::uint8_t ny = y;
  if (neighbor(x, y, wall_to_direction(wall), nx, ny)) {
    maze_[ny][nx].walls[static_cast<std::uint8_t>(opposite)] = present;
    maze_[ny][nx].walls_known[static_cast<std::uint8_t>(opposite)] = true;
  }
}

void FloodFillSolver::set_wall(std::uint8_t x, std::uint8_t y, Wall wall, bool present) {
  set_wall_internal(x, y, wall, present);
  flood_fill();
}

void FloodFillSolver::update_walls_from_sensors(const WallSensors& sensors) {
  const bool front = sensors.front_left || sensors.front_right;

  set_wall_internal(x_, y_, direction_to_wall(heading_), front);
  set_wall_internal(x_, y_, direction_to_wall(turn_left(heading_)), sensors.left);
  set_wall_internal(x_, y_, direction_to_wall(turn_right(heading_)), sensors.right);

  flood_fill();
}

bool FloodFillSolver::neighbor(std::uint8_t x, std::uint8_t y, Direction direction,
                               std::uint8_t& nx, std::uint8_t& ny) const {
  nx = x;
  ny = y;

  switch (direction) {
    case Direction::North:
      if (y == 0) {
        return false;
      }
      ny = static_cast<std::uint8_t>(y - 1);
      return true;
    case Direction::East:
      if (x >= kMazeSize - 1) {
        return false;
      }
      nx = static_cast<std::uint8_t>(x + 1);
      return true;
    case Direction::South:
      if (y >= kMazeSize - 1) {
        return false;
      }
      ny = static_cast<std::uint8_t>(y + 1);
      return true;
    case Direction::West:
      if (x == 0) {
        return false;
      }
      nx = static_cast<std::uint8_t>(x - 1);
      return true;
  }

  return false;
}

bool FloodFillSolver::is_open(std::uint8_t x, std::uint8_t y, Direction direction) const {
  const auto wall = direction_to_wall(direction);
  const auto index = static_cast<std::uint8_t>(wall);
  if (maze_[y][x].walls_known[index] && maze_[y][x].walls[index]) {
    return false;
  }

  std::uint8_t nx = x;
  std::uint8_t ny = y;
  return neighbor(x, y, direction, nx, ny);
}

void FloodFillSolver::flood_fill() {
  for (auto& row : maze_) {
    for (auto& cell : row) {
      cell.distance = kUnreachable;
    }
  }

  maze_[goal_y_][goal_x_].distance = 0;

  std::array<QueueEntry, kMazeSize * kMazeSize> queue{};
  std::size_t head = 0;
  std::size_t tail = 0;

  queue[tail++] = QueueEntry{goal_x_, goal_y_};

  while (head < tail) {
    const QueueEntry current = queue[head++];
    const std::uint8_t base_distance = maze_[current.y][current.x].distance;

    for (std::uint8_t dir = 0; dir < 4; ++dir) {
      const auto direction = static_cast<Direction>(dir);
      if (!is_open(current.x, current.y, direction)) {
        continue;
      }

      std::uint8_t nx = current.x;
      std::uint8_t ny = current.y;
      if (!neighbor(current.x, current.y, direction, nx, ny)) {
        continue;
      }

      if (maze_[ny][nx].distance == kUnreachable) {
        maze_[ny][nx].distance = static_cast<std::uint8_t>(base_distance + 1);
        queue[tail++] = QueueEntry{nx, ny};
      }
    }
  }
}

bool FloodFillSolver::has_escape_route() const {
  for (std::uint8_t dir = 0; dir < 4; ++dir) {
    const auto direction = static_cast<Direction>(dir);
    if (!is_open(x_, y_, direction)) {
      continue;
    }

    std::uint8_t nx = x_;
    std::uint8_t ny = y_;
    if (!neighbor(x_, y_, direction, nx, ny)) {
      continue;
    }

    if (maze_[ny][nx].distance < maze_[y_][x_].distance) {
      return true;
    }
  }

  return false;
}

Direction FloodFillSolver::preferred_heading() const {
  Direction best = heading_;
  std::uint8_t best_distance = kUnreachable;

  for (std::uint8_t dir = 0; dir < 4; ++dir) {
    const auto direction = static_cast<Direction>(dir);
    if (!is_open(x_, y_, direction)) {
      continue;
    }

    std::uint8_t nx = x_;
    std::uint8_t ny = y_;
    if (!neighbor(x_, y_, direction, nx, ny)) {
      continue;
    }

    const std::uint8_t neighbor_distance = maze_[ny][nx].distance;
    if (neighbor_distance < best_distance) {
      best_distance = neighbor_distance;
      best = direction;
    }
  }

  return best;
}

void FloodFillSolver::move(Direction heading) {
  std::uint8_t nx = x_;
  std::uint8_t ny = y_;
  if (!neighbor(x_, y_, heading, nx, ny)) {
    return;
  }

  x_ = nx;
  y_ = ny;
  heading_ = heading;
}

}  // namespace aratmicro::maze
