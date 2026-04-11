#include "FleetManager/Controllers/UsersController.h"
#include <crow/app.h>
#include <crow/common.h>
#include <crow/http_connection.h>
#include <crow/http_request.h>
#include <crow/http_response.h>
#include <crow/json.h>
#include <memory>

UsersController::UsersController(std::shared_ptr<IUsersService> usersService)
    : usersService{usersService} {
  if (usersService == nullptr)
    throw 0;
}

void UsersController::Start(crow::SimpleApp &app) { Register(app); }

void UsersController::Register(crow::SimpleApp &app) {
  CROW_ROUTE(app, "/register")
      .methods("POST"_method)([this](const crow::request &req) {
        auto x = crow::json::load(req.body);
        if (!x) {
          return crow::response(crow::status::BAD_REQUEST);
        }
        User user(x);
        usersService->Register(user);
        return crow::response(crow::status::ACCEPTED);
      });
}
