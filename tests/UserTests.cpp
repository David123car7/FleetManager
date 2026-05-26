#include "cppapi/Common/Constants/Routes.h"
#include "cppapi/Common/Entitys/User.h"
#include "cppapi/Common/Models/Requests/Auth/RegisterRequest.h"
#include "cppapi/Controllers/AuthController.h"
#include "cppapi/Controllers/UserController.h"
#include "cppapi/Middlewares/AuthMiddleware.h"
#include "cppapi/Services/AuthService.h"
#include "cppapi/Services/EncryptionService.h"
#include "cppapi/Services/JwtService.h"
#include "cppapi/Services/UserService.h"
#include <crow/app.h>
#include <crow/common.h>
#include <doctest/doctest.h>
#include <memory>
#include <pqxx/pqxx>
#include <sodium.h>
#include <sodium/core.h>
#include <stdexcept>

using API::Controllers::AuthController;
using API::Controllers::UserController;
using API::Middlewares::AuthMiddleware;
using API::Models::Requests::Auth::RegisterRequest;
using API::Services::AuthService;
using API::Services::JwtService;
using API::Services::UserService;

TEST_CASE("UserTests") {
  auto dbConnection = std::make_shared<pqxx::connection>(
      "postgresql://test:test@localhost:5433/cpp-rest-api-db-tests");

  // Deletes the User
  {
    pqxx::work tx{*dbConnection};
    tx.exec("DELETE FROM users WHERE email = $1",
            pqxx::params("email@email.com"));
    tx.commit();
  }

  auto encryptionService = std::make_shared<EncryptionService>();
  if (sodium_init() < 0)
    throw std::runtime_error("Failed sodium");

  auto jwtService = std::make_shared<JwtService>();

  auto authService = std::make_shared<AuthService>(
      dbConnection, encryptionService, jwtService);

  auto userService = std::make_shared<UserService>(
      dbConnection, encryptionService, jwtService);

  // Creates User
  RegisterRequest reg{"email@email.com", "password"};
  authService->Register(reg);

  std::string userId;
  {
    pqxx::work tx{*dbConnection};
    userId =
        tx.query_value<std::string>("SELECT id FROM users WHERE email = $1",
                                    pqxx::params("email@email.com"));
    tx.commit();
  }

  AuthController authController(authService);
  UserController userController(userService);

  crow::App<AuthMiddleware> app;
  app.get_middleware<AuthMiddleware>() = AuthMiddleware(jwtService);
  authController.Start(app);
  userController.Start(app);
  app.validate();

  SUBCASE("Update Password - 200 OK") {
    std::string token = jwtService->CreateJwtToken(userId, false);
    app.validate();
    crow::request req;
    crow::response res;
    req.url = API::Constants::Routes::UpdatePassword;
    req.method = crow::HTTPMethod::POST;
    req.body = R"({"password": "newPassword"})";
    req.add_header("Authorization", token);
    app.handle_full(req, res);
    REQUIRE(res.code == crow::status::OK);
    REQUIRE(!res.body.empty());
  }

  SUBCASE("Update Password (empty password) - 400 Bad Request") {
    std::string token = jwtService->CreateJwtToken(userId, false);
    app.validate();
    crow::request req;
    crow::response res;
    req.url = API::Constants::Routes::UpdatePassword;
    req.method = crow::HTTPMethod::POST;
    req.body = R"({"password": ""})";
    req.add_header("Authorization", token);
    app.handle_full(req, res);
    Result<std::string> result(res.body);
    REQUIRE(res.code == crow::status::BAD_REQUEST);
    REQUIRE(result.GetMessage() == UserError::EmptyPassword());
    REQUIRE(!res.body.empty());
  }
  SUBCASE("Update Password (password is the same as the old password) - 400 "
          "Bad Request") {
    std::string token = jwtService->CreateJwtToken(userId, false);
    app.validate();
    crow::request req;
    crow::response res;
    req.url = API::Constants::Routes::UpdatePassword;
    req.method = crow::HTTPMethod::POST;
    req.body = R"({"password": "password"})";
    req.add_header("Authorization", token);
    app.handle_full(req, res);
    Result<std::string> result(res.body);
    REQUIRE(res.code == crow::status::BAD_REQUEST);
    REQUIRE(result.GetMessage() == UserError::PasswordEqualsOldPassword());
    REQUIRE(!res.body.empty());
  }
  SUBCASE("Update isAdmin - 200 OK") {
    std::string token = jwtService->CreateJwtToken(userId, true);
    app.validate();
    crow::request req;
    crow::response res;
    req.url = API::Constants::Routes::UpdateIsAdmin;
    req.method = crow::HTTPMethod::POST;
    req.body = R"({"isAdmin": true})";
    req.add_header("Authorization", token);
    app.handle_full(req, res);
    REQUIRE(res.code == crow::status::OK);
    REQUIRE(!res.body.empty());
  }
}
