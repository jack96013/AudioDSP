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
        receiveData();
        // sendTestData();
    }
}

void ClassD::setFpgaEqEnable(bool enable)
{
    uint16_t data = !enable;
    sendData(CLASSD_SETTINGS_MUX_ADDRESS, data);   
}

void ClassD::setMainVolume(float percentage)
{
    int16_t volume =  percentage * 10000;
    settings.l_volume =  volume;

    sendData(CLASSD_SETTINGS_MAIN_VOLUME_ADDRESS, volume);
    
}

void ClassD::setSubwooferVolume(float percentage)
{
    int16_t volume =  percentage * 10000;
    settings.sub_volume =  volume;

    sendData(CLASSD_SETTINGS_SUB_VOLUME_ADDRESS, volume);
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

void ClassD::receiveData()
{
    return;
    Wire.beginTransmission(this->address);
    Wire.write(CLASSD_SETTINGS_TEST_ADDRESS);
    Wire.endTransmission(); 
    
    Wire.requestFrom(this->address, 8);
    
    while (Wire.available())
    {
        receiveBuffer = Wire.read();  // 讀取接收到的字節
        Serial.print("Received: ");
        Serial.println(receiveBuffer);  // 將接收到的數據打印到串口，或進行其他處理 
        
    }
    
    Wire.endTransmission();
    
}
