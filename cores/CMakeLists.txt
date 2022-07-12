
ADD_LIBRARY(ESPtux
        arduino/api/Common.cpp
        arduino/api/IPAddress.cpp
        arduino/api/Print.cpp
        arduino/api/Stream.cpp
        arduino/api/String.cpp

        ESPtux/FS/FS.cpp
        ESPtux/FS/vfs_api.cpp

        ESPtux/main.cpp
        ESPtux/Common.cpp
        ESPtux/dtostrf.c
        ESPtux/itoa.cpp
        ESPtux/logging.cpp
        ESPtux/SimGPIO.cpp
        ESPtux/SimI2C.cpp
        ESPtux/SimSerial.cpp
        ESPtux/SimSPI.cpp
        ESPtux/Utility.cpp)
