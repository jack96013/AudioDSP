#include "AudioManager.h"
#include "ESPAudioDsp.h"

AudioManager::AudioManager()
{
    // Initialize audio engine
}

void AudioManager::init()
{
    pinMode(BOARD_ASRC_MODE0_PIN, OUTPUT);
    pinMode(BOARD_ASRC_MODE1_PIN, OUTPUT);
    pinMode(BOARD_ASRC_MODE2_PIN, OUTPUT);

    pinMode(BOARD_MUX1_SEL_PIN, OUTPUT);
    pinMode(BOARD_MUX2_SEL_PIN, OUTPUT);

    digitalWrite(BOARD_ASRC_MODE0_PIN, LOW);
    digitalWrite(BOARD_ASRC_MODE1_PIN, HIGH);
    digitalWrite(BOARD_ASRC_MODE2_PIN, HIGH);
    

    setSource(AudioSource::BT);

    setVolume(80);

    // TODO: FPGA Data sync
}

void AudioManager::loop()
{

}

void AudioManager::setSource(AudioSource source)
{
    // this->source = source;
    switch (getSource())
    {
    case AudioSource::XLR1:
        setFpgaEqEnable(true);
        digitalWrite(BOARD_MUX1_SEL_PIN, HIGH);
        digitalWrite(BOARD_MUX2_SEL_PIN, HIGH);
        audioDSP.setSource(AudioDspSource::I2S);
        break;
    case AudioSource::XLR2:
        setFpgaEqEnable(false);
        digitalWrite(BOARD_MUX1_SEL_PIN, HIGH);
        digitalWrite(BOARD_MUX2_SEL_PIN, HIGH);
        audioDSP.setSource(AudioDspSource::I2S);
        // Serial.println(digitalRead(BOARD_MUX2_SEL_PIN));
        break;
    case AudioSource::BT:
        setFpgaEqEnable(false);
        digitalWrite(BOARD_MUX1_SEL_PIN, LOW);
        audioDSP.setSource(AudioDspSource::I2S);
        break;
    case AudioSource::USB:
        setFpgaEqEnable(false);
        digitalWrite(BOARD_MUX1_SEL_PIN, HIGH);
        digitalWrite(BOARD_MUX2_SEL_PIN, LOW);
        // audioDSP.setSource(AudioDspSource::SINE);
        audioDSP.setSource(AudioDspSource::I2S);
        break;
    }
}
AudioSource AudioManager::getSource()
{
    return sources[sourceSelectIndex];
}

void AudioManager::switchSource()
{
    sourceSelectIndex ++;
    if (sourceSelectIndex >= sourceLength)
    {
        sourceSelectIndex = 0;
    }
    setSource(sources[sourceSelectIndex]);
}

int AudioManager::getVolume()
{
    return volume;
}

void AudioManager::setVolume(int vol)
{
    if (vol <= 0) vol = 0;
    else if (vol > 100) vol = 100;

    volume = vol;

    if (isFpgaEqEnable())
    {
        classD.setMainVolume(volume / 100.0f);
        classD.setSubwooferVolume(volume / 100.0f - 0.1f);
    }
    else
    {
        audioDSP.setVolume(vol/100.0f);
    }
    
    
}

int AudioManager::getLevel()
{
    // audioDSP.fft_data();
    return 0;
}

void AudioManager::mute()
{
    switch (getSource())
    {
        case AudioSource::BT:
            break;

    }
}
void AudioManager::play()
{

}
void AudioManager::pause()
{
    
}
void AudioManager::skip()
{

}
void AudioManager::last()
{

}

void AudioManager::setFpgaEqEnable(bool bypass)
{
    fpgaEqEnable = bypass;
    classD.setFpgaEqEnable(bypass);
    
    // audioDSP.setFpgaEqBypass(bypass);
    // classD.setFpgaEqModeEnable
}

bool AudioManager::isFpgaEqEnable()
{
    return fpgaEqEnable;
}
