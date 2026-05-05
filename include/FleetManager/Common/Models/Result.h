#pragma once

#include <crow/common.h>
#include <crow/json.h>
#include <cstddef>
#include <optional>
#include <string>

namespace Fleet::Models {
template <class T = std::nullptr_t> struct Result {
  const std::optional<T> data;
  const std::optional<std::string> message;
  int httpCode;

  Result(std::optional<T> data, std::optional<std::string> message,
         int httpCode)
      : data{data}, message{message}, httpCode{httpCode} {}

  static Result Sucess(int httpCode = crow::status::OK,
                       std::optional<T> data = std::nullopt,
                       std::optional<std::string> message = std::nullopt) {
    return {data, message, httpCode};
  }

  static Result Failure(std::string message, int httpCode) {
    return {std::nullopt, message, httpCode};
  }

  operator crow::json::wvalue() {
    crow::json::wvalue json;
    if (data.has_value())
      json["data"] = data.value();
    if (message.has_value())
      json["message"] = message.value();
    return json;
  }
};
} // namespace Fleet::Models
