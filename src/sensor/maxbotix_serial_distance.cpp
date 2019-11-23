#include "maxbotix_serial_distance.h"

#define MINIMUM_READABLE_DISTANCE_MM 500
#define MAXIMUM_READABLE_DISTANCE_MM 9999
#define MINIMUM_BETWEEN_READINGS_MS 200

MaxbotixDistanceSensor::MaxbotixDistanceSensor() : stats(NUMBER_OF_SAMPLES){};

void MaxbotixDistanceSensor::setup()
{
    last_update_ms = millis() - MINIMUM_BETWEEN_READINGS_MS;
    Serial1.begin(9600);
}

void MaxbotixDistanceSensor::loop()
{
    if (millis() - last_update_ms >= MINIMUM_BETWEEN_READINGS_MS)
    {
        int distance_mm = read_sensor();
        if (MINIMUM_READABLE_DISTANCE_MM <= distance_mm && distance_mm < MAXIMUM_READABLE_DISTANCE_MM)
        {
            stats.addData(distance_mm);
            last_update_ms = millis();

            DataLog.add_value("distance", value());
            DataLog.add_value("std_dev", std_deviation());
        }
    }
}

int MaxbotixDistanceSensor::read_sensor()
{

    while (Serial1.available())
    {
        if (Serial1.peek() == 'R')
        {
            // pop off the R
            Serial1.read();

            char buf[5];

            for (int i = 0; i < 4; i++)
            {
                char data = Serial1.read();
                buf[i] = data;
            }

            int distance_mm = atoi(buf);

            return distance_mm;
        }
        else
        {
            // Not an R, try to clear
            Serial1.read();
        }

        delay(MINIMUM_BETWEEN_READINGS_MS);
    }
}

float MaxbotixDistanceSensor::value()
{
    return stats.mean();
}

float MaxbotixDistanceSensor::std_deviation()
{
    return stats.stdDeviation();
}