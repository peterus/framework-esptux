/*
  WiFiClient.cpp - Library for Arduino Wifi shield.
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

extern "C" {
#include "string.h"
#include "utility/debug.h"
#include "utility/wifi_spi.h"
#include "utility/wl_definitions.h"
}

#include "WiFi.h"
#include "WiFiClient.h"
#include "WiFiServer.h"
#include "logging.h"
#include <arpa/inet.h> //inet_addr
#include <assert.h>
#include <errno.h>
#include <fcntl.h>
#include <sys/socket.h>
#include <unistd.h>
#include <netdb.h>

WiFiClient::WiFiClient(int sock) : psock(sock) {
  if (psock) {
    int flags = fcntl(psock, F_GETFL, 0);
    fcntl(psock, F_SETFL, flags | O_NONBLOCK);
    errorCode = 0;
  }
}

int WiFiClient::connect(const char *host, uint16_t port) {
  int socket_desc;

  struct hostent *dns = gethostbyname(host);
  if (!dns) {
    ::printf("WiFiClient: Hostname lookup failed %s\n", host);
    return false;
  }

  // Create socket
  int sock = socket(AF_INET, SOCK_STREAM, 0);
  if (sock == -1) {
    ::printf("WiFiClient: Could not create socket\n");
    return false;
  }

  struct sockaddr_in server;
  server.sin_addr = *((struct in_addr *)dns->h_addr);
  // server.sin_addr.s_addr = inet_addr(host);
  server.sin_family = AF_INET;
  server.sin_port = htons(port);

  // Connect to remote server
  if (::connect(sock, (struct sockaddr *)&server, sizeof(server)) < 0) {
    ::printf("WiFiClient: connect error\n");
    return false;
  }

  psock = sock;
  errorCode = 0;

  // turn on nonblock
  int flags = fcntl(psock, F_GETFL, 0);
  fcntl(psock, F_SETFL, flags | O_NONBLOCK);

  return true;
}

int WiFiClient::connect(IPAddress ip, uint16_t port) {
  notImplemented("WiFiClient::connect-ipaddr");
  return false;
}

size_t WiFiClient::write(uint8_t b) { return write(&b, 1); }

size_t WiFiClient::write(const uint8_t *buf, size_t size) {
  if (!psock) {
    setWriteError();
    return 0;
  }
  if (size == 0) {
    setWriteError();
    return 0;
  }

  // return ::write(psock, buf, size);
  int res = ::send(psock, buf, size, MSG_NOSIGNAL);
  if (res ==
      -1) { // Better than write because, we dont want to receive bogus SIGPIPE signals for dropped connections
    setWriteError();
    return 0;
  }
}

int WiFiClient::available() {
  if (psock) {
    if (ready == -1) { // No char already read, ask the OS
      uint8_t b;
      int numread = ::read(psock, &b, 1);
      if (numread < 1) {
        errorCode = errno;
        // EAGAIN means timeout
        if (errorCode == EAGAIN)
          errorCode = 0;

        ready = -1;
      } else {
        ready = b;
      }
    }

    int len = (ready == -1) ? 0 : 1;

    // log(SysWifi, LogVerbose, "available %d", len);
    return len;
  }

  return 0;
}

int WiFiClient::read() {
  char b;
  if (!available())
    return -1;

  b = ready;
  ready = -1; // consumed
  return (uint8_t)b;
}

int WiFiClient::read(uint8_t *buf, size_t size) {
  assert(psock);
  auto r = ::read(psock, buf, size);
  errorCode = errno;

  return r;
}

int WiFiClient::peek() {
  uint8_t b;
  if (!available())
    return -1;

  b = ready;
  return b;
}

void WiFiClient::flush() {
}

void WiFiClient::stop() {
  if (!psock)
    return;

  ::close(psock);
  psock = 0;
}

uint8_t WiFiClient::connected() {

  if (!psock) {
    return 0;
  } else {
    return errorCode == 0;
  }
}

uint8_t WiFiClient::status() {
  if (!psock) {
    return CLOSED;
  } else {
    return ESTABLISHED;
  }
}

WiFiClient::operator bool() { return connected(); }
