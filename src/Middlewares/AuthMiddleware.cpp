#include "cppapi/Middlewares/AuthMiddleware.h"
#include <crow/common.h>

namespace API::Middlewares {
void AuthMiddleware::before_handle(crow::request &req, crow::response &res,
                                   context &ctx) {
  if (IsProtectedRoute(req.url)) {
    std::string token = req.get_header_value("Authorization");
    if (!jwt->IsJwtTokenValid(token, IsAdminRoute(req.url))) {
      res.code = crow::status::UNAUTHORIZED;
      res.end();
    }
  }
}

void AuthMiddleware::after_handle(crow::request &req, crow::response &res,
                                  context &ctx) {}

bool AuthMiddleware::IsProtectedRoute(std::string &route) {
  std::string key = "";
  for (int i = 1; i < route.size(); i++) {
    if (route[i] == '/')
      break;
    key += route[i];
  }
  return key == "private";
}

bool AuthMiddleware::IsAdminRoute(std::string &route) {
  std::string key = "";
  int count = 0;
  for (int i = 1; i < route.size(); i++) {
    if (count == 2) {
      break;
    } else if (route[i] == '/') {
      count++;
    } else if (count == 1) {
      key += route[i];
    }
  }
  return key == "admin";
}
} // namespace API::Middlewares
