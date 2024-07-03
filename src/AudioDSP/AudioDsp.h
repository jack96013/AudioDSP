/*
 * @Author       : TZU-CHIEH, HSU
 * @Mail         : j.k96013@gmail.com
 * @Department   : ECIE Lab, NTUT
 * @Date         : 2024-07-01 20:19:16
 * @LastEditTime : 2024-07-02 18:31:16
 * @Description  : 
 */
#ifndef __AUDIO_DSP_H__
#define __AUDIO_DSP_H__

#include <SigmaDsp.h>
#include <Wire.h>
#include "SigmaDsp_parameters.h"
#include "SoftTimers.h"

class AudioDSP
{
    public:
    AudioDSP();
    void init();
    
    void loop();

    void setVolume(float percent);

    float fft_data[7];


    void setSubwooferCutOffFrequency(int freq);
    void setSubwooferGaindB(int freq);
    

    private:
    SigmaDSP dsp = SigmaDSP(Wire, DSP_I2C_ADDRESS, 48000.00F);


    void getAuioFFT();
    SoftTimer timer;


    static float fixedToFloat(uint32_t fixedval);
    
    

};

#endif