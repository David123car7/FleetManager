#pragma once

#include <crow/json.h>
#include <cstddef>
#include <optional>
#include <string>

template <class T = std::nullptr_t> struct Result {
  const std::optional<T> data;
  const int statusCode;
  const std::string message;

  Result(T data, int statusCode, std::string message)
      : data{data}, statusCode{statusCode}, message{message} {}

  Result(int statusCode, std::string message)
      : data{nullptr}, statusCode{statusCode}, message{message} {}

  crow::json::wvalue toJson() const {
    crow::json::wvalue json;
    if (data.has_value())
      json["data"] = data.value();
    else
      json["data"] = nullptr;
    json["statusCode"] = statusCode;
    json["message"] = message;
    return json;
  }
};
