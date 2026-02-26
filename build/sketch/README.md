#line 1 "C:\\Users\\Shree\\Documents\\Arduino\\Embedsol\\Gateway_TestBenach\\periferal_testing\\README.md"
## 🚜 ESP32 Peripheral BenchTest 

### 📖 Overview

This project is a lightweight lab/test harness for an ESP32-S3 that exercises common peripherals (WiFi, Ethernet, MQTT, PCF8574 I/O, RGB LEDs, RTC, MAC, inputs/outputs, etc.).

Control is via a small serial command protocol (suitable for human use or automated rigs). The device prints structured responses you can parse from a host machine.

### 📚 Libraries Used

| Library Name       | Purpose                                          |
|--------------------|--------------------------------------------------|
| `WiFi`             | WiFi connectivity (ESP32)                        |
| `PubSubClient`     | MQTT client when testing MQTT connectivity       |
| `Wire`             | I2C for PCF8574 tests                            |
| `Adafruit_NeoPixel`| WS2812 / RGB control                             |
| `Arduino`          | Core Arduino APIs                                |


### 📁 File Structure & Description

| File                         | Purpose                                         |
|------------------------------|-------------------------------------------------|
| `periferal_testing.ino`      | Main sketch: serial loop, boot messages         |
| `config.h`                   | Pins, WiFi/MQTT settings, I2C addresses         |
| `command_handler.h`          | Parses serial commands and dispatches to tests  |
| `wifi_test.h`                | WiFi connect test (prints success/failure)      |
| `mqtt_test.h`                | MQTT connect/publish check                      |
| `pcf_test.h`                 | PCF8574 input/output checks                     |
| `rgb_test.h`                 | WS2812 LED test                                 |
| `input_test.h`               | Input Test                                      |
| `output_test.h`              | Output test  tests                              |

### 🔁 Serial Command Protocol

Commands are single-line and terminated with `#`.

Format:

```
$<PERIPHERAL>,<ACTION>#
```

- `PERIPHERAL`: e.g. `WIFI`, `MQTT`, `OUTTEST`, `MAC`, `PCF`.
- `ACTION`: integer action code (typically `1` = start/test, `2` = stop).

Examples:

```
$<WIFI>,<1>#       // start WiFi test
$<MQTT>,<1>#       // run MQTT connect test
$<OUTPUT>,<1>#    // run output pins test
```

### 🖨️ Serial Output — Example

The sketch prints human- and machine-readable logs:

```
Welcome ESP32-S3 Peripheral BenchTest
...
$<WIFI>,<1>,<CONNECTED TO 192.168.1.42>#
$<MQTT>,<1>,<MQTT SERVER CONNECTED,0>#
$<PCF>,<1>,<INPUTS: 0x12>#
```

---
