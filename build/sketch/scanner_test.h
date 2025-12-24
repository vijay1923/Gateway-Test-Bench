#line 1 "C:\\Users\\Shree\\Documents\\Arduino\\Gateway_TestBenach\\periferal_testing\\scanner_test.h"
// #ifndef SCANNER_TEST_H
// #define SCANNER_TEST_H

// #include <Arduino.h>
// #include <usb_scanner_Lib.h>

// bool scanReceived = false;  
// String lastBarcode = "";
// int lastLen = 0;
// // callback function
// void onBarcodeScanned(const char *barcode, int length)
// {
//     if (!scanReceived)            
//     {
//         scanReceived = true;
//         lastBarcode = String(barcode);
//         lastLen     = length;
//     }
// }

// void scanner_test()
// {
   
 //       CHECK_ABORT();  
//     scanReceived = false;
//     lastBarcode  = "";
//     lastLen      = 0;

//     usb_scannerInit();
//     set_barcode_callback(onBarcodeScanned);

//     unsigned long start = millis();
//     while (millis() - start < 5000)
//     {
//         if (scanReceived)
//             break;
//     }

//     if (scanReceived)
//     {
//         Serial.print("$,SCANNER,1,PASS,");
//         Serial.print(lastBarcode);
//         Serial.print(",LEN=");
//         Serial.print(lastLen);
//         Serial.println(",#");
//     }
//     else
//     {
//         Serial.println("$,SCANNER,2,FAIL,#");
//     }

//    CHECK_ABORT();  
// }

// #endif
