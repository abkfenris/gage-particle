/**
 * Read from Maxbotix ultrasonic sensor
 * 
 * @author Alex Kerney
 */
#ifndef MaxbotixDistanceSensor_h
#define MaxbotixDistanceSensor_h

#include "Particle.h"
#include "stats/Statistics.h"
#include "math.h"

#include "sensor/sensor.h"
#include "logging/data_logger_manager.h"

// Number of samples that should be kept in the statistics history
const int NUMBER_OF_SAMPLES = 100;

/**
 * Maxbotix Distance Sensor
 */
class MaxbotixDistanceSensor : public Sensor
{
private:
    /**
     * Running statistics of samples that are collected at the sensor update frequency
     */
    Statistics stats;
    // Milliseconds when the sensor was last read
    unsigned long last_update_ms;

public:
    MaxbotixDistanceSensor();

    /**
     * Starts the serial connection to the ultrasonic sensor,
     * and sets the update timing
     */
    void setup();

    // Reads the sensor once every 200 ms
    void loop();

    // Return the millimeters from the sensor
    int read_sensor();

    // Return the mean of the last 20 samples
    float value();
    // Return the current standard deviation
    float std_deviation();
};

#endif