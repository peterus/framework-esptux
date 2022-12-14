/*
 *  This sketch sends random data over UDP on a ESP32 device
 *
 */
#include <WiFi.h>
#include <WiFiUdp.h>

// WiFi network name and password:
const char *networkName = "your-ssid";
const char *networkPswd = "your-password";

// IP address to send UDP data to:
// either use the ip address of the server or
// a network broadcast address
const char *udpAddress = "127.0.0.1";
// const char *udpAddress = "google.at";
const int udpPort = 3333;

// The udp library class
WiFiUDP udp;

void connectToWiFi(const char *ssid, const char *pwd);

void setup() {
  // Initilize hardware serial:
  Serial.begin(115200);

  // Connect to the WiFi network
  connectToWiFi(networkName, networkPswd);

  udp.begin(udpPort + 1);
}

void loop() {
  // only send data when connected
  if (WiFi.isConnected()) {
    // Send a packet
    Serial.println("Sending data to UDP host/port");
    udp.beginPacket(udpAddress, udpPort);
    udp.printf("Seconds since boot: %lu", millis() / 1000);
    udp.endPacket();
  }
  // Wait for 1 second
  delay(1000);
}

void connectToWiFi(const char *ssid, const char *pwd) {
  Serial.println("Connecting to WiFi network: " + String(ssid));

  // delete old config
  WiFi.disconnect();

  // Initiate connection
  WiFi.begin(ssid, pwd);

  Serial.println("Waiting for WIFI connection...");
}
