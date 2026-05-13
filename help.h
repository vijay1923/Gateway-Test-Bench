#ifndef HELP_H
#define HELP_H

/// this file tells all commands on help command

void print_help()
{
    update_test_result(TEST_HELP, true);
    Serial.println("Available Commands:");
    Serial.println("1. WIFI - Test Wi-Fi connectivity | Command : $,WIFI,1,#");  
    Serial.println("2. MQTT - Test MQTT connectivity | Command : $,MQTT,1,#");
    Serial.println("3. RGB - Test RGB LED functionality | Command : $,RGB,1,#");
    Serial.println("4. PCF1 - Test PCF8574 input expander | Command : $,PCF1,1,#");
    Serial.println("5. PCF2 - Test PCF8574 output expander | Command : $,PCF2,1,#");
    Serial.println("6. INPUT - Test button inputs | Command : $,INPUT,1,#");
    Serial.println("7. OUTPUT - Test output pins | Command : $,OUTPUT,1,#");
    Serial.println("8. MAC - Display MAC address | Command : $,MAC,1,#");
    Serial.println("9. ETHERNET - Test Ethernet connectivity | Command : $,ETHERNET,1,#");
    Serial.println("10. RTC - Test Real-Time Clock functionality | Command : $,RTC,1,#");
    Serial.println("11. SCANNER - Scan I2C devices | Command : $,SCANNER,1,#");
    Serial.println("12. RESET - Reset the device | Command : $,RESET,1,#");
    Serial.println("13. RS232 - Test RS232 communication | Command : $,RS232,1,#");
    Serial.println("14. UART2 - Test UART2 communication | Command : $,UART2,1,#");
    Serial.println("15. RS485 - Test RS485 communication | Command : $,RS485,1,#");
    Serial.println("16. FILESYSTEM - Test SPIFFS and LittleFS functionality | Command : $,FILESYSTEM,1,#");
    Serial.println("17. SUMMARY - One-line status for all tests | Command : $,SUMMARY,1,#");
}


#endif