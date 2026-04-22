#pragma once

#include "crow/http_response.h"

namespace Fleet::Middlewares {
struct AuthMiddleware {
  struct context {};
  void before_handle(crow::request &req, crow::response &res, context &ctx);
  void after_handle(crow::request &req, crow::response &res, context &ctx);
};
} // namespace Fleet::Middlewares
