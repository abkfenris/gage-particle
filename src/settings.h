/**
 * Settings structure
 * 
 * @author Alex Kerney
 */
#ifndef Setting_h
#define Setting_h

// Version history

// Ubidots update timing is introduced in version 1
const int SETTING_VERSION_1 = 1;

const int SETTING_CURRENT_VERSION = SETTING_VERSION_1;
const int SETTING_NULL_VERSION = 255;

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

#endif