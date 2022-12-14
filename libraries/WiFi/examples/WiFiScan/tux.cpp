#include "Arduino.h"
#include "WiFi.h"
#include "logging.h"
#include <memory>

void coreInit() {
  loggerSetLevel(SysWifi, LogInfo);
}

void coreSetup() {
  WiFi.addWiFiBroadcast(std::make_shared<WiFiConnection>("test", -20));
  WiFi.addWiFiBroadcast(std::make_shared<WiFiConnection>("foo", -19));
  WiFi.addWiFiBroadcast(std::make_shared<WiFiConnection>("bar", -25, IPAddress(10, 0, 0, 2), IPAddress(10, 0, 0, 1), IPAddress(10, 0, 0, 1)));
  WiFi.addWiFiBroadcast(std::make_shared<WiFiConnection>("locked", "password", WIFI_AUTH_WPA2_PSK, -25));
}
