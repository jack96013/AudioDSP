#ifndef __CONTROLHANDLER_H__
#define __CONTROLHANDLER_H__

#include <Arduino.h>
#include <ClickEncoder.h>
#include "SoftTimers.h"
#include "ESPAudioDSP.h"

#include "board.h"


class ControlHandler
{
    public:
    ControlHandler();
    void init();
    void loop();

    private:
    SoftTimer checkTimer;
    ClickEncoder encoder = ClickEncoder(BOARD_EC11_A_PIN,
                                    BOARD_EC11_B_PIN,
                                    BOARD_EC11_SW_PIN,
                                    4);
    DigitalButton button = DigitalButton(BOARD_BUTTON_1_PIN);

    int encoderValue = 0;
    
    
    void readEncoder();
    void readButton();

    

};

#endif