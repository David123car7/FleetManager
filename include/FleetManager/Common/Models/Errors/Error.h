#pragma once

#include <string>

namespace Fleet::Models::Errors {
struct Error {
private:
  std::string message;

public:
  Error(std::string message) : message{message} {}
  operator const std::string() { return std::string{message}; }
};
} // namespace Fleet::Models::Errors
