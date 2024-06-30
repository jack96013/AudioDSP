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
}

void AudioManager::loop()
{
}

void AudioManager::setSource(AudioSource source)
{
    this->source = source;
    switch (source)
    {
    case AudioSource::XLR1:
        digitalWrite(BOARD_MUX1_SEL_PIN, LOW);
        digitalWrite(BOARD_MUX1_SEL_PIN, LOW);
        break;
    case AudioSource::XLR2:
        digitalWrite(BOARD_MUX1_SEL_PIN, HIGH);
        digitalWrite(BOARD_MUX1_SEL_PIN, HIGH);
        break;
    case AudioSource::BT:
        digitalWrite(BOARD_MUX1_SEL_PIN, LOW);
        digitalWrite(BOARD_MUX1_SEL_PIN, LOW);
        break;
    case AudioSource::USB:
        digitalWrite(BOARD_MUX1_SEL_PIN, HIGH);
        digitalWrite(BOARD_MUX1_SEL_PIN, HIGH);
        break;
    }
}
AudioSource AudioManager::getSource()
{
    return source;
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

    audioDSP.setVolume(vol/100.0f);
}

void AudioManager::mute()
{
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
