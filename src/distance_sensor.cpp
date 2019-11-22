#include "math.h"

#include "distance_sensor.h"

const int MINIMUM_READABLE_DISTANCE = 500;

void DistanceSensor::setup()
{
    Serial1.begin(9600);
}

void DistanceSensor::loop()
{
    last_distance_mm = read_sensor();
}

int DistanceSensor::read_sensor()
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

            if (MINIMUM_READABLE_DISTANCE <= distance_mm)
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

float DistanceSensor::get_distance()
{
    return last_distance_mm;
}