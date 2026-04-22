#pragma once

#include <crow/json.h>
#include <cstddef>
#include <optional>
#include <string>
#include <string_view>

namespace Fleet::Models {
template <class T = std::nullptr_t> struct Result {
  const std::optional<T> data;
  const std::string_view message;

  Result(T data, std::string_view message) : data{data}, message{message} {}
  Result(std::string_view message) : data{nullptr}, message{message} {}

  operator crow::json::wvalue() {
    crow::json::wvalue json;
    if (data.has_value())
      json["data"] = data.value();
    else
      json["data"] = nullptr;
    std::string msg{message};
    json["message"] = msg;
    return json;
  }
};
} // namespace Fleet::Models
