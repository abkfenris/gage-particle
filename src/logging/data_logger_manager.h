#ifndef Data_Logger_Manager_h
#define Data_Logger_Manager_h

#include "data_logger.h"

/**
 * A DataLoggerManager keeps track of loggers that
 * are added to it, and passes commands to each
 * logger.
 */
class DataLoggerManager : public DataLogger
{
private:
    // List of DataLoggers being managed
    std::list<std::reference_wrapper<DataLogger>> loggers;

public:
    // Trigger setup() of all loaded loggers
    void setup();

    // Trigger loop() of all loaded loggers
    void loop();

    /**
     * Adds a value to be persisted by all loggers.
     * If a new value is added for a given key,
     * then the new value will be used instead.
     * 
     * Usually the value will not be persisted until
     * a specific interval triggered in the loop(),
     * or until persist_values() is explicitly called.
     * 
     * @param key Key that identifies value
     * @param value Value to be persisted
     */
    void add_value(char *key, float value);

    /**
     * Log a message immediately by all loggers
     * 
     * @param message String message to be logged
     */
    void log_message(char *message);

    // Have all loggers persist their current values
    void persist_values();

    /**
     * Update the settings of loaded loggers
     * 
     * @param settings Updated settings to pass to loaded loggers
     */
    void update_settings(struct Settings settings);

    /**
     * Add a new DataLogger to be managed
     * 
     * @param logger DataLogger to be managed
     */
    void add_logger(DataLogger &logger);
};

#endif