#include "settings_manager.h"

SettingManager::SettingManager(int ubidots_update_frequency_s)
{
    default_ubidots_update_frequency_s = ubidots_update_frequency_s;

    get_from_eeprom();
};

void SettingManager::setup()
{
    Particle.function("settings-ubidots_update_seconds",
                      &SettingManager::change_ubidot_update_seconds,
                      this);

    DataLog.log_message(setting_string());
};

void SettingManager::loop(){};

void SettingManager::upgrade_settings()
{
    if (settings.version < SETTING_VERSION_1 || settings.version == SETTING_NULL_VERSION)
    {
        settings.version = SETTING_VERSION_1;
        settings.ubidots_update_frequency_s = default_ubidots_update_frequency_s;
    }

    persist_to_eeprom();
};

void SettingManager::get_from_eeprom()
{
    EEPROM.get(SETTING_EEPROM_ADDRESS, settings);

    // Upgrade if out of date
    if (settings.version < SETTING_CURRENT_VERSION || settings.version == SETTING_NULL_VERSION)
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

int SettingManager::change_ubidot_update_seconds(String message)
{
    Serial.println("Recieved new ubidots function");
    int value;
    if (message.toLowerCase() == "stop")
    {
        value = 0;
    }
    else
    {
        int result = message.toInt();
        if (result != 0)
        {
            value = result;
        }
    }

    Serial.print("Recieved new ubidots value: ");
    Serial.println(value);

    if (value != settings.ubidots_update_frequency_s)
    {
        settings.ubidots_update_frequency_s = value;
        persist_to_eeprom();
    }
}