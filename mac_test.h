#ifndef MAC_TEST_H
#define MAC_TEST_H

#include <Arduino.h>
#include "esp_mac.h"  //  esp_read_mac api and esp_mac_type_t 
#include "esp_err.h"  // esp_err_t and ESP_OK   

void mac_test()
{
    Serial.println("MAC Address Test Started");
    CHECK_ABORT();
    uint8_t mac[6]; // Array to hold the MAC address

    /*  this api reads the MAC address of the WiFi station interface, 
        which is typically used for network communication. 
        The MAC address is stored in the provided array mac, 
        and the function returns an error code indicating success or failure. */
    esp_err_t err = esp_read_mac(mac, ESP_MAC_WIFI_STA);  
    if (err == ESP_OK) // on success print mac address in standard format
    {
        Serial.print("$,MAC,1,PASS");
        Serial.printf("%02X:%02X:%02X:%02X:%02X:%02X", mac[0], mac[1], mac[2], mac[3], mac[4], mac[5]);  // Print MAC in standard format
        Serial.println("#");
    }
    else
    {
        Serial.println("$,MAC,2,FAIL,#");
    }

    CHECK_ABORT();  
}

#endif
