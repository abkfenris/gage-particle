#include "data_logger_manager.h"

void DataLoggerManager::setup()
{
    std::list<std::reference_wrapper<DataLogger>>::iterator logger_iter;
    for (logger_iter = loggers.begin(); logger_iter != loggers.end(); logger_iter++)
    {
        (*logger_iter).get().setup();
    }
}

void DataLoggerManager::loop()
{
    std::list<std::reference_wrapper<DataLogger>>::iterator logger_iter;
    for (logger_iter = loggers.begin(); logger_iter != loggers.end(); logger_iter++)
    {
        (*logger_iter).get().loop();
    }
}

void DataLoggerManager::add_value(char *key, float value)
{
    std::list<std::reference_wrapper<DataLogger>>::iterator logger_iter;
    for (logger_iter = loggers.begin(); logger_iter != loggers.end(); logger_iter++)
    {
        (*logger_iter).get().add_value(key, value);
    }
}

void DataLoggerManager::log_message(char *message)
{
    std::list<std::reference_wrapper<DataLogger>>::iterator logger_iter;
    for (logger_iter = loggers.begin(); logger_iter != loggers.end(); logger_iter++)
    {
        (*logger_iter).get().log_message(message);
    }
}

void DataLoggerManager::persist_values()
{
    std::list<std::reference_wrapper<DataLogger>>::iterator logger_iter;
    for (logger_iter = loggers.begin(); logger_iter != loggers.end(); logger_iter++)
    {
        (*logger_iter).get().persist_values();
    }
}

void DataLoggerManager::update_settings(struct Settings settings)
{
    std::list<std::reference_wrapper<DataLogger>>::iterator logger_iter;
    for (logger_iter = loggers.begin(); logger_iter != loggers.end(); logger_iter++)
    {
        (*logger_iter).get().update_settings(settings);
    }
}

void DataLoggerManager::add_logger(DataLogger &logger)
{
    loggers.push_back(logger);
};
