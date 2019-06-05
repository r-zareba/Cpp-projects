//
// Created by rafal on 04.06.19.
//

#ifndef WEBASTO_ESP8266_BUTTON_H
#define WEBASTO_ESP8266_BUTTON_H

#include <Arduino.h>
#include <stdint.h>

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



#endif //WEBASTO_ESP8266_BUTTON_H
