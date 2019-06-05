//
// Created by rafal on 04.06.19.
//

#ifndef CAMPER_CONTROLLER_ENCODER_H
#define CAMPER_CONTROLLER_ENCODER_H


#include <HID.h>


class Encoder {
private:
    const uint8_t pinA;
    const uint8_t pinB;
    uint8_t minRange = 0;
    uint8_t maxRange = 2;
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



#endif //CAMPER_CONTROLLER_ENCODER_H
