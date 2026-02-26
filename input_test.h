#ifndef IO_TEST_H
#define IO_TEST_H

#include <Wire.h>
#include "config.h"


bool io_passed[8] = {false,false,false,false,false,false,false,false};   // bool array to track passed inputs

void input_test()
{
    Serial.println("Input test started - Press each button one by one");
    CHECK_ABORT();  // check before test 

    Wire.begin(I2C_SDA, I2C_SCL);   // inditilizing I2C Bus 

    // Set all 8 pins HIGH
    Wire.beginTransmission(PCF1_ADDR); // PCF1 is input expander
    Wire.write(0xFF);  // Set all pins HIGH (inputs with pull-ups)
    Wire.endTransmission(); // Send data

    int completed = 0; // input count 
    unsigned long startTime = millis();
    const unsigned long TIMEOUT = 30000; // 30 seconds timeout

    while (completed < 8 && (millis() - startTime) < TIMEOUT)  // Loop until all inputs are tested or timeout
    {
        CHECK_ABORT(); 
        Wire.requestFrom(PCF1_ADDR, 1);  // Request 1 byte from PCF8574

        if (Wire.available())
        {
            uint8_t inputs = Wire.read(); // Read input states

            for (int i = 0; i < 8; i++)
            {
                CHECK_ABORT(); 
                if (!io_passed[i])    // Only check pins not passed yet
                {
                    bool pressed = !(inputs & (1 << i));   // LOW = pressed

                    if (pressed)
                    {
                        Serial.print("$,IN,");
                        Serial.print(i);
                        Serial.println(",1,PASS,#");

                        io_passed[i] = true;
                        completed++;

                        delay(200);  // debounce time
                    }
                }
                CHECK_ABORT(); 
            }
        }
        CHECK_ABORT(); 
        delay(50);
    }

    // Check if timeout occurred
    for (int i = 0; i < 8; i++)
    {
        CHECK_ABORT(); 
        if (!io_passed[i])
        {
            Serial.print("$,INPUT,");
            Serial.print(i);
            Serial.println(",2,FAIL,BUTTON NOT PRESSED OR INPUT FAULT,#");  // Input not pressed in timeout
        }
    }
    CHECK_ABORT();  
}

#endif
