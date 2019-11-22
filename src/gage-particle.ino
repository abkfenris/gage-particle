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

#define DHTPIN A2                              // temperature sensor pin
const int DEFAULT_UBIDOTS_UPDATE_SECONDS = 30; // Default amount of time between updating Ubidots
char *WEBHOOK_NAME = "Ubidots";                // Webhook name that Ubidots listens to

// SYSTEM_THREAD(ENABLED);

SettingManager setting_manager(DEFAULT_UBIDOTS_UPDATE_SECONDS);

TempSensor tempSensor(DHTPIN);
Communicate communicate(WEBHOOK_NAME, 1000 * setting_manager.current_settings().ubidots_update_frequency_s);
DistanceSensor distance;

void setup()
{
  Serial.begin(9600);

  setting_manager.setup();
  Serial.println(setting_manager.setting_string());

  Serial.println("Begin readings!");

  tempSensor.setup();
  communicate.setup();
  distance.setup();
}

void loop()
{
  tempSensor.loop();
  communicate.add_value("temperature", tempSensor.value());

  distance.loop();
  communicate.add_value("distance", distance.value());

  communicate.loop();
}