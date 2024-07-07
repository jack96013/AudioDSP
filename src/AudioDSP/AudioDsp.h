#ifndef __AUDIO_DSP_H__
#define __AUDIO_DSP_H__

#include <SigmaDsp.h>
#include <Wire.h>
#include "SigmaDsp_parameters.h"
#include "SoftTimers.h"

enum class AudioDspSource
{
    ADC = 0,
    I2S = 1,
    SINE = 2
};

class AudioDSP
{
    public:
    AudioDSP();
    void init();
    
    void loop();

    void setVolume(float percent);

    void setSineWave(int freq);

    void setSource(AudioDspSource source);

    float fft_data[7];

    private:
    SigmaDSP dsp = SigmaDSP(Wire, DSP_I2C_ADDRESS, 48000.00F);


    void getAuioFFT();
    SoftTimer timer;


    static float fixedToFloat(uint32_t fixedval);
    
    

};

#endif