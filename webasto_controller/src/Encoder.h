//
// Created by rafal on 18.05.19.
//

#ifndef WEBASTO_CONTROLLER_ENCODER_H
#define WEBASTO_CONTROLLER_ENCODER_H


#include <HID.h>


class Encoder {
private:
    uint8_t pinA;
    uint8_t pinB;
    uint8_t minRange = 1;
    uint8_t maxRange = 5;
    uint8_t currentPos = minRange;
    bool encoderAset = LOW;
    bool encoderBset = LOW;

public:
    Encoder(uint8_t pinA, uint8_t pinB);
    void encodeA();
    void encodeB();
    void setCurrentPos(uint8_t pos);
    uint8_t getCurrentPos() const;
    void resetPos();
    void setRange(uint8_t min, uint8_t max);
    void keepInRange();


};


#endif //WEBASTO_CONTROLLER_ENCODER_H
