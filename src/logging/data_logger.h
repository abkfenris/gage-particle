/**
 * Tools for logging data and messages,
 * and managing multiple methods of doing so.
 * 
 * @author Alex Kerney
 */
#ifndef Data_Logger_h
#define Data_Logger_h

#include "Particle.h"
#include "list"

#include "../runnable.h"
#include "../settings.h"

/**
 * DataLoggers present common interfaces for
 * recording values or messages.
 * 
 * Not all loggers will handle both values
 * and messages.
 */
class DataLogger : public Runnable
{
public:
    /**
     * Adds a value to be persisted. If a new value
     * is added for a given key, then the new value
     * will be used instead.
     * 
     * Usually the value will not be persisted until
     * a specific interval triggered in the loop(),
     * or until persist_values() is explicitly called.
     * 
     * @param key Key that identifies value
     * @param value Value to be persisted
     */
    virtual void add_value(char *key, float value) = 0;

    /**
     * Log a message immediately.
     * 
     * @param message Message to be immediately logged.
     */
    virtual void log_message(String message) = 0;

    /**
     * Persist any known values immediately.
     */
    virtual void persist_values() = 0;

    /**
     * Update any settings necessary to run the logger
     * 
     * @param settings Settings struct
     */
    virtual void update_settings(struct Settings settings) = 0;
};

#endif