# ESPtux

This is a port of the Arduino API to Linux for the ESP family. It can be used to create a test environment for different projects.

Use-Cases:

- Debug and develop Arduino code on your desktop OS.
- Faster implementation and testing because of no download to target.
- Core is running much faster on x86 or 64bit machine.
- Run your code in 'user-space' and simulate your SPI, I2C, GPIO etc. devices with an simple interface.

Currently supported:
- I2C
- simple algorithms, Arduino structure

## What is done

- basic Arduino structure
- timing (`delay()`, `millis()` etc.)
- core logging
- gpio
- serial
- I2C bus

## open parts

- SPI
- WiFi
- Ethernet
- some ESP-IDF functions

## contribution

If you found a bug, please create a ticket or resolve it yourself and push a push-request.
If you are missing a feature please add the feature and create a push-request. New features are just implemented on demand.

## How to use the ESPtux core

Add this to your platformio.ini file:

```
platform = https://github.com/peterus/platform-native.git  
framework = arduino
```

## pre work

Thanks to @geeksville for all the work already done.
