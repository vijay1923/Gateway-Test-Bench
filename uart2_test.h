#ifndef UART2_TEST_H    
#define UART2_TEST_H


#include "config.h"

void uart2_test()
{
    Serial.println("UART2 Test Started");
    CHECK_ABORT();  // check before test 
    bool pass = false;

    Serial2.begin(SERIAL_BAUD, SERIAL_8N1, UART2_RX, UART2_TX);
    Serial2.println("UART2 Test Message");

    unsigned long start = millis();
    while (Serial2.available() == 0 && millis() - start < 5000)
    {
        CHECK_ABORT();
        ABORTABLE_DELAY(10);
    }
    if (Serial2.available() > 0)   // Response received
    {
        pass = true;
        String response = Serial2.readStringUntil('\n');  
        Serial.println("$,UART2,1,PASS,RESPONSE: " + response); 
    } 
    else  
    {
        Serial.println("$,UART2,2,FAIL,NO RESPONSE,#"); 
    }

    update_test_result(TEST_UART2, pass);

    CHECK_ABORT();



}



#endif