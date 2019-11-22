/**
 * Temperature from Grove Temperature and Humidity sensor
 * 
 * @author Alex Kerney
 */
#ifndef TempSensor_h
#define TempSensor_h

#include "Particle.h"
#include "Grove_Temperature_And_Humidity_Sensor.h"

#include "sensor.h"

/**
 * Grove Temperature Sensor
 */
class TempSensor : public Sensor
{
private:
    // Milliseconds when the sensor was last read
    int last_update_ms;
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
    TempSensor(byte dhtPin);

    // Start up temperature sensor
    void setup();
    // Update sensor readings once per second
    void loop();
    // Return the most recent temperature value
    float value();
};

#endif