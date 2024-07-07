/*
 * @Author       : TZU-CHIEH, HSU
 * @Mail         : j.k96013@gmail.com
 * @Department   : ECIE Lab, NTUT
 * @Date         : 2024-06-27 17:23:52
 * @LastEditTime : 2024-07-07 16:36:41
 * @Description  : 
 */
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
    float dB = -80.0f + percent * 100.0f;
    // Serial.println(dB);
    dsp.volume(MOD_SWVOL1_ALG0_TARGET_ADDR, dB);
    // dsp.volume_slew(MOD_SWVOL1_ALG0_TARGET_ADDR, dB);
    
}

void AudioDSP::setSineWave(int32_t freq)
{
    dsp.sineSource(MOD_TONE1_ALG0_INCREMENT_ADDR, freq);
}

void AudioDSP::setSource(AudioDspSource source)
{
    // int32_t value  = dsp.readBack(MOD_7XRTA1_ALG0_ADDR, MOD_READBACK2_ALG0_VAL0_ADDR , 4);
    // dsp.dcSource(MOD_DC3_DCINPALG1_ADDR, (uint32_t)1);
    uint32_t value = (uint32_t)source;
    uint8_t array[4]; 
    array[0] = (uint8_t)(value >> 24); // 最高位
    array[1] = (uint8_t)(value >> 16); // 次高位
    array[2] = (uint8_t)(value >> 8);  // 次低位
    array[3] = (uint8_t)(value);       // 最低位

    dsp.writeRegister(MOD_DC3_DCINPALG1_ADDR, 4, array);
    // Serial.println("Source: ");
    // Serial.println(value);
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

    // dsp.safeload_writeRegister
    
}

float AudioDSP::fixedToFloat(uint32_t fixedval)
{
    // 將固定點數值轉換為浮點數
    float value = fixedval / ((float)(1 << 23));
    
    return value;
}

