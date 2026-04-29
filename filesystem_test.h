
#ifndef FILESYSTEM_TEST_H
#define FILESYSTEM_TEST_H

#include "header.h"
#include "config.h"

void filesystem_test() 
{
    CHECK_ABORT();  // check before test

    if (!SPIFFS.begin(true)) 
    {
        Serial.println("$,FILESYSTEM,2,SPIFFS FAIL,Failed to mount SPIFFS,#");
        return;
    }

    // Create a test file
    File file = SPIFFS.open(SPIFFS_TEST_FILE, FILE_WRITE);
    if (!file) 
    {
        Serial.println("$,FILESYSTEM,2,SPIFFS FAIL,Failed to create file,#");
        return;
    }
    file.print(SPIFFS_TEST_CONTENT);
    file.close();

    // Read the test file
    file = SPIFFS.open(SPIFFS_TEST_FILE);
    if (!file) 
    {
        Serial.println("$,FILESYSTEM,2,SPIFFS FAIL,Failed to open file for reading,#");
        return;
    }
    
    String content = file.readString();
    file.close();
    content.trim();

    if (content == SPIFFS_TEST_CONTENT) 
    {
        Serial.println("$,FILESYSTEM,1,SPIFFS PASS,#");
    } 
    else 
    {
        Serial.println("$,FILESYSTEM,2,SPIFFS FAIL,File content mismatch,#");
    }
    ABORTABLE_DELAY(50);
    SPIFFS.end();

     CHECK_ABORT();  // check before next test
     
}



#endif