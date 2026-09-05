#ifndef RS485_TEST_h
#define RS485_TEST_h

#include "config.h"

ModbusMaster node;  // Create ModbusMaster object

uint8_t result;    // Variable to store Modbus result
uint16_t value;    // Variable to store read value

void rs485_test() 
{ 
    bool pass = false;
    Serial2.begin(9600, SERIAL_8N1, RS485_TX, RS485_RX);
    delay(50);
    node.begin(Serial2);    // Modbus serial port
    result = node.readHoldingRegisters(1, 0, 1);   // Slave ID 1, read 1 register starting at address 0
    if(result == node.ku8MBSuccess)
    {
        pass = true;
        value = node.getResponseBuffer(0);
        Serial.println("$,RS485,1,PASS,VALUE: " + String(value));
    }
    else
    {
        Serial.println("$,RS485,2,FAIL,ERROR CODE : " + String(result) + ",#");
    }
    update_test_result(TEST_RS485, pass);
    delay(50);
    Serial2.end();
}


#endif