#include "AudioDsp.h"

AudioDsp::AudioDsp()
{
    //ctor
    
}

void AudioDsp::init()
{
    dsp.begin();
    delay(200);
    
    Serial.println(F("Pinging i2c lines...\n0 -> deveice is present\n2 -> device is not present"));
    Serial.print(F("DSP response: "));
    Serial.println(dsp.ping());

    Serial.print(F("\nLoading DSP program... "));
    loadProgram(dsp);
    Serial.println("Done!\n");


}

void AudioDsp::loop()
{

}

