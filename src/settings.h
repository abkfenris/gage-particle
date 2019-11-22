/**
 * Common management of settings controlling device operation.
 * 
 * @author Alex Kerney
 */
#ifndef Setting_Manager_h
#define Setting_Manager_h

#include "Particle.h"

#include "runnable.h"

// Setting EEPROM address
const int SETTING_EEPROM_ADDRESS = 10;

// Version history

// Ubidots update timing is introduced in version 1
const int VERSION_1 = 1;

const int CURRENT_VERSION = VERSION_1;
const int NULL_VERSION = 255;

/**
 * Various settings controlling device operation.
 */
struct Settings
{
    /**
     * Version of settings struct. When behind
     * the manager will set new values based on defaults
     */
    uint8_t version;
    /**
     * Seconds between updates being sent to Ubidots.
     * If set to 0, updates will never be sent
     */
    int ubidots_update_frequency_s;
};

/**
 * Manage storing and updating settings.
 * 
 * Particle.functions are used to update individual settings,
 * allowing individual devices to be customized. Settings are
 * persisted to and loaded from the EEPROM.
 */
class SettingManager : public Runnable
{
private:
    /**
     * Current version of setting struct. Needs to be incremented,
     * and an upgrade migration created for each new setting tracked.
     */
    int version = CURRENT_VERSION;

    // Default number of seconds to send updates to Ubidots
    int default_ubidots_update_frequency_s;

    // Current Settings struct
    struct Settings settings;

    /**
     * upgrade_settings makes sure the version of the settings struct
     * and the attributes that it has are up to date. If behind
     * the default values will be used to set new attributes.
     */
    void upgrade_settings();

    // Retrieve the current settings values from the EEPROM.
    void get_from_eeprom();

    // Persists the current settings values to the EEPROM.
    void persist_to_eeprom();

public:
    /**
     * Create a new SettingManager with given default values.
     * 
     * @param ubidots_update_frequency_s Default number of seconds between sending updates to Ubidots.
     */
    SettingManager(int ubidots_update_frequency_s);

    void setup();
    void loop();

    // Return the current settings
    struct Settings current_settings();

    // Output the current settings over serial
    void print_settings();

    // Return the current settings as a string for logging or print
    String setting_string();

    /**
     * Cloud function to control how many seconds between
     * Ubidots updates being sent. "Stop" will disable updates.
     * 
     * @param message Seconds as a string between updates.
     * Will be converted into an int.
     * 
     * @returns Number of seconds set between updates, or -1
     * if unable to interpert the message.
     */
    int change_ubidot_update_seconds(String message);
};

#endif