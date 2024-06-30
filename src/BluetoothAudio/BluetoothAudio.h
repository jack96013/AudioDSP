#ifndef __BLUETOOTH_AUDIO_H__
#define __BLUETOOTH_AUDIO_H__

#include <Arduino.h>
#include "SoftTimers.h"
#include <ATConnection.hpp>
#include "config.h"
#include "SerialReceiver/SerialReceiver.h"
class BluetoothAudio
{
public:
    BluetoothAudio();
    void init();

    void loop();

    

private:
    SoftTimer runTimer;
    SerialReceiver receiver = SerialReceiver();
    
    void _run();
    void serial_relay();
    void parseCommand();

    
};

#endif