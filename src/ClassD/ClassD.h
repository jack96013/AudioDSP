#ifndef __CLASSD_H__
#define __CLASSD_H__

#include <Arduino.h>
#include <Wire.h>
#include <SoftTimers.h>


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
    
    //
    void setLeftVolume(float percentage);
    void setRightVolume(float percentage);
    void setSubwooferVolume(float percentage);

    void sendTestData();

  

    
    private:
    SoftTimer timer;
    ClassDSettings settings;
    String deviceName;
    int8_t address;

};

#endif