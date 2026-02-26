#ifndef PCF_TEST_H
#define PCF_TEST_H

#include <Wire.h>
#include "config.h"

#define PCF1_ADDR 0x25
#define PCF2_ADDR 0x26

void pcf1_test()
{
    Serial.println("PCF 1 test started ");
    CHECK_ABORT();  
    Wire.begin(I2C_SDA, I2C_SCL);

    bool foundPCF1 = false;

    uint8_t addr;
    // Scan I2C for PCF1
    for ( addr = 1; addr < 127; addr++)
    {
        Wire.beginTransmission(addr);
        if (Wire.endTransmission() == 0)
        {
            if (addr == PCF1_ADDR)
            {
                foundPCF1 = true;
                break;
            }
        }
    }

    if (foundPCF1) // if found at address
    Serial.printf("$,PCF1,1,PASS,0X%02X,#\n",addr);
    else
    Serial.println("$,PCF1,2,FAIL,#");

    CHECK_ABORT(); 
    delay(100);     
}

void pcf2_test()
{
    Serial.println("PCF 2 test started ");
    CHECK_ABORT();  
    Wire.begin(I2C_SDA, I2C_SCL);

    bool foundPCF2 = false;
    uint8_t addr;
    // Scan I2C for PCF2
    for ( addr = 1; addr < 127; addr++)
    {
        Wire.beginTransmission(addr);
        if (Wire.endTransmission() == 0)
        {
            if (addr == PCF2_ADDR)
            { 
                foundPCF2 = true;
                break;
            }   
        }
    }

    if (foundPCF2)  // if found at address
    Serial.printf("$,PCF2,1,PASS,0x%02X,#\n", addr);
    else
    Serial.println("$,PCF2,2,FAIL,#");
    CHECK_ABORT();
    delay(100);  
}

#endif
