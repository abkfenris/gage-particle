#include "communicate.h"

Communicate::Communicate(char *set_webhook_name, long set_update_interval_ms) : ubidots("webhook", UBI_PARTICLE)
{
    webhook_name = set_webhook_name;
    update_interval_ms = set_update_interval_ms;
}

void Communicate::setup()
{
    last_update_ms = millis();
    ubidots.setDebug(true);
}

void Communicate::loop()
{
    if (millis() - last_update_ms >= update_interval_ms)
    {
        last_update_ms = millis(); // Reset last update time

        std::map<char *, float>::iterator iter;
        for (iter = data.begin(); iter != data.end(); iter++)
        {
            char *key = iter->first;
            float value = iter->second;

            ubidots.add(key, value);
        }

        ubidots.send(webhook_name, PUBLIC);

        data.clear();
    }
}

void Communicate::add_value(char *key, float value)
{
    if (!isnan(value))
    {
        // ubidots.add(key, value);
        data[key] = value;
    }
}