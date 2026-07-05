#include <Arduino.h>
#include <OneWire.h>
#include <DallasTemperature.h>
#include <DHT.h>
#include "sensors.h"

#define DHTPIN 1
#define DHTTYPE DHT22
#define ONE_WIRE_BUS 2

OneWire oneWire(ONE_WIRE_BUS);
DallasTemperature ds18b20(&oneWire);
DHT dht(DHTPIN, DHTTYPE);

float airTemp = NAN;
float humidity = NAN;
float waterTemp = DEVICE_DISCONNECTED_C;
int waterLevel = 73;

static unsigned long lastRead = 0;

void initSensors()
{
    ds18b20.begin();
    dht.begin();
}

void readSensors()
{
    if (millis() - lastRead < 1000)
        return;

    lastRead = millis();

    ds18b20.requestTemperatures();
    waterTemp = ds18b20.getTempCByIndex(0);

    //humidity = dht.readHumidity();
    airTemp = dht.readTemperature();

    // TODO:
    // waterLevel = analogRead(...)
}

bool isDHTOk()
{
    return !(isnan(airTemp) );
}

bool isWaterTempOk()
{
    return waterTemp != DEVICE_DISCONNECTED_C;
}