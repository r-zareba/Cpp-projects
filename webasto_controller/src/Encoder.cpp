//
// Created by rafal on 18.05.19.
//

#include "Encoder.h"


const uint8_t Encoder::encoderDelay = 5;


Encoder::Encoder(uint8_t pinA, uint8_t pinB)
:
pinA(pinA),
pinB(pinB)
{
    pinMode(this->pinA, INPUT);
    pinMode(this->pinB, INPUT);
}

void Encoder::keepInRange() {
    if (this->currentPos >= this->maxRange) this->currentPos = this->maxRange;
    if (this->currentPos <= this->minRange) this->currentPos = this->minRange;
}

void Encoder::encodeA() {
    bool pinState = digitalRead(this->pinA);

    if (pinState != this->encoderAset) {
        this->encoderAset = !this->encoderAset;

        if (this->encoderAset && !this->encoderBset) this->currentPos++;
    }
    this->keepInRange();
}

void Encoder::encodeB() {
    bool pinState = digitalRead(this->pinB);

    if (pinState != this->encoderBset) {
        this->encoderBset = !this->encoderBset;

        if (this->encoderBset && !this->encoderAset) this->currentPos--;
    }
    this->keepInRange();
}

uint8_t Encoder::getCurrentPos() const {
    return this->currentPos;
}

void Encoder::setCurrentPos(uint8_t pos) {
    this->currentPos = pos;
}

void Encoder::resetPos() {
    this->setCurrentPos(1);
}

void Encoder::setRange(uint8_t min, uint8_t max) {
    this->minRange = min;
    this->maxRange = max;
}
