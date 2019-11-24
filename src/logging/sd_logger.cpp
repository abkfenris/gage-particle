#include "sd_logger.h"

// The SD card CS pin on the Adafruit AdaLogger FeatherWing is D5.
const int SD_CHIP_SELECT = D5;

SDLogger::SDLogger(SdCardPrintHandler &sd_print_handler) : sd_print(sd_print_handler)
{
}

void SDLogger::setup() {}

void SDLogger::loop() {}

void SDLogger::add_value(char *key, float value)
{
    JsonWriterStatic<256> jw;

    jw.setFloatPlaces(1);
    jw.startObject();

    jw.insertKeyValue("key", key);
    jw.insertKeyValue("value", value);
    jw.insertKeyValue("timestamp", Time.format(Time.now(), TIME_FORMAT_ISO8601_FULL));

    jw.finishObjectOrArray();

    sd_print.println(jw.getBuffer());
}

void SDLogger::log_message(String message)
{
    sd_print.println(message);
}

void SDLogger::persist_values() {}

void SDLogger::update_settings(struct Settings settings) {}