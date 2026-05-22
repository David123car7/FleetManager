#pragma once

#include <string>

namespace API::Models::Errors {
struct Error {
private:
  std::string message;

public:
  Error(std::string message) : message{message} {}
  operator const std::string() { return std::string{message}; }
};
} // namespace API::Models::Errors
