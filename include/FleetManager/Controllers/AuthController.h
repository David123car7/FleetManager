#pragma once

#include "FleetManager/Common/Models/Errors/AuthError.h"
#include "FleetManager/Common/Models/Errors/UserError.h"
#include "FleetManager/Common/Models/Results/Result.h"
#include "FleetManager/Interfaces/IAuthService.h"
#include "FleetManager/Services/AuthService.h"
#include <crow/app.h>
#include <crow/common.h>
#include <crow/http_response.h>
#include <crow/json.h>
#include <memory>
#include <stdexcept>

using Fleet::Interfaces::IAuthService;
using Fleet::Models::Result;
using Fleet::Models::Errors::AuthError;
using Fleet::Models::Errors::UserError;

namespace Fleet::Controllers {
class AuthController {
private:
  std::shared_ptr<IAuthService> authService = nullptr;
  template <class... T> void Register(crow::App<T...> &app);
  template <class... T> void Login(crow::App<T...> &app);
  template <class... T> void IsAuthenticated(crow::App<T...> &app);

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
  IsAuthenticated(app);
}

template <class... T> void AuthController::Register(crow::App<T...> &app) {
  CROW_ROUTE(app, "/register")
      .methods("POST"_method)([this](const crow::request &req) {
        auto x = crow::json::load(req.body);
        if (!x) {
          return crow::response(crow::status::BAD_REQUEST);
        }
        Fleet::Entitys::User user(x);
        auto res = authService->Register(user);
        return crow::response(res.GetHttpCode(), res);
      });
}

template <class... T> void AuthController::Login(crow::App<T...> &app) {
  CROW_ROUTE(app, "/login")
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

template <class... T>
void AuthController::IsAuthenticated(crow::App<T...> &app) {
  CROW_ROUTE(app, "/authenticated")
      .methods("GET"_method)([this](const crow::request &req) {
        std::string token = req.get_header_value("Authorization");
        if (token.empty())
          return crow::response(
              crow::status::UNAUTHORIZED,
              Result<>::Failure(AuthError::AuthHeaderMissing()));
        if (!authService->IsAuthenticated(token))
          return crow::response(
              crow::status::UNAUTHORIZED,
              Result<>::Failure(AuthError::InvalidAuthToken()));
        else
          return crow::response(crow::status::OK);
      });
}
} // namespace Fleet::Controllers
