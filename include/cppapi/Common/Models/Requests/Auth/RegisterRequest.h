#pragma once

#include <crow/json.h>
#include <nlohmann/json.hpp>
#include <string>

namespace API::Models::Requests::Auth {
struct RegisterRequest {
  std::string email;
  std::string password;

  RegisterRequest(std::string email, std::string password)
      : email{email}, password{password} {}

  RegisterRequest(const crow::json::rvalue &body) {
    email = body["email"].s();
    password = body["password"].s();
  }

  std::string ToString() const {
    crow::json::wvalue json;
    json["email"] = email;
    json["password"] = password;
    return json.dump();
  }
};
} // namespace API::Models::Requests::Auth
