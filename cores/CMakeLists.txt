
ADD_LIBRARY(Portduino
        arduino/api/Common.cpp
        arduino/api/IPAddress.cpp
        arduino/api/Print.cpp
        arduino/api/Stream.cpp
        arduino/api/String.cpp

        portduino/FS/FS.cpp
        portduino/FS/vfs_api.cpp

        portduino/main.cpp
        portduino/Common.cpp
        portduino/dtostrf.c
        portduino/itoa.cpp
        portduino/logging.cpp
        portduino/SimGPIO.cpp
        portduino/SimI2C.cpp
        portduino/SimSerial.cpp
        portduino/SimSPI.cpp
        portduino/Utility.cpp)
