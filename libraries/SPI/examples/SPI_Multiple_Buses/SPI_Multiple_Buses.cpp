

/* The ESP32 has four SPi buses, however as of right now only two of
 * them are available to use, HSPI and VSPI. Simply using the SPI API
 * as illustrated in Arduino examples will use VSPI, leaving HSPI unused.
 *
 * However if we simply intialise two instance of the SPI class for both
 * of these buses both can be used. However when just using these the Arduino
 * way only will actually be outputting at a time.
 *
 * Logic analyser capture is in the same folder as this example as
 * "multiple_bus_output.png"
 *
 * created 30/04/2018 by Alistair Symonds
 */
#include <SPI.h>

// Define ALTERNATE_PINS to use non-standard GPIO pins for SPI bus

#ifdef ALTERNATE_PINS
#define VSPI_MISO 2
#define VSPI_MOSI 4
#define VSPI_SCLK 0
#define VSPI_SS   33

#define HSPI_MISO 26
#define HSPI_MOSI 27
#define HSPI_SCLK 25
#define HSPI_SS   32
#else
#define VSPI_MISO MISO
#define VSPI_MOSI MOSI
#define VSPI_SCLK SCK
#define VSPI_SS   SS

#define HSPI_MISO 12
#define HSPI_MOSI 13
#define HSPI_SCLK 14
#define HSPI_SS   15
#endif

static const int spiClk = 1000000; // 1 MHz

void setup() {
  // clock miso mosi ss

#ifndef ALTERNATE_PINS
  // initialise vspi with default pins
  // SCLK = 18, MISO = 19, MOSI = 23, SS = 5
  SPI.begin();
#else
  // alternatively route through GPIO pins of your choice
  SPI.begin(VSPI_SCLK, VSPI_MISO, VSPI_MOSI, VSPI_SS); // SCLK, MISO, MOSI, SS
#endif

  // set up slave select pins as outputs as the Arduino API
  // doesn't handle automatically pulling SS low
  pinMode(SPI.pinSS(), OUTPUT); // SPI SS
}

uint8_t spiCommand(byte data) {
  // use it as you would the regular arduino SPI API
  SPI.beginTransaction(SPISettings(spiClk, MSBFIRST, SPI_MODE0));
  digitalWrite(SPI.pinSS(), LOW); // pull SS slow to prep other end for transfer
  uint8_t d = SPI.transfer(data);
  digitalWrite(SPI.pinSS(), HIGH); // pull ss high to signify end of data transfer
  SPI.endTransaction();
  return d;
}

// the loop function runs over and over again until power down or reset
void loop() {
  // use the SPI buses
  uint8_t data = spiCommand(0b01010101); // junk data to illustrate usage
  Serial.println(data);
  delay(100);
}
