/**
 * Log data to an SD card
 * 
 * @author Alex Kerney
 */
#ifndef SD_Logger_h
#define SD_Logger_h

#include "SdFat.h"
#include "JsonParserGeneratorRK.h"
#include "SdCardLogHandlerRK.h"

#include "data_logger.h"

/**
 * DataLogger to send values and messages to an SD card
 */
class SDLogger : public DataLogger
{
private:
    // Interface for working with SD cards
    SdCardPrintHandler &sd_print;

public:
    /**
     * Initialize a new SD card logger
     * 
     * @param sd_print_handler Requires initialized SDCardPrintHandler.
     * This also allows for configuration of the sd handler rotation.
     */
    SDLogger(SdCardPrintHandler &sd_print_handler);

    // Setup logging to card
    void setup();

    // Not implemented, things are logged immediately
    void loop();

    /**
     * Logs key, value and time recieved immediately to the SD card
     * 
     * @param key Sensor value name
     * @param value Reading from a sensor
     */
    void add_value(char *key, float value);

    // Logs the message to the sd card
    void log_message(String message);

    // Not implemented. Values and messages are immediately logged
    void persist_values();

    // Not implemented. No settings to update
    void update_settings(struct Settings settings);
};

#endif