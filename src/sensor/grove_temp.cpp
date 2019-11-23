#include "sensor/grove_temp.h"

#define MINIMUM_BETWEEN_READINGS_MS 1000

GroveTempSensor::GroveTempSensor(byte dhtPin) : dht(dhtPin)
{
    last_update_ms = millis() - MINIMUM_BETWEEN_READINGS_MS;
}

void GroveTempSensor::setup()
{
    dht.begin();
}

void GroveTempSensor::loop()
{
    if (millis() - last_update_ms >= MINIMUM_BETWEEN_READINGS_MS)
    {
        last_temp_f = dht.getTempFarenheit();
        DataLog.add_value("temperature", value());
    }
}

float GroveTempSensor::value()
{
    return last_temp_f;
}
