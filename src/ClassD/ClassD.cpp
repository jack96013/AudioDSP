/*
 * @Author: jack96013 j.k96013@gmail.com
 * @Date: 2024-06-27 19:20:56
 * @LastEditors: jack96013 j.k96013@gmail.com
 * @LastEditTime: 2024-06-27 20:25:59
 * @FilePath: \EspAudioDsp\src\ClassD\ClassD.cpp
 * @Description: Class D library
 */

#include "ClassD.h"
#include "ESPAudioDsp.h"

ClassD::ClassD()
{
    this->address = BOARD_CLASSD_I2C_ADDRESS;
    timer.setTimeOutTime(100);
    timer.reset();
    
    Wire.begin();
    // Wire.setClock(10000);
    
}


void ClassD::init()
{
    
}

void ClassD::loop()
{
    if (timer.hasTimedOut())
    {
        timer.reset();
        sendTestData();
    }
}


void ClassD::setLeftVolume(float percentage)
{
    int16_t volume =  percentage * 4095;
    settings.l_volume =  volume;

    Wire.beginTransmission(this->address);
    Wire.write((uint8_t*)&volume, sizeof(volume));
    Wire.endTransmission();
    
}

void ClassD::setRightVolume(float percentage)
{
    int16_t volume =  percentage * 4095;
    settings.r_volume =  volume;

    Wire.beginTransmission(this->address);
    Wire.write((uint8_t*)&volume, sizeof(volume));
    Wire.endTransmission();
}

void ClassD::setSubwooferVolume(float percentage)
{
    int16_t volume =  percentage * 4095;
    settings.sub_volume =  volume;

    Wire.beginTransmission(this->address);
    Wire.write((uint8_t*)&volume, sizeof(volume));
    Wire.endTransmission();
}

void ClassD::sendTestData()
{    
    uint8_t value[] = {(uint8_t)(0xAA),(uint8_t)audioManager.getVolume()};
    uint16_t val = (uint16_t)value[0] << 8 | (uint16_t)value[1];
    // Serial.print(F("TEST DATA :"));
    // Serial.println(val);
    sendData(CLASSD_SETTINGS_TEST_ADDRESS, val);
}

void ClassD::sendData(uint8_t data_address, uint16_t data)
{
    Wire.beginTransmission(this->address);
    Wire.write(data_address);
    Wire.write(highByte(data));
    Wire.write(lowByte(data));
    Wire.endTransmission();
}
