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

void setup();
void loop();
#line 13 "/Users/akerney/Geek/Gage/gage-particle/src/gage-particle.ino"
#define DHTPIN A2 // temperature sensor pin

const long UPDATE_INTERVAL_MS = 300000;

const int UBIDOTS_UPDATE_SECONDS_TEST = 30;

char *WEBHOOK_NAME = "Ubidots";

SettingManager setting_manager(UBIDOTS_UPDATE_SECONDS_TEST);

TempSensor tempSensor(DHTPIN);
Communicate communicate(WEBHOOK_NAME, UPDATE_INTERVAL_MS);
DistanceSensor distance;

void setup()
{
  Serial.begin(9600);
  setting_manager.print_settings();
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