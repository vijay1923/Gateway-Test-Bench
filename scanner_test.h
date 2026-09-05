#ifndef SCANNER_TEST_H
#define SCANNER_TEST_H

#include <Arduino.h>
#include <usb_scanner_Lib.h>

bool scanReceived = false;  
String lastBarcode = "";
int lastLen = 0;
bool scannerUsbInitialized = false;
// callback function to handle scanned barcode
void onBarcodeScanned(const char *barcode, int length)
{
    if (!scanReceived)            
    {
        scanReceived = true;  // set flag to indicate scan received
        lastBarcode = String(barcode);  // store scanned barcode
        lastLen     = length;  // store barcode length

    }
}

void scanner_test()
{
   Serial.println("Scanner Test Started");
   
    CHECK_ABORT();  
    scanReceived = false;
    lastBarcode  = ""; 
    lastLen      = 0;

    if (!scannerUsbInitialized)
    {
        usb_scannerInit();
        scannerUsbInitialized = true;
    }
    set_barcode_callback(onBarcodeScanned);

    unsigned long start = millis();
    while (millis() - start < 5000)
    {
        CHECK_ABORT();
        if (scanReceived)
            break;

        ABORTABLE_DELAY(10);
    }

    if (scanReceived)
    {
        Serial.print("$,SCANNER,1,PASS,");
        Serial.print(lastBarcode);
        Serial.print(",LEN=");
        Serial.print(lastLen);
        Serial.println(",#");
    }
    else
    {
        Serial.println("$,SCANNER,2,FAIL,#");
    }

    update_test_result(TEST_SCANNER, scanReceived);

   CHECK_ABORT();  
}

#endif
