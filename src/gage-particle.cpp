/******************************************************/
//       THIS IS A GENERATED FILE - DO NOT EDIT       //
/******************************************************/

#include "application.h"
#line 1 "/Users/akerney/Geek/Gage/gage-particle/src/gage-particle.ino"
/*
 * Project gage-particle
 * Description: 
 * Author: Alex Kerney (abk@mac.com)
 * Date: 2019-03-06
 */

#include "logging/data_logger_manager.h"

#include "settings_manager.h"
#include "network.h"

#include "logging/ubidots_logger.h"
#include "logging/serial_logger.h"

#include "temp_sensor.h"
#include "distance_sensor.h"

void setup();
void loop();
#line 19 "/Users/akerney/Geek/Gage/gage-particle/src/gage-particle.ino"
#define DHTPIN A2                              // temperature sensor pin
const int DEFAULT_UBIDOTS_UPDATE_SECONDS = 30; // Default amount of time between updating Ubidots
char *WEBHOOK_NAME = "Ubidots";                // Webhook name that Ubidots listens to

// SYSTEM_THREAD(ENABLED);

SettingManager setting_manager(DEFAULT_UBIDOTS_UPDATE_SECONDS);

NetworkManager network_manager;

UbidotsLogger ubidots_logger(WEBHOOK_NAME, setting_manager.current_settings());
SerialLogger serial_logger;

TempSensor tempSensor(DHTPIN);
DistanceSensor distance;

void setup()
{
  Serial.begin(9600);

  DataLog.add_logger(ubidots_logger);
  DataLog.add_logger(serial_logger);
  DataLog.setup();

  setting_manager.setup();
  network_manager.setup();

  // DataLog.log_message(setting_manager.setting_string());
  DataLog.log_message(network_manager.current_networks());

  DataLog.log_message("Begin readings!");

  tempSensor.setup();
  distance.setup();
}

void loop()
{
  setting_manager.loop();
  network_manager.loop();

  tempSensor.loop();
  DataLog.add_value("temperature", tempSensor.value());

  distance.loop();

  DataLog.add_value("distance", distance.value());
  DataLog.add_value("std_dev", distance.std_deviation());

  DataLog.update_settings(setting_manager.current_settings());
  DataLog.loop();
}