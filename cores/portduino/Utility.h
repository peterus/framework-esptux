#ifndef PORTDUINO_UTILITY_H
#define PORTDUINO_UTILITY_H

#include <stdexcept>
#include <string>

class Exception : public std::runtime_error {
public:
  explicit Exception(const std::string &message) : runtime_error(message) {
  }
};

void notImplemented(const char *msg);

[[noreturn]] void portduinoError(const char *msg, ...);

int portduinoCheckNotNeg(int result, const char *msg, ...);
int portduinoCheckZero(int result, const char *msg, ...);

void portduinoDebug();

#endif // PORTDUINO_UTILITY_H
