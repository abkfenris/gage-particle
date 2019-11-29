/**
 * Read from a Maxbotix ultrasonic sensor via PWM
 * 
 * @author Alex Kerney
 */
#ifndef MaxbotixPWMDistanceSensor_h
#define MaxbotixPWMDistanceSensor_h

#include "sensor/sampled_sensor.h"
#include "logging/data_logger_manager.h"

const int MAXBOTIX_ULTRASOUND_PWM_PIN = D2;

/**
 * Maxbotix PWM ultrasonic sensor
 */
class MaxbotixPWMDistanceSensor : SampledSensor
{
private:
    // Milliseconds when the sensor was last read
    unsigned long last_update_ms;

    // Milliseconds when the sensor was last logged
    unsigned long last_log_ms;

public:
    // Set the pin used
    void setup();

    // Reads the sensor once every 200 ms
    void loop();

    // Read the millimeters from the sensor
    int read_sensor();

    // Recent mean
    float value();
};

#endif