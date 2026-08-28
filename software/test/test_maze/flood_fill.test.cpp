#include <unity.h>

#include "aratmicro/maze/flood_fill.hpp"

using aratmicro::maze::Direction;
using aratmicro::maze::FloodFillSolver;
using aratmicro::maze::Wall;
using aratmicro::maze::WallSensors;
using aratmicro::maze::kMazeSize;
using aratmicro::maze::kUnreachable;

void test_flood_fill_goal_is_zero() {
  FloodFillSolver solver;
  solver.reset(0, 0, Direction::North, 3, 3);

  TEST_ASSERT_EQUAL_UINT8(0, solver.cell(3, 3).distance);
  TEST_ASSERT_EQUAL_UINT8(1, solver.cell(3, 2).distance);
  TEST_ASSERT_EQUAL_UINT8(6, solver.cell(0, 0).distance);
}

void test_flood_fill_wall_blocks_path() {
  FloodFillSolver solver;
  solver.reset(0, 0, Direction::North, 2, 0);

  solver.set_wall(0, 0, Wall::East, true);

  TEST_ASSERT_EQUAL_UINT8(kUnreachable, solver.cell(0, 0).distance);
  TEST_ASSERT_FALSE(solver.has_escape_route());
}

void test_flood_fill_prefers_shortest_open_neighbor() {
  FloodFillSolver solver;
  solver.reset(0, 0, Direction::North, 2, 0);

  TEST_ASSERT_EQUAL(static_cast<int>(Direction::East), static_cast<int>(solver.preferred_heading()));
}

void test_flood_fill_sensor_update_marks_walls() {
  FloodFillSolver solver;
  solver.reset(1, 1, Direction::North, kMazeSize - 1, kMazeSize - 1);

  WallSensors sensors{};
  sensors.front_left = true;
  sensors.front_right = true;
  sensors.left = true;
  sensors.right = true;
  solver.update_walls_from_sensors(sensors);

  TEST_ASSERT_TRUE(solver.cell(1, 1).walls[static_cast<std::uint8_t>(Wall::North)]);
  TEST_ASSERT_TRUE(solver.cell(1, 1).walls[static_cast<std::uint8_t>(Wall::West)]);
  TEST_ASSERT_TRUE(solver.cell(1, 1).walls[static_cast<std::uint8_t>(Wall::East)]);
  TEST_ASSERT_FALSE(solver.has_escape_route());
}

void test_flood_fill_move_updates_pose() {
  FloodFillSolver solver;
  solver.reset(0, 0, Direction::East, 1, 0);

  solver.move(Direction::East);

  TEST_ASSERT_EQUAL_UINT8(1, solver.x());
  TEST_ASSERT_EQUAL_UINT8(0, solver.y());
  TEST_ASSERT_EQUAL(static_cast<int>(Direction::East), static_cast<int>(solver.heading()));
}

int main(int argc, char** argv) {
  (void)argc;
  (void)argv;
  UNITY_BEGIN();
  RUN_TEST(test_flood_fill_goal_is_zero);
  RUN_TEST(test_flood_fill_wall_blocks_path);
  RUN_TEST(test_flood_fill_prefers_shortest_open_neighbor);
  RUN_TEST(test_flood_fill_sensor_update_marks_walls);
  RUN_TEST(test_flood_fill_move_updates_pose);
  return UNITY_END();
}
