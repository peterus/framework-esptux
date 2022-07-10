#ifndef UTILITY_H_
#define UTILITY_H_

#include <stdexcept>
#include <string>

class Exception : public std::runtime_error {
public:
  explicit Exception(const std::string &message) : runtime_error(message) {
  }
};

void notImplemented(const char *msg);

int checkNotNeg(int result, const char *msg, ...);
int checkZero(int result, const char *msg, ...);

void debug();

#define UNUSED(x) (void)(x)

#endif
