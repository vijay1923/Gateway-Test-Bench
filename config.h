#ifndef CONFIG_H
#define CONFIG_H

// ===== Include Secrets (Credentials) =====
// secrets.h contains Wi-Fi SSID/password and MQTT credentials
// Copy secrets.h.example to secrets.h and fill in your values
// secrets.h is in .gitignore - never commit it
#include "secrets.h"

///////////////////   Serial  of S3  /////////////////////////////
#define SERIAL_BAUD 115200  
#define TX0_PIN 43
#define RX0_PIN 44

////////////////// WIfi ////////////////////////
// WIFI_SSID and WIFI_PASSWORD are now in secrets.h
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
// MQTT_SERVER, MQTT_PORT, MQTT_USER, MQTT_PASS are now in secrets.h
// Note: These are #define values, not const char* 

////////////////////  I2C Pins  ///////////////////
#define I2C_SDA 42
#define I2C_SCL 2
bool rtc_detected = false; // global flag to track RTC detection status

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

//////////// Test result storage ///////////

enum TestIndex
{
    TEST_WIFI,
    TEST_RGB,
    TEST_PCF1,
    TEST_PCF2,
    TEST_INPUT,
    TEST_OUTPUT,
    TEST_MAC,
    TEST_ETHERNET,
    TEST_MQTT,
    TEST_RTC,
    TEST_RESET,
    TEST_SCANNER,
    TEST_RS232,
    TEST_RS485,
    TEST_UART2,
    TEST_FILESYSTEM,
    TEST_HELP,
    TEST_COUNT
    
};

bool test_executed[TEST_COUNT] = {false};
bool test_result[TEST_COUNT] = {false}; // 1: PASS, 0: FAIL

inline void update_test_result(TestIndex test, bool is_pass)
{
    test_executed[test] = true;
    test_result[test] = is_pass;
}

inline void reset_all_test_results()
{
    for (int idx = 0; idx < TEST_COUNT; idx++)
    {
        test_executed[idx] = false;
        test_result[idx] = false;
    }
}


/////   RS232   ///////////

#define RS232_TX 17
#define RS232_RX 35

///// RS485  ///////

#define RS485_TX 17
#define RS485_RX 35


////////////  UART 2 (HMI) ///////////

#define UART2_TX 37
#define UART2_RX 36



////////////////  SPIFFS  ////////////
#define SPIFFS_TEST_FILE "/spiffs_test.txt"
#define SPIFFS_TEST_CONTENT "SPIFFS Test Successful!"


//////////// LittleFS  ////////////
#define LITTLEFS_TEST_FILE "/littlefs_test.txt"
#define LITTLEFS_TEST_CONTENT "LittleFS Test Successful!"

// runtime globals 
volatile char frame[32] = {0}; // string to store received command
volatile int i = 0;            // frame index
volatile bool frameready = false;

// abort 
volatile bool abortrequested = false;   /// abort flag 
volatile bool abortresponsesent = false;
volatile bool testrunning = false;
const char* currenttestname = "NONE";

void serviceAbortCommand();
bool cooperativeDelay(unsigned long durationMs);
void beginTestExecution();
void endTestExecution();
void setCurrentTest(const char* testName);

#define CHECK_ABORT()                      \
    do                                     \
    {                                      \
        serviceAbortCommand();             \
        if (abortrequested)                \
        {                                  \
            if (!abortresponsesent)        \
            {                              \
                Serial.print("$,ABORTED,"); \
                Serial.print(currenttestname); \
                Serial.println(",#"); \
                abortresponsesent = true;  \
            }                              \
            return;                        \
        }                                  \
    } while (0)

#define ABORTABLE_DELAY(ms)            \
    do                                 \
    {                                  \
        if (cooperativeDelay(ms))      \
        {                              \
            return;                    \
        }                              \
    } while (0)

#endif



