#include "ScreenManager.h"
#include "ESPAudioDsp.h"

ScreenManager::ScreenManager()
{
}

void ScreenManager::init()
{
    if (!display.begin(SSD1306_SWITCHCAPVCC))
    {
        Serial.println(F("SSD1306 allocation failed"));
        for (;;)
            ;
    }
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
            display.clearDisplay();
            layout = ScreenManagerLayout::STARTUP;
            
            break;
        }
        case ScreenManagerLayout::STARTUP:
        {
            if (!isInitialized())
            {
                display.clearDisplay();
                display.setTextColor(WHITE);
                display.setTextSize(2);
                display.setCursor(60, 15);
                display.println("ECIE");
                display.drawBitmap(5, 15, resource_ecie_logo, 40, 25, 1);
                display.setCursor(60, 32);
                display.setTextSize(1);
                display.println("IFEEC 2024");
                display.display();

                finishInitialization(); // Finish

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
            
            break;
        }
        case ScreenManagerLayout::LOADING:
        {
            
        }
        case ScreenManagerLayout::MAIN_MENU:
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

                display.clearDisplay();
                display.setTextColor(WHITE);
                display.setTextSize(1);
                // 音量
                display.setCursor(100, 5);
                display.println("VOL");
                display.setTextSize(2);
                display.setCursor(90, 15);
                int volume = audioManager.getVolume();
                
                display.println(String(volume));
                

                if (audioManager.getSource() == AudioSource::XLR1)
                {
                    int start_x = 8;
                    int start_y = 8;
                    display.fillCircle(start_x+10, start_y+10, 10, 1);
                    display.fillCircle(start_x+10, start_y+10, 8, 0);
                    display.fillRect(start_x+5, start_y+2, 11, 3, 1);
                    display.drawCircle(start_x+6, start_y+9, 2, 1);
                    display.drawCircle(start_x+14, start_y+9, 2, 1);
                    display.drawCircle(start_x+10, start_y+15, 2, 1);
                    display.setCursor(40, 13);
                    display.setTextSize(2);
                    display.println("XLR");
                }
                else if (audioManager.getSource() == AudioSource::BT)
                {
                    display.drawBitmap(5, 8, resource_bluetooth, 24, 24, 1);
                    display.setCursor(40, 13);
                    display.setTextSize(2);
                    display.println("BT");
                }
                    

                // int size = 64;
                // // 生成隨機的 FFT 數據
                // uint8_t fftData[size];
                // for (int i = 0; i < size; i++) {
                //     fftData[i] = random(0, SCREEN_HEIGHT * 0.5);
                // }                  

                // int barWidth = SCREEN_WIDTH / size; // 計算每個條的寬度

                // for (int i = 0; i < size; i++) {
                //     display.fillRect(i * barWidth, SCREEN_HEIGHT - fftData[i], barWidth, fftData[i], SSD1306_WHITE);
                // }
                
                // display.display();
                               
                // 生成隨機的 FFT 數據
                int size = 7;
                uint8_t fftData[size];
                for (int i = 0; i < size; i++) {

                    if (audioDSP.fft_data[i] == INFINITY)
                    {
                        fftData[i] = 0;
                    }
                    else
                    {
                        if (audioDSP.fft_data[i] >= -10.0f) audioDSP.fft_data[i] = -10.0f;
                        if (audioDSP.fft_data[i] <= -30.0f) audioDSP.fft_data[i] = -30.0f;

                        fftData[i] = ((audioDSP.fft_data[i] - (-30.0f)) / 20.0f) * (SCREEN_HEIGHT)*2;
                    }
                    
                    
                }                  

                int barWidth = SCREEN_WIDTH / size; // 計算每個條的寬度

                for (int i = 0; i < size; i++) {
                    display.fillRect(i * barWidth+2, SCREEN_HEIGHT - fftData[i], barWidth-2, fftData[i], SSD1306_WHITE);
                }
                
                display.display();
            }
            
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
    display.clearDisplay();
    display.setTextSize(2);
    display.setTextColor(SSD1306_WHITE);
    display.setCursor(5, 28);
    display.println("ECIE LAB");
    display.display();
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

