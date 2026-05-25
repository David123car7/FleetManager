#pragma once

#include <string>

namespace API::Models::Errors {
struct Error {
  std::string message;
  Error(std::string message) : message{message} {}
  operator const std::string() { return std::string{message}; }
};
} // namespace API::Models::Errors
