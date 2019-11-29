/**
 * Read from Maxbotix ultrasonic sensor
 * 
 * @author Alex Kerney
 */
#ifndef MaxbotixDistanceSensor_h
#define MaxbotixDistanceSensor_h

#include "Particle.h"
#include "math.h"

#include "sensor/sampled_sensor.h"
#include "logging/data_logger_manager.h"

// Number of samples that should be kept in the statistics history
const int NUMBER_OF_SAMPLES = 100;

/**
 * Maxbotix Distance Sensor
 */
// class MaxbotixDistanceSensor : public Sensor
class MaxbotixDistanceSensor : SampledSensor
{
protected:
    // Milliseconds when the sensor was last read
    unsigned long last_update_ms;

    // Milliseconds when the sensor was last logged
    unsigned long last_log_ms;

public:
    /**
     * Starts the serial connection to the ultrasonic sensor,
     * and sets the update timing
     */
    void setup();

    // Reads the sensor once every 200 ms
    void loop();

    // Return the millimeters from the sensor
    int read_sensor();

    // Return the mean of the last 100 samples
    float value();
};

#endif