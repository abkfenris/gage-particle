#ifndef DistanceSensor_h
#define DistanceSensor_h

#include "Particle.h"

#include "sensor.h"

class DistanceSensor : public Sensor
{
private:
    int last_distance_mm;
    int last_update_ms;
    char buf[5];

public:
    void setup();
    void loop();

    int read_sensor();

    float value();
};

#endif