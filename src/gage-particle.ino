/*
 * Project gage-particle
 * Description: 
 * Author: Alex Kerney (abk@mac.com)
 * Date: 2019-03-06
 */

#include "AdafruitDataLoggerRK.h"

#include "logging/data_logger_manager.h"

#include "settings_manager.h"
#include "network.h"

#include "logging/serial_logger.h"
#include "logging/publish_logger.h"

#include "sensor/grove_temp.h"
#include "sensor/maxbotix_serial_distance.h"

#define DHTPIN A2                              // temperature sensor pin
const int DEFAULT_UBIDOTS_UPDATE_SECONDS = 30; // Default amount of time between updating Ubidots
char *WEBHOOK_NAME = "Ubidots";                // Webhook name that Ubidots listens to

SYSTEM_THREAD(ENABLED);

// Initialize our key systems

// log general system info to Serial
// Remove to only have messages and values
// Output via DataLog loggers
SerialLogHandler log_handler;

RTCSynchronizer rtc_sync;

// Settings manager persists settings to the EEPROM
// and exposes Particle.functions for changing them
SettingManager setting_manager(DEFAULT_UBIDOTS_UPDATE_SECONDS);

// Network manager helps manage Wifi networks on an Argon
NetworkManager network_manager;

// Now for the specific loggers that should be registered to the DataLog
SerialLogger serial_logger;
PublishLogger publish_logger(WEBHOOK_NAME, setting_manager.current_settings());

// Finally our sensors
GroveTempSensor tempSensor(DHTPIN);
MaxbotixDistanceSensor distance;

void setup()
{
  rtc_sync.setup();
  // We first add our loggers in setup, so they are avaliable
  // when other instances run through their setup.
  DataLog.add_logger(serial_logger);
  DataLog.add_logger(publish_logger);
  DataLog.setup();

  // Run through common setups/
  setting_manager.setup();
  network_manager.setup();

  DataLog.log_message("Begin readings!");

  // Finally setup our sensors
  tempSensor.setup();
  distance.setup();
}

void loop()
{
  // First we loop through system level management
  rtc_sync.loop();
  setting_manager.loop();
  network_manager.loop();

  // Then the sensor loops run which allows them to
  // register values with the DataLog before they run
  tempSensor.loop();
  distance.loop();

  // DataLog updates settings of any loggers that may have changes,
  // Then completes the loggers complete their own loops.
  DataLog.update_settings(setting_manager.current_settings());
  DataLog.loop();
}