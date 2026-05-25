#pragma once

#include "cppapi/Common/Constants/Routes.h"
#include "cppapi/Common/Models/Errors/AuthError.h"
#include "cppapi/Common/Models/Errors/UserError.h"
#include "cppapi/Common/Models/Results/Result.h"
#include "cppapi/Interfaces/IAuthService.h"
#include "cppapi/Services/AuthService.h"
#include <crow/app.h>
#include <crow/common.h>
#include <crow/http_response.h>
#include <crow/json.h>
#include <memory>
#include <stdexcept>

using API::Interfaces::IAuthService;
using API::Models::Result;
using API::Models::Errors::AuthError;
using API::Models::Errors::UserError;

namespace API::Controllers {
class AuthController {
private:
  std::shared_ptr<IAuthService> authService = nullptr;
  template <class... T> void Register(crow::App<T...> &app);
  template <class... T> void Login(crow::App<T...> &app);

public:
  AuthController(std::shared_ptr<IAuthService> authService)
      : authService{authService} {
    if (authService == nullptr)
      throw std::invalid_argument("Invalid authService");
  }

  template <class... T> void Start(crow::App<T...> &app);
};

template <class... T> void AuthController::Start(crow::App<T...> &app) {
  Register(app);
  Login(app);
}

template <class... T> void AuthController::Register(crow::App<T...> &app) {
  CROW_ROUTE(app, Constants::Routes::RegisterRoute)
      .methods("POST"_method)([this](const crow::request &req) {
        auto x = crow::json::load(req.body);
        if (!x) {
          return crow::response(crow::status::BAD_REQUEST);
        }
        RegisterRequest regReq{x};
        if (regReq.email.empty()) {
          return crow::response(crow::status::BAD_REQUEST,
                                Result<>::Failure(UserError::EmptyEmail()));
        }
        if (regReq.password.empty()) {
          return crow::response(crow::status::BAD_REQUEST,
                                Result<>::Failure(UserError::EmptyPassword()));
        }
        auto res = authService->Register(regReq);
        return crow::response(res.GetHttpCode(), res);
      });
}

template <class... T> void AuthController::Login(crow::App<T...> &app) {
  CROW_ROUTE(app, Constants::Routes::LoginRoute)
      .methods("POST"_method)([this](const crow::request &req) {
        auto x = crow::json::load(req.body);
        if (!x) {
          return crow::response(crow::status::BAD_REQUEST);
        }
        LoginRequest loginReq{x};
        auto res = authService->Login(loginReq);
        return crow::response(res.GetHttpCode(), res);
      });
}
} // namespace API::Controllers
