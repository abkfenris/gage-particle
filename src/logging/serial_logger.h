/**
 * Log data to serial standard out
 * 
 * @author Alex Kerney
 */
#ifndef Serial_Logger_h
#define Serial_Logger_h

#include "map"

#include "data_logger.h"

#define SERIAL_UPDATE_INTERVAL_MS 15000

/**
 * DataLogger to send values and messages out over serial
 */
class SerialLogger : public DataLogger
{
private:
    // How many milliseconds between updates
    int update_interval_ms = SERIAL_UPDATE_INTERVAL_MS;

    // Milliseconds of last update
    int last_update_ms;

    // Mapping of descriptive keys to data values
    std::map<char *, float> data;

public:
    // Makes sure that the Serial port has started
    void setup();

    // Triggers updates at specified interval
    void loop();

    /**
     * Add new data to be logged to serial. Any data with a
     * duplicate key will replace previous data.
     * 
     * @param key Sensor value name
     * @param value Reading from a sensor
     */
    void add_value(char *key, float value);

    // Log message to serial
    void log_message(String message);

    // Immediately log out values to serial
    void persist_values();

    // Ignore settings updates
    void update_settings(struct Settings settings);
};

#endif