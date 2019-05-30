//
// Created by rafal on 18.05.19.
//

#ifndef WEBASTO_CONTROLLER_ENCODER_H
#define WEBASTO_CONTROLLER_ENCODER_H


#include <HID.h>


class Encoder {
private:
    const uint8_t pinA;
    const uint8_t pinB;
    uint8_t minRange = 0;
    uint8_t maxRange = 3;
    int8_t currentPos = minRange;
    bool encoderAset = LOW;
    bool encoderBset = LOW;
    bool rotatingRight = false;
    bool rotatingLeft = false;

public:
    static const uint8_t encoderDelay;

    Encoder(uint8_t pinA, uint8_t pinB);
    void encodeA();
    void encodeB();
    void setCurrentPos(uint8_t pos);
    uint8_t getCurrentPos() const;
    void resetPos();
    void setRange(uint8_t min, uint8_t max);
    void keepInRange();
    bool isRotatingLeft() const;
    bool isRotatingRight() const;
    void resetRotating();


};


#endif //WEBASTO_CONTROLLER_ENCODER_H
