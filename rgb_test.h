#ifndef RGB_TEST_H
#define RGB_TEST_H

#include <Adafruit_NeoPixel.h>
#include "config.h"

Adafruit_NeoPixel rgb(RGB_COUNT, RGB_PIN, NEO_GRB + NEO_KHZ800);   // create rgb object
void rgb_init()
{
    rgb.begin();
    rgb.show(); 
}

bool showColor(uint8_t r, uint8_t g, uint8_t b)
{
    rgb.setPixelColor(0, rgb.Color(r, g, b));
    rgb.show();
    if (cooperativeDelay(300)) return false;
    return true;
}

void rgb_test()
{
    Serial.println("RGB Test Started");
     CHECK_ABORT();
     
    bool pass = true;

    // RED
    if (!showColor(255, 0, 0)) pass = false;

    // GREEN
    if (!showColor(0, 255, 0)) pass = false;

    // BLUE
    if (!showColor(0, 0, 255)) pass = false;

    // YELLOW
    if (!showColor(255, 255, 0)) pass = false;

    // CYAN
    if (!showColor(0, 255, 255)) pass = false;

    // MAGENTA
    if (!showColor(255, 0, 255)) pass = false;

    // WHITE
    if (!showColor(255, 255, 255)) pass = false;

    // OFF
    showColor(0, 0, 0);

    // Clear NeoPixel data
    rgb.clear();
    rgb.show();
    ABORTABLE_DELAY(50);

    if (pass)
    Serial.println("$,RGB,1,PASS,#");
    else
    Serial.println("$,RGB,2,FAIL,#");
    update_test_result(TEST_RGB, pass);
    CHECK_ABORT();  
}


#endif
