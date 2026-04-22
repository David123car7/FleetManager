#pragma once

#include "FleetManager/Common/Models/Errors/UserError.h"
#include "FleetManager/Common/Models/Result.h"
#include "FleetManager/Interfaces/IUsersService.h"
#include "FleetManager/Services/UsersService.h"
#include <crow/app.h>
#include <crow/common.h>
#include <crow/http_response.h>
#include <crow/json.h>
#include <memory>

using Fleet::Interfaces::IUsersService;
using Fleet::Models::Result;
using Fleet::Models::Errors::UserError;

namespace Fleet::Controllers {
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
        Fleet::Entitys::User user(x);
        usersService->Register(user);
        Result res{UserError::InvalidEmail()};
        return crow::response(crow::status::OK, res);
      });
}
} // namespace Fleet::Controllers
