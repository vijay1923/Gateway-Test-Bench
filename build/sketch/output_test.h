#line 1 "C:\\Users\\Shree\\Documents\\Arduino\\Embedsol\\Gateway_TestBenach\\periferal_testing\\output_test.h"
#ifndef OUTPUT_TEST_H
#define OUTPUT_TEST_H   

#include <Wire.h>
#include "config.h"

void output_test()
{
    Serial.println("output test started ");
    CHECK_ABORT();  
    Wire.begin(I2C_SDA, I2C_SCL);  // initilizing I2C Bus 
    delay(100);

    Wire.beginTransmission(PCF2_ADDR);  
    Wire.write(0x00);  // all outputs LOW
    Wire.endTransmission();  // Send data
    delay(100);

    bool io_passed[8] = {false,false,false,false,false,false,false,false};  // Track passed outputs

    unsigned long startTime = millis();

    for (int i = 0; i < 8; i++)
    {
        CHECK_ABORT(); 
        // Set only the i th output other low 
        byte outByte = 0x00;
        outByte |= (1 << i);  // set the perticuler bit at i th position  

        Wire.beginTransmission(PCF2_ADDR);   
        Wire.write(outByte); // write at pcf /tern on theperticuler output 
        Wire.endTransmission();

        bool received = false;
        unsigned long pinStartTime = millis();

        while (!received && (millis() - pinStartTime) < 1000)
        {
            CHECK_ABORT(); 
            Wire.requestFrom(PCF1_ADDR, 1);   /// Request 1 byte from pcf1 of input expander
            if (Wire.available())
            {
                uint8_t inputs = Wire.read();  // geting 
                if (inputs & (1 << i))  
                {
                    received = true;
                    io_passed[i] = true;
                    Serial.print("$,OUT,");
                    Serial.print(i);
                    Serial.println(",1,PASS,#");
                    break;
                }
            }
            delay(50);
            CHECK_ABORT(); 
        }
        
        if (!received)
        {
            Serial.print("$,OUT,");
            Serial.print(i);
            Serial.println(",2,FAIL,#");
        }
        CHECK_ABORT(); 
        delay(200); // delay for next output
    }

    // Reset all outputs LOW after test
    Wire.beginTransmission(PCF2_ADDR);   // pcf2 of output expander
    Wire.write(0x00);
    Wire.endTransmission();
    CHECK_ABORT();  
}

#endif
