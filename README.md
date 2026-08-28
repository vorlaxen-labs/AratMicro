# AratMicro

High-performance, open-source **micromouse** robot platform built for **[Robosam](https://robosam.org/)** and **MEB Robot** (Ministry of National Education Robotics Competition, Turkey).

AratMicro is a competition-focused maze-solving robot with a custom PCB, wall-detection sensors, dual-encoder drive, and STM32F411-based firmware. Hardware and software are developed together; all design files are shared in this repository.

## Competition target

This robot is designed to meet the maze-solving requirements of:

- **Robosam** — national robotics competition (micromouse / labyrinth category)
- **MEB Robot** — Ministry of National Education (MEB) robotics competition for schools

The mechanical dimensions, sensor layout, and control architecture are tuned for fast, reliable maze exploration and shortest-path solving under competition rules.

## Features

| Area | Detail |
|------|--------|
| **MCU** | STM32F411CEU6 — Cortex-M4 @ 100 MHz, 512 KB Flash, 128 KB RAM |
| **Motor driver** | DRV8833 — dual-channel H-bridge |
| **Wall sensors** | 4× IR receivers + 4× IR LEDs (front left/right, left, right) |
| **Maze solver** | Flood fill (16×16 grid) |
| **Position feedback** | Left/right quadrature encoders (L_ENC_A/B, R_ENC_A/B) |
| **I/O expansion** | PCF8574AP — I2C GPIO expander |
| **Power** | 2S LiPo → AP63203WU buck (3.3 V logic), separate motor rail |
| **Programming** | ST-Link SWD (PA13/PA14), optional UART Bluetooth |
| **Firmware** | PlatformIO + Arduino framework, C++17 |

## Mechanical (target parts)

| Part | Size | Notes |
|------|------|-------|
| **Motor** | 40 × 12 × 17 mm | 3 mm D-shaft |
| **Wheel** | 32 × 7 mm | 3 mm D-shaft |

> Mechanical CAD files are not yet included. Dimensions were chosen to match the PCB and drivetrain layout.

## Repository layout

```
AratMicro/
├── hardware/
│   └── pcb/          # KiCad 10 schematics and PCB (AratMicro.kicad_pro)
├── software/
│   ├── src/          # Firmware source code
│   ├── include/      # Public API headers
│   ├── lib/          # PlatformIO module libraries
│   ├── test/         # Host-side unit tests (Unity)
│   ├── docs/         # Architecture and hardware reference
│   └── platformio.ini
├── LICENSE
└── CONTRIBUTING.md
```

## Quick start

### Requirements

- [PlatformIO](https://platformio.org/) (VS Code extension or CLI)
- ST-Link V2 (or compatible programmer)
- KiCad 10.x (for hardware edits)

### Build and upload firmware

```bash
cd software
pio run -e aratmicro_f411
pio run -e aratmicro_f411 -t upload
```

### Host tests

Algorithms and core logic can be tested on the host:

```bash
cd software
pio test -e native
```

### Hardware

KiCad project: `hardware/pcb/AratMicro.kicad_pro`

Schematic sub-sheets:

| Sheet | File | Contents |
|-------|------|----------|
| Power Supply | `power_supply.kicad_sch` | 2S LiPo input, buck, protection |
| MCU | `mcu.kicad_sch` | STM32F411, clocks, SWD, I/O |
| Motor Controller | `mc.kicad_sch` | DRV8833 motor driver |
| Sensor Unit | `su.kicad_sch` | IR wall-detection circuit |

Full BOM and signal list: [`hardware/README.md`](hardware/README.md)

## Software architecture

Firmware is organized in layers:

- **core** — Hardware-independent application lifecycle
- **platform** — Time and pin abstractions
- **lib/** — Motor, IMU, maze solver modules (planned)

Details: [`software/docs/architecture.md`](software/docs/architecture.md)

## Status

| Component | Status |
|-----------|--------|
| PCB schematic | Active development |
| PCB layout | Active development |
| Firmware skeleton | Available |
| Motor driver code | Planned |
| Wall sensor code | Planned |
| Maze solver (flood fill) | Available (host-tested) |
| Mechanical CAD | Planned |

## Contributing

Contributions are welcome. Please read [`CONTRIBUTING.md`](CONTRIBUTING.md).

## License

This project is released under the [MIT License](LICENSE) — hardware and software may be used, modified, and shared freely.
