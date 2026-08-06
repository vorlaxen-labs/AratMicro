# lib — PlatformIO module libraries

Each subfolder is an independent PlatformIO library (linked automatically via LDF).

Modules:

- `maze/` — flood fill maze solver (`FloodFillSolver`, 4-sensor wall mapping)

Planned (not yet added):

- `motor/` — DRV8833 driver abstraction
- `imu/` — MPU6500

When adding a module: use your own `include/` and `src/` directories; shared types come from `include/aratmicro/core/types.hpp`.
