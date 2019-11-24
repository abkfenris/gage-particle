/**
 * Log data via Particle.publish
 * 
 * @author Alex Kerney
 */
#ifndef Publish_Logger_h
#define Publish_Logger_h

#include "map"
#include "math.h"

#include "JsonParserGeneratorRK.h"

#include "data_logger.h"

/**
 * Track the time that each value was published at
 */
struct ValueTime
{
    // Value
    float value;
    // Time in seconds since epoch
    uint32_t time;
};

/**
 * Data logger to send values via Particle.publish in
 * a Ubidots compatible format
 */
class PublishLogger : public DataLogger
{
private:
    // Name of webhook to submit data to
    char *webhook_name;

    // How many milliseconds between updates
    unsigned long update_interval_ms;

    // Milliseconds of last update
    unsigned long last_update_ms;

    // Mapping of descriptive keys to data values
    std::map<char *, struct ValueTime> data;

public:
    /**
     * 
     * @param webhook_name
     * @param settings Current settings that has the update frequency
     */
    PublishLogger(char *set_webhook_name, struct Settings settings);

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

    // Ignored. Messages are not sent to Particle.publish
    void log_message(String message);

    // Immediately send values to Particle.publish
    void persist_values();

    // Update settings from settings struct
    void update_settings(struct Settings settings);
};

#endif