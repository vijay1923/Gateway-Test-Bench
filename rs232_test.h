#ifndef RS232_TEST_h
#define RS232_TEST_h

#include "config.h"

void rs232_test() 
{ 
    // Serial1.begin(9600, SERIAL_8N1, RS232_RX_PIN, RS232_TX_PIN);
    // Serial.println("RS232 Test Started");

     CHECK_ABORT();  // check before test   
     Serial.println("$,RS232,2,FAIL,#"); 

}


#endif 