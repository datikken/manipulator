# Manipulator — Arduino Uno Joystick Reader

A small firmware project for the **Arduino Uno** that reads an analog joystick
(two axes + push-button) and prints the values to the serial monitor.

- **Board:** Arduino Uno (ATmega328P, 16 MHz, 2 KB RAM, 32 KB Flash)
- **Framework:** Arduino
- **Build system:** PlatformIO
- **Serial output:** `9600` baud

```
X:512 | Y:511 | Z: 0
```

---

## Hardware

### Components

- 1 × Arduino Uno
- 1 × analog joystick module (e.g. KY-023 / PS2-style with VRx, VRy, SW, +5V, GND)

### Wiring

| Joystick pin | Arduino Uno pin | Notes |
|---|---|---|
| `+5V` | `5V` | Power |
| `GND` | `GND` | Ground |
| `VRx` | `A0` | X axis (analog) |
| `VRy` | `A1` | Y axis (analog) |
| `SW`  | `D2` | Push button (digital, `INPUT_PULLUP`) |

> The button uses the internal pull-up, so it reads **LOW when pressed**.
> The firmware returns `1` = pressed, `0` = released.

---

## Project structure

```
manipulator/
├── platformio.ini        # PlatformIO configuration (env: uno)
├── README.md
├── include/              # Public headers (PlatformIO)
├── lib/                  # Project libraries (Servo, etc.)
├── src/
│   ├── main.cpp          # Entry point: setup() / loop()
│   ├── Joystick/
│   │   ├── Joystick.h    # Joystick class: getValX/Y/Z, activateBtn
│   │   └── Joystick.cpp
│   └── Axis/
│       ├── Axis.h        # Axis class (wraps Servo)
│       └── Axis.cpp
└── test/                 # PlatformIO unit tests
```

---

## Requirements

- [PlatformIO Core](https://docs.platformio.org/en/latest/core/installation/index.html) (`pio`)
  **or** the [VS Code + PlatformIO IDE extension](https://platformio.org/install/ide?install=vscode).
- USB driver for the Uno's serial chip (genuine Uno works out of the box;
  clones with CH340 need the CH340 driver).
- A USB cable to connect the board.

Check PlatformIO is installed:

```bash
pio --version
```

---

## Build

From the project root (the folder containing `platformio.ini`):

```bash
pio run
```

This compiles the firmware for `env:uno`. Output goes to `.pio/build/uno/firmware.elf`.

Expected result on a clean build:

```
RAM:   [=         ]  11.8% (used 241 bytes from 2048 bytes)
Flash: [=         ]   8.3% (used 2672 bytes from 32256 bytes)
========================= [SUCCESS] =========================
```

---

## Upload (flash to the board)

Connect the Uno via USB, then:

```bash
pio run --target upload
```

PlatformIO auto-detects the port. If auto-detection fails, specify it explicitly:

```bash
# Windows
pio run -t upload --upload-port COM3

# Linux / macOS
pio run -t upload --upload-port /dev/ttyUSB0
```

To list detected serial ports:

```bash
pio device list
```

---

## Run / monitor serial output

After uploading, open the serial monitor at **9600 baud**:

```bash
pio device monitor --baud 9600
```

Or use the VS Code PlatformIO toolbar → **Serial Monitor**.

Expected output (values move as you push the stick):

```
X:512 | Y:511 | Z: 0
X:1023 | Y:511 | Z: 0
X:0 | Y:511 | Z: 1
```

| Field | Meaning | Range |
|---|---|---|
| `X` | X axis, raw ADC value | `0`–`1023` (center ≈ `512`) |
| `Y` | Y axis, raw ADC value | `0`–`1023` (center ≈ `512`) |
| `Z` | Button state | `1` = pressed, `0` = released |

Exit the monitor with `Ctrl+C`.

---

## One-shot build + upload + monitor

```bash
pio run -t upload && pio device monitor --baud 9600
```

---

## Clean

Remove build artifacts:

```bash
pio run --target clean
```

---

## Troubleshooting

| Problem | Fix |
|---|---|
| `pio: command not found` | PlatformIO not on PATH — use the VS Code extension, or run it from `~/.platformio/penv/Scripts/`. |
| Upload fails / port busy | Close any open Serial Monitor, then retry. Verify port with `pio device list`. |
| `class Joystick has no member ...` | `Joystick.h` must declare the methods used in `main.cpp`. Rebuild after saving the header. |
| Values stuck at `0` or `1023` | Check wiring of `VRx`/`VRy` and `5V`/`GND`; a disconnected axis floats. |
| `Z` always `1` | `SW` not wired to `D2`, or module has no pull-up on the board (firmware already enables the internal one). |
| Garbage in Serial Monitor | Wrong baud rate — must be `9600`. |

---

## Notes & possible next steps

- Current `main.cpp` is a **debug reader** — it only prints joystick values.
- The `Axis` class (in `src/Axis/`) wraps a `Servo` but is not yet wired into
  `main.cpp`. To drive servos from the joystick, map the `0`–`1023` range to
  `0`–`180` (e.g. with `map()`) and add a `setAngle()` method to `Axis`.
- Consider adding a **dead zone** around center (`512 ± ~30`) to avoid jitter.
