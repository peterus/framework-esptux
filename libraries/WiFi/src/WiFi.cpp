/*
  WiFi.cpp - Library for Arduino Wifi shield.
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

#include "WiFi.h"
#include "Utility.h"
#include "WiFiType.h"
#include "logging.h"

#include <arpa/inet.h> //inet_addr
#include <assert.h>
#include <cstdio>
#include <errno.h>
#include <fcntl.h>
#include <netdb.h>
#include <sys/socket.h>
#include <unistd.h>

WiFiConnection::WiFiConnection(String _ssid, int32_t _rssi, IPAddress _local_ip, IPAddress _dns_server, IPAddress _gateway, IPAddress _subnet) : ssid(_ssid), password(""), rssi(_rssi), encryptionType(WIFI_AUTH_OPEN), local_ip(_local_ip), dns_server(_dns_server), gateway(_gateway), subnet(_subnet) {
}

WiFiConnection::WiFiConnection(String _ssid, String _password, wifi_auth_mode_t _encryptionType, int32_t _rssi, IPAddress _local_ip, IPAddress _dns_server, IPAddress _gateway, IPAddress _subnet) : ssid(_ssid), password(_password), rssi(_rssi), encryptionType(_encryptionType), local_ip(_local_ip), dns_server(_dns_server), gateway(_gateway), subnet(_subnet) {
}

WiFiClass::WiFiClass() : _activeConnection(0) {
}

int WiFiClass::begin(const char *ssid) {
  for (auto broadcast : _broadcasts) {
    if (broadcast->ssid == ssid) {
      _activeConnection = broadcast;
      return 1;
    }
  }
  return 0;
}

int WiFiClass::begin(const char *ssid, uint8_t key_idx, const char *key) {
  notImplemented("WiFi begin with key_idx");
  UNUSED(ssid);
  UNUSED(key_idx);
  UNUSED(key);
  return 0;
}

int WiFiClass::begin(const char *ssid, const char *passphrase) {
  for (auto broadcast : _broadcasts) {
    if (broadcast->ssid == ssid && broadcast->password == passphrase) {
      _activeConnection = broadcast;
      return 1;
    }
  }
  return 0;
}

bool WiFiClass::mode(wifi_mode_t m) {
  if (m != WIFI_MODE_STA) {
    notImplemented("other than WIFI_MODE_STA");
    return false;
  }
  return true;
}

void WiFiClass::config(IPAddress local_ip) {
  UNUSED(local_ip);
}

void WiFiClass::config(IPAddress local_ip, IPAddress dns_server) {
  UNUSED(local_ip);
  UNUSED(dns_server);
}

void WiFiClass::config(IPAddress local_ip, IPAddress dns_server, IPAddress gateway) {
  UNUSED(local_ip);
  UNUSED(dns_server);
  UNUSED(gateway);
}

void WiFiClass::config(IPAddress local_ip, IPAddress dns_server, IPAddress gateway, IPAddress subnet) {
  UNUSED(local_ip);
  UNUSED(dns_server);
  UNUSED(gateway);
  UNUSED(subnet);
}

void WiFiClass::setDNS(IPAddress dns_server1) {
  UNUSED(dns_server1);
}

void WiFiClass::setDNS(IPAddress dns_server1, IPAddress dns_server2) {
  UNUSED(dns_server1);
  UNUSED(dns_server2);
}

int WiFiClass::disconnect() {
  _activeConnection = 0;
  return 0;
}

uint8_t *WiFiClass::macAddress(uint8_t *mac) {
  // uint8_t* _mac = WiFiDrv::getMacAddress();
  // memcpy(mac, _mac, WL_MAC_ADDR_LENGTH);
  UNUSED(mac);
  notImplemented("macAddress");
  return (uint8_t *)"";
}

IPAddress WiFiClass::localIP() {
  if (!isConnected()) {
    return IPAddress();
  }
  return _activeConnection->local_ip;
}

IPAddress WiFiClass::subnetMask() {
  if (!isConnected()) {
    return IPAddress();
  }
  return _activeConnection->subnet;
}

IPAddress WiFiClass::gatewayIP() {
  if (!isConnected()) {
    return IPAddress();
  }
  return _activeConnection->gateway;
}

char *WiFiClass::SSID() {
  if (!isConnected()) {
    return (char *)"";
  }
  return (char *)_activeConnection->ssid.c_str();
}

uint8_t *WiFiClass::BSSID(uint8_t *bssid) {
  UNUSED(bssid);
  return (uint8_t *)"";
}

int32_t WiFiClass::RSSI() {
  if (!isConnected()) {
    return 0;
  }
  return _activeConnection->rssi;
}

uint8_t WiFiClass::encryptionType() {
  if (!isConnected()) {
    return 0;
  }
  return _activeConnection->encryptionType;
}

int8_t WiFiClass::scanNetworks() {
  return _broadcasts.size();
}

char *WiFiClass::SSID(uint8_t networkItem) {
  return (char *)_broadcasts[networkItem]->ssid.c_str();
}

int32_t WiFiClass::RSSI(uint8_t networkItem) {
  return _broadcasts[networkItem]->rssi;
}

uint8_t WiFiClass::encryptionType(uint8_t networkItem) {
  return _broadcasts[networkItem]->encryptionType;
}

uint8_t WiFiClass::status() {
  if (isConnected()) {
    return WL_CONNECTED;
  }
  return WL_DISCONNECTED;
}

bool WiFiClass::isConnected() {
  return _activeConnection != 0;
}

int WiFiClass::hostByName(const char *aHostname, IPAddress &aResult) {
  struct hostent *dns = gethostbyname2(aHostname, AF_INET);
  if (!dns) {
    log_e(LogSystem::SysWifi, "Hostname lookup failed: %s", aHostname);
    return 0;
  }
  aResult.fromString(inet_ntoa(*((struct in_addr *)dns->h_addr)));
  return 1;
}

void WiFiClass::addWiFiBroadcast(std::shared_ptr<WiFiConnection> con) {
  _broadcasts.push_back(con);
}

WiFiClass WiFi;
