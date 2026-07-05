#include "button.h"

#define BUTTON_PIN 3

uint8_t page = 1;

static unsigned long lastDebounce = 0;
static const unsigned long debounceTime = 50;

void initButton()
{
    pinMode(BUTTON_PIN, INPUT_PULLUP);
}

void handleButton()
{
    static bool lastReading = HIGH;
    static bool buttonState = HIGH;

    bool reading = digitalRead(BUTTON_PIN);

    if (reading != lastReading)
        lastDebounce = millis();

    if ((millis() - lastDebounce) > debounceTime)
    {
        if (reading != buttonState)
        {
            buttonState = reading;

            if (buttonState == LOW)
            {
                page++;

                if (page > 4)
                    page = 1;
            }
        }
    }

    lastReading = reading;
}