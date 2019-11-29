/**
 * Read current battery state
 * 
 * @author Alex Kerney
 */
#ifndef BatterySensor_h
#define BatterySensor_h

#include "sensor/sensor.h"
#include "logging/data_logger_manager.h"

/**
 * Battery voltage sensor
 */
class BatterySensor : public Sensor
{
private:
    // Milliseconds when the sensor was last read
    unsigned long last_update_ms;

    // last reading value
    float last_voltage;

public:
    // Set last update time
    void setup();

    // Read the battery voltage once every 10 seconds
    void loop();

    // return the latest value
    float value();
};

#endif
