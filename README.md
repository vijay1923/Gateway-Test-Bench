# ESP32-S3 Peripheral Test Bench

## Overview

This project is an ESP32-S3 hardware validation sketch for production/lab testing.
It exposes a serial command interface to run peripheral tests and returns structured
PASS/FAIL responses for automation.

Core capabilities include:

- Wi-Fi connectivity
- MQTT broker connection
- Ethernet (DHCP + link)
- PCF8574 detection (`PCF1`, `PCF2`)
- Digital input/output loop checks through PCF expanders
- RGB (WS2812) LED sequence
- MAC address read
- RTC + NTP synchronization check
- USB scanner callback test
- UART2 loopback style check
- RS485 Modbus read check
- SPIFFS filesystem write/read validation
- Reset/restart validation
- Test abort during long-running checks

## Serial command protocol

### Command format

All incoming commands must match:

`$,<COMMAND>,<VALUE>,#`

Examples:

- `$,WIFI,1,#`
- `$,MQTT,1,#`
- `$,ALL,1,#`
- `$,SUMMARY,1,#`
- `$,ABORT,1,#`

Notes:

- `<COMMAND>` is case-insensitive in firmware.
- `<VALUE>` must be numeric (`1` or `2` accepted by parser).
- Frames not matching the format are rejected.

### Abort behavior

While a test is running, send:

`$,ABORT,1,#`

When accepted, firmware returns:

`$,ABORTED,<CURRENT_TEST>,#`

## Supported commands

| Command | Purpose |
|---|---|
| `WIFI` | Run Wi-Fi connect test |
| `MQTT` | Run MQTT connect/publish test (requires Wi-Fi) |
| `ETHERNET` | Run Ethernet DHCP/link test |
| `PCF1` | Detect PCF8574 at input address |
| `PCF2` | Detect PCF8574 at output address |
| `INPUT` | Validate 8 input channels via PCF1 |
| `OUTPUT` | Validate 8 output channels via PCF2/PCF1 feedback |
| `RGB` | Run RGB LED color sequence |
| `MAC` | Read ESP32 MAC address |
| `RTC` | Sync NTP and verify RTC progression |
| `SCANNER` | Wait for barcode scan callback |
| `UART2` | UART2 send/receive check |
| `RS232` | Placeholder test (currently reports FAIL) |
| `RS485` | Modbus holding register read check |
| `FILESYSTEM` | SPIFFS write/read consistency test |
| `RESET` | EEPROM-armed restart test |
| `HELP` | Print list of available commands |
| `SUMMARY` | Return one-line status for all tests (`0` not run, `1` pass, `2` fail) |
| `ALL` | Execute full sequence of major tests |

## Typical response format

Most test results follow:

`$,<COMMAND>,<1|2>,<PASS|FAIL>,<DETAILS>,#`

Where:

- `1` typically indicates PASS
- `2` typically indicates FAIL

Some tests emit per-channel results (for example `INPUT`/`OUTPUT`) with `IN` or `OUT`
labels and pin index.

### Summary response format

`SUMMARY` returns a single line in test-index order:

`$,SUMMARY,<S1>,<S2>,...,<SN>,#`

Status code meaning:

- `0` = Not executed
- `1` = PASS
- `2` = FAIL

This format is intended for production jigs and host scripts (easy to parse and fixed order).

## Project file map

| File | Purpose |
|---|---|
| `periferal_testing.ino` | Main parser, command dispatcher, abort handling, setup/loop |
| `config.h` | Pin map, Wi-Fi/MQTT/RTC settings, test constants |
| `secrets.h` | Local-only credentials (`.gitignore` protected) |
| `secrets.h.example` | Template for configuring local credentials |
| `header.h` | Central include aggregator |
| `wifi_test.h` | Wi-Fi test implementation |
| `mqtt_test.h` | MQTT test implementation |
| `ethernet_test.h` | Ethernet test implementation |
| `pcf_test.h` | PCF1/PCF2 scan tests |
| `input_test.h` | Input verification flow |
| `output_test.h` | Output verification flow |
| `rgb_test.h` | RGB LED test and init |
| `mac_test.h` | MAC read test |
| `rtc_test.h` | RTC/NTP test |
| `scanner_test.h` | USB scanner callback test |
| `uart2_test.h` | UART2 test |
| `rs232_test.h` | RS232 test (current placeholder behavior) |
| `rs485_test.h` | RS485/Modbus test |
| `filesystem_test.h` | SPIFFS filesystem test |
| `reset_test.h` | Reset/EEPROM test init and execution |

## Build & flash

This sketch is structured for Arduino ESP32 (ESP32-S3 target) and can be built/flashed
using Arduino IDE or Arduino CLI with the appropriate ESP32 board package.

## Important configuration note

Credentials are now separated from `config.h`:

- `secrets.h` stores local Wi-Fi/MQTT credentials (ignored by git).
- `secrets.h.example` is the shareable template committed to the repository.

For a new setup:

1. Copy `secrets.h.example` to `secrets.h`
2. Fill your real credentials in `secrets.h`
3. Build and flash
