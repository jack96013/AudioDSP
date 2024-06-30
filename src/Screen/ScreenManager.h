#ifndef __SCREENMANAGER_H__
#define __SCREENMANAGER_H__

#include <Arduino.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <SoftTimers.h>
#include "Resource/ECIE_LOGO_80x50.h"
#include "board.h"


#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64

enum class ScreenManagerLayout
{
    IDLE,
    STARTUP,
    LOADING,
    MAIN_MENU,
    SETTINGS,
};


class ScreenManager
{
    public:
    ScreenManager();
    void init();
    void loop();
    
    void showStartUpScreen();

    void switchLayout(ScreenManagerLayout layout);


    
    
    private:
    Adafruit_SSD1306 display = Adafruit_SSD1306(SCREEN_WIDTH, SCREEN_HEIGHT,
                           BOARD_OLED_MOSI_PIN, BOARD_OLED_SCK_PIN, BOARD_OLED_DC_PIN, BOARD_OLED_RES_PIN, BOARD_OLED_CS_PIN);

    void handle();

    ScreenManagerLayout layout = ScreenManagerLayout::IDLE;
    
    SoftTimer refreshTimer;
    SoftTimer pendingTimer;

    bool isInitialized();
    void finishInitialization();
    bool initialized;
    
};

#endif
