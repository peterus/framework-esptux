/*
  WiFiUdp.cpp - Library for Arduino Wifi shield.
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
#include "Utility.h"
#include <cstdarg>
#include <netdb.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>

#undef INADDR_NONE

#include "WiFi.h"
#include "WiFiClient.h"
#include "WiFiServer.h"
#include "WiFiUdp.h"
#include "logging.h"

WiFiUDP::WiFiUDP() : _sock(0) {
}

uint8_t WiFiUDP::begin(uint16_t port) {
  _sock = socket(AF_INET, SOCK_DGRAM, 0);
  if (_sock == -1) {
    log_e(LogSystem::SysWifi, "Could not create socket");
    return 0;
  }

  sockaddr_in servaddr;
  memset(&servaddr, 0, sizeof(servaddr));
  // memset(&cliaddr, 0, sizeof(cliaddr));

  servaddr.sin_family      = AF_INET;
  servaddr.sin_addr.s_addr = INADDR_ANY;
  servaddr.sin_port        = htons(port);

  // Bind the socket with the server address
  if (bind(_sock, (const sockaddr *)&servaddr, sizeof(servaddr)) < 0) {
    log_e(LogSystem::SysWifi, "Could not bind port");
    return 0;
  }
  return 1;
}

void WiFiUDP::stop() {
  if (_sock != 0) {
    close(_sock);
    _sock = 0;
  }
}

int WiFiUDP::beginPacket(const char *host, uint16_t port) {
  IPAddress remote_addr;
  if (WiFi.hostByName(host, remote_addr)) {
    return beginPacket(remote_addr, port);
  }
  return 0;
}

int WiFiUDP::beginPacket(IPAddress ip, uint16_t port) {

  char str[255];
  sprintf(str, "%d.%d.%d.%d", ip[0], ip[1], ip[2], ip[3]);
  String _ip(str);

  memset(&_sendtoaddr, 0, sizeof(_sendtoaddr));

  _sendtoaddr.sin_family = AF_INET;
  _sendtoaddr.sin_port   = htons(port);
  inet_aton(_ip.c_str(), &_sendtoaddr.sin_addr);

  return 1;
}

int WiFiUDP::endPacket() {
  sendto(_sock, _sendBuffer.c_str(), _sendBuffer.length(), MSG_CONFIRM, (const sockaddr *)&_sendtoaddr, sizeof(_sendtoaddr));
  return 0;
}

size_t WiFiUDP::write(uint8_t byte) {
  return write(&byte, 1);
}

size_t WiFiUDP::write(const uint8_t *buffer, size_t size) {
  for (size_t i = 0; i < size; i++) {
    _sendBuffer += buffer[i];
  }
  return size;
}

#define MAX_STR_LEN 256

size_t WiFiUDP::printf(const char *format, ...) {
  char    buf[MAX_STR_LEN];
  va_list args;
  va_start(args, format);
  vsnprintf(buf, sizeof(buf), format, args);
  write(buf);
  va_end(args);
  return strlen(buf);
}

int WiFiUDP::parsePacket() {
  return available();
}

int WiFiUDP::available() {
  return 0;
}

int WiFiUDP::read() {
  if (available()) {
    return 0;
  } else {
    return -1;
  }
}

int WiFiUDP::read(unsigned char *buffer, size_t len) {
  UNUSED(buffer);
  UNUSED(len);
  if (available()) {
    uint16_t size = 0;
    return size;
  } else {
    return -1;
  }
}

int WiFiUDP::read(char *buffer, size_t len) {
  return read((unsigned char *)buffer, len);
};

int WiFiUDP::peek() {
  if (!available()) {
    return -1;
  }
  return 0;
}

void WiFiUDP::flush() {
}

IPAddress WiFiUDP::remoteIP() {
  return IPAddress();
}

uint16_t WiFiUDP::remotePort() {
  return 0;
}
