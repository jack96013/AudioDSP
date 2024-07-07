/*
 * @Author       : TZU-CHIEH, HSU
 * @Mail         : j.k96013@gmail.com
 * @Department   : ECIE Lab, NTUT
 * @Date         : 2024-06-28 13:40:51
 * @LastEditTime: 2024-07-07 22:37:27
 * @Description  : 
 */
/*
 * @Author       : TZU-CHIEH, HSU
 * @Mail         : j.k96013@gmail.com
 * @Department   : ECIE Lab, NTUT
 * @Date         : 2024-06-28 13:40:51
 * @LastEditTime : 2024-06-30 15:22:39
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
    void switchSource();

    // Volume Adjustment 
    int getVolume();
    void setVolume(int vol);

    int getLevel();

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


    // FPGA
    void setFpgaEqEnable(bool bypass);
    bool isFpgaEqEnable();
    

    private:

    int volume = 100;     // 音量
    int r_volume = 100;   // 右音量
    
    bool fpgaEqEnable = false; // FPGA 混音模式

    int sourceSelectIndex = 0;

    AudioSource sources[4] = {
        AudioSource::XLR1, //
        AudioSource::XLR2, //
        AudioSource::BT,   //
        AudioSource::USB,  //
    };

    size_t sourceLength = sizeof(sources) / sizeof(sources[0]);
    
};

#endif