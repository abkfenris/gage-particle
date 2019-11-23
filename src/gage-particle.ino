/*
 * Project gage-particle
 * Description: 
 * Author: Alex Kerney (abk@mac.com)
 * Date: 2019-03-06
 */

#include "settings.h"
#include "network.h"

#include "logging/data_logger_manager.h"
#include "logging/ubidots_logger.h"
#include "logging/serial_logger.h"

#include "temp_sensor.h"
#include "distance_sensor.h"

#define DHTPIN A2                              // temperature sensor pin
const int DEFAULT_UBIDOTS_UPDATE_SECONDS = 30; // Default amount of time between updating Ubidots
char *WEBHOOK_NAME = "Ubidots";                // Webhook name that Ubidots listens to

// SYSTEM_THREAD(ENABLED);

SettingManager setting_manager(DEFAULT_UBIDOTS_UPDATE_SECONDS);

NetworkManager network_manager;

DataLoggerManager logger_manager;
UbidotsLogger ubidots_logger(WEBHOOK_NAME, setting_manager.current_settings());
SerialLogger serial_logger;

TempSensor tempSensor(DHTPIN);
DistanceSensor distance;

void setup()
{
  Serial.begin(9600);

  setting_manager.setup();

  network_manager.setup();

  logger_manager.add_logger(ubidots_logger);
  logger_manager.add_logger(serial_logger);
  logger_manager.setup();
  logger_manager.log_message(setting_manager.setting_string());
  logger_manager.log_message(network_manager.current_networks());

  logger_manager.log_message("Begin readings!");

  tempSensor.setup();
  distance.setup();
}

void loop()
{
  setting_manager.loop();
  network_manager.loop();

  tempSensor.loop();
  logger_manager.add_value("temperature", tempSensor.value());

  distance.loop();

  logger_manager.add_value("distance", distance.value());
  logger_manager.add_value("std_dev", distance.std_deviation());

  logger_manager.update_settings(setting_manager.current_settings());
  logger_manager.loop();
}