#ifndef ETHERNET_TEST_H
#define ETHERNET_TEST_H

#include <SPI.h>
#include <Ethernet.h>
#include "config.h"

byte macAddr[] = 
{
    ETH_MAC_1, ETH_MAC_2, ETH_MAC_3,
    ETH_MAC_4, ETH_MAC_5, ETH_MAC_6
};

void ethernet_test() 
{ 
    Serial.println("Ethernet Test Started");
     CHECK_ABORT();  // check before test 
    bool pass = false;

    SPI.begin();
    Ethernet.init(ETH_CS_PIN); // set CS pin for SPI

    if (Ethernet.begin(macAddr) == 0)  // DHCP fail
    {
        update_test_result(TEST_ETHERNET, false);
        Serial.println("$,ETHERNET,2,FAIL,DHCP FAIL,#");  /// send fail responce
        return;
    }
     ABORTABLE_DELAY(200);
    if (Ethernet.linkStatus() == LinkON)    // check for link status
    {
        pass = true;
        IPAddress ip = Ethernet.localIP();

        Serial.printf("$,ETHERNET,1,PASS,%d.%d.%d.%d,#\n", ip[0], ip[1], ip[2], ip[3]);
    }
    else 
    {
        Serial.println("$,ETHERNET,2,FAIL,NO LINK,#");
    }

    update_test_result(TEST_ETHERNET, pass);

     CHECK_ABORT();  // ceck aftre test
    ABORTABLE_DELAY(100);
}

#endif
