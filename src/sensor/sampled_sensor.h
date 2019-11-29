/**
 * A sensor that has an internal sample array
 * 
 * @author Alex Kerney
 */
#ifndef SampleSensor_h
#define SampleSensor_h

#include "math.h"

#include "sensor/sensor.h"

#define SAMPLED_SENSOR_NUMBER_OF_SAMPLES 100

/**
 * A sensor that has an internal array of samples
 * and methods to access them
 */
class SampledSensor : public Sensor
{
protected:
    int number_of_samples = SAMPLED_SENSOR_NUMBER_OF_SAMPLES;
    float samples[SAMPLED_SENSOR_NUMBER_OF_SAMPLES] = {};
    int insert_index = 0;
    int added_count = 0;

    void add(float value);
    float mean();
    float stddev();
    void bubble_sort(float sorted[]);
    float median();
};

#endif