/*
 * @Author       : TZU-CHIEH, HSU
 * @Mail         : j.k96013@gmail.com
 * @Department   : ECIE Lab, NTUT
 * @Date         : 2024-06-15 17:17:20
 * @LastEditTime : 2024-07-01 21:44:15
 * @Description  : 
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
  ledController.init();
  controlHandler.init();
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
  ledController.loop();
  audioDSP.loop();
}
