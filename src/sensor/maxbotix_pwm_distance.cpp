#include "sensor/maxbotix_pwm_distance.h"

// Use a little bit larger range for error readings
// As PWM can sometimes be a bit less percise
#define MINIMUM_READABLE_DISTANCE_MM 600
#define MAXIMUM_READABLE_DISTANCE_MM 9900
#define ERROR_READING_MM 999

#define MINIMUM_BETWEEN_READINGS_MS 200
#define MINIMUM_BETWEEN_LOGS_MS 10000

void MaxbotixPWMDistanceSensor::setup()
{
    last_update_ms = millis() - MINIMUM_BETWEEN_READINGS_MS;
    last_log_ms = millis() - MINIMUM_BETWEEN_LOGS_MS;
    pinMode(MAXBOTIX_ULTRASOUND_PWM_PIN, INPUT);
}

void MaxbotixPWMDistanceSensor::loop()
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
                last_log_ms = millis();

                DataLog.add_value("pwm:mean", mean());
                DataLog.add_value("pwm:std_dev", stddev());
                DataLog.add_value("pwm:median", median());
            }
        }
    }
}

int MaxbotixPWMDistanceSensor::read_sensor()
{
    return pulseIn(MAXBOTIX_ULTRASOUND_PWM_PIN, HIGH);
}

float MaxbotixPWMDistanceSensor::value()
{
    return mean();
}