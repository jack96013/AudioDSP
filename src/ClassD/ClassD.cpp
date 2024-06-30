/*
 * @Author: jack96013 j.k96013@gmail.com
 * @Date: 2024-06-27 19:20:56
 * @LastEditors: jack96013 j.k96013@gmail.com
 * @LastEditTime: 2024-06-27 20:25:59
 * @FilePath: \EspAudioDsp\src\ClassD\ClassD.cpp
 * @Description: 这是默认设置,请设置`customMade`, 打开koroFileHeader查看配置 进行设置: https://github.com/OBKoro1/koro1FileHeader/wiki/%E9%85%8D%E7%BD%AE
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
    uint8_t value_address = 0;

    uint8_t value = audioManager.getVolume();
    // value ++;
    
    Wire.beginTransmission(this->address);
    Wire.write((uint8_t*)&value_address, sizeof(value_address));
    Wire.write((uint8_t*)&value, sizeof(value));
    Wire.endTransmission();

    // Wire.beginTransmission(this->address);
    // Wire.write((uint8_t*)&value, sizeof(value));
    // Wire.endTransmission();
}
