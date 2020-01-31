#include "sensor/tfmini_plus_lidar_distance.h"

#define TFMINIPLUS_MINIMUM_BETWEEN_READINGS_MS 200
#define TFMINIPLUS_MINIMUM_BETWEEN_LOGS_MS 10000

#define TFMINIPLUS_MINIMUM_STRENGTH 100
#define TFMINIPLUS_MAXIMUM_STRENGTH 65535

void TfMiniPlusLidarDistanceSensor::setup()
{
    // enable 5v power to LIDAR
    pinMode(TFMiniPlus_ENABLE_PIN, OUTPUT);
    digitalWrite(TFMiniPlus_ENABLE_PIN, HIGH);

    Serial1.begin(TFMiniPlus_SERIAL_RATE);

    tfmini.begin(&Serial1);

    // Read MM rather than CM
    tfmini.setMeasurementTo(TFMINI_MEASUREMENT_MM);

    // Only read on demand
    tfmini.setFrameRate(0);
}

void TfMiniPlusLidarDistanceSensor::loop()
{
    if (millis() - last_update_ms >= TFMINIPLUS_MINIMUM_BETWEEN_READINGS_MS)
    {
        tfmini.triggerDetection();

        if (tfmini.readData())
        {
            int strength = tfmini.getSignalStrength();

            if (TFMINIPLUS_MINIMUM_STRENGTH < strength && strength < TFMINIPLUS_MAXIMUM_STRENGTH)
            {
                add(tfmini.getDistance());

                last_update_ms = millis();

                if (millis() - last_log_ms >= TFMINIPLUS_MINIMUM_BETWEEN_LOGS_MS)
                {
                    last_log_ms = millis();

                    DataLog.add_value("lidar:mean", mean());
                    DataLog.add_value("lidar:std_dev", stddev());
                    DataLog.add_value("lidar:median", median());
                    DataLog.add_value("lidar:temp", tfmini.getSensorTemperature());
                }
            }
        }
    }
}

float TfMiniPlusLidarDistanceSensor::value()
{
    return mean();
}