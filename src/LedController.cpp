#include "LedController.h"

LedController::LedController() {
    // this->pin = pin;
    // pinMode(pin, OUTPUT);
    // digitalWrite(pin, LOW);
}


void LedController::init() {
    
}

void LedController::loop() {
    
}

void LedController::setEnabled(bool enable) {
    this->enable = enable;
}

bool LedController::isEnabled() {
    return enable;
}

