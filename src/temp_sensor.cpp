#include "temp_sensor.h"

TempSensor::TempSensor(byte dhtPin) : dht(dhtPin)
{
}

void TempSensor::setup()
{
    dht.begin();
}

void TempSensor::loop()
{
}

float TempSensor::tempF()
{
    return dht.getTempFarenheit();
}

