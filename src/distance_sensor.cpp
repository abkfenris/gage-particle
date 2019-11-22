#include "math.h"

#include "distance_sensor.h"

#define MINIMUM_READABLE_DISTANCE_MM 500
#define MINIMUM_BETWEEN_READINGS_MS 200

void DistanceSensor::setup()
{
    last_update_ms = millis() - MINIMUM_BETWEEN_READINGS_MS;
    Serial1.begin(9600);
}

void DistanceSensor::loop()
{
    last_distance_mm = read_sensor();
}

int DistanceSensor::read_sensor()
{
    if (millis() - last_update_ms >= MINIMUM_BETWEEN_READINGS_MS)
    {
        while (Serial1.available())
        {
            if (Serial1.peek() == 'R')
            {
                // pop off the R
                Serial1.read();

                for (int i = 0; i < 4; i++)
                {
                    char data = Serial1.read();
                    buf[i] = data;
                }

                int distance_mm = atoi(buf);

                if (MINIMUM_READABLE_DISTANCE_MM <= distance_mm)
                {
                    return distance_mm;
                }
            }
            else
            {
                // Not an R, try to clear
                Serial1.read();
            }

            delay(50);
        }
    }
}

float DistanceSensor::value()
{
    return last_distance_mm;
}