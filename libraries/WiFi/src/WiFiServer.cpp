/*
  WiFiServer.cpp - Library for Arduino Wifi shield.
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

#include <string.h>

extern "C" {
#include "logging.h"
#include "utility/debug.h"
#include "utility/wifi_spi.h"
}

#include "WiFi.h"
#include "WiFiClient.h"
#include "WiFiServer.h"

#include <assert.h>
#include <fcntl.h>
#include <netdb.h>
#include <netinet/in.h>
#include <stdlib.h>
#include <unistd.h>

WiFiServer::WiFiServer(uint16_t port) {
  _port = port;
}

WiFiServer::~WiFiServer() {
  if (psock) {
    ::close(psock);
    psock = 0;
  }
}

void WiFiServer::begin() {
  // bind and listen

  /* First call to socket() function */
  psock = checkNotNeg(socket(AF_INET, SOCK_STREAM, 0), "error opening socket");

  // allow immediate portnum reuse if our process quits
  int iSetOption = 1;
  checkNotNeg(setsockopt(psock, SOL_SOCKET, SO_REUSEADDR, (char *)&iSetOption, sizeof(iSetOption)), "can't set reuse addr");

  /* Initialize socket structure */
  struct sockaddr_in serv_addr;
  bzero((char *)&serv_addr, sizeof(serv_addr));

  serv_addr.sin_family      = AF_INET;
  serv_addr.sin_addr.s_addr = INADDR_ANY;
  serv_addr.sin_port        = htons(_port);

  /* Now bind the host address using bind() call.*/
  checkNotNeg(bind(psock, (struct sockaddr *)&serv_addr, sizeof(serv_addr)), "failed to bind");

  /* Now start listening for the clients, here process will
   * go in sleep mode and will wait for the incoming connection
   */

  checkZero(listen(psock, 5), "listen failed");

  // Turn off blocking on accept()
  int flags = checkNotNeg(fcntl(psock, F_GETFL, 0), "socket get flags failed");
  checkNotNeg(fcntl(psock, F_SETFL, flags | O_NONBLOCK), "socket set non-block failed");
}

WiFiClient WiFiServer::available(byte *status) {

  assert(psock);
  log(SysWifi, LogVerbose, "calling accept");

  struct sockaddr_in cli_addr;
  socklen_t          clilen = sizeof(cli_addr);

  /* Accept actual connection from the client */
  int s = accept(psock, (struct sockaddr *)&cli_addr, &clilen);
  if (s < 0) {
    if ((errno == ENETDOWN || errno == EPROTO || errno == ENOPROTOOPT || errno == EHOSTDOWN || errno == EHOSTUNREACH || errno == EOPNOTSUPP || errno == ENETUNREACH || errno == EWOULDBLOCK)) {
      s = 0; // harmless error, return a non-connected client instance
    } else {
      checkNotNeg(s, "accept failed");
    }
  }

  log(SysWifi, LogVerbose, "accept=%d", s);

  return WiFiClient(s);
}

uint8_t WiFiServer::status() {
  notImplemented("WiFiServer::write");
  return 0; // FIXME
}

size_t WiFiServer::write(uint8_t b) {
  notImplemented("WiFiServer::write");
  return 0;
}

size_t WiFiServer::write(const uint8_t *buffer, size_t size) {
  size_t n = 0;

  notImplemented("WiFiServer::writen");
  debug();
  return n;
}
