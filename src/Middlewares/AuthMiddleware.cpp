#include "FleetManager/Middlewares/AuthMiddleware.h"
#include <iostream>

void AuthMiddleware::before_handle(crow::request &req, crow::response &res,
                                   context &ctx) {
  std::cout << "AuthMiddleware Before";
}

void AuthMiddleware::after_handle(crow::request &req, crow::response &res,
                                  context &ctx) {
  std::cout << "AuthMiddleware After";
}
