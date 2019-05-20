//
// Created by rafal on 19.05.19.
//

#ifndef WEBASTO_CONTROLLER_MENU_H
#define WEBASTO_CONTROLLER_MENU_H


#include <HID.h>

class Menu {
private:
    const uint8_t maxLevel = 2;
    uint8_t currentPage = 0;
    uint8_t currentLevel = 0;

};


#endif //WEBASTO_CONTROLLER_MENU_H
