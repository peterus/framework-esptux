
ADD_LIBRARY(Portduino
        arduino/api/Common.cpp
        arduino/api/IPAddress.cpp
        arduino/api/Print.cpp
        arduino/api/Stream.cpp
        arduino/api/String.cpp

        portduino/FS/FS.cpp
        portduino/FS/PortduinoFS.cpp
        portduino/FS/vfs_api.cpp

        portduino/Arduino.cpp
        portduino/Common.cpp
        portduino/dtostrf.c
        portduino/itoa.cpp
        portduino/logging.cpp
        portduino/PortduinoGPIO.cpp
        portduino/PortduinoHardwareI2C.cpp
        portduino/PortduinoHardwareSerial.cpp
        portduino/PortduinoHardwareSPI.cpp
        portduino/PortduinoPrint.cpp
        portduino/Utility.cpp)
