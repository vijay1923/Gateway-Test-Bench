## 🚜 ESP32 Peripheral BenchTest 

### 📖 Overview

This project is a lightweight lab/test harness for an ESP32-S3 that exercises common peripherals (WiFi, Ethernet, MQTT, PCF8574 I/O, RGB LEDs, RTC, MAC, inputs/outputs, etc.).

Control is via a small serial command protocol (suitable for human use or automated rigs). The device prints structured responses you can parse from a host machine.

### 📚 Libraries Used

| Library Name       | Purpose                                          |
|--------------------|--------------------------------------------------|
| `WiFi`             | WiFi connectivity                                |
| `PubSubClient`     | MQTT client when testing MQTT connectivity       |
| `Wire`             | I2C for PCF8574 tests                            |
| `Adafruit_NeoPixel`| WS2812 / RGB control                             |
| `Ethernet`         | Ethernet connectivity                            |
| `RTClib`           | Real-time clock (RTC) functionality              |
| `Adafruit_BusIO`   | I2C/SPI abstraction layer (Adafruit utility)     |
| `EEPROM`           | ESP32 EEPROM for data persistence                |
| `usb_scanner_Lib`  | USB barcode scanner interface                    |
| `Arduino`          | Core Arduino APIs                                |


### 📁 File Structure & Description

| File                         | Purpose                                         |
|------------------------------|-------------------------------------------------|
| `periferal_testing.ino`      | Main sketch: serial loop, boot messages         |
| `header.h`                   | Main header: includes all libraries and tests    |
| `config.h`                   | Pins, WiFi/MQTT settings, I2C addresses         |
| `wifi_test.h`                | WiFi connectivity test                          |
| `mqtt_test.h`                | MQTT connect/publish test                       |
| `ethernet_test.h`            | Ethernet connectivity test                      |
| `pcf_test.h`                 | PCF8574 I/O expander test                       |
| `rgb_test.h`                 | WS2812 RGB LED test                             |
| `input_test.h`               | Input pins test                                 |
| `output_test.h`              | Output pins test                                |
| `mac_test.h`                 | MAC address test                                |
| `rtc_test.h`                 | Real-time clock test                            |
| `scanner_test.h`             | Barcode scanner test                            |
| `reset_test.h`               | EEPROM reset/restart test                       |
| `rs232_test.h`               | RS232 serial communication test                 |
| `rs485_test.h`               | RS485 serial communication test                 |

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
$<ETHERNET>,<1>#   // start Ethernet test
$<PCF>,<1>#        // run PCF8574 I/O test
$<RGB>,<1>#        // run RGB LED test
$<INPUT>,<1>#      // run input pins test
$<OUTPUT>,<1>#     // run output pins test
$<MAC>,<1>#        // run MAC address test
$<RTC>,<1>#        // run RTC test
$<SCANNER>,<1>#    // run barcode scanner test
$<RESET>,<1>#      // run reset test
$<RS232>,<1>#      // run RS232 test
$<RS485>,<1>#      // run RS485 test
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
