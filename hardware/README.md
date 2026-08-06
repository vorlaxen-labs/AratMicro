# AratMicro — Hardware

KiCad 10 main board (PCB) design for the Robosam and MEB Robot micromouse platform. Project file: [`pcb/AratMicro.kicad_pro`](pcb/AratMicro.kicad_pro)

## Schematic hierarchy

```
AratMicro.kicad_sch
├── Power Supply/      power_supply.kicad_sch
├── MCU/               mcu.kicad_sch
├── Motor Controller Unit/   mc.kicad_sch
└── Sensor Unit/       su.kicad_sch
```

## Key components (BOM summary)

| Ref | Part | Description |
|-----|------|-------------|
| U2 | STM32F411CEU6 | Main MCU, UFQFPN-48 |
| U3 | DRV8833PWP | Dual H-bridge motor driver, HTSSOP-16 |
| U4 | PCF8574AP | I2C GPIO expander |
| U1 | AP63203WU | 2 A buck, fixed 3.3 V output |
| Y1 | 8 MHz crystal | HSE |
| Y2 | 32.768 kHz crystal | LSE (RTC) |
| BZ1 | Murata PKMCS0909E | Piezo buzzer |
| J (LiPo) | 2S LiPo connector | Battery input |

Protection: polyfuse, TVS diode, AO3401A P-channel MOSFET (power path).

## MCU signal map

Signal names are taken from schematic hierarchical labels. STM32 pin assignments will be finalized during PCB layout.

### Motor driver (DRV8833)

| Signal | Direction | Description |
|--------|-----------|-------------|
| MC_IN1 | MCU → DRV | Motor A direction 1 |
| MC_IN2 | MCU → DRV | Motor A direction 2 |
| MC_BIN1 | MCU → DRV | Motor B direction 1 |
| MC_BIN2 | MCU → DRV | Motor B direction 2 |
| MC_SLEEP | MCU → DRV | Sleep / enable |
| MC_FAULT | DRV → MCU | Fault output |
| AOUT1, AOUT2 | DRV → motor | Motor A |
| BOUT1, BOUT2 | DRV → motor | Motor B |

### Encoders

| Signal | Description |
|--------|-------------|
| L_ENC_A, L_ENC_B | Left wheel quadrature |
| R_ENC_A, R_ENC_B | Right wheel quadrature |

### Wall sensors (IR)

| Signal | Description |
|--------|-------------|
| IR_ON | Enable IR LEDs (Sensor Unit) |
| REC_F_L | Front-left receiver |
| REC_F_R | Front-right receiver |
| REC_L | Left wall receiver |
| REC_R | Right wall receiver |

The Sensor Unit uses 4× IR receivers paired with 4× IR LEDs (one emitter per direction: front-left, front-right, left, right). LED drivers are controlled via BC817 NPN transistors.

### Other

| Signal | Description |
|--------|-------------|
| SNIFF_SDA, SNIFF_SCL | I2C (IMU / external sensor bus) |
| BT_TX, BT_RX | UART — wireless module (optional) |
| Buzzer | Audio feedback |
| LED1–LED4 | Status LEDs |
| PA13, PA14 | SWD (ST-Link) |
| NRST, BOOT0 | Reset and boot mode |
| BATTS | Battery voltage (ADC) |

## Power architecture

```
2S LiPo (7.4 V nominal)
    │
    ├── Motor rail ──► DRV8833 VM
    │
    └── AP63203WU buck ──► +3.3 V logic
            │
            ├── STM32F411
            ├── PCF8574AP
            └── Sensor Unit (IR circuit)
```

Logic runs at 3.3 V; motor supply is driven directly from the battery rail. Polyfuse and TVS provide input protection.

## Mechanical interface

The drivetrain is designed for these off-the-shelf parts:

| Part | Size |
|------|------|
| DC motor | 40 × 12 × 17 mm, 3 mm D-shaft |
| Wheel | 32 × 7 mm, 3 mm D-shaft |

Motor connectors are defined on the Motor Controller Unit sheet.

## Opening in KiCad

1. Install KiCad 10.x.
2. Open `pcb/AratMicro.kicad_pro`.
3. Use the top-level hierarchy sheet in Eeschema to navigate sub-sheets.

## Fabrication

When PCB layout is complete:

- Export Gerber and drill files to `hardware/pcb/fabrication/`.
- BOM CSV: Eeschema → Tools → Generate Bill of Materials.

> **Note:** Layout and fabrication files are not final yet; the repository version is under active development.
