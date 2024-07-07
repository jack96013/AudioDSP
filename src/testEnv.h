#ifndef __TESTENV_H__
#define __TESTENV_H__

#include "Arduino.h"
#include "board.h"

#include <SPI.h>
#include <Wire.h>






void i2c_scanner();



void test_setup()
{
  Serial.println();
  Serial.println("Initializing...");
  Serial.flush();

  Serial.println();
  Serial.println("Running...");

  // Wire.begin();
  i2c_scanner();


  Serial2.begin(115200);
  Serial2.println("AT+REBOOT");


  pinMode(BOARD_RESET_PIN, OUTPUT);
  digitalWrite(BOARD_RESET_PIN, LOW);
  delay(100);
  digitalWrite(BOARD_RESET_PIN, HIGH);
}



void test_loop()
{

}



void i2c_scanner()
{
  byte error, address;
  int nDevices;
  Serial.println("Scanning...");
  nDevices = 0;
  for (address = 1; address < 127; address++)
  {
    Wire.beginTransmission(address);
    error = Wire.endTransmission();
    if (error == 0)
    {
      Serial.print("I2C device found at address 0x");
      if (address < 16)
      {
        Serial.print("0");
      }
      Serial.println(address, HEX);
      nDevices++;
    }
    else if (error == 4)
    {
      Serial.print("Unknow error at address 0x");
      if (address < 16)
      {
        Serial.print("0");
      }
      Serial.println(address, HEX);
    }
  }
  if (nDevices == 0)
  {
    Serial.println("No I2C devices found\n");
  }
  else
  {
    Serial.println("done\n");
  }
}

#endif

