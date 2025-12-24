#include <Arduino.h>
#line 1 "C:\\Users\\Shree\\Documents\\Arduino\\Gateway_TestBenach\\periferal_testing\\periferal_testing.ino"
#include "header.h" 
char  frame[32];  // string to store received command
int i=0;   // frame index  
#line 4 "C:\\Users\\Shree\\Documents\\Arduino\\Gateway_TestBenach\\periferal_testing\\periferal_testing.ino"
void parseFrame(String frame );
#line 41 "C:\\Users\\Shree\\Documents\\Arduino\\Gateway_TestBenach\\periferal_testing\\periferal_testing.ino"
void cmdhandler(String cmd, int val);
#line 111 "C:\\Users\\Shree\\Documents\\Arduino\\Gateway_TestBenach\\periferal_testing\\periferal_testing.ino"
void serial_rx();
#line 128 "C:\\Users\\Shree\\Documents\\Arduino\\Gateway_TestBenach\\periferal_testing\\periferal_testing.ino"
void setup();
#line 137 "C:\\Users\\Shree\\Documents\\Arduino\\Gateway_TestBenach\\periferal_testing\\periferal_testing.ino"
void loop();
#line 4 "C:\\Users\\Shree\\Documents\\Arduino\\Gateway_TestBenach\\periferal_testing\\periferal_testing.ino"
void parseFrame(String frame ) 
{
    frame.trim();
    // ignore responce 
    if (!frame.startsWith("$")|| frame.indexOf("PASS") != -1 || frame.indexOf("FAIL") != -1)
    {
        return;     // Skip outgoing frames 
    }

    // validate frame format 
    if (!frame.startsWith("$,") || !frame.endsWith(",#"))    
    {
        Serial.println("ERR: Invalid Command Format");
        return;
    }
    // Remove "$," from start and ",#" from end
    frame = frame.substring(2, frame.length() - 2);   // extract command frame between delimiters
    int commaIndex = frame.indexOf(',');   // find first comma position
    String cmd = frame.substring(0, commaIndex);   // extract periferal name  from position 0 to comma
    String valStr = frame.substring(commaIndex + 1);  // extract value as string from next position of comma to end

    // Convert value to integer
    int val = valStr.toInt();

    if (val == 0 && valStr != "0")  // if conversion fails
    {
        Serial.print("$,");
        Serial.print(cmd);
        Serial.print(",");
        Serial.print(valStr);
        Serial.println(",WRONG COMMAND,#");
        return;
    }

    cmdhandler(cmd, val);
}

void cmdhandler(String cmd, int val)
{
    cmd.toUpperCase();
    if (cmd == "ABORT")
    {
        abortrequested = true;
        return;
    }
    abortrequested = false;

    if (mac_executed == 0)
    {
        mac_test();
        mac_executed = 1;
    }

    if (val != 1 && val != 2) 
    {
        Serial.print("$,");
        Serial.print(cmd);
        Serial.print(",");
        Serial.print(val);
        Serial.println(",WRONG COMMAND,#");
        return;
    }

    if (cmd == "WIFI")
        wifi_test();
    else if (cmd == "RGB")
        rgb_test();
    else if (cmd == "PCF1")
        pcf1_test();
    else if (cmd == "PCF2")
        pcf2_test();
    else if (cmd == "INPUT")
        input_test();
    else if (cmd == "OUTPUT")
        output_test();
    else if (cmd == "MAC")
        mac_test();
    else if (cmd == "ETHERNET")
        ethernet_test();
    else if (cmd == "MQTT")
        mqtt_test();
    else if (cmd == "RTC")
        rtc_test();
    else if (cmd == "RESET")
        reset_test();
    else if (cmd == "ALL") 
    {
        rgb_test();       CHECK_ABORT();
        wifi_test();      CHECK_ABORT();
        mqtt_test();      CHECK_ABORT();
        rtc_test();       CHECK_ABORT();
        ethernet_test();  CHECK_ABORT();
        pcf1_test();      CHECK_ABORT();
        pcf2_test();      CHECK_ABORT();
        input_test();     CHECK_ABORT();
        output_test();    CHECK_ABORT();
        reset_test();
    }
    else {
        Serial.print("$,");
        Serial.print(cmd);
        Serial.print(",");
        Serial.print(val);
        Serial.println(",INVALID COMMAND,#");
    }
}

void serial_rx()
{
    while (Serial.available())
    {
        char c = Serial.read();
        frame[i++] = c;
        if (c == '#') 
        {
            frame[i] = '\0';
            parseFrame(String(frame));
            i = 0;   
        }
    }
}



void setup() 
{
   Serial.begin(SERIAL_BAUD, SERIAL_8N1, RX0_PIN, TX0_PIN);
    Serial.println("Welcome ESP32-S3 Peripheral BenchTest");
    rgb_init();  // initialize RGB
    reset_test_init();  // initialize reset test
}


void loop() 
{
    serial_rx();  /// 
    
}
