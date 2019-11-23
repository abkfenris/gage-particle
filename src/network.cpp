#include "network.h"

void NetworkManager::setup()
{
#if Wiring_WiFi
    Particle.function("wifi_add_network",
                      &NetworkManager::add_network,
                      this);
#endif
}

void NetworkManager::loop()
{
}

#if Wiring_WiFi
int NetworkManager::add_network(String message)
{
    int split_index = message.indexOf(':');

    if (split_index == -1)
    {
        return -1;
    }

    String ssid = message.substring(0, split_index);
    String password = message.substring(split_index + 1);

    WiFi.setCredentials(ssid, password);

    Serial.print("Added SSID: ");
    Serial.println(ssid);
};

String NetworkManager::current_networks()
{
    int max_ap_for_platform = 10;

    WiFiAccessPoint ap[max_ap_for_platform];
    int found = WiFi.getCredentials(ap, max_ap_for_platform);

    String networks = "Saved networks: ";
    for (int i = 0; i < found; i++)
    {
        if (i > 0)
        {
            networks = String(networks + ", ");
        };
        networks = String(networks + ap[i].ssid);
    }
    return networks;
};
#endif