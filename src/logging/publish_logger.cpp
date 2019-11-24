#include "logging/publish_logger.h"

PublishLogger::PublishLogger(char *set_webhook_name, struct Settings settings)
{
    webhook_name = set_webhook_name;
    update_settings(settings);
}

void PublishLogger::setup()
{
    last_update_ms = millis() - update_interval_ms;
}

void PublishLogger::loop()
{
    if (update_interval_ms > 0)
    {
        if (millis() - last_update_ms >= update_interval_ms)
        {
            last_update_ms = millis();
            persist_values();
        }
    }
}

void PublishLogger::add_value(char *key, float value)
{
    if (!isnan(value))
    {
        data[key] = {value, Time.now()};
    }
}

void PublishLogger::log_message(String message){};

void PublishLogger::persist_values()
{
    std::map<char *, ValueTime>::iterator iter;
    JsonWriterStatic<256> jw;

    jw.setFloatPlaces(1);
    jw.startObject();

    for (iter = data.begin(); iter != data.end(); iter++)
    {
        char *key = iter->first;
        struct ValueTime value_time = iter->second;
        char time[14];
        sprintf(time, "%ld000", value_time.time);

        jw.insertKeyObject(key);
        jw.insertKeyValue("value", value_time.value);
        jw.insertKeyValue("timestamp", time);
        jw.finishObjectOrArray();
    }

    jw.finishObjectOrArray();

    Particle.publish(webhook_name, jw.getBuffer(), PRIVATE);
    data.clear();
}

void PublishLogger::update_settings(struct Settings settings)
{
    update_interval_ms = settings.ubidots_update_frequency_s * 1000;
}
