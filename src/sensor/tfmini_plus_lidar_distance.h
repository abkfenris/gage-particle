/**
 * Read from a Benewake TFMini Plus ultrasonic sensor via UART
 * 
 * @author Alex Kerney
 */
#ifndef TfMiniPlusLidarDistanceSensor_h
#define TfMiniPlusLidarDistanceSensor_h

#include "TFMiniPlus.h"

#include "sensor/sampled_sensor.h"
#include "logging/data_logger_manager.h"

// Pin to enable 5V power for LIDAR sensor
const int TFMiniPlus_ENABLE_PIN = D3;

// Serial rate
const int TFMiniPlus_SERIAL_RATE = 115200;

class TfMiniPlusLidarDistanceSensor : SampledSensor
{
private:
    // Milliseconds when the sensor was last read
    unsigned long last_update_ms;

    // Milliseconds when the sensor was last logged
    unsigned long last_log_ms;

    // Sensor interface
    TFMiniPlus tfmini;

public:
    // Set up the enable pin and configure the sensor
    void setup();

    // Read the sensor once every 200 ms
    void loop();

    // Recent mean
    float value();
};

#endif