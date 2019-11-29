#include "battery_sensor.h"

#define MINIMUM_BETWEEN_READINGS_MS 10000

void BatterySensor::setup()
{
    last_update_ms = millis() - MINIMUM_BETWEEN_READINGS_MS;
}

void BatterySensor::loop()
{
    if (millis() - last_update_ms >= MINIMUM_BETWEEN_READINGS_MS)
    {
        last_update_ms = millis();

        last_voltage = analogRead(BATT) * 0.0011224;

        DataLog.add_value("voltage", last_voltage);
    }
}

float BatterySensor::value()
{
    return last_voltage;
}