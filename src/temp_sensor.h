#ifndef TempSensor_h
#define TempSensor_h

#include "Particle.h"
#include "Grove_Temperature_And_Humidity_Sensor.h"

#include "sensor.h"

class TempSensor : public Sensor
{
private:
    DHT dht;

public:
    TempSensor(byte dhtPin);

    void setup();
    void loop();
    float value();
};

#endif