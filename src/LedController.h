#ifndef __LEDCONTROLLER_H__
#define __LEDCONTROLLER_H__

#include "Arduino.h"


class LedController
{
    public:
    LedController();
    void init();
    void loop();

    void setEnabled(bool enabled);
    bool isEnabled();

    
    private:
    bool enable = true;
    
};


#endif