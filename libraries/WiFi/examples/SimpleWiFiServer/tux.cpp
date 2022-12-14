#include "Arduino.h"
#include "WiFi.h"
#include "logging.h"
#include <memory>

void coreInit() {
  // loggerSetLevel(SysWifi, LogInfo);
}

void coreSetup() {
  WiFi.addWiFiBroadcast(std::make_shared<WiFiConnection>("yourssid", "yourpasswd", WIFI_AUTH_WPA2_PSK, -25));
}
