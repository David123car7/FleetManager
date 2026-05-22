#pragma once

#include "crow/http_response.h"
#include <cppapi/Interfaces/IJwtService.h>
#include <stdexcept>
#include <string>

using API::Interfaces::IJwtService;

namespace API::Middlewares {
class AuthMiddleware {
private:
  std::shared_ptr<IJwtService> jwt;

public:
  AuthMiddleware() : jwt{nullptr} {}
  AuthMiddleware(std::shared_ptr<IJwtService> jwt) : jwt{jwt} {
    if (jwt == nullptr)
      throw std::invalid_argument("Invalid jwt service");
  }

  class context {};
  bool IsRouteProtected(std::string &route);
  void before_handle(crow::request &req, crow::response &res, context &ctx);
  void after_handle(crow::request &req, crow::response &res, context &ctx);
};
} // namespace API::Middlewares
