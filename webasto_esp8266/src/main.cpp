#include <Arduino.h>
#include <SPI.h>               // include SPI library
#include <Adafruit_GFX.h>      // include adafruit graphics library
#include <Adafruit_PCD8544.h>  // include adafruit PCD8544 (Nokia 5110) library

#include "Encoder.h"
#include "Button.h"

// Nokia 5110 LCD module connections (CLK, DIN, D/C, CS, RST)
Adafruit_PCD8544 display = Adafruit_PCD8544(D4, D3, D2, D1, D0);

const static uint8_t encoderApin = 12;
const static uint8_t encoderBpin = 14;

static volatile bool posChanged = false;
static volatile bool rotating = false;

static void doEncoderA();
static void doEncoderB();

unsigned long currentTime;
unsigned long printTime;

uint8_t encoderPos;

Encoder encoder(encoderApin, encoderBpin);

void setup()   {
    Serial.begin(115200);
//
    attachInterrupt(digitalPinToInterrupt(D5) ,doEncoderA, CHANGE);
    attachInterrupt(digitalPinToInterrupt(D6), doEncoderB, CHANGE);

    encoder.setRange(0, 10);

    display.begin();
    // init done

    // you can change the contrast around to adapt the display
    // for the best viewing!
    display.setContrast(50);
    display.clearDisplay();


    // text display tests
    display.setTextSize(1);
    display.setTextColor(BLACK);
    display.setCursor(0,0);
    display.println("Dziala gowno !!!!");
    display.setTextColor(WHITE, BLACK); // 'inverted' text
    display.println(3.141592);
    display.setTextSize(2);
    display.setTextColor(BLACK);
    display.print("0x"); display.println(0xDEADBEEF, HEX);
    display.display();
    delay(2000);
// 
//  // rotation example
//  display.clearDisplay();
//  display.setRotation(1);  // rotate 90 degrees counter clockwise, can also use values of 2 and 3 to go further.
//  display.setTextSize(1);
//  display.setTextColor(BLACK);
//  display.setCursor(0,0);
//  display.println("Rotation");
//  display.setTextSize(2);
//  display.println("Example!");
//  display.display();
//  delay(2000);
// 
//  // revert back to no rotation
//  display.setRotation(0);
// 
//  // miniature bitmap display
//  display.clearDisplay();
//  display.drawBitmap(30, 16,  logo16_glcd_bmp, 16, 16, 1);
//  display.display();
// 
//  // invert the display
//  display.invertDisplay(true);
//  delay(1000); 
//  display.invertDisplay(false);
//  delay(1000); 
// 
//  // draw a bitmap icon and 'animate' movement
//  testdrawbitmap(logo16_glcd_bmp, LOGO16_GLCD_WIDTH, LOGO16_GLCD_HEIGHT);
}
// 

void loop() {

    currentTime = millis();
    encoderPos = encoder.getCurrentPos();

    if (currentTime - printTime >=500){
        printTime = currentTime;
//        Serial.print("  ");
        Serial.print(encoderPos);
//        Serial.print("--->");
//        Serial.print(lastPos[0]);
//        Serial.print(", ");
//        Serial.print(lastPos[1]);
//        Serial.print(", ");
//        Serial.print(lastPos[2]);
//        Serial.print("....");
//        Serial.print(timeSetterPos);
    }

}




// External Interupts functions to trigger encoder
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