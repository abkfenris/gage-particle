#ifndef Network_Manager_h
#define Network_Manager_h

#include "runnable.h"
#include "logging/data_logger_manager.h"

class NetworkManager : public Runnable
{
public:
    void setup();
    void loop();

#if Wiring_WiFi
    /**
     * Particle.function to remotely add a new network
     * 
     * @param message Expects a string with ssid:password
     * If password is empty, but ssid and : then a network with
     * no password will be added.
     */
    int add_network(String message);

    /**
     * Returns a string with the current WiFi network names
     */
    String current_networks();
#endif
};

#endif