//
// Created by rafal on 04.06.19.
//

#ifndef CAMPER_CONTROLLER_BUTTON_H
#define CAMPER_CONTROLLER_BUTTON_H


#include <HID.h>

class Button {
private:
    const uint8_t pin;
    const bool idleState;
    bool buttonState = idleState;
    bool lastButtonState = idleState;
    bool currentState = idleState;

    static unsigned long lastTimeButton;
    static const uint8_t buttonDelay;

public:


    Button(uint8_t pin, bool idleState);
    bool isClicked();

};

#endif //CAMPER_CONTROLLER_BUTTON_H
