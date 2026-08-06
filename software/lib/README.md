# lib — PlatformIO module libraries

Each subfolder is an independent PlatformIO library (linked automatically via LDF).

Planned modules (not yet added):

- `motor/` — DRV8833 driver abstraction
- `imu/` — MPU6500
- `maze/` — maze solving and flash data

When adding a module: use your own `include/` and `src/` directories; shared types come from `include/aratmicro/core/types.hpp`.
