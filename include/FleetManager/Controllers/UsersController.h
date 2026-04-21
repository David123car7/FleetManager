#pragma once

#include "FleetManager/Common/Models/Result.h"
#include "FleetManager/Interfaces/IUsersService.h"
#include <crow/app.h>
#include <crow/common.h>
#include <crow/http_response.h>
#include <crow/json.h>
#include <memory>

class UsersController {
private:
  std::shared_ptr<IUsersService> usersService = nullptr;
  template <class... T> void Register(crow::App<T...> &app);

public:
  UsersController(std::shared_ptr<IUsersService> usersService);
  template <class... T> void Start(crow::App<T...> &app);
};

template <class... T> void UsersController::Start(crow::App<T...> &app) {
  Register(app);
}

template <class... T> void UsersController::Register(crow::App<T...> &app) {
  CROW_ROUTE(app, "/register")
      .methods("POST"_method)([this](const crow::request &req) {
        auto x = crow::json::load(req.body);
        if (!x) {
          return crow::response(crow::status::BAD_REQUEST);
        }
        User user(x);
        usersService->Register(user);
        Result res{crow::status::OK, "User registered"};
        return crow::response(res.toJson());
      });
}
