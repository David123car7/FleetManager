#pragma once

#include <crow/common.h>
#include <crow/json.h>
#include <cstddef>
#include <optional>
#include <string>

namespace Fleet::Models {
template <class T = std::nullptr_t> struct Result {
  const std::optional<T> data;
  const std::string message;
  int httpCode;

  Result(T data, std::string message, int httpCode)
      : data{data}, message{message}, httpCode{httpCode} {}
  Result(std::string message, int httpCode)
      : data{nullptr}, message{message}, httpCode{httpCode} {}
  Result(int httpCode) : data{nullptr}, message{""}, httpCode{httpCode} {}

  operator crow::json::wvalue() {
    crow::json::wvalue json;
    if (data.has_value())
      json["data"] = data.value();
    else
      json["data"] = nullptr;
    json["message"] = message;
    return json;
  }
};
} // namespace Fleet::Models
