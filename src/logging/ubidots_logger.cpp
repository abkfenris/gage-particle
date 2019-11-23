#include "logging/ubidots_logger.h"

UbidotsLogger::UbidotsLogger(char *set_webhook_name, struct Settings settings) : ubidots("webhook", UBI_PARTICLE)
{
    webhook_name = set_webhook_name;
    update_settings(settings);
}

void UbidotsLogger::setup()
{
    last_update_ms = millis() - update_interval_ms;
    ubidots.setDebug(true);
}

void UbidotsLogger::loop()
{
    if (update_interval_ms != 0)
    {
        if (millis() - last_update_ms >= update_interval_ms)
        {
            last_update_ms = millis();

            persist_values();
        }
    }
}

void UbidotsLogger::add_value(char *key, float value)
{
    if (!isnan(value))
    {
        data[key] = value;
    }
}

void UbidotsLogger::log_message(String message){};

void UbidotsLogger::persist_values()
{
    std::map<char *, float>::iterator iter;

    for (iter = data.begin(); iter != data.end(); iter++)
    {
        char *key = iter->first;
        float value = iter->second;

        ubidots.add(key, value);
    }

    ubidots.send(webhook_name, PUBLIC);

    // Remove saved values in the map
    data.clear();
}

void UbidotsLogger::update_settings(struct Settings settings)
{
    update_interval_ms = settings.ubidots_update_frequency_s * 1000;
}