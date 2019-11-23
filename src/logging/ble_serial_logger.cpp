#include "logging/ble_serial_logger.h"

void BleUartLogger::setup()
{
    ble_serial.setup();
    ble_serial.advertise();
}

void BleUartLogger::loop()
{
    ble_serial.loop();

    if (millis() - last_update_ms >= update_interval_ms)
    {
        last_update_ms = millis();

        persist_values();
    }
}

void BleUartLogger::add_value(char *key, float value)
{
    data[key] = value;
}

void BleUartLogger::log_message(String message)
{
    ble_serial.println(message);
}

void BleUartLogger::persist_values()
{
    ble_serial.println(key_value_string());
}