//
// Created by rafal on 06.06.19.
//

#include "Button.h"

unsigned long Button::lastTimeButton = 0;
const uint8_t Button::buttonDelay = 20;


Button::Button(uint8_t pin, bool idleState)
        :
        pin(pin),
        idleState(idleState)
{
    pinMode(this->pin, INPUT);
}


bool Button::beenClicked() {
    /*
     * Implementation of checking if button was clicked
     * Reduces debouncing effect
     */
    this->currentState = digitalRead(this->pin);

    if (this->currentState != lastButtonState) Button::lastTimeButton = millis();

    if ((millis() - Button::lastTimeButton) > Button::buttonDelay) {
        if (this->currentState != this->buttonState) {
            this->buttonState = this->currentState;

            if (this->buttonState != this->idleState){
                this->lastButtonState = this->currentState;
                return true;
            }
        }
    }

    this->lastButtonState = this->currentState;
    return false;
}

bool Button::isPressed() {

    this->currentState = digitalRead(this->pin);
    return this->currentState != this->idleState;
}