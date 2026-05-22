#pragma once

#include <crow/json.h>
#include <string>

namespace API::Models::Requests::Users {
struct LoginRequest {
  std::string email;
  std::string password;

  LoginRequest(crow::json::rvalue body) {
    email = body["email"].s();
    password = body["password"].s();
  }
};
} // namespace API::Models::Requests::Users
