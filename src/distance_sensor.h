#ifndef DistanceSensor_h
#define DistanceSensor_h

#include "Particle.h"

class DistanceSensor
{
private:
    int last_distance_mm;
    char buf[5];


public:
    void setup();
    void loop();

    int read_sensor();

    float get_distance();
};

#endif