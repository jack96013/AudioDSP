#include "ControlHandler.h"

ControlHandler::ControlHandler()
{

    // ctor
}

void ControlHandler::init()
{
    encoder.setAccelerationEnabled(true);
    encoder.setButtonHeldEnabled(true);
    encoder.setDoubleClickEnabled(true);
    encoder.setButtonOnPinZeroEnabled(true);

    button.setButtonHeldEnabled(true);

    checkTimer.setTimeOutTime(1);
    checkTimer.reset();
}

void ControlHandler::loop()
{
    if (checkTimer.hasTimedOut())
    {
        readEncoder();
        readButton();
        checkTimer.reset();
    }
}

void ControlHandler::readEncoder()
{
    encoder.service();

    static int16_t last, value;
    value += encoder.getValue();
    int16_t diff = -1*(last - value);

    

    if (value != last)
    {
        int volume = audioManager.getVolume();
        audioManager.setVolume(volume + diff);
        if (value < last)
        {
            encoderValue -= diff;
            Serial.println("-");
            
        }
        else
        {
            encoderValue += diff;
            Serial.println("+");
        }
        last = value;

        if (encoderValue > 100)
        {
            encoderValue = 100;
        }
        else if (encoderValue < 0)
        {
            encoderValue = 0;
        }
        Serial.print("Encoder Value: ");
        Serial.println(value);
        Serial.print("b Value: ");
        Serial.println(encoderValue);
    }

    ClickEncoder::Button b = encoder.getButton();
    if (b != ClickEncoder::Open)
    {
        Serial.print("Button: ");
#define VERBOSECASE(label)      \
    case label:                 \
        Serial.println(#label); \
        break;
        switch (b)
        {
            // case ClickEncoder::Clicked:
            // digitalWrite(BOARD_MUX_SEL_PIN, !digitalRead(BOARD_MUX_SEL_PIN));
            // Serial.println("MUX");
            case ClickEncoder::Pressed:
            {
                
                break;   
            }
            case ClickEncoder::Held:
            {

                break;   
            }
            case ClickEncoder::Released:
            {

                break;   
            }
            case ClickEncoder::Clicked:
            {
                audioManager.switchSource();
                break;   
            }
            case ClickEncoder::DoubleClicked:
            {

                break;   
            }
        }
    }
}

void ControlHandler::readButton()
{
    button.service();
    ClickEncoder::Button status = button.getButton();

    if (status == ClickEncoder::Open)
    {
        return;
    }
    Serial.print("Button: ");

#define VERBOSECASE(label)      \
    case label:                 \
        Serial.println(#label); \
        break;

    switch (status)
    {
        break;
            case ClickEncoder::Pressed:
            {
                
                break;   
            }
            case ClickEncoder::Held:
            {
                
                break;   
            }
            case ClickEncoder::Released:
            {
                
                break;   
            }
            case ClickEncoder::Clicked:
            {
                
                break;   
            }
            case ClickEncoder::DoubleClicked:
            {
                
                break;   
            }
    }
}