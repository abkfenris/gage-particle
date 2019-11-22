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

#include "settings.h"
#include "communicate.h"
#include "temp_sensor.h"
#include "distance_sensor.h"
#include "network.h"

void setup();
void loop();
#line 14 "/Users/akerney/Geek/Gage/gage-particle/src/gage-particle.ino"
#define DHTPIN A2                              // temperature sensor pin
const int DEFAULT_UBIDOTS_UPDATE_SECONDS = 30; // Default amount of time between updating Ubidots
char *WEBHOOK_NAME = "Ubidots";                // Webhook name that Ubidots listens to

// SYSTEM_THREAD(ENABLED);

SettingManager setting_manager(DEFAULT_UBIDOTS_UPDATE_SECONDS);

NetworkManager network_manager;
TempSensor tempSensor(DHTPIN);
Communicate communicate(WEBHOOK_NAME, 1000 * setting_manager.current_settings().ubidots_update_frequency_s);
DistanceSensor distance;

void setup()
{
  Serial.begin(9600);

  setting_manager.setup();
  Serial.println(setting_manager.setting_string());

  network_manager.setup();

  Serial.println("Begin readings!");

  tempSensor.setup();
  communicate.setup();
  distance.setup();
}

void loop()
{
  setting_manager.loop();
  network_manager.loop();

  tempSensor.loop();
  communicate.add_value("temperature", tempSensor.value());

  distance.loop();
  communicate.add_value("distance", distance.value());

  communicate.loop();
}