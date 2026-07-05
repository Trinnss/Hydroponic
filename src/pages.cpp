#include "pages.h"
uint8_t waveOffset = 0;
void drawPage1(U8G2_SH1106_128X64_NONAME_F_HW_I2C &display,
               float airTemp,
               float humidity)
{
    //================ Header ================
    display.setFont(u8g2_font_6x12_tf);

    display.drawRBox(0, 0, 128, 13, 2);

    display.setDrawColor(0);
    const char *title = "AIR TEMPERATURE";
    display.drawStr((128 - display.getStrWidth(title)) / 2, 10, title);
    display.setDrawColor(1);

    //================ Thermometer ================
    const int thermX = 15;
    const int thermY = 18;
    const int thermH = 26;

    // Outline
    display.drawRFrame(thermX, thermY, 8, thermH, 2);

    // Bulb
    display.drawDisc(thermX + 4, thermY + thermH + 4, 5);

    // Scale marks
    for (int i = 0; i < 5; i++)
    {
        display.drawHLine(thermX + 10, thermY + i * 6, 3);
    }

    // Animated fill
    static int currentFill = 0;

    int targetFill = map((int)constrain(airTemp, 0, 50), 0, 50, 0, thermH - 2);

    if (currentFill < targetFill)
        currentFill++;

    if (currentFill > targetFill)
        currentFill--;

    display.drawBox(
        thermX + 2,
        thermY + thermH - currentFill,
        4,
        currentFill);

    // Fill inside bulb
    display.drawDisc(thermX + 4, thermY + thermH + 4, 3);

    //================ Temperature ================
    char tempTxt[8];
    sprintf(tempTxt, "%.1f", airTemp);

    display.setFont(u8g2_font_logisoso20_tf);
    display.drawStr(40, 38, tempTxt);

    display.setFont(u8g2_font_8x13_tf);
    display.drawUTF8(102, 34, "°C");

    //================ Humidity Badge ================
    display.drawRFrame(42, 41, 78, 16, 3);

    display.setFont(u8g2_font_6x12_tf);

    char humTxt[10];
    sprintf(humTxt, "%.1f%%", humidity);

    display.drawStr(48, 53, "HUM");
    display.drawStr(74, 53, humTxt);
}

void drawPage2(U8G2_SH1106_128X64_NONAME_F_HW_I2C &display, float waterTemp)
{

    display.setFont(u8g2_font_6x12_tf);

    // Header
    display.drawRBox(0, 0, 128, 13, 2);
    display.setDrawColor(0);
    const char *title = "WATER TEMPERATURE";
    display.drawStr((128 - display.getStrWidth(title)) / 2, 10, title);
    display.setDrawColor(1);

    const int thermX = 15;
    const int thermY = 18;
    const int thermH = 26;

    // Outline
    display.drawRFrame(thermX, thermY, 8, thermH, 2);

    // Bulb
    display.drawDisc(thermX + 4, thermY + thermH + 4, 5);

    // Scale marks
    for (int i = 0; i < 5; i++)
    {
        display.drawHLine(thermX + 10, thermY + i * 6, 3);
    }

    // Animated fill
    static int currentFill = 0;

    int targetFill = map((int)constrain(waterTemp, 0, 50), 0, 50, 0, thermH - 2);

    if (currentFill < targetFill)
        currentFill++;

    if (currentFill > targetFill)
        currentFill--;

    display.drawBox(
        thermX + 2,
        thermY + thermH - currentFill,
        4,
        currentFill);

    // Fill inside bulb
    display.drawDisc(thermX + 4, thermY + thermH + 4, 3);

    //================ Temperature ================
    char tempTxt[8];
    sprintf(tempTxt, "%.1f", waterTemp);

    display.setFont(u8g2_font_logisoso20_tf);
    display.drawStr(40, 45, tempTxt);

    display.setFont(u8g2_font_8x13_tf);
    display.drawUTF8(102, 40, "°C");
}

void drawPage3(U8G2_SH1106_128X64_NONAME_F_HW_I2C &display, float waterLevel)
{
    //================ Header ================
    display.drawRBox(0, 0, 128, 13, 2);
    display.setDrawColor(0);
    display.setFont(u8g2_font_6x12_tf);
    const char *title = "WATER LEVEL";
    display.drawStr((128 - display.getStrWidth(title)) / 2, 10, title);
    display.setDrawColor(1);

    // Clamp value
    waterLevel = constrain(waterLevel, 0, 100);

    // Tank dimensions
    const int tankX = 12;
    const int tankY = 19;
    const int tankW = 28;
    const int tankH = 40;

    // Water height
    int fillHeight = map(waterLevel, 0, 100, 0, tankH - 2);

    // Tank
    display.drawRFrame(tankX, tankY, tankW, tankH, 4);

    // Tank cap
    //  display.drawBox(tankX + 7, tankY - 3, 10, 3);
    // scale
    for (int i = 0; i <= 4; i++)
    {
        int yy = tankY + i * (tankH / 4);

        display.drawHLine(tankX + tankW + 4, yy, 3);
    }

    int waterHeight = map(waterLevel, 0, 100, 0, tankH - 2);
    int y = tankY + tankH - waterHeight;

    for (int x = tankX + 2; x < tankX + tankW - 2; x++)
    {
        int wave = (x + waveOffset) % 8;

        int yy;

        if (wave < 2)
            yy = y;
        else if (wave < 4)
            yy = y - 1;
        else if (wave < 6)
            yy = y;
        else
            yy = y + 1;

        display.drawPixel(x, yy);
    }
    display.drawBox(
        tankX + 1,
        y + 1,
        tankW - 2,
        tankY + tankH - y - 2);

    // Percentage
    display.setFont(u8g2_font_logisoso18_tf);

    char txt[8];
    sprintf(txt, "%d%%", (int)waterLevel);

    display.drawStr(63, 37, txt);

    // Status
    display.drawRFrame(60, 41, 53, 15, 4);

    display.setFont(u8g2_font_6x12_tf);

    if (waterLevel < 30)
        display.drawStr(75, 51, "LOW");
    else if (waterLevel < 75)
        display.drawStr(67, 52, "NORMAL");
    else
        display.drawStr(72, 52, "HIGH");
    waveOffset++;
    waveOffset %= 8;
}

void drawDashboard(U8G2_SH1106_128X64_NONAME_F_HW_I2C &display,
                   float airTemp,
                   float humidity,
                   float waterTemp,
                   float waterLevel)
{
    //================ Header =================
    display.setFont(u8g2_font_6x12_tf);

    display.drawRBox(0, 0, 128, 13, 2);
    display.setDrawColor(0);

    const char *title = "DASHBOARD";
    display.drawStr((128 - display.getStrWidth(title)) / 2, 10, title);

    display.setDrawColor(1);

    //=============== Cards ===================
    display.drawRFrame(4, 17, 58, 19, 3);
    display.drawRFrame(66, 17, 58, 19, 3);

    display.drawRFrame(4, 39, 58, 19, 3);
    display.drawRFrame(66, 39, 58, 19, 3);

    char txt[12];

    //----------- Air Temp --------------------
    display.setFont(u8g2_font_5x8_tf);
    display.drawStr(8, 24, "AIR TEMP");

    sprintf(txt, "%.1fC", airTemp);

    display.setFont(u8g2_font_6x12_tf);
    display.drawStr((4 + (58 - display.getStrWidth(txt)) / 2), 33, txt);

    //----------- Humidity --------------------
    display.setFont(u8g2_font_5x8_tf);
    display.drawStr(70, 24, "HUMIDITY");

    sprintf(txt, "%.1f%%", humidity);

    display.setFont(u8g2_font_6x12_tf);
    display.drawStr((66 + (58 - display.getStrWidth(txt)) / 2), 33, txt);

    //----------- Water Temp ------------------
    display.setFont(u8g2_font_5x8_tf);
    display.drawStr(8, 46, "WATER TMP");

    sprintf(txt, "%.1fC", waterTemp);

    display.setFont(u8g2_font_6x12_tf);
    display.drawStr((4 + (58 - display.getStrWidth(txt)) / 2), 55, txt);

    //----------- Water Level -----------------
    display.setFont(u8g2_font_5x8_tf);
    display.drawStr(70, 46, "LEVEL");

    sprintf(txt, "%.0f%%", waterLevel);

    display.setFont(u8g2_font_6x12_tf);
    display.drawStr((66 + (58 - display.getStrWidth(txt)) / 2), 55, txt);

    //=========== Corner Decorations ==========
    // Top-left card
    display.drawPixel(7,20);
    display.drawPixel(58,20);

    // Top-right card
    display.drawPixel(69,20);
    display.drawPixel(120,20);

    // Bottom-left card
    display.drawPixel(7,42);
    display.drawPixel(58,42);

    // Bottom-right card
    display.drawPixel(69,42);
    display.drawPixel(120,42);
}