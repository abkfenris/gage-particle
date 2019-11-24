/**
 * Temperature from Grove Temperature and Humidity sensor
 * 
 * @author Alex Kerney
 */
#ifndef GroveTempSensor_h
#define GroveTempSensor_h

#include "Particle.h"
#include "Grove_Temperature_And_Humidity_Sensor.h"

#include "sensor/sensor.h"
#include "logging/data_logger_manager.h"

/**
 * Grove Temperature Sensor
 */
class GroveTempSensor : public Sensor
{
private:
    // Milliseconds when the sensor was last read
    unsigned long last_update_ms;
    // Last read sensor value
    float last_temp_f;
    // sensor
    DHT dht;

public:
    /**
     * Grove Temperature Sensor
     * 
     * @param dhtPin Pin on breakout board where sensor cable is connected
     */
    GroveTempSensor(byte dhtPin);

    // Start up temperature sensor
    void setup();
    // Update sensor readings once per second
    void loop();
    // Return the most recent temperature value
    float value();
};

#endif