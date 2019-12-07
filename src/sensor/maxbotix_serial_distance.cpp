#include "maxbotix_serial_distance.h"

#define MINIMUM_READABLE_DISTANCE_MM 500
#define MAXIMUM_READABLE_DISTANCE_MM 9999
#define ERROR_READING_MM 999

#define MINIMUM_BETWEEN_READINGS_MS 200
#define MINIMUM_BETWEEN_LOGS_MS 10000

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
        if (MINIMUM_READABLE_DISTANCE_MM < distance_mm && distance_mm < MAXIMUM_READABLE_DISTANCE_MM && distance_mm != ERROR_READING_MM)
        {
            add(distance_mm);

            last_update_ms = millis();

            if (millis() - last_log_ms >= MINIMUM_BETWEEN_LOGS_MS && added_count >= 10)
            {
                DataLog.add_value("distance", value());
                DataLog.add_value("std_dev", stddev());
                DataLog.add_value("median", median());
            }
        }
    }
}

int MaxbotixDistanceSensor::read_sensor() // adapted from https://community.particle.io/t/maxbotix-sensor-and-ttl-serial/36831/13
{
    char buf[7];
    unsigned long timeout_ms = 0;

    while (Serial1.available())
    {
        if (Serial1.peek() == 'R')
        {
            if (!timeout_ms)
            {
                timeout_ms = millis(); // store timestamp when  R is found
            }

            if (Serial1.available() >= 5)
            {
                memset(buf, 0x00, sizeof(buf));

                Serial1.readBytes(buf, 6);

                int distance_mm = atoi(&buf[1]);

                return distance_mm;
            }
            else if (millis() - timeout_ms > 1000)
            {
                if (Serial1.available() > 0)
                {
                    Serial1.read(); // flush outdated R
                    timeout_ms = 0;
                }
            }
        }
        else
        {
            if (Serial1.available() > 0)
            {
                // Not an R, try to clear
                Serial1.read();
            }
        }

        delay(MINIMUM_BETWEEN_READINGS_MS);
    }
}

float MaxbotixDistanceSensor::value()
{
    return mean();
}
