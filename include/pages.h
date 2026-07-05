#ifndef PAGES_H
#define PAGES_H

#include <U8g2lib.h>

// Function prototype
void drawPage2(U8G2_SH1106_128X64_NONAME_F_HW_I2C &display, float waterTemp);
void drawPage1(U8G2_SH1106_128X64_NONAME_F_HW_I2C &display, float airTemperature, float humidity);
void drawPage3(U8G2_SH1106_128X64_NONAME_F_HW_I2C &display, float waterLevel);
void drawDashboard(U8G2_SH1106_128X64_NONAME_F_HW_I2C &display, float airTemp, float humidity, float waterTemp, float waterLevel);


#endif