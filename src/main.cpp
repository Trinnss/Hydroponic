#include <Wire.h>
#include <U8g2lib.h>

#include "button.h"
#include "display.h"
#include "sensors.h"

#define SDA_PIN 8
#define SCL_PIN 9

U8G2_SH1106_128X64_NONAME_F_HW_I2C display(U8G2_R0, U8X8_PIN_NONE);

void setup()
{
    //Serial.begin(115200);

    Wire.begin(SDA_PIN, SCL_PIN);

    display.begin();
    display.enableUTF8Print();

    initButton();
    initSensors();
}

void loop()
{
    handleButton();
    readSensors();
    updateDisplay();
}