#include "ScreenManager.h"
#include "ESPAudioDsp.h"

ScreenManager::ScreenManager()
{
}

void ScreenManager::init()
{
    display.begin();
    showStartUpScreen();

    refreshTimer.setTimeOutTime(100);
    refreshTimer.reset();
}

void ScreenManager::loop()
{
    handle();
}

void ScreenManager::handle()
{
    switch (layout)
    {
    case ScreenManagerLayout::IDLE:
    {
        display.clearBuffer();
        layout = ScreenManagerLayout::STARTUP;
        break;
    }
    case ScreenManagerLayout::STARTUP:
    {
        page_startup();
        break;
    }
    case ScreenManagerLayout::LOADING:
    {
        break;
    }
    case ScreenManagerLayout::MAIN_MENU:
    {
        page_main_menu();
        break;
    }
    case ScreenManagerLayout::SETTINGS:
    {
        break;
    }
    }
}

void ScreenManager::showStartUpScreen()
{
    display.clearBuffer();
    display.setFont(u8g2_font_ncenB14_tr);
    display.drawStr(5, 28, "ECIE LAB");
    display.sendBuffer();
}

bool ScreenManager::isInitialized()
{
    return initialized;
}

void ScreenManager::finishInitialization()
{
    initialized = true;
}

void ScreenManager::switchLayout(ScreenManagerLayout layout)
{
    if (this->layout == layout)
        return;
    this->layout = layout;
    this->initialized = false;
}

void ScreenManager::page_startup()
{
    if (!isInitialized())
    {
        display.clearBuffer();
        display.setDrawColor(1);
        display.setFont(u8g2_font_ncenB14_tr);
        display.drawStr(60, 25, "ECIE");
        display.drawXBM(5, 15, 40, 25, resource_ecie_logo);
        display.setFont(u8g2_font_ncenB08_tr);
        display.drawStr(60, 42, "IFEEC 2024");
        display.sendBuffer();

        finishInitialization();

        refreshTimer.setTimeOutTime(5000);
        refreshTimer.reset();
    }
    else
    {
        if (refreshTimer.hasTimedOut())
        {
            switchLayout(ScreenManagerLayout::MAIN_MENU);
        }
    }
}

void ScreenManager::page_loading()
{
}

void ScreenManager::page_main_menu()
{
    if (!isInitialized())
        {
            refreshTimer.setTimeOutTime(100);
            refreshTimer.reset();
            finishInitialization();
        }
        else
        {
            if (!refreshTimer.hasTimedOut())
                return;
            refreshTimer.reset();

            display.clearBuffer();
            display.setDrawColor(1);
            // display.setFont(u8g2_font_ncenB08_tr);
            // display.drawStr(100, 12, "VOL");
            display.setFont(u8g2_font_ncenB14_tr);
            int volume = audioManager.getVolume();
            display.setCursor(90, 14);
            display.print(volume);

            display.setFont(u8g2_font_ncenB10_tr);
            display.setCursor(30, 14);
            display.print(classD.settings.volume);

            if (audioManager.getSource() == AudioSource::XLR1)
            {
                int start_x = 8;
                int start_y = 12;
                display.setColorIndex(1);
                display.drawDisc(start_x + 10, start_y + 10, 10, U8G2_DRAW_ALL);

                display.setColorIndex(0);
                display.drawDisc(start_x + 10, start_y + 10, 8);
                display.setColorIndex(1);
                display.drawBox(start_x + 5, start_y + 2, 11, 3);
                display.drawDisc(start_x + 6, start_y + 10, 1);
                display.drawDisc(start_x + 14, start_y + 10, 1);
                display.drawDisc(start_x + 10, start_y + 15, 1);
                display.setColorIndex(1);
                display.setFont(u8g2_font_ncenB14_tr);
                display.drawStr(40, 30, "XLR");
            }
            else if (audioManager.getSource() == AudioSource::XLR2)
            {
                int start_x = 8;
                int start_y = 12;
                display.setColorIndex(1);
                display.drawDisc(start_x + 10, start_y + 10, 10, U8G2_DRAW_ALL);

                display.setColorIndex(0);
                display.drawDisc(start_x + 10, start_y + 10, 8);
                display.setColorIndex(1);
                display.drawBox(start_x + 5, start_y + 2, 11, 3);
                display.drawDisc(start_x + 6, start_y + 10, 1);
                display.drawDisc(start_x + 14, start_y + 10, 1);
                display.drawDisc(start_x + 10, start_y + 15, 1);
                display.setColorIndex(1);
                display.setFont(u8g2_font_ncenB14_tr);
                display.drawStr(40, 30, "XLR-DSP");
            }
            else if (audioManager.getSource() == AudioSource::BT)
            {
                // display.drawXBM(5, 8, 24, 24, resource_bluetooth);
                // display.setFont(u8g2_font_ncenB14_tr);
                // display.drawStr(40, 30, "BT");
                static int offset = 0;
                display.setFont(u8g2_font_open_iconic_embedded_2x_t); // 選擇圖示字體
                display.drawGlyph(5, 16, 74);                         // 繪製藍牙圖示 (參考字體中的圖示碼)
                display.setFont(u8g2_font_unifont_t_chinese1);        // 設置字體
                const char *message = btAudio.getTrackTitle().c_str();
                int textWidth = display.getStrWidth(message);
                int displayWidth = 100;
                int tempWidth = 0;
                int visibleChars = 0;
                while (tempWidth < displayWidth && message[visibleChars] != '\0')
                {
                    tempWidth += display.getStrWidth(&message[visibleChars]);
                    if (tempWidth <= displayWidth)
                    {
                        visibleChars++;
                    }
                }
                if (offset + visibleChars < strlen(message))
                {
                    display.drawStr(0, 30, &message[offset]);
                }
                else
                {
                    // 當超過字符串尾部時，重新開始顯示
                    int firstPart = strlen(message) - offset;
                    display.drawStr(0, 30, &message[offset]);
                    display.drawStr(display.getStrWidth(&message[offset]), 30, message);
                }
                offset += 1; // 增加偏移量以實現滾動效果

                // 當 offset 超過字符串長度時重置為 0
                if (offset >= strlen(message))
                {
                    offset = 0;
                }

                display.setColorIndex(1); // 设置为白色
                // Serial.print("OFFSET = ");
                // Serial.print(offset);

                int padding = 10;
                int width = (float)(SCREEN_WIDTH - 2 * padding) * btAudio.getTrackProgress();

                display.drawBox(0 + padding, SCREEN_HEIGHT * 0.5 + 2, width, 2); // 绘制进度条
            }
            else if (audioManager.getSource() == AudioSource::USB)
            {
                int start_x = 8;
                int start_y = 12;
                display.setColorIndex(1);
                display.drawDisc(start_x + 10, start_y + 10, 10, U8G2_DRAW_ALL);

                display.setColorIndex(0);
                display.drawDisc(start_x + 10, start_y + 10, 8);
                display.setColorIndex(1);
                display.drawBox(start_x + 5, start_y + 2, 11, 3);
                display.drawDisc(start_x + 6, start_y + 10, 1);
                display.drawDisc(start_x + 14, start_y + 10, 1);
                display.drawDisc(start_x + 10, start_y + 15, 1);
                display.setColorIndex(1);
                display.setFont(u8g2_font_ncenB14_tr);
                display.drawStr(40, 30, "USB");
            }

            // 生成隨機的 FFT 數據
            int size = 7;
            uint8_t fftData[size];
            for (int i = 0; i < size; i++)
            {
                if (audioDSP.fft_data[i] == INFINITY)
                {
                    fftData[i] = 0;
                }
                else
                {
                    if (audioDSP.fft_data[i] >= -10.0f)
                        audioDSP.fft_data[i] = -10.0f;
                    if (audioDSP.fft_data[i] <= -30.0f)
                        audioDSP.fft_data[i] = -30.0f;

                    fftData[i] = ((audioDSP.fft_data[i] - (-30.0f)) / 20.0f) * (SCREEN_HEIGHT) * 2;
                    if (fftData[i] >= SCREEN_HEIGHT * 0.5)
                    {
                        fftData[i] = SCREEN_HEIGHT * 0.5;
                    }
                }
            }

            int barWidth = SCREEN_WIDTH / size; // 計算每個條的寬度

            for (int i = 0; i < size; i++)
            {
                display.drawBox(i * barWidth + 2, SCREEN_HEIGHT - fftData[i], barWidth - 2, fftData[i]);
            }

            display.sendBuffer();
        }
}

void ScreenManager::page_settings()
{
    
}
