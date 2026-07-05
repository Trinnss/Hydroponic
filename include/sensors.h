#ifndef SENSORS_H
#define SENSORS_H

extern float airTemp;
extern float humidity;
extern float waterTemp;
extern float waterLevel;

void initSensors();
void readSensors();

bool isDHTOk();
bool isWaterTempOk();

#endif