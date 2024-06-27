#ifndef __AUDIO_DSP_H__
#define __AUDIO_DSP_H__

#include <SigmaDsp.h>
#include <Wire.h>
#include "SigmaDsp_parameters.h"

class AudioDsp
{
    public:
    AudioDsp();
    void init();
    
    void loop();

    private:
    SigmaDSP dsp = SigmaDSP(Wire, DSP_I2C_ADDRESS, 48000.00F);


};

#endif