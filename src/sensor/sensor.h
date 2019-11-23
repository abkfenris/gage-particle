/**
 * Sensors collect data about the environment or device.
 * 
 * @author Alex Kerney
 */
#ifndef Sensor_h
#define Sensor_h

#include "../runnable.h"

/**
 * Sensors collect data about the environment or device.
 * 
 * They present a common interface `.value()` for accessing
 * the most recent value recorded. Some sensors may keep an
 * interal buffer of readings and present a mean or other
 * aggregation.
 */
class Sensor : public Runnable
{
public:
    /**
     * Returns the most recent value of a sensor, or an aggregation
     * of recent readings.
     */
    virtual float value() = 0;
};

#endif