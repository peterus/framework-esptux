/*
  WiFiUdp.h - Library for Arduino Wifi shield.
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

#ifndef wifiudp_h
#define wifiudp_h

#include <arpa/inet.h>

#include <Udp.h>

#define UDP_TX_PACKET_MAX_SIZE 24

class WiFiUDP : public UDP {
public:
  WiFiUDP();

  uint8_t begin(uint16_t port) final;
  void    stop() final;

  int beginPacket(IPAddress ip, uint16_t port) final;
  int beginPacket(const char *host, uint16_t port) final;
  int endPacket() final;

  size_t write(uint8_t) final;
  size_t write(const uint8_t *buffer, size_t size) final;

  size_t printf(const char *format, ...);

  using Print::write;

  int parsePacket() final;
  int available() final;
  int read() final;
  int read(unsigned char *buffer, size_t len) final;
  int read(char *buffer, size_t len) final;

  int  peek() final;
  void flush() final;

  IPAddress remoteIP() final;
  uint16_t  remotePort() final;

private:
  int         _sock;
  sockaddr_in _sendtoaddr;
  String      _sendBuffer;
};

#endif
