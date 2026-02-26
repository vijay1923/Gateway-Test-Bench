#ifndef RESET_TEST_H
#define RESET_TEST_H    

#include "config.h"
#include "header.h"


void reset_test_init()
{
    CHECK_ABORT(); 
    EEPROM.begin(EEPROM_SIZE);  // Initialize EEPROM with defined size
    EEPROM.write(RESET_EEPROM_ADDR, RESET_ARMED);  // writing armed state at defined address
    EEPROM.commit();
    CHECK_ABORT(); 
}


void reset_test()
{
    Serial.println("Reset Test Started");
     CHECK_ABORT();  
     EEPROM.begin(EEPROM_SIZE);  // Initialize EEPROM with defined size 
    byte state = EEPROM.read(RESET_EEPROM_ADDR);
    if (state == RESET_ARMED)   // if prior state is armed then reset 
    {
        Serial.println("$,RESET,1,PASS,#");
        delay(500);
        ESP.restart();
    }
    else
    {
        Serial.println("$,RESET,2,FAIL,#");
    }
    CHECK_ABORT();  
}

#endif