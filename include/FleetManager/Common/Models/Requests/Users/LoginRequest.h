#pragma once

#include <crow/json.h>
#include <string>

namespace Fleet::Models::Requests::Users {
struct LoginRequest {
  std::string email;
  std::string password;

  LoginRequest(crow::json::rvalue body) {
    email = body["email"].s();
    password = body["password"].s();
  }
};
} // namespace Fleet::Models::Requests::Users
