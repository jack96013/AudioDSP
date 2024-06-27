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
#include "Board.h"
#include "BluetoothAudio.h"
#include "ClassD\ClassD.h"

#include <SoftTimers.h>
#include "SerialReceiver/SerialReceiver.h"

SoftTimer testTimer; //millisecond timer
BluetoothAudio btAudio;
ClassD classD; //class


// put function declarations here:
int myFunction(int, int);

void setup() {
  // put your setup code here, to run once:
  int result = myFunction(2, 3);
  Serial.begin(115200);
  

  test_setup();

  testTimer.setTimeOutTime(10);
  testTimer.reset();

  btAudio.init();

  classD.init();

}


void loop() {
  // put your main code here, to run repeatedly:
  btAudio.loop();

  classD.loop();

  test_loop();
  if (testTimer.hasTimedOut())
  {
    test_loop();
    testTimer.reset();
  }
  

  

}

// put function definitions here:
int myFunction(int x, int y) {
  return x + y;
}

