#line 1 "C:\\Users\\Shree\\Documents\\Arduino\\Embedsol\\Gateway_TestBenach\\periferal_testing\\mqtt_test.h"
#ifndef MQTT_TEST_H
#define MQTT_TEST_H

#include <WiFi.h>
#include <PubSubClient.h>
#include "config.h"
#include "wifi_test.h"

#define TEST_BENCH_TOPIC "Gateway/TestBench"   // mqtt topic 

WiFiClient wifiClient;
PubSubClient mqttClient(wifiClient);

void mqtt_test()
{
    Serial.println("MQTT Test Started");
    CHECK_ABORT();  
    if (WiFi.status() != WL_CONNECTED)   // check wifi is connected or not 
    wifi_test();  
    
    if (WiFi.status() != WL_CONNECTED) 
    {
        Serial.println("$,MQTT,2,FAIL,NO WIFI,#");
        return;
    }  
    if (mqttClient.connected())   //  Disconnect previous  MQTT connections 
    {
        mqttClient.disconnect();
        delay(50);
        CHECK_ABORT(); 
    }

    mqttClient.setServer(mqtt_server, mqtt_port); // Configure MQTT broker
    String clientId = "TestBench-" + WiFi.macAddress();  // Use MAC address as unique client ID
    bool ok = mqttClient.connect(clientId.c_str(), mqtt_user, mqtt_pass); // Connect to MQTT broker
  
    if (ok)
    {
        Serial.println("$,MQTT,1,PASS,#");  
        mqttClient.publish(TEST_BENCH_TOPIC, "Gateway Test Bench Online");  //  Publish topic 
        mqttClient.subscribe(TEST_BENCH_TOPIC);   // subscribe  to same topic 
    }
    else 
    {
        Serial.print("$,MQTT,2,FAIL,");
        Serial.print(mqttClient.state());  
        Serial.println(",#");
    }
    CHECK_ABORT(); 
    delay(200);
     
}

#endif
