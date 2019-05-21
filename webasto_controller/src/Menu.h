//
// Created by rafal on 19.05.19.
//

#ifndef WEBASTO_CONTROLLER_MENU_H
#define WEBASTO_CONTROLLER_MENU_H


#include <HID.h>

class Menu {
private:
    const uint8_t maxLevel = 2;
    uint8_t currentPos = 0;
    uint8_t currentLevel = 0;

public:
    void printCurrentPage(uint8_t currentLevel, uint8_t currentPos);
    void setHome();


};


#endif //WEBASTO_CONTROLLER_MENU_H
