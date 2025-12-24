#ifndef RTC_TEST_H
#define RTC_TEST_H

#include <Wire.h>
#include <RTClib.h>
#include <time.h>
#include "config.h"

RTC_DS3231 rtc;   // rtc object 

void rtc_test()
{
    CHECK_ABORT();  
    if (WiFi.status() != WL_CONNECTED) 
        wifi_test();  

    Wire.begin(I2C_SDA, I2C_SCL);
    delay(100);

    if (!rtc.begin())
    {
        Serial.println("$,RTC,2,FAIL,RTC NOT DETECTED,#");
        return;
    }

    configTime(GMT_OFFSET_SEC, DAYLIGHT_OFFSET, NTP_SERVER);

    struct tm timeinfo;

    if (!getLocalTime(&timeinfo)) 
    {
        Serial.println("$,RTC,2,FAIL,NTP SERVER,#");
        return;
    }

    // Convert NTP → RTC
    DateTime ntpTime
    (
        timeinfo.tm_year + 1900,
        timeinfo.tm_mon + 1,
        timeinfo.tm_mday,
        timeinfo.tm_hour,
        timeinfo.tm_min,
        timeinfo.tm_sec
    );

    rtc.adjust(ntpTime);

    DateTime t1 = rtc.now();
    delay(5000);
    DateTime t2 = rtc.now();

    int diff = t2.second() - t1.second();
    if (diff < 0) diff += 60;

    if (diff >= 5) // respond passs with current time
    Serial.printf("$,RTC,1,PASS,%02d:%02d:%02d,#\n",t2.hour(), t2.minute(), t2.second());
    else
    Serial.println("$,RTC,2,FAIL,RTC TIME NOT INCREASING,#");

    CHECK_ABORT(); 
    delay(100);
    
}

#endif
