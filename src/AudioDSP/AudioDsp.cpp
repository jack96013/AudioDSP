#include "AudioDsp.h"

AudioDSP::AudioDSP()
{
    //ctor
    
}

void AudioDSP::init()
{
    
    dsp.begin();
    delay(1000);
    
    Serial.println(F("Pinging i2c lines...\n0 -> deveice is present\n2 -> device is not present"));
    Serial.print(F("DSP response: "));
    Serial.println(dsp.ping());

    Serial.print(F("\nLoading DSP program... "));
    loadProgram(dsp);
    Serial.println("Done!\n");

    timer.setTimeOutTime(100);
    timer.reset();


}

void AudioDSP::loop()
{
    if (timer.hasTimedOut())
    {
        timer.reset();
        getAuioFFT();
    }
}

void AudioDSP::setVolume(float percent)
{
    float dB = -80.0f + percent * 80.0f;
    Serial.println(dB);
    dsp.volume(MOD_SWVOL1_ALG0_TARGET_ADDR, dB);
}

void AudioDSP::getAuioFFT()
{
    // Serial.print(F("FFT value: "));
     
    for (int i = 0; i < 7; i++)
    {
        int value  = dsp.readBack(MOD_7XRTA1_ALG0_ADDR, MOD_7XRTA1_ALG0_VALUES + ((uint16_t)168 * i), 3);
        fft_data[i] = 20*log10f(fixedToFloat(value)); 
        // Serial.print(fft_data[i]);
        // Serial.print(",");
    }
    // Serial.println();
    
}

float AudioDSP::fixedToFloat(uint32_t fixedval)
{
    // 將固定點數值轉換為浮點數
    float value = fixedval / ((float)(1 << 23));
    
    return value;
}

