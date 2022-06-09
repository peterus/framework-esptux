CMAKE_MINIMUM_REQUIRED(VERSION 3.16.3)
PROJECT(Portduino)

SET(CMAKE_CXX_STANDARD 20)

INCLUDE_DIRECTORIES(cores/arduino/api)
INCLUDE_DIRECTORIES(cores/portduino)
INCLUDE_DIRECTORIES(cores/portduino/FS)

ADD_LIBRARY(Portduino
        cores/arduino/api/Common.cpp
        cores/arduino/api/IPAddress.cpp
        cores/arduino/api/Print.cpp
        cores/arduino/api/Stream.cpp
        cores/arduino/api/String.cpp

        cores/portduino/FS/FS.cpp
        cores/portduino/FS/PortduinoFS.cpp
        cores/portduino/FS/vfs_api.cpp

        cores/portduino/Common.cpp
        cores/portduino/dtostrf.c
        cores/portduino/itoa.cpp
        cores/portduino/logging.cpp
        cores/portduino/main.cpp
        cores/portduino/PortduinoGPIO.cpp
        cores/portduino/PortduinoHardwareI2C.cpp
        cores/portduino/PortduinoHardwareSerial.cpp
        cores/portduino/PortduinoHardwareSPI.cpp
        cores/portduino/PortduinoPrint.cpp
        cores/portduino/Utility.cpp)

ADD_EXECUTABLE(example example/test.cpp)
TARGET_LINK_LIBRARIES(example Portduino)
