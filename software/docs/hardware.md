# Hardware reference

> Full hardware details: [`../../hardware/README.md`](../../hardware/README.md)

AratMicro hardware targets Robosam and MEB Robot maze-solving rules. See the main [README](../../README.md) for competition context.

## BOM

| Part | Model | Notes |
|------|-------|-------|
| Microcontroller | STM32F411CEU6 | 512 KB Flash, 128 KB RAM, 100 MHz |
| Motor driver | DRV8833PWP | 2-channel DC, H-bridge |
| I/O expander | PCF8574AP | I2C GPIO |
| Buck regulator | AP63203WU | 3.3 V logic supply |

IMU and other I2C sensors are planned on the `SNIFF_SDA` / `SNIFF_SCL` bus (not yet on the BOM).

## Signals

Schematic hierarchical labels (`AratMicro.net`):

| Group | Signals |
|-------|---------|
| Motor | MC_IN1, MC_IN2, MC_BIN1, MC_BIN2, MC_SLEEP, MC_FAULT |
| Encoder | L_ENC_A, L_ENC_B, R_ENC_A, R_ENC_B |
| Wall IR | IR_ON, REC_F_L, REC_F_R, REC_L, REC_R |
| I2C | SNIFF_SDA, SNIFF_SCL |
| UART | BT_TX, BT_RX |
| Debug | PA13 (SWDIO), PA14 (SWCLK), NRST, BOOT0 |

STM32 pin → GPIO mapping will be defined under `include/aratmicro/platform/` during firmware development.

## Upload

Default board manifest uses ST-Link (`upload.protocol = stlink`). If using DFU boot mode, update the protocol in `platformio.ini`.

## Power

- **Input:** 2S LiPo (~7.4 V)
- **Logic:** 3.3 V (AP63203WU)
- **Motor:** Battery rail → DRV8833 VM

Battery level will be read via ADC on the `BATTS` signal.
