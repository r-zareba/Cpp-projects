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


uint8_t lastPos[3];


LiquidCrystal_I2C lcd(0x27, 16, 2); // Change the 0x27
Encoder encoder(ENCODER_A, ENCODER_B);


uint8_t encoderPos;
uint8_t lastEncoderPos;

static bool rotating = false;

static void doEncoderA();
static void doEncoderB();

static uint8_t arrow[8] = {0x0, 0x04 ,0x06, 0x1f, 0x06, 0x04, 0x00, 0x00};
static uint8_t hourArrow[] = {0x08, 0x0C, 0x0E, 0x1F, 0x0E, 0x0C, 0x08, 0x00};

int8_t currentLevel = 0;

bool levelChanged = false;
volatile bool posChanged = false;

// Read params
float waterTemp = 33.3;
float waterLevel = 50.2;
float fuelLevel = 43.4;

// Settings
float temperatureSetting = 45.0;
int8_t startMinute;
int8_t startHour;
int8_t endMinute;
int8_t endHour;

int8_t timeSetterPos;



void printArrow(uint8_t row);
void printPage(const String &item1, const String &item2, uint8_t cursorAt);
void printSingleItem(const String &item, bool cursor);
void printParam(const String &param, const float &value);
void printParams(const String &param1, const String &param2,
                 const float &value1, const float &value2);
void printHourSetting();

template <typename T>
void setSetting(const String &name, T &value, float step, Encoder &encoder);

template <typename T>
void setSetting(T &value, float step, Encoder &encoder);

//void lockScreen()

void keepInRange(int8_t &value, uint8_t min, uint8_t max, bool overflow);


//std::vector<Settings> settings;


Button nextButton(BUTTON_1, LOW);
Button prevButton(BUTTON_2, LOW);
Button homeButton(BUTTON_3, LOW);

unsigned long currentTime;
unsigned long printTime;


void setup()
{
    attachInterrupt(0, doEncoderA, CHANGE);
    attachInterrupt(1, doEncoderB, CHANGE);

    Serial.begin(9600);
    lcd.begin();
    lcd.clear();
    // Create custom symbols
    lcd.createChar(0, arrow);
    lcd.createChar(1, hourArrow);

    lcd.home();

    encoder.setRange(0, 2);
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


    if (levelChanged){
        lcd.clear();

        if (currentLevel == 0) encoder.setRange(0, 2);
        else if (currentLevel == 1 && lastPos[0] == 0) encoder.setRange(0, 2);
        else if (currentLevel == 1 && lastPos[0] == 2) encoder.setRange(0, 1);
        levelChanged = false;
    }

    if (posChanged){
        lcd.clear();

        // If was locked
        if (currentLevel == 1 && lastPos[0] == 1){
            currentLevel = 0;
        }
        lcd.backlight();
        posChanged = false;
    }

    keepInRange(currentLevel, 0, 4, false);
    if (currentLevel == 2 && lastPos[0] == 2) keepInRange(currentLevel, 0, 2, false);
    if (currentLevel == 2 && lastPos[0] == 2 && lastPos[1] == 1) keepInRange(currentLevel, 0, 4, false);
//    else keepInRange(currentLevel, 0, 1, false);


    currentTime = millis();

    if (currentTime - printTime >=500){
        printTime = currentTime;
//        Serial.print("  ");
        Serial.print(encoderPos);
        Serial.print("--->");
        Serial.print(lastPos[0]);
        Serial.print(", ");
        Serial.print(lastPos[1]);
        Serial.print(", ");
        Serial.print(lastPos[2]);
        Serial.print("....");
//        Serial.print(timeSetterPos);
    }




//    Serial.print(lastEncoderPos);
//    Serial.print(encoder.getCurrentPos());


    if (nextButton.isClicked()){
        lastPos[currentLevel] = encoderPos;
        encoder.resetPos();
        currentLevel ++;
        levelChanged = true;
    }

    if (prevButton.isClicked()){
        currentLevel --;
        encoder.setCurrentPos(lastPos[currentLevel]);
        levelChanged = true;
    }

    if (homeButton.isClicked()){
        currentLevel = 0;
        encoder.resetPos();
        levelChanged = true;
    }

    /*
     * Interactive menu logic implementation
     */
    // Level 0 - Main Menu, check only encoder value
    if (currentLevel == 0 && encoderPos == 0){
        printPage("CURRENT PARAMS", "LOCK", 0);
    } else if (currentLevel == 0 && encoderPos == 1){
        printPage("CURRENT PARAMS", "LOCK", 1);
    } else if (currentLevel == 0 && encoderPos == 2){
        printSingleItem("SETTINGS", true);
    }

    // Level 1 - check previous value and encoder pos
    // CURRENT PARAMS clicked
    if (currentLevel == 1 && lastPos[0] == 0 && encoderPos == 0){
        printParams("WATER TEMP", "WATER LVL", waterTemp, waterLevel);
    } else if (currentLevel == 1 && lastPos[0] == 0 && encoderPos == 1){
        printParam("FUEL LVL", fuelLevel);
    }
        // LOCK clicked
    else if (currentLevel == 1 && lastPos[0] == 1) lcd.noBacklight();

        // SETTINGS clicked
    else if (currentLevel == 1 && lastPos[0] == 2 && encoderPos == 0){
        printPage("Temperature", "Time", 0);
    } else if (currentLevel == 1 && lastPos[0] == 2 && encoderPos == 1){
        printPage("Temperature", "Time", 1);
    }

        // SETTING -> Temperature
    else if (currentLevel == 2 && lastPos[0] == 2 && lastPos[1] == 0){
        setSetting("Temperature", temperatureSetting, 0.5, encoder);
    }
        // SETTING -> Time

        //TODO
        //if current level == 3 and lastpos[1] == 1 and timeSetterPos == 9 lub 10
        // setSetting(start hour)
        // TODO
    else if (currentLevel == 2 && lastPos[0] == 2 && lastPos[1] == 1) {
        printHourSetting();

//        if (timeSetterPos == 11) timeSetterPos = 12;
//        if (timeSetterPos == 16) timeSetterPos = 17;

        lcd.setCursor(timeSetterPos, 0);
        if (timeSetterPos > 13) lcd.setCursor(11+(timeSetterPos-16), 1);
        lcd.print("_");

        setSetting(timeSetterPos, 1, encoder);
    } else if (currentLevel == 3 && lastPos[0] == 2 && lastPos[1] == 1 && (timeSetterPos == 9 || timeSetterPos == 10)){
        printHourSetting();
        setSetting(startHour, 1, encoder);
    } else if (currentLevel == 3 && lastPos[0] == 2 && lastPos[1] == 1 && (timeSetterPos == 12 || timeSetterPos == 13)){
        printHourSetting();
        setSetting(startMinute, 1, encoder);
    } else if (currentLevel == 3 && lastPos[0] == 2 && lastPos[1] == 1 && (timeSetterPos == 14 || timeSetterPos == 15)){
        printHourSetting();
        setSetting(endHour, 1, encoder);
    } else if (currentLevel == 3 && lastPos[0] == 2 && lastPos[1] == 1 && (timeSetterPos == 17 || timeSetterPos == 18)){
        printHourSetting();
        setSetting(endMinute, 1, encoder);
    }



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

void printParam(const String &param, const float &value){
    lcd.setCursor(0, 0);
    lcd.print(param);
    lcd.setCursor(12, 0);
    lcd.print(value);
}
void printParams(const String &param1, const String &param2,
                 const float &value1, const float &value2){

    lcd.setCursor(0, 0);
    lcd.print(param1);
    lcd.setCursor(12, 0);
    lcd.print(value1);

    lcd.setCursor(0, 1);
    lcd.print(param2);
    lcd.setCursor(12, 1);
    lcd.print(value2);
}

void printHourSetting(){
    keepInRange(startMinute, 0, 59, true);
    keepInRange(endMinute, 0, 59, true);
    keepInRange(startHour, 0, 23, true);
    keepInRange(endHour, 0, 23, true);
    keepInRange(timeSetterPos, 9, 18, true);

    lcd.setCursor(0, 0);
    lcd.print("START -");
    lcd.setCursor(7, 0);
    lcd.write(1); //my arrow
    lcd.setCursor(9, 0);

    if (startHour < 10) lcd.print(0);

    lcd.print(startHour);
    lcd.print(":");

    if (startMinute < 10) lcd.print(0);

    lcd.print(startMinute);
    lcd.setCursor(0, 1);
    lcd.print("END   -");
    lcd.setCursor(7, 1);
    lcd.write(1); //my arrow
    lcd.setCursor(9, 1);

    if (endHour < 10) lcd.print(0);

    lcd.print(endHour);
    lcd.print(":");
    if (endMinute < 10) lcd.print(0);
    lcd.print(endMinute);
}


// TODO przeniesc do klasy enkoder !
template <typename T>
void setSetting(const String &name, T &value, float step, Encoder &encoderr){
    if (encoder.isRotatingRight()){
        value += step;
        encoder.resetRotating();
    } else if (encoder.isRotatingLeft()){
        value -= step;
        encoder.resetRotating();
    }

    printParam(name, value);

}

template <typename T>
void setSetting(T &value, float step, Encoder &encoderr){
    if (encoder.isRotatingRight()){
        value += step;
        encoder.resetRotating();
    } else if (encoder.isRotatingLeft()){
        value -= step;
        encoder.resetRotating();
    }

}


void keepInRange(int8_t &value, uint8_t min, uint8_t max, bool overflow=false){

    if (overflow){
        if (value > max) value = min;
        if (value < min) value = max;
    } else{
        if (value >= max) value = max;
        if (value <= min) value = min;
    }

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