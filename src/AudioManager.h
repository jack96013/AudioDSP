/*
 * @Author       : TZU-CHIEH, HSU
 * @Mail         : j.k96013@gmail.com
 * @Department   : ECIE Lab, NTUT
 * @Date         : 2024-06-28 13:40:51
 * @LastEditTime : 2024-06-29 10:37:33
 * @Description  : 
 */
#ifndef __AUDIOMANAGER_H__
#define __AUDIOMANAGER_H__
#include "Arduino.h"
#include "board.h"

enum class AudioSource
{
    XLR1,
    XLR2,
    BT,
    USB,
};


class AudioManager
{
    public:
    AudioManager();
    void init();
    void loop();

    // AUDIO SOURCE
    void setSource(AudioSource source);
    AudioSource getSource();


    // Volume Adjustment 
    int getVolume();
    void setVolume(int vol);

    int getVolumeL();
    void setVolumeL(int vol);

    int getVolumeR();
    void setVolumeR(int vol);

    void saveSettings();


    // Control
    void mute();
    void play();
    void pause();
    void skip();
    void last();


    private:
    AudioSource source = AudioSource::XLR1; // 音源

    int volume;     // 音量
    int l_volume;   // 左音量
    int r_volume;   // 右音量
    

    
};

#endif