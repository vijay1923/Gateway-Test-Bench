#line 1 "C:\\Users\\Shree\\Documents\\Arduino\\Embedsol\\Gateway_TestBenach\\periferal_testing\\wifi_test.h"
#ifndef WIFI_TEST_H
#define WIFI_TEST_H

#include <WiFi.h>
#include "config.h"

// Function to START WiFi test
void wifi_test() 
{
    Serial.println("WiFi Test Started");
    CHECK_ABORT();  // check before test 
    // if wifi is already connected skip the test 
    if (WiFi.status() == WL_CONNECTED)
    {
        Serial.println("$,WIFI,1,PASS,ALREADY CONNECTED TO ," + WiFi.localIP().toString() + ",#");  /// send responce 
        return;
    }

    WiFi.mode(WIFI_STA);  // Set WiFi to station mode
    WiFi.disconnect(true);  // Disconnect from any previous connections
    delay(1000);

    WiFi.begin(WIFI_SSID, WIFI_PASSWORD);  // Connect to the specified SSID
    delay(1000);

    // Wait for connection with timeout
    unsigned long start = millis();
    while (WiFi.status() != WL_CONNECTED && millis() - start < WIFI_TIMEOUT) {}  

    if (WiFi.status() == WL_CONNECTED)   // Connected successfully
    {
        Serial.println("$,WIFI,1,PASS," + WiFi.localIP().toString() + ",#");  /// PASS RESPONSE 
    } 
    else   // Failed to connect
    {
        Serial.println("$,WIFI,2,FAIL, ERROR CODE - " + String(WiFi.status()) + ",#");  // FAIL RESPONSE   
    }
    CHECK_ABORT();  
    delay(100);  // Short delay for next operations
}

#endif
