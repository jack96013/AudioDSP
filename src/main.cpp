/*
 * @Author: jack96013 j.k96013@gmail.com
 * @Date: 2024-06-15 17:17:20
 * @LastEditors: jack96013 j.k96013@gmail.com
 * @LastEditTime: 2024-06-27 20:10:14
 * @FilePath: \EspAudioDsp\src\main.cpp
 * @Description:
 */
#include <Arduino.h>
#include "testEnv.h"

#include <SoftTimers.h>
#include "SerialReceiver/SerialReceiver.h"

#include "ESPAudioDSP.h"
#include "AudioDSP/AudioDSP.h"

SoftTimer testTimer; // millisecond timer
BluetoothAudio btAudio;
ClassD classD; // class
ScreenManager screenManager;
ControlHandler controlHandler;
LedController ledController;
AudioManager audioManager;
WifiManager wifiManager; // wifi manager
AudioDSP audioDSP; // audio


void setup()
{
  Serial.begin(115200);

  

  testTimer.setTimeOutTime(10);
  testTimer.reset();

  btAudio.init();

  classD.init();

  screenManager.init();
  controlHandler.init();

  ledController.showRing(0.2);
  audioManager.init();

  wifiManager.begin();

  test_setup();

  audioDSP.init();

  
}

void loop()
{
  classD.loop();
  controlHandler.loop();
  screenManager.loop();
  wifiManager.check();
  btAudio.loop();
  audioDSP.loop();
}
