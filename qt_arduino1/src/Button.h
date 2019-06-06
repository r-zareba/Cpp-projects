//
// Created by rafal on 06.06.19.
//

#ifndef QT_ARDUINO1_BUTTON_H
#define QT_ARDUINO1_BUTTON_H


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
    bool beenClicked();
    bool isPressed();

};


#endif //QT_ARDUINO1_BUTTON_H
