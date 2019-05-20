//
// Created by rafal on 18.05.19.
//

#include <Arduino.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <ArduinoSTL.h>
#include "Encoder.h"


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




LiquidCrystal_I2C lcd(0x27, 16, 2); // Change the 0x27
Encoder encoder(ENCODER_A, ENCODER_B);

uint8_t encoderPos = 0;
static bool rotating = false;
uint8_t encoderDelay = 5;

static void doEncoderA();
static void doEncoderB();

static uint8_t arrow[8] = {0x0, 0x04 ,0x06, 0x1f, 0x06, 0x04, 0x00, 0x00};

unsigned long
    lastTimeLcd = 0,
    lastTimeButton = 0;

uint8_t lcdDelay = 20;
uint8_t buttonDelay = 20;

uint8_t currentLevel = 0;

bool button1State;
bool button2State;

bool lastbutton1State = LOW;
bool lastbutton2State = LOW;

bool levelChanged = false;
volatile bool posChanged = false;



void printArrow(uint8_t row);
void printPage(const String &item1, const String &item2, uint8_t cursorAt);
//std::vector<Settings> settings;


void setup()
{
    attachInterrupt(0, doEncoderA, CHANGE);
    attachInterrupt(1, doEncoderB, CHANGE);

    pinMode(BUTTON_1, INPUT);
    pinMode(BUTTON_2, INPUT);
    pinMode(BUTTON_3, INPUT);

    Serial.begin(9600);
    lcd.begin();
    lcd.clear();
    lcd.createChar(0, arrow);   //Create the arrow symbol
    lcd.home();

    encoder.setRange(1, 4);
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

    if (posChanged || levelChanged){
        lcd.clear();
        posChanged = false;
        levelChanged = false;
    }


    if ((millis() - lastTimeLcd) > lcdDelay){
//        lcd.clear();
        Serial.print("Pos: ");
        Serial.println(encoderPos);
        Serial.print("Level: ");
        Serial.println(currentLevel);
        lastTimeLcd = millis();
    }

    bool button1 = digitalRead(BUTTON_1);
    bool button2 = digitalRead(BUTTON_2);


    if (button1 != lastbutton1State) lastTimeButton = millis();

    if ((millis() - lastTimeButton) > buttonDelay){
        if (button1 != button1State){
            button1State = button1;

            if (button1State == HIGH){
                encoder.resetPos();
                currentLevel ++;
                levelChanged = true;
            }
        }
    }


    if (button2 != lastbutton2State) lastTimeButton = millis();

    if ((millis() - lastTimeButton) > buttonDelay){
        if (button2 != button2State){
            button2State = button2;

            if (button2State == HIGH){
                encoder.resetPos();
                currentLevel --;
                levelChanged = true;
            }
        }
    }
    lastbutton1State = button1;
    lastbutton2State = button2;



    if (currentLevel >= 3) currentLevel = 3;
    if (currentLevel <= 1) currentLevel = 1;

    if (levelChanged && currentLevel == 1){
        encoder.setRange(1, 4);
        levelChanged = false;
    }
    else if (levelChanged && currentLevel == 2){
        encoder.setRange(1, 5);
        levelChanged = false;
    }


    switch (currentLevel){
        case 1:
            switch (encoderPos){
                case 1:
                    printPage("Option 1", "Option 2", 0);
                    break;

                case 2:
                    printPage("Option 1", "Option 2", 1);
                    break;

                case 3:
                    printPage("Option 3", "Option 4", 0);
                    break;

                case 4:
                    printPage("Option 3", "Option 4", 1);
                    break;


                default:
                    printArrow(0);
            }
            break;

        case 2:
//            encoder.setRange(1, 5);
            switch (encoderPos){
                case 1:
                    printPage("Temperature", "Start hour", 0);
                    break;

                case 2:
                    printPage("Temperature", "Start hour", 1);
                    break;

                case 3:
                    printPage("Start minute", "End hour", 0);
                    break;

                case 4:
                    printPage("Start minute", "End hour", 1);
                    break;

                case 5:
                    printPage("End minute", "", 0);
                    break;


                default:
                    printArrow(0);
            }
            break;


//        case 3:
//            printPage("opcja 3", "opcja 4", 0);
//            break;
//
//        case 4:
//            printPage("opcja 3", "opcja 4", 1);
//            break;


        default:
            printArrow(0);
    }


}



void printArrow(uint8_t row){
    lcd.setCursor(0, row);
    lcd.write(0);
}


void printPage(const String &item1, const String &item2, uint8_t cursorAt){
    printArrow(cursorAt);
    lcd.setCursor(1, 0);
    lcd.print(item1);
    lcd.setCursor(1, 1);
    lcd.print(item2);


}



void doEncoderA(){
    if (rotating) delay(encoderDelay); // debouncing
    encoder.encodeA();
    rotating=false;
    posChanged = true;
}


void doEncoderB(){
    if (rotating) delay(encoderDelay); // debouncing
    encoder.encodeB();
    rotating=false;
    posChanged = true;
}