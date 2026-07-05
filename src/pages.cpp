#include "pages.h"

void drawPage1(U8G2_SH1106_128X64_NONAME_F_HW_I2C &display, float airTemp)
{
    display.setFont(u8g2_font_6x12_tf);

    // Header
    display.drawRBox(0, 0, 128, 13, 2);
    display.setDrawColor(0);
    display.drawStr(5, 10, "AIR TEMPERATURE");
    display.setDrawColor(1);

    // Temperature
    char txt[10];
    dtostrf(airTemp, 4, 1, txt);

    display.setFont(u8g2_font_logisoso24_tf);
    display.drawStr(25, 43, txt);

    display.setFont(u8g2_font_8x13_tf);
    display.drawUTF8(93, 40, "°C");

    // Thermometer
    int fill = map((int)airTemp, 0, 50, 0, 20);

    display.drawFrame(12, 24, 5, 25);
    display.drawDisc(14, 48, 4);
    display.drawBox(13, 48 - fill, 3, fill);

    // Progress bar
    int width = map((int)airTemp, 0, 50, 0, 100);

    display.drawFrame(14, 54, 100, 7);
    display.drawBox(15, 55, width, 5);

}

void drawPage2(U8G2_SH1106_128X64_NONAME_F_HW_I2C &display, float waterTemp)
{

  display.setFont(u8g2_font_6x12_tf);

  // Header
  display.drawRBox(0, 0, 128, 13, 2);
  display.setDrawColor(0);
  display.drawStr(5, 10, "WATER TEMPERATURE");
  display.setDrawColor(1);

  char txt[10];
  dtostrf(waterTemp, 4, 1, txt);

  display.setFont(u8g2_font_logisoso24_tf);
  display.drawStr(25, 43, txt);

  display.setFont(u8g2_font_8x13_tf);
  display.drawUTF8(93, 40, "°C");

  // Thermometer
  int fill = map((int)waterTemp, 0, 50, 0, 20);

  display.drawFrame(12, 24, 5, 25);
  display.drawDisc(14, 48, 4);
  display.drawBox(13, 48 - fill, 3, fill);
  
  /*int bar = map((int)waterTemp, 0, 50, 0, 100);

  display.drawFrame(14, 54, 100, 7);
  display.drawBox(15, 55, bar, 5);*/
}


void drawPage3(U8G2_SH1106_128X64_NONAME_F_HW_I2C &display, int waterLevel)
{
    display.setFont(u8g2_font_6x12_tf);

    // Header
    display.drawRBox(0, 0, 128, 13, 2);
    display.setDrawColor(0);
    display.drawStr(5, 10, "WATER LEVEL");
    display.setDrawColor(1);

    int h = map(waterLevel, 0, 100, 0, 34);

    display.drawFrame(48, 18, 26, 36);

    display.drawBox(49, 53 - h, 24, h);

    display.setFont(u8g2_font_logisoso18_tf);

    char txt[10];
    sprintf(txt, "%d%%", waterLevel);

    display.drawStr(80, 42, txt);

    display.setFont(u8g2_font_5x8_tf);

    if (waterLevel > 70)
        display.drawStr(80, 56, "HIGH");
    else if (waterLevel > 30)
        display.drawStr(80, 56, "NORMAL");
    else
        display.drawStr(80, 56, "LOW");
        
}

void drawDashboard(U8G2_SH1106_128X64_NONAME_F_HW_I2C &display, float airTemp, float waterTemp, int waterLevel)
{
    display.setFont(u8g2_font_6x12_tf);

    // Header
    display.drawRBox(0, 0, 128, 13, 2);
    display.setDrawColor(0);
    display.drawStr(5, 10, "DASHBOARD");
    display.setDrawColor(1);

    display.setFont(u8g2_font_6x12_tf);

    display.drawStr(5, 24, "Air");
    display.drawStr(5, 40, "Water");
    display.drawStr(5, 56, "Level");

    char txt[15];

    sprintf(txt, "%.1f C", airTemp);
    display.drawStr(55, 24, txt);

    sprintf(txt, "%.1f C", waterTemp);
    display.drawStr(55, 40, txt);

    sprintf(txt, "%d %%", waterLevel);
    display.drawStr(55, 56, txt);

    display.drawFrame(108, 18, 12, 36);
    // bar
    int h = map(waterLevel, 0, 100, 0, 34);
    display.drawBox(109, 53 - h, 10, h);
}