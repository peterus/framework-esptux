/*
  WiFi.h - Library for Arduino Wifi shield.
  Copyright (c) 2011-2014 Arduino LLC.  All right reserved.

  This library is free software; you can redistribute it and/or
  modify it under the terms of the GNU Lesser General Public
  License as published by the Free Software Foundation; either
  version 2.1 of the License, or (at your option) any later version.

  This library is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
  Lesser General Public License for more details.

  You should have received a copy of the GNU Lesser General Public
  License along with this library; if not, write to the Free Software
  Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
*/

#ifndef WiFi_h
#define WiFi_h

#include <array>
#include <inttypes.h>
#include <memory>
#include <vector>

#include "IPAddress.h"
#include "WiFiClient.h"
#include "WiFiServer.h"

#include "WiFiType.h"

using namespace arduino;

class WiFiConnection {
public:
  WiFiConnection(String _ssid, int32_t _rssi, IPAddress _local_ip = IPAddress(192, 168, 0, 2), IPAddress _dns_server = IPAddress(192, 168, 0, 1), IPAddress _gateway = IPAddress(192, 168, 0, 1), IPAddress _subnet = IPAddress(255, 255, 255, 0));
  WiFiConnection(String _ssid, String _password, wifi_auth_mode_t _encryptionType, int32_t _rssi, IPAddress _local_ip = IPAddress(192, 168, 0, 2), IPAddress _dns_server = IPAddress(192, 168, 0, 1), IPAddress _gateway = IPAddress(192, 168, 0, 1), IPAddress _subnet = IPAddress(255, 255, 255, 0));

  const String           ssid;
  const String           password;
  const int32_t          rssi;
  const wifi_auth_mode_t encryptionType;
  const IPAddress        local_ip;
  const IPAddress        dns_server;
  const IPAddress        gateway;
  const IPAddress        subnet;
};

class WiFiClass {
public:
  WiFiClass();

  int begin(const char *ssid);
  int begin(const char *ssid, uint8_t key_idx, const char *key);
  int begin(const char *ssid, const char *passphrase);

  bool mode(wifi_mode_t);

  void config(IPAddress local_ip);
  void config(IPAddress local_ip, IPAddress dns_server);
  void config(IPAddress local_ip, IPAddress dns_server, IPAddress gateway);
  void config(IPAddress local_ip, IPAddress dns_server, IPAddress gateway, IPAddress subnet);

  void setDNS(IPAddress dns_server1);
  void setDNS(IPAddress dns_server1, IPAddress dns_server2);

  int disconnect(void);

  uint8_t *macAddress(uint8_t *mac);

  IPAddress localIP();
  IPAddress subnetMask();
  IPAddress gatewayIP();

  char *   SSID();
  uint8_t *BSSID(uint8_t *bssid);
  int32_t  RSSI();

  uint8_t encryptionType();

  int8_t scanNetworks();

  char *  SSID(uint8_t networkItem);
  uint8_t encryptionType(uint8_t networkItem);
  int32_t RSSI(uint8_t networkItem);

  uint8_t status();

  int hostByName(const char *aHostname, IPAddress &aResult);

  bool isConnected();

  friend class WiFiClient;
  friend class WiFiServer;

  void addWiFiBroadcast(std::shared_ptr<WiFiConnection> con);

private:
  std::vector<std::shared_ptr<WiFiConnection>> _broadcasts;
  std::shared_ptr<WiFiConnection>              _activeConnection;
};

extern WiFiClass WiFi;

#endif
