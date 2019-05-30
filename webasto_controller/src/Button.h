//
// Created by rafal on 21.05.19.
//

#ifndef WEBASTO_CONTROLLER_BUTTON_H
#define WEBASTO_CONTROLLER_BUTTON_H


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


#endif //WEBASTO_CONTROLLER_BUTTON_H
