#include "cppapi/Middlewares/AuthMiddleware.h"
#include <crow/common.h>

namespace API::Middlewares {
void AuthMiddleware::before_handle(crow::request &req, crow::response &res,
                                   context &ctx) {
  if (IsRouteProtected(req.url)) {
    std::string token = req.get_header_value("Authorization");
    if (!jwt->IsJwtTokenValid(token)) {
      res.code = crow::status::UNAUTHORIZED;
      res.end();
    }
  }
}

void AuthMiddleware::after_handle(crow::request &req, crow::response &res,
                                  context &ctx) {}

bool AuthMiddleware::IsRouteProtected(std::string &route) {
  std::string key = "";
  for (int i = 1; i < route.size(); i++) {
    if (route[i] == '/')
      break;
    key += route[i];
  }
  return key == "private";
}
} // namespace API::Middlewares
