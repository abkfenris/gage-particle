#include "logging/serial_logger.h"

void SerialLogger::setup()
{
    Serial.begin();
    last_update_ms = millis() - update_interval_ms;
}

void SerialLogger::loop()
{
    if (millis() - last_update_ms >= update_interval_ms)
    {
        last_update_ms = millis();

        persist_values();
    }
}

void SerialLogger::add_value(char *key, float value)
{
    data[key] = value;
}

void SerialLogger::log_message(String message)
{
    Serial.println(message);
}

void SerialLogger::persist_values()
{
    Serial.println("Current values:");

    std::map<char *, float>::iterator iter;

    for (iter = data.begin(); iter != data.end(); iter++)
    {
        char *key = iter->first;
        float value = iter->second;

        Serial.println("  " + String(key) + ": " + String(value));
    }

    data.clear();
}

void SerialLogger::update_settings(struct Settings settings) {}