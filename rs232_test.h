#ifndef RS232_TEST_h
#define RS232_TEST_h

#include "config.h"

// RS232 Test using Serial1
// This test sends a message over Serial1 and waits for a response to verify RS232 communication.

void rs232_test() 
{ 
    bool pass = false;
    Serial1.begin(9600, SERIAL_8N1, RS232_RX, RS232_TX);
    Serial1.println("RS232 Test Message");

    unsigned long start = millis();
    while (Serial1.available() == 0 && millis() - start < 5000)
    {
        CHECK_ABORT();
        ABORTABLE_DELAY(10);
    }
    if (Serial1.available() > 0)   // Response received
    {
        pass = true;
        String response = Serial1.readStringUntil('\n');  
        Serial.println("$,RS232,1,PASS,RESPONSE: " + response + ",#"); 
    } 
    else  
    {
        Serial.println("$,RS232,2,FAIL,NO RESPONSE,#"); 
    }

    update_test_result(TEST_RS232, pass);

    CHECK_ABORT();
}


#endif 