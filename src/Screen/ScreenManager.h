#ifndef __SCREENMANAGER_H__
#define __SCREENMANAGER_H__

#include <Arduino.h>
#include <U8g2lib.h>
#include <SoftTimers.h>
#include "Resource/ECIE_LOGO_80x50.h"
#include "board.h"


// #define SCREEN_TYPE_SH1106

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
#ifdef SCREEN_TYPE_SH1106
    U8G2_SH1106_128X64_NONAME_F_4W_HW_SPI  display = U8G2_SH1106_128X64_NONAME_F_4W_HW_SPI(U8G2_R0, /* cs=*/ BOARD_OLED_CS_PIN, /* dc=*/ BOARD_OLED_DC_PIN, /* reset=*/ BOARD_OLED_RES_PIN);
#else
    U8G2_SSD1306_128X64_NONAME_F_4W_HW_SPI  display = U8G2_SSD1306_128X64_NONAME_F_4W_HW_SPI(U8G2_R0, /* cs=*/ BOARD_OLED_CS_PIN, /* dc=*/ BOARD_OLED_DC_PIN, /* reset=*/ BOARD_OLED_RES_PIN);
#endif

    void handle();

    ScreenManagerLayout layout = ScreenManagerLayout::IDLE;
    
    SoftTimer refreshTimer;
    SoftTimer pendingTimer;

    bool isInitialized();
    void finishInitialization();
    bool initialized;
};

#endif