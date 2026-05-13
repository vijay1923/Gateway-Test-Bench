#ifndef MQTT_TEST_H
#define MQTT_TEST_H

#include <WiFi.h>
#include <PubSubClient.h>
#include "config.h"
#include "wifi_test.h"
#include "secrets.h"  // Include secrets for MQTT credentials

#define TEST_BENCH_TOPIC "Gateway/TestBench"   // mqtt topic 

WiFiClient wifiClient;
PubSubClient mqttClient(wifiClient);

void mqtt_test()
{
    Serial.println("MQTT Test Started");
    CHECK_ABORT();  
    bool pass = false;
    if (WiFi.status() != WL_CONNECTED)   // check wifi is connected or not 
    wifi_test();  
    
    if (WiFi.status() != WL_CONNECTED) 
    {
        update_test_result(TEST_MQTT, false);
        Serial.println("$,MQTT,2,FAIL,NO WIFI,#");
        return;
    }  
    if (mqttClient.connected())   //  Disconnect previous  MQTT connections 
    {
        mqttClient.disconnect();
        ABORTABLE_DELAY(50);
        CHECK_ABORT(); 
    }

    mqttClient.setServer(MQTT_SERVER, MQTT_PORT); // Configure MQTT broker
    String clientId = "TestBench-" + WiFi.macAddress();  // Use MAC address as unique client ID
    bool ok = mqttClient.connect(clientId.c_str(), MQTT_USER, MQTT_PASS); // Connect to MQTT broker
  
    if (ok)
    {
        pass = true;
        Serial.println("$,MQTT,1,PASS,#");  
        mqttClient.publish(TEST_BENCH_TOPIC, "Gateway Test Bench");  //  Publish topic 
        mqttClient.subscribe(TEST_BENCH_TOPIC);   // subscribe  to same topic 
    }
    else 
    {
        Serial.print("$,MQTT,2,FAIL,");
        Serial.print(mqttClient.state());  
        Serial.println(",#");
    }
    update_test_result(TEST_MQTT, pass);
    CHECK_ABORT(); 
    ABORTABLE_DELAY(200);
     
}

#endif
