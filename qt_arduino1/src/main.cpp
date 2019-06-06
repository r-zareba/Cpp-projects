#include <Arduino.h>
#include "Button.h"


static const uint8_t button1Pin = 51;
static const uint8_t button2Pin = 52;
static const uint8_t button3Pin = 53;

static const uint8_t greenLedPin = 8;
static const uint8_t yellowLedPin = 9;
static const uint8_t redLedPin = 10;

Button button1(button1Pin, LOW);
Button button2(button2Pin, LOW);
Button button3(button3Pin, LOW);

unsigned long currentTime;
unsigned long printTime;

bool ledState = LOW;


void writeLeds(char &led, uint8_t &ledBrightness);

void setup(){

    Serial.begin(9600);

    pinMode(greenLedPin, OUTPUT);
    pinMode(yellowLedPin, OUTPUT);
    pinMode(redLedPin, OUTPUT);

}

void loop(){

    currentTime = millis();

    if (button1.beenClicked()) {
        ledState = !ledState;
        digitalWrite(greenLedPin, ledState);
    }

//    if (button2.isPressed()) digitalWrite(yellowLedPin, HIGH);
//    else digitalWrite(yellowLedPin, LOW);

//    if ((currentTime - printTime) > 200){
//        Serial.print(button2.isPressed());
//        printTime = currentTime;
//    }

    if (Serial.available()){
        char ledPin = Serial.read();
        uint8_t ledBrightness = Serial.parseInt();
        writeLeds(ledPin, ledBrightness);
    }


}

void writeLeds(char &led, uint8_t &brightness){

    Serial.println("\n\nFUNCTION GETS: ");
    Serial.print(led);
    Serial.print(brightness);
    Serial.println("\n\n");

    if (led == 'g') analogWrite(greenLedPin, brightness);
    if (led == 'y') analogWrite(yellowLedPin, brightness);
    if (led == 'r') analogWrite(redLedPin, brightness);

}