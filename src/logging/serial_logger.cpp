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

String SerialLogger::key_value_string()
{
    String output = "\n\nCurrent values:";

    std::map<char *, float>::iterator iter;

    for (iter = data.begin(); iter != data.end(); iter++)
    {
        char *key = iter->first;
        float value = iter->second;

        output = String(output + "\n  " + key + ": " + String(value));
    }

    output = String(output + "\n");

    data.clear();

    return output;
}

void SerialLogger::persist_values()
{
    Serial.print(key_value_string());
}

void SerialLogger::update_settings(struct Settings settings) {}