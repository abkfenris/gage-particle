/**
 * Log data to Bluetooth Low Energy UART
 * 
 * @author Alex Kerney
 */
#ifndef BLE_UART_Logger_h
#define BLE_UART_Logger_h

#include "map"

#include "BleSerialPeripheralRK.h"

#include "serial_logger.h"

/**
 * Datalogger to send values and messages out over
 * Bluetooth Low Energy UART
 */
class BleUartLogger : public SerialLogger
{
private:
    // How many milliseconds between updates
    int update_interval_ms = SERIAL_UPDATE_INTERVAL_MS;

    // Milliseconds of last update
    int last_update_ms;

    // Mapping of descriptive keys to data values
    std::map<char *, float> data;

    // BLE Uart
    BleSerialPeripheralStatic<32, 256> ble_serial;

public:
    // Makes sure that the Serial port has started
    void setup();

    // Triggers updates at specified interval
    void loop();

    /**
     * Add new data to be logged to serial. Any data with a
     * duplicate key will replace previous data.
     * 
     * @param key Sensor value name
     * @param value Reading from a sensor
     */
    void add_value(char *key, float value);

    // Log message to Bluetooth Low Energy UART
    void log_message(String message);

    // Immediately log out values to Bluetooth Low Energy UART
    void persist_values();
};
#endif