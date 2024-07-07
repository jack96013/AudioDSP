/*
 * @Author       : TZU-CHIEH, HSU
 * @Mail         : j.k96013@gmail.com
 * @Department   : ECIE Lab, NTUT
 * @Date         : 2024-06-15 17:52:41
 * @LastEditTime : 2024-07-01 17:12:53
 * @Description  :
 */

#include "LedController.h"
#include "ESPAudioDsp.h"

LedController::LedController()
{
    // this->pin = pin;
    // pinMode(pin, OUTPUT);
    // digitalWrite(pin, LOW);
}

void LedController::init()
{
    strip.begin(); // INITIALIZE NeoPixel strip object (REQUIRED)
    for (int i = 0; i < strip.numPixels(); i++)
    {
        strip.setPixelColor(i, strip.Color(255, 255, 255));
    }
    strip.setBrightness(50);

    strip.show();

    strip2.begin(); // INITIALIZE NeoPixel strip2 object (REQUIRED)
    strip2.setPixelColor(0, strip2.Color(0, 150, 0));
    strip2.setPixelColor(1, strip2.Color(150, 0, 0));
    strip2.show(); // Turn OFF all pixels ASAP

    softTimer.setTimeOutTime(100);
    softTimer.reset();
    
    
}

void LedController::loop()
{
    if (softTimer.hasTimedOut())
    {
        softTimer.reset();
        refresh();
    }
}

void LedController::setEnabled(bool enable)
{
    this->enable = enable;
}

bool LedController::isEnabled()
{
    return enable;
}

void LedController::test()
{
    // static uint32_t lastService = 0;
    // if (lastService + 100 < millis())
    // {
    //     lastService = millis();
    //     float percent = encoderValue / 100.0f;
    //     int num = 24 * percent;
    //     for (int i = 0; i < num; i++)
    //     {
    //         strip.setPixelColor(getWheelIndex(i), strip.Color((255 - 255.0 * (i / 23)), (255.0 * (i / 23.0)), 0));
    //     }
    //     for (int i = num; i < strip.numPixels(); i++)
    //     {
    //         strip.setPixelColor(getWheelIndex(i), strip.Color(255, 255, 255));
    //     }
    //     strip.show();
    // }
}

int LedController::mapLedIndex(int i)
{
    int newValue = 18 - i;
    if (newValue < 0)
    {
        return 23 - (newValue * -1 - 1);
    }
    else
        return newValue;
}

// 顯示光環
void LedController::showRing(float percent)
{
    int num = strip.numPixels() * percent;
    
    for (int i = 0; i < num; i++)
    {
        strip.setPixelColor(mapLedIndex(i), strip.Color((255 - 255.0 * (i / 23)), (255.0 * (i / 23.0)), 0));
    }
    for (int i = num; i < strip.numPixels(); i++)
    {
        strip.setPixelColor(mapLedIndex(i), strip.Color(255, 255, 255));
    }
    strip.setBrightness(50);
    strip.show();
}

void LedController::refresh()
{
    // showRing(audioManager.getVolume() / 100.0);
    showRing(audioManager.getVolume() / 100.0);
}
