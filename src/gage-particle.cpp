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
#include "logging/ble_serial_logger.h"

#include "sensor/grove_temp.h"
#include "sensor/maxbotix_serial_distance.h"

void setup();
void loop();
#line 20 "/Users/akerney/Geek/Gage/gage-particle/src/gage-particle.ino"
#define DHTPIN A2                              // temperature sensor pin
const int DEFAULT_UBIDOTS_UPDATE_SECONDS = 30; // Default amount of time between updating Ubidots
char *WEBHOOK_NAME = "Ubidots";                // Webhook name that Ubidots listens to

// SYSTEM_THREAD(ENABLED);

SettingManager setting_manager(DEFAULT_UBIDOTS_UPDATE_SECONDS);

NetworkManager network_manager;

UbidotsLogger ubidots_logger(WEBHOOK_NAME, setting_manager.current_settings());
SerialLogger serial_logger;
BleUartLogger bluetooth_logger;

GroveTempSensor tempSensor(DHTPIN);
MaxbotixDistanceSensor distance;

void setup()
{
  DataLog.add_logger(ubidots_logger);
  DataLog.add_logger(serial_logger);
  DataLog.add_logger(bluetooth_logger);
  DataLog.setup();

  setting_manager.setup();
  network_manager.setup();

  DataLog.log_message("Begin readings!");

  tempSensor.setup();
  distance.setup();
}

void loop()
{
  setting_manager.loop();
  network_manager.loop();

  tempSensor.loop();
  distance.loop();

  DataLog.update_settings(setting_manager.current_settings());
  DataLog.loop();
}