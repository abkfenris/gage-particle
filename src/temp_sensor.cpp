#include "temp_sensor.h"

#define MINIMUM_BETWEEN_READINGS_MS 1000

TempSensor::TempSensor(byte dhtPin) : dht(dhtPin)
{
    last_update_ms = millis() - MINIMUM_BETWEEN_READINGS_MS;
}

void TempSensor::setup()
{
    dht.begin();
}

void TempSensor::loop()
{
    if (millis() - last_update_ms >= MINIMUM_BETWEEN_READINGS_MS)
    {
        last_temp_f = dht.getTempFarenheit();
    }
}

float TempSensor::value()
{
    return last_temp_f;
}
