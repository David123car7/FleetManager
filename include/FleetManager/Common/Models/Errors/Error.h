#pragma once

#include <string>
#include <string_view>

namespace Fleet::Models::Errors {
struct Error {
private:
  std::string_view message;

public:
  Error(std::string_view message) : message{message} {}
  operator const std::string_view() { return message; }
  operator const std::string() { return std::string{message}; }
};
} // namespace Fleet::Models::Errors
