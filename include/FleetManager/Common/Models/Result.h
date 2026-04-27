#pragma once

#include <crow/common.h>
#include <crow/json.h>
#include <cstddef>
#include <optional>
#include <string>
#include <string_view>

namespace Fleet::Models {
template <class T = std::nullptr_t> struct Result {
  const std::optional<T> data;
  const std::string_view message;
  int httpCode;
  bool sucess;

  Result(T data, std::string_view message, int httpCode, bool sucess)
      : data{data}, message{message}, httpCode{httpCode}, sucess{sucess} {}
  Result(std::string_view message, int httpCode, bool sucess)
      : data{nullptr}, message{message}, httpCode{httpCode}, sucess{sucess} {}
  Result(bool sucess)
      : data{nullptr}, message{""}, httpCode{200}, sucess{sucess} {}

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
