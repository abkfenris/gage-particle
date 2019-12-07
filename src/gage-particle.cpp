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

#include "SdFat.h"
#include "AdafruitDataLoggerRK.h"
#include "SdCardLogHandlerRK.h"

#include "logging/data_logger_manager.h"

#include "settings_manager.h"
#include "network.h"

#include "logging/serial_logger.h"
#include "logging/publish_logger.h"
#include "logging/sd_logger.h"

#include "sensor/grove_temp.h"
#include "sensor/tfmini_plus_lidar_distance.h"
#include "sensor/maxbotix_pwm_distance.h"
#include "sensor/battery_sensor.h"

void setup();
void loop();
#line 26 "/Users/akerney/Geek/Gage/gage-particle/src/gage-particle.ino"
#define DHTPIN A2                              // temperature sensor pin
const int DEFAULT_UBIDOTS_UPDATE_SECONDS = 30; // Default amount of time between updating Ubidots
char *WEBHOOK_NAME = "Ubidots";                // Webhook name that Ubidots listens to

SYSTEM_THREAD(ENABLED);

// Initialize our key systems

// log general system info to Serial
// Remove to only have messages and values
// Output via DataLog loggers
SerialLogHandler log_handler;

// MicroSD card access and print logger need to be initialized early,
// And configuration needs to happen at startup, rather than in a
// Specific logger.
SdFat sd;
const int SD_CHIP_SELECT = D5;
SdCardPrintHandler sd_print(sd, SD_CHIP_SELECT, SPI_FULL_SPEED);
STARTUP(sd_print.withMaxFilesToKeep(1000));

RTCSynchronizer rtc_sync;

// Settings manager persists settings to the EEPROM
// and exposes Particle.functions for changing them
SettingManager setting_manager(DEFAULT_UBIDOTS_UPDATE_SECONDS);

// Network manager helps manage Wifi networks on an Argon
NetworkManager network_manager;

// Now for the specific loggers that should be registered to the DataLog
SerialLogger serial_logger;
PublishLogger publish_logger(WEBHOOK_NAME, setting_manager.current_settings());
SDLogger sd_logger(sd_print);

// Finally our sensors
GroveTempSensor tempSensor(DHTPIN);
MaxbotixPWMDistanceSensor distance_pwm;
TfMiniPlusLidarDistanceSensor lidar;
BatterySensor battery;

void setup()
{
  rtc_sync.setup();
  // We first add our loggers in setup, so they are avaliable
  // when other instances run through their setup.
  DataLog.add_logger(serial_logger);
  DataLog.add_logger(publish_logger);
  DataLog.add_logger(sd_logger);
  DataLog.setup();

  // Run through common setups/
  setting_manager.setup();
  network_manager.setup();

  DataLog.log_message("Begin readings!");

  // Finally setup our sensors
  tempSensor.setup();
  lidar.setup();
  distance_pwm.setup();
  battery.setup();
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
  lidar.loop();
  distance_pwm.loop();
  battery.loop();

  // DataLog updates settings of any loggers that may have changes,
  // Then completes the loggers complete their own loops.
  DataLog.update_settings(setting_manager.current_settings());
  DataLog.loop();
}