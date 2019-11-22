/**
 * Runnables are classes that follow the Arduino pattern for operation.
 * 
 * @author Alex Kerney
 */
#ifndef Runnable_h
#define Runnable_h

#include "Particle.h"

/**
 * Runnables are classes that follow Arduino patterns for operation.
 */
class Runnable
{
public:
    /**
     * Anything that needs to be run during the initial setup phase
     * of device operation.
     */
    virtual void setup() = 0;

    /**
     * Anything that should run periodically in the loop phase of
     * device operation.
     */
    virtual void loop() = 0;
};

#endif
