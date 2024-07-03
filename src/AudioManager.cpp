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
    digitalWrite(BOARD_ASRC_MODE2_PIN, LOW);

    setSource(AudioSource::BT);

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
        digitalWrite(BOARD_MUX1_SEL_PIN, LOW);
        digitalWrite(BOARD_MUX1_SEL_PIN, LOW);
        break;
    case AudioSource::XLR2:
        setFpgaEqEnable(false);
        digitalWrite(BOARD_MUX1_SEL_PIN, HIGH);
        digitalWrite(BOARD_MUX1_SEL_PIN, HIGH);
        break;
    case AudioSource::BT:
        setFpgaEqEnable(false);
        digitalWrite(BOARD_MUX1_SEL_PIN, LOW);
        digitalWrite(BOARD_MUX1_SEL_PIN, LOW);
        break;
    case AudioSource::USB:
        setFpgaEqEnable(false);
        digitalWrite(BOARD_MUX1_SEL_PIN, HIGH);
        digitalWrite(BOARD_MUX1_SEL_PIN, HIGH);
        break;
    }
}
AudioSource AudioManager::getSource()
{
    return sources[sourceSelectIndex];
}

void AudioManager::switchSource()
{
    sourceSelectIndex++;
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
    if (vol <= 0)
        vol = 0;
    else if (vol > 100)
        vol = 100;

    volume = vol;

    if (isFpgaEqEnable())
    {
        classD.setLeftVolume(volume / 100.0f);
        classD.setRightVolume(volume / 100.0f);
        classD.setSubwooferVolume(volume / 100.0f);
    }
    else
    {
        audioDSP.setVolume(vol / 100.0f);
    }
}

float AudioManager::getLevel()
{
    float averageVolume = 0;
    for (int i = 0; i < 7; i++)
    {
        if (audioDSP.fft_data[i] >= -10.0f)
            audioDSP.fft_data[i] = -10.0f;
        if (audioDSP.fft_data[i] <= -30.0f)
            audioDSP.fft_data[i] = -30.0f;

        averageVolume += audioDSP.fft_data[i];
    }
    
    averageVolume = audioDSP.fft_data[0];
    // averageVolume /= 7.0f;
    averageVolume = ((averageVolume -30.0f) / 20.0f) * 2;
    Serial.println(averageVolume);
    if (fabs(averageVolume) == INFINITY)
    {
        // Serial.println("dddd");
        return 0;
    }
    // ;
    return averageVolume;
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
    // audioDSP.setFpgaEqBypass(bypass);
    // classD.setFpgaEqModeEnable
}

bool AudioManager::isFpgaEqEnable()
{
    return fpgaEqEnable;
}
