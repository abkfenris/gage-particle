/**
 * Log data to Ubidots
 * 
 * @author Alex Kerney
 */
#ifndef Ubidots_Data_Logger_h
#define Ubidots_Data_Logger_h

#include "Ubidots.h"
#include "map"
#include "math.h"

#include "data_logger.h"

/**
 * Datalogger to send values up to Ubidots via Particle.publish webhook
 */
class UbidotsLogger : public DataLogger
{
private:
    // Ubidots defined class
    Ubidots ubidots;

    // Name of webhook to submit data to
    char *webhook_name;

    // How many milliseconds between updates
    int update_interval_ms;

    // Milliseconds of last update
    int last_update_ms;

    // Mapping of descriptive keys to data values
    std::map<char *, float> data;

public:
    /**
     * 
     * @param webhook_name
     * @param settings Current settings that has the update frequency
     */
    UbidotsLogger(char *set_webhook_name, struct Settings settings);

    // Set the last_update_ms so that it will update immediately
    void setup();

    // Trigger updates at the update interval
    void loop();

    /**
     * Add new data to be sent next time. Any data with a
     * duplicate key will replace previous data.
     * 
     * @param key Sensor value name
     * @param value Reading from a sensor
     */
    void add_value(char *key, float value);

    // Ignored. Messages are not sent to Ubidots
    void log_message(char *message);

    // Immediately send values to Ubidots
    void persist_values();

    // Update settings from settings struct
    void update_settings(struct Settings settings);
};

#endif