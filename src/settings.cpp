#include "settings.h"

SettingManager::SettingManager(int ubidots_update_frequency_s)
{
    default_ubidots_update_frequency_s = ubidots_update_frequency_s;

    get_from_eeprom();
};

void SettingManager::upgrade_settings()
{
    if (settings.version < VERSION_1 || settings.version == NULL_VERSION)
    {
        settings.version = VERSION_1;
        settings.ubidots_update_frequency_s = default_ubidots_update_frequency_s;
    }

    persist_to_eeprom();
};

void SettingManager::get_from_eeprom()
{
    EEPROM.get(SETTING_EEPROM_ADDRESS, settings);

    // Upgrade if out of date
    if (settings.version < CURRENT_VERSION || settings.version == NULL_VERSION)
    {
        upgrade_settings();
    }
};

void SettingManager::persist_to_eeprom()
{
    EEPROM.put(SETTING_EEPROM_ADDRESS, settings);
    print_settings();
};

struct Settings SettingManager::current_settings()
{
    return settings;
};

void SettingManager::print_settings()
{
    Serial.println(setting_string());
};

String SettingManager::setting_string()
{
    String message = "Settings: ";
    message = String(message + "version: " + String(settings.version));
    message = String(message + ", Ubidots updates every (S): " + String(settings.ubidots_update_frequency_s));

    return message;
};

void SettingManager::setup(){};

void SettingManager::loop(){};