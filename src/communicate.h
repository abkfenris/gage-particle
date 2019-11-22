#ifndef Communicate_h
#define Communicate_h

#include "Particle.h"
#include "Ubidots.h"
#include "math.h"
#include "map"

#include "runnable.h"

class Communicate : public Runnable
{
private:
    Ubidots ubidots;
    char *webhook_name;
    int update_interval_ms;
    int last_update_ms;
    std::map<char *, float> data;

public:
    Communicate(char *webhook_name, long update_interval_ms);
    void setup();
    void loop();

    void add_value(char *key, float value);
};

#endif
