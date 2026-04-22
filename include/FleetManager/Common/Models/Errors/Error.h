#pragma once

#include <string>
#include <string_view>

struct Error {
private:
  std::string_view message;

public:
  Error(std::string_view message) : message{message} {}
  operator std::string_view() { return message; }
  operator std::string() { return std::string{message}; }
};
