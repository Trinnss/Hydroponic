#include "display.h"
#include "pages.h"
#include "sensors.h"
#include <button.h>

extern U8G2_SH1106_128X64_NONAME_F_HW_I2C display;
extern uint8_t page;
void drawSensorError(U8G2_SH1106_128X64_NONAME_F_HW_I2C &display, const char *sensorName)
{
    char msg[32];

    display.setFont(u8g2_font_6x12_tf);
    display.drawStr(18, 20, "SENSOR ERROR");

    snprintf(msg, sizeof(msg), "%s not detected", sensorName);

    display.setFont(u8g2_font_5x8_tf);
    display.drawStr(10, 38, msg);
    display.drawStr(18, 50, "Check Wiring");

    display.drawCircle(110, 18, 8);
    display.drawLine(106, 14, 114, 22);
    display.drawLine(114, 14, 106, 22);
}

void updateDisplay()
{
    display.clearBuffer();

    switch (page)
    {
    case 1:

        if (isDHTOk())
            drawPage1(display, airTemp);
        else
            drawSensorError(display, "DHT22");

        break;

    case 2:

        if (isWaterTempOk())
            drawPage2(display, waterTemp);
        else
            drawSensorError(display, "DS18B20");

        break;

    case 3:

        drawPage3(display, waterLevel);
        break;

    case 4:

        drawDashboard(display,
                      airTemp,
                      waterTemp,
                      waterLevel);

        break;
    }

    for (int i = 0; i < 4; i++)
    {
        if (i == page - 1)
            display.drawDisc(52 + i * 8, 60, 2);
        else
            display.drawCircle(52 + i * 8, 60, 2);
    }

    display.sendBuffer();
}