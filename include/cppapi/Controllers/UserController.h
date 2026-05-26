#pragma once

#include "cppapi/Common/Constants/Routes.h"
#include "cppapi/Common/Models/Errors/AuthError.h"
#include "cppapi/Common/Models/Errors/UserError.h"
#include "cppapi/Common/Models/Results/Result.h"
#include "cppapi/Interfaces/IUserService.h"
#include <crow/app.h>
#include <crow/common.h>
#include <crow/http_response.h>
#include <crow/json.h>
#include <memory>
#include <stdexcept>
#include <string>

using API::Interfaces::IUserService;
using API::Models::Result;
using API::Models::Errors::AuthError;
using API::Models::Errors::UserError;

namespace API::Controllers {
class UserController {
private:
  std::shared_ptr<IUserService> userService = nullptr;
  template <class... T> void UpdatePassword(crow::App<T...> &app);
  template <class... T> void UpdateIsAdmin(crow::App<T...> &app);

public:
  UserController(std::shared_ptr<IUserService> userService)
      : userService{userService} {
    if (userService == nullptr)
      throw std::invalid_argument("Invalid userService");
  }

  template <class... T> void Start(crow::App<T...> &app);
};

template <class... T> void UserController::Start(crow::App<T...> &app) {
  UpdatePassword(app);
  UpdateIsAdmin(app);
}

template <class... T>
void UserController::UpdatePassword(crow::App<T...> &app) {
  CROW_ROUTE(app, Constants::Routes::UpdatePassword)
      .methods("POST"_method)([this](const crow::request &req) {
        auto x = crow::json::load(req.body);
        if (!x || !x.has("password")) {
          return crow::response(crow::status::BAD_REQUEST);
        }
        std::string password = x["password"].s();
        if (password.empty()) {
          return crow::response(crow::status::BAD_REQUEST,
                                Result<>::Failure(UserError::EmptyPassword()));
        }
        std::string token = req.get_header_value("Authorization");
        auto res = userService->UpdatePassword(token, password);
        return crow::response(res.GetHttpCode(), res);
      });
}

template <class... T> void UserController::UpdateIsAdmin(crow::App<T...> &app) {
  CROW_ROUTE(app, Constants::Routes::UpdateIsAdmin)
      .methods("POST"_method)([this](const crow::request &req) {
        auto x = crow::json::load(req.body);
        if (!x || !x.has("isAdmin")) {
          return crow::response(crow::status::BAD_REQUEST);
        }
        bool isAdmin = x["isAdmin"].b();
        std::string token = req.get_header_value("Authorization");
        auto res = userService->UpdateIsAdmin(token, isAdmin);
        return crow::response(res.GetHttpCode(), res);
      });
}
} // namespace API::Controllers
