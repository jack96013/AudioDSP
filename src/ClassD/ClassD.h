/*
 * @Author       : TZU-CHIEH, HSU
 * @Mail         : j.k96013@gmail.com
 * @Department   : ECIE Lab, NTUT
 * @Date         : 2024-06-27 19:20:50
 * @LastEditTime : 2024-07-02 15:55:47
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
    int16_t l_volume;
    int16_t r_volume;
    int16_t sub_volume;
} ClassDSettings;

class ClassD
{
    public:
    ClassD();
    void init();
    void loop();
    
    void setFpgaEqEnable(bool enable);    // FPGA 混音模式 
    //
    void setLeftVolume(float percentage);
    void setRightVolume(float percentage);
    void setSubwooferVolume(float percentage);

    void sendTestData();
    void sendData(uint8_t data_address, uint16_t data);

    void receiveData();

    uint16_t receiveBuffer;
    
    private:
    SoftTimer timer;
    ClassDSettings settings;
    String deviceName;
    int8_t address;
    


};

#endif