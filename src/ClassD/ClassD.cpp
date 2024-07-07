/*
 * @Author: jack96013 j.k96013@gmail.com
 * @Date: 2024-06-27 19:20:56
 * @LastEditors: jack96013 j.k96013@gmail.com
 * @LastEditTime: 2024-07-08 02:12:50
 * @FilePath: \EspAudioDsp\src\ClassD\ClassD.cpp
 * @Description: Class D library
 */

#include "ClassD.h"
#include "ESPAudioDsp.h"

ClassD::ClassD()
{
    
    
}


void ClassD::init()
{
    this->address = BOARD_CLASSD_I2C_ADDRESS;
    timer.setTimeOutTime(1000);
    timer.reset();
    
    // Wire.begin();
    // Wire.setClock(10000);
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
    uint16_t volume =  percentage * (uint16_t)10000;
    settings.volume =  volume;

    sendData(CLASSD_SETTINGS_MAIN_VOLUME_ADDRESS, volume);
    
}

void ClassD::setSubwooferVolume(float percentage)
{
    uint16_t volume =  percentage * (uint16_t)10000;
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
    Serial.print("Request Data...");
    // return;
    Wire.beginTransmission(this->address);
    Wire.write(CLASSD_SETTINGS_MAIN_VOLUME_ADDRESS);
    Wire.endTransmission(0); 
    uint32_t start_millis = millis();
    Wire.requestFrom(this->address, 2);
    Serial.println(millis() - start_millis);

    if (Wire.available() == 2) {  // 確保接收到兩個字節
        receiveBuffer = Wire.read();  // 讀取高位字節
        receiveBuffer = (receiveBuffer << 8) | Wire.read();  // 讀取低位字節並合併到高位字節中
        Serial.print("Volume: ");
        Serial.println(receiveBuffer);  // 將接收到的數據以十六進制格式打印到串口
    }
}
