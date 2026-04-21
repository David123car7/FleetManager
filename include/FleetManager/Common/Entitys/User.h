#pragma once

#include <crow/http_request.h>
#include <crow/json.h>
#include <string>

struct User {
  std::string email;
  std::string password;

  User(crow::json::rvalue body) {
    email = body["email"].s();
    password = body["password"].s();
  }
};
