//
// Created by rafal on 18.05.19.
//

#include <Arduino.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
//#include <ArduinoSTL.h>
#include "Encoder.h"
#include "Button.h"


#define LED_1 2

// Encoder pins
#define ENCODER_A 2
#define ENCODER_B 3

// Buttons pins
#define BUTTON_1 11
#define BUTTON_2 12
#define BUTTON_3 13


//struct Settings{
//    float x, y, z;
//
//    Settings(float x, float y, float z)
//    :
//    x(x), y(y), z(z)
//    {
//
//    }
//};


String menuLevel1[] = {"Option 1", "Option 2", "CURRENT TEMP", "SETTINGS"};
uint8_t lastPos[3];


LiquidCrystal_I2C lcd(0x27, 16, 2); // Change the 0x27
Encoder encoder(ENCODER_A, ENCODER_B);


uint8_t encoderPos;
uint8_t lastEncoderPos;

static bool rotating = false;

static void doEncoderA();
static void doEncoderB();

static uint8_t arrow[8] = {0x0, 0x04 ,0x06, 0x1f, 0x06, 0x04, 0x00, 0x00};

int8_t currentLevel = 0;

bool levelChanged = false;
volatile bool posChanged = false;


void printArrow(uint8_t row);
void printPage(const String &item1, const String &item2, uint8_t cursorAt);
void printSingleItem(const String &item, bool cursor);
//std::vector<Settings> settings;


Button button1(BUTTON_1, LOW);
Button button2(BUTTON_2, LOW);

uint8_t temperatureSetting = 45;
unsigned long currentTime;
unsigned long printTime;

uint8_t pos;


void setup()
{
    attachInterrupt(0, doEncoderA, CHANGE);
    attachInterrupt(1, doEncoderB, CHANGE);

    Serial.begin(9600);
    lcd.begin();
    lcd.clear();
    lcd.createChar(0, arrow);   //Create the arrow symbol
    lcd.home();

    encoder.setRange(0, 3);
//
//    Settings settings1(1, 2, 3);
//    Settings settings2(4, 5, 6);
//    Settings settings3(7, 8, 9);
//
//    settings.push_back(settings1);
//    settings.push_back(settings2);
//    settings.push_back(settings3);
//
//    for (auto &value: settings){
//        Serial.println(value.x);
//    }

}



void loop()
{
    rotating = true;
    encoderPos = encoder.getCurrentPos();

//    if (currentLevel == 0) lastPos[0] = encoder.getCurrentPos();
//    else if (currentLevel == 2) encoderPos = encoder.getCurrentPos();
//    else if (currentLevel == 3) lastEncoderPos = encoderPos;

    if (levelChanged){
        lcd.clear();
        if (currentLevel == 0) encoder.setRange(0, 3);
        else if (currentLevel == 1 && lastEncoderPos == 3) encoder.setRange(0, 1);
        levelChanged = false;
    }

    if (posChanged){
        lcd.clear();
        posChanged = false;
    }


    if (currentLevel >= 2) currentLevel = 2;
    if (currentLevel <= 0) currentLevel = 0;


    currentTime = millis();

    if (currentTime - printTime >=500){
        printTime = currentTime;
//        Serial.print("  ");
//        Serial.print(encoderPos);
        Serial.print("--->");
        Serial.print(lastPos[0]);
        Serial.print(", ");
        Serial.print(lastPos[1]);
        Serial.print(", ");
        Serial.print(lastPos[2]);
        Serial.print("....");
//        Serial.println(currentLevel);
    }




//    Serial.print(lastEncoderPos);
//    Serial.print(encoder.getCurrentPos());


    if (button1.isClicked()){
        lastPos[currentLevel] = encoderPos;
        if (currentLevel == 0) encoder.resetPos();
        currentLevel ++;
        levelChanged = true;
    }

    if (button2.isClicked()){
        if (currentLevel == 1) encoder.resetPos();
        currentLevel --;
        levelChanged = true;
    }

    pos = lastPos[currentLevel-1];
    switch (currentLevel){
        case 0:
            switch (encoderPos){
                case 0:
                    printPage(menuLevel1[encoderPos], menuLevel1[encoderPos+1], 0);
                    break;

                case 1:
                    printPage(menuLevel1[encoderPos-1], menuLevel1[encoderPos], 1);
                    break;

                case 2:
                    printPage(menuLevel1[encoderPos], menuLevel1[encoderPos+1], 0);
                    break;

                case 3:
                    printPage(menuLevel1[encoderPos-1], menuLevel1[encoderPos], 1);
                    break;


                default:
                    printArrow(0);
            }
//            lastEncoderPos = encoderPos;
            break;

        case 1:
            switch (pos){
                case 0:
                    printSingleItem("ASD", false);
                    break;

                case 1:
                    printSingleItem("ASD", false);
                    break;

                case 2:
                    printSingleItem("ASD", false);
                    break;

                case 3:
                    pos = lastPos[currentLevel];
                    switch (encoderPos){
                        case 0:
                            printPage("Temperature", "Start hour", 0);
                            break;
                        case 1:
                            printPage("Temperature", "Start hour", 1);
                            break;
                        default:
                            printArrow(0);
                            break;
                    }
                    break;

                case 5:
                    printSingleItem("", false);
                    break;


                default:
                    printArrow(0);
            }
//            lastEncoderPos = encoderPos;
            break;


        case 2:
            switch (pos){
                case 0:
                    if (encoder.isRotatingRight()){
                        temperatureSetting ++;
                        encoder.resetRotating();
                    } else if (encoder.isRotatingLeft()){
                        temperatureSetting --;
                        encoder.resetRotating();
                    }

                    lcd.setCursor(0, 0);
                    lcd.print("Temperature: ");
                    lcd.setCursor(13, 0);
                    lcd.print(temperatureSetting);
                    break;
                case 1:
                    break;
                case 2:
                    break;
                default:
                    break;
            }

//            settingLevel = encoder.getCurrentPos();

//
//        case 4:
//            printPage("opcja 3", "opcja 4", 1);
//            break;


        default:
            printArrow(0);
            break;
    }


//    if (currentLevel == 3 && encoderPos == 1){
//        lcd.setCursor(1, 0);
//        lcd.print("Temperature: ");
//        lcd.setCursor(13, 0);
//        lcd.print(temperatureSetting);
//
//        temperatureSetting = encoderPos*10;
//    }


}



void printArrow(uint8_t row){
    lcd.setCursor(0, row);
    lcd.write(0);
}


void printSingleItem(const String &item, bool cursor=true){
    if (cursor) printArrow(0);
    lcd.setCursor(1, 0);
    lcd.print(item);
}


void printPage(const String &item1, const String &item2, uint8_t cursorAt){
    printArrow(cursorAt);
    lcd.setCursor(1, 0);
    lcd.print(item1);
    lcd.setCursor(1, 1);
    lcd.print(item2);
}



void doEncoderA(){
    if (rotating) delay(Encoder::encoderDelay); // debouncing
    encoder.encodeA();
    rotating=false;
    posChanged = true;
}


void doEncoderB(){
    if (rotating) delay(Encoder::encoderDelay); // debouncing
    encoder.encodeB();
    rotating=false;
    posChanged = true;
}