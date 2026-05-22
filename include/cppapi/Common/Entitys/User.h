#pragma once

#include <crow/http_request.h>
#include <crow/json.h>
#include <pqxx/pqxx>
#include <string>

namespace API::Entitys {
struct User {
  std::string id;
  std::string email;
  std::string password;

  User(crow::json::rvalue body) {
    email = body["email"].s();
    password = body["password"].s();
  }

  User(pqxx::row result) {
    id = result["id"].as<std::string>();
    email = result["email"].as<std::string>();
    password = result["password"].as<std::string>();
  }
};
} // namespace API::Entitys
