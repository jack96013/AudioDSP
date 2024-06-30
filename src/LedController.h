/*
 * @Author       : TZU-CHIEH, HSU
 * @Mail         : j.k96013@gmail.com
 * @Department   : ECIE Lab, NTUT
 * @Date         : 2024-06-15 17:51:03
 * @LastEditTime : 2024-06-27 21:46:17
 * @Description  : 
 */

#ifndef __LEDCONTROLLER_H__
#define __LEDCONTROLLER_H__

#include "Arduino.h"
#include <Adafruit_NeoPixel.h>
#include "board.h"

class LedController
{
public:
    LedController();
    void init();
    void loop();

    void setEnabled(bool enabled);
    bool isEnabled();

    void test();

    void showRing(float perenct);

private:

    Adafruit_NeoPixel strip = Adafruit_NeoPixel(24, BOARD_RGB_LED_1_PIN, NEO_GRB + NEO_KHZ800);
    Adafruit_NeoPixel strip2 = Adafruit_NeoPixel(2, BOARD_RGB_LED_2_PIN, NEO_GRB + NEO_KHZ800);

    bool enable = true;

    int mapLedIndex(int i);

};

#endif