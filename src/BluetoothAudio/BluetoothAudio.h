#ifndef __BLUETOOTH_AUDIO_H__
#define __BLUETOOTH_AUDIO_H__

#include <Arduino.h>
#include "SoftTimers.h"
#include <ATConnection.hpp>
#include "config.h"
#include "SerialReceiver/SerialReceiver.h"


enum class BluetoothAudioPlayState
{
    Stopped,
	Playing,
	Paused,
	Fast_Forwarding,
	Fast_Rewinding,
};


class BluetoothAudio
{
public:
    BluetoothAudio();
    void init();

    void loop();

    BluetoothAudioPlayState getPlayState();
    
    String getTrackTitle();
    String getTrackArtist();
    String getTrackAblum();

    int getTrackTotalTime();
    int getTrackElapsedTime();
    float getTrackProgress();

    void setPlayState(BluetoothAudioPlayState state);


    

private:
    SoftTimer runTimer;
    SerialReceiver receiver = SerialReceiver();
    
    void _run();
    void serial_relay();
    void parseCommand(String &response);

    static void onReceive(void *arg, String &payload);

    BluetoothAudioPlayState playState;
    String trackTitle = "";
    String trackArtist = "";
    String trackAblum = "";
    time_t trackTotalTime = 0;    
    time_t trackElapsedTime = 0;    
    
};

#endif