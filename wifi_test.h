#ifndef WIFI_TEST_H
#define WIFI_TEST_H

#include <WiFi.h>
#include "config.h"
#include "secrets.h"  // Include secrets for Wi-Fi credentials

// Function to START WiFi test
void wifi_test() 
{
    Serial.println("WiFi Test Started");
    CHECK_ABORT();  // check before test 
    bool pass = false;
    // if wifi is already connected skip the test 
    if (WiFi.status() == WL_CONNECTED)
    {
        pass = true;
        update_test_result(TEST_WIFI, pass);
        Serial.println("$,WIFI,1,PASS,ALREADY CONNECTED TO IP:" + WiFi.localIP().toString() + ",#");  /// send responce 
        return;
    }

    WiFi.mode(WIFI_STA);  // Set WiFi to station mode
    WiFi.disconnect(true);  // Disconnect from any previous connections
    ABORTABLE_DELAY(1000);

    WiFi.begin(WIFI_SSID, WIFI_PASSWORD);  // Connect to the specified SSID
    ABORTABLE_DELAY(1000);

    // Wait for connection with timeout
    unsigned long start = millis();
    while (WiFi.status() != WL_CONNECTED && millis() - start < WIFI_TIMEOUT)
    {
        CHECK_ABORT();
        ABORTABLE_DELAY(10);
    }

    if (WiFi.status() == WL_CONNECTED)   // Connected successfully
    {
        pass = true;
        Serial.println("$,WIFI,1,PASS,IP:" + WiFi.localIP().toString() + ",#");  /// PASS RESPONSE 
    } 
    else   // Failed to connect
    {
        Serial.println("$,WIFI,2,FAIL,ERROR CODE - " + String(WiFi.status()) + ",#");  // FAIL RESPONSE   
    }
    update_test_result(TEST_WIFI, pass);
    CHECK_ABORT();  
    ABORTABLE_DELAY(100);  // Short delay for next operations
}

#endif
