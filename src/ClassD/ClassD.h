/*
 * @Author       : TZU-CHIEH, HSU
 * @Mail         : j.k96013@gmail.com
 * @Department   : ECIE Lab, NTUT
 * @Date         : 2024-06-27 19:20:50
 * @LastEditTime: 2024-07-07 22:36:44
 * @Description  : FPGA class D control.
 */
#ifndef __CLASSD_H__
#define __CLASSD_H__

#include <Arduino.h>
#include <Wire.h>
#include <SoftTimers.h>

#include "ClassDConfig.h"
#include "board.h"

#define  CLASSD_I2S_VOLUEM


typedef struct  {
    uint16_t volume;
    uint16_t r_volume;
    uint16_t sub_volume;
} ClassDSettings;

class ClassD
{
    public:
    ClassD();
    void init();
    void loop();
    
    void setFpgaEqEnable(bool enable);    // FPGA 混音模式 
    //
    void setMainVolume(float percentage);
    // void setRightVolume(float percentage);
    void setSubwooferVolume(float percentage);

    void sendTestData();
    void sendData(uint8_t data_address, uint16_t data);

    void receiveData();

    int16_t receiveBuffer;
    
    ClassDSettings settings;
    
    private:
    SoftTimer timer;
    
    String deviceName;
    int8_t address;
    


};

#endif