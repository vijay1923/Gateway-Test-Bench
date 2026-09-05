
#ifndef FILESYSTEM_TEST_H
#define FILESYSTEM_TEST_H

#include "header.h"
#include "config.h"

void filesystem_test() 
{
    Serial.println("FILESYSTEM Test Started");
    CHECK_ABORT();  // check before test
    bool pass = false;

    if (!SPIFFS.begin(true)) 
    {
        update_test_result(TEST_FILESYSTEM, false);
        Serial.println("$,FILESYSTEM,2,SPIFFS FAIL,Failed to mount SPIFFS,#");
        return;

    }

    // Create a test file
    File file = SPIFFS.open(SPIFFS_TEST_FILE, FILE_WRITE);
    if (!file) 
    {
        update_test_result(TEST_FILESYSTEM, false);
        Serial.println("$,FILESYSTEM,2,SPIFFS FAIL,Failed to create file,#");
        return;
    }
    file.print(SPIFFS_TEST_CONTENT);
    file.close();

    // Read the test file
    file = SPIFFS.open(SPIFFS_TEST_FILE);
    if (!file) 
    {
        update_test_result(TEST_FILESYSTEM, false);
        Serial.println("$,FILESYSTEM,2,SPIFFS FAIL,Failed to open file for reading,#");
        return;
    }
    
    String content = file.readString();
    file.close();
    content.trim();

    if (content == SPIFFS_TEST_CONTENT) 
    {
        pass = true;

        // Free RAM
        // Serial.print("Free heap: ");
        // Serial.print(ESP.getFreeHeap());
        // Serial.println(" bytes");

        // Serial.print("Largest allocatable block: ");
        // Serial.print(ESP.getMaxAllocHeap());
        // Serial.println(" bytes");

        // Free SPIFFS storage
        // size_t freeFlash = SPIFFS.totalBytes() - SPIFFS.usedBytes();

        // Serial.print("SPIFFS free: ");
        // Serial.print(freeFlash);
        // Serial.println(" bytes");

        Serial.print("$,FILESYSTEM,1,SPIFFS PASS,");
        
        // Serial.print(freeFlash);
        // Serial.println(" bytes,#");
    } 
    else 
    {
        Serial.println("$,FILESYSTEM,2,SPIFFS FAIL,File content mismatch,#");
    }
    update_test_result(TEST_FILESYSTEM, pass);
    ABORTABLE_DELAY(50);
    SPIFFS.end();

     CHECK_ABORT();  // check before next test
     
}



#endif