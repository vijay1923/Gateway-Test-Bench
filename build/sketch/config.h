#line 1 "C:\\Users\\Shree\\Documents\\Arduino\\Embedsol\\Gateway_TestBenach\\periferal_testing\\config.h"
#ifndef CONFIG_H
#define CONFIG_H

///////////////////   Serial  of S3  /////////////////////////////
#define SERIAL_BAUD 115200  
#define TX0_PIN 43
#define RX0_PIN 44

////////////////// WIfi ////////////////////////

#define WIFI_SSID     "Embedsol Technologies LLP"
#define WIFI_PASSWORD "EmbedSolTech"  
#define WIFI_TIMEOUT 5000     // WiFi Timeout  

////////////////// Ethernet  Module ////////////////////////

#define ETH_CS_PIN 5

#define ETH_MAC_1 0xDE
#define ETH_MAC_2 0xAD
#define ETH_MAC_3 0xBE
#define ETH_MAC_4 0xEF
#define ETH_MAC_5 0xFE
#define ETH_MAC_6 0xED

#define ETHERNET_NAME "ETHERNET"

///////////////   MQTT ///////////////////////

const char* mqtt_server = "193.203.160.176"; // MQTT Broker IP
const int   mqtt_port   = 1883;        // MQTT Broker Port
const char* mqtt_user   = "mosca";     // MQTT Username
const char* mqtt_pass   = "PassworD";  // MQTT Password 

////////////////////  I2C Pins  ///////////////////
#define I2C_SDA 42
#define I2C_SCL 2

// NTP Settings -----
#define NTP_SERVER       "pool.ntp.org"   // NTP Server
#define GMT_OFFSET_SEC   19800     // GMT +5:30
#define DAYLIGHT_OFFSET  0   


////////////////////// PCF8574 Configuration   /////////////////////
#define PCF1_ADDR   0x25   // PCF1 (Inputs)
#define PCF2_ADDR  0x26   // PCF2 (Outputs)
#define PCF_INT_PIN   7  /// input pcf interrupt pin  for s3 

#define IO_TEST_DURATION   30000 // 30 seconds

///////////////////////  RGB /////////////////////

#define RGB_PIN     15      // WS2812 data pin  
#define RGB_COUNT   1       // Only 1 LED

/////////////////  RESET TEST //////////////////////
#define EEPROM_SIZE          32   // EEPROM size in bytes
#define RESET_EEPROM_ADDR    0     // Address to store reset state
#define RESET_ARMED          0xA5   // Reset test armed state


/////////   MAC  //////////////////

char flag = 0; // to indicate mac_test only one time in all test
char mac_executed = 0; // flag to ensure mac_test runs only once when a valid command is received

// abort 
volatile bool abortrequested = false  ; /// abort flag 

#define CHECK_ABORT()                  \
    if (abortrequested)                \
    {                                  \
        Serial.println("$,ABORTED,#"); \
        return;                        \
    }

#endif



