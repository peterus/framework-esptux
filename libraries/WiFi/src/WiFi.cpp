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

WiFiClass::WiFiClass() {
}

void WiFiClass::init() {
}

int WiFiClass::begin(char *ssid) {
  return 0;
}

int WiFiClass::begin(char *ssid, uint8_t key_idx, const char *key) {
  return 0;
}

int WiFiClass::begin(char *ssid, const char *passphrase) {
  return 0;
}

void WiFiClass::config(IPAddress local_ip) {
}

void WiFiClass::config(IPAddress local_ip, IPAddress dns_server) {
}

void WiFiClass::config(IPAddress local_ip, IPAddress dns_server, IPAddress gateway) {
}

void WiFiClass::config(IPAddress local_ip, IPAddress dns_server, IPAddress gateway, IPAddress subnet) {
}

void WiFiClass::setDNS(IPAddress dns_server1) {
}

void WiFiClass::setDNS(IPAddress dns_server1, IPAddress dns_server2) {
}

int WiFiClass::disconnect() {
  notImplemented("disconnect");
  return 0;
}

uint8_t *WiFiClass::macAddress(uint8_t *mac) {
  // uint8_t* _mac = WiFiDrv::getMacAddress();
  // memcpy(mac, _mac, WL_MAC_ADDR_LENGTH);
  notImplemented("macAddress");
  return (uint8_t *)"";
}

IPAddress WiFiClass::localIP() {
  IPAddress ret;
  return ret;
}

IPAddress WiFiClass::subnetMask() {
  IPAddress ret;
  return ret;
}

IPAddress WiFiClass::gatewayIP() {
  IPAddress ret;
  return ret;
}

char *WiFiClass::SSID() {
  return "";
}

uint8_t *WiFiClass::BSSID(uint8_t *bssid) {
  return (uint8_t *)"";
}

int32_t WiFiClass::RSSI() {
  return 0;
}

uint8_t WiFiClass::encryptionType() {
  return 0;
}

int8_t WiFiClass::scanNetworks() {
  return 0;
}

char *WiFiClass::SSID(uint8_t networkItem) {
  return "";
}

int32_t WiFiClass::RSSI(uint8_t networkItem) {
  return 0;
}

uint8_t WiFiClass::encryptionType(uint8_t networkItem) {
  return 0;
}

uint8_t WiFiClass::status() {
  return 0;
}

bool WiFiClass::isConnected() {
  return true;
}

int WiFiClass::hostByName(const char *aHostname, IPAddress &aResult) {
  notImplemented("hostByName");
  return 0;
}

WiFiClass WiFi;
