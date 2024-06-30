#include "I2SHandler.h"

I2SHandler::I2SHandler()
{
}

void I2SHandler::init()
{
    pinMode(BOARD_ASRC_MODE0_PIN, OUTPUT);
    pinMode(BOARD_ASRC_MODE1_PIN, OUTPUT);
    pinMode(BOARD_ASRC_MODE2_PIN, OUTPUT);

    pinMode(BOARD_MUX1_SEL_PIN, OUTPUT);
    pinMode(BOARD_MUX2_SEL_PIN, OUTPUT);
}

void I2SHandler::loop()
{
}

void I2SHandler::setAudioInput(I2SHandlerMux mux)
{
    _audioInput = mux;
    switch (mux)
    {
    case I2SHandlerMux::BT:
        digitalWrite(BOARD_MUX1_SEL_PIN, LOW);
        digitalWrite(BOARD_MUX1_SEL_PIN, LOW);
        break;
    case I2SHandlerMux::USB:
        digitalWrite(BOARD_MUX1_SEL_PIN, HIGH);
        digitalWrite(BOARD_MUX1_SEL_PIN, HIGH);
        break;
    case I2SHandlerMux::FPGA:
        digitalWrite(BOARD_MUX1_SEL_PIN, LOW);
        digitalWrite(BOARD_MUX1_SEL_PIN, LOW);
        break;
    }
}
