#ifndef RS485_TEST_h
#define RS485_TEST_h

#include "config.h"


void rs485_test() 
{ 
    // Serial2.begin(9600, SERIAL_8N1, RS485_RX_PIN, RS485_TX_PIN);
    // Serial.println("RS485 Test Started");
    
     CHECK_ABORT();  // check before test   
     Serial.println("$,RS485,2,FAIL,#"); 

}


#endif