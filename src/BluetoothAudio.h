#ifndef __BLUETOOTH_AUDIO_H__
#define __BLUETOOTH_AUDIO_H__

#include <Arduino.h>
#include "SoftTimers.h"
#include <ATConnection.hpp>
#include "config.h"
class BluetoothAudio
{
public:
    BluetoothAudio();
    void init();

    void loop();

private:
    SoftTimer runTimer;
    ATConnection at = ATConnection(&Serial2);
    
    void _run();
    void serial_relay();
};

#endif