#pragma once

#include <crow/common.h>
#include <crow/json.h>
#include <cstddef>
#include <nlohmann/json_fwd.hpp>
#include <optional>
#include <stdexcept>
#include <string>

namespace API::Models {
template <class T = std::nullptr_t> class Result {
private:
  std::optional<T> data;
  std::optional<std::string> message;
  std::optional<int> httpCode;

public:
  Result(std::optional<T> data, std::optional<std::string> message,
         std::optional<int> httpCode)
      : data{data}, message{message}, httpCode{httpCode} {}

  static Result Sucess(int httpCode = crow::status::OK,
                       std::optional<T> data = std::nullopt,
                       std::optional<std::string> message = std::nullopt) {
    return {data, message, httpCode};
  }

  static Result Failure(std::string message,
                        std::optional<int> httpCode = std::nullopt) {
    return {std::nullopt, message, httpCode};
  }

  Result(std::string &jsonBody) {
    auto json = crow::json::load(jsonBody);
    if (!json)
      throw std::invalid_argument("Invalid Json Body");
    if (json.has("data"))
      data = (T)json["data"];
    if (json.has("message"))
      message = json["message"].s();
  }

  int GetHttpCode() {
    if (httpCode.has_value())
      return httpCode.value();
    else
      return -1;
  }

  std::string GetMessage() {
    if (message.has_value())
      return message.value();
    else
      return "";
  }

  T GetDate() {
    if (data.has_value())
      return data;
    else
      return {};
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
} // namespace API::Models
