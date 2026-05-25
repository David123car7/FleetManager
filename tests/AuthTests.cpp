#include "cppapi/Common/Entitys/User.h"
#include "cppapi/Common/Models/Requests/Auth/LoginRequest.h"
#include "cppapi/Common/Models/Requests/Auth/RegisterRequest.h"
#include "cppapi/Controllers/AuthController.h"
#include "cppapi/Middlewares/AuthMiddleware.h"
#include "cppapi/Services/AuthService.h"
#include "cppapi/Services/EncryptionService.h"
#include "cppapi/Services/JwtService.h"
#include <crow/app.h>
#include <crow/common.h>
#include <doctest/doctest.h>
#include <memory>
#include <pqxx/pqxx>
#include <sodium.h>
#include <sodium/core.h>
#include <stdexcept>

using API::Controllers::AuthController;
using API::Middlewares::AuthMiddleware;
using API::Services::AuthService;
using API::Services::JwtService;

TEST_CASE("AuthTests") {
  auto dbConnection = std::make_shared<pqxx::connection>(
      "postgresql://test:test@localhost:5433/cpp-rest-api-db-tests");

  pqxx::work tx{*dbConnection};
  tx.exec("DELETE FROM users WHERE email = $1",
          pqxx::params("email@email.com"));
  tx.commit();

  auto encryptionService = std::make_shared<EncryptionService>();
  if (sodium_init() < 0)
    throw std::runtime_error("Failed sodium");

  auto jwtService = std::make_shared<JwtService>();

  auto authService = std::make_shared<AuthService>(
      dbConnection, encryptionService, jwtService);

  AuthController authController(authService);

  crow::App<AuthMiddleware> app;
  app.get_middleware<AuthMiddleware>() = AuthMiddleware(jwtService);
  authController.Start(app);

  SUBCASE("Register User - 200 OK") {
    app.validate();
    crow::request req;
    crow::response res;
    req.url = "/public/register";
    req.method = crow::HTTPMethod::POST;
    req.body = API::Models::Requests::Auth::RegisterRequest("email@email.com",
                                                            "password")
                   .ToString();
    app.handle_full(req, res);
    REQUIRE(res.code == 200);
    REQUIRE(!res.body.empty());
  }

  SUBCASE("Register User (same email allready exists) - 409 Conflict") {
    RegisterRequest registerReq("email@email.com", "password");
    authService->Register(registerReq);
    app.validate();
    crow::request req;
    crow::response res;
    req.url = "/public/register";
    req.method = crow::HTTPMethod::POST;
    req.body = API::Models::Requests::Auth::RegisterRequest("email@email.com",
                                                            "password")
                   .ToString();
    app.handle_full(req, res);
    Result<std::string> result(res.body);
    REQUIRE(res.code == crow::status::CONFLICT);
    REQUIRE(result.GetMessage() == UserError::EmailAllreadyExists());
    REQUIRE(!res.body.empty());
  }

  SUBCASE("Register User (with empty email) - 400 Bad Request") {
    app.validate();
    crow::request req;
    crow::response res;
    req.url = "/public/register";
    req.method = crow::HTTPMethod::POST;
    req.body =
        API::Models::Requests::Auth::RegisterRequest("", "password").ToString();
    app.handle_full(req, res);
    Result<std::string> result(res.body);
    REQUIRE(res.code == crow::status::BAD_REQUEST);
    REQUIRE(result.GetMessage() == UserError::EmptyEmail());
    REQUIRE(!res.body.empty());
  }

  SUBCASE("Register User (with empty password) - 400 Bad Request") {
    app.validate();
    crow::request req;
    crow::response res;
    req.url = "/public/register";
    req.method = crow::HTTPMethod::POST;
    req.body =
        API::Models::Requests::Auth::RegisterRequest("email@email.com", "")
            .ToString();
    app.handle_full(req, res);
    Result<std::string> result(res.body);
    REQUIRE(res.code == crow::status::BAD_REQUEST);
    REQUIRE(result.GetMessage() == UserError::EmptyPassword());
    REQUIRE(!res.body.empty());
  }

  SUBCASE("Login - 200 OK") {
    RegisterRequest registerReq("email@email.com", "password");
    authService->Register(registerReq);
    app.validate();
    crow::request req;
    crow::response res;
    req.url = "/public/login";
    req.method = crow::HTTPMethod::POST;
    req.body =
        API::Models::Requests::Auth::LoginRequest("email@email.com", "password")
            .ToString();
    app.handle_full(req, res);
    REQUIRE(res.code == 200);
    REQUIRE(!res.body.empty());
  }

  SUBCASE("Login (email does not exist) - 500 INTERNAL_SERVER_ERROR") {
    app.validate();
    crow::request req;
    crow::response res;
    req.url = "/public/login";
    req.method = crow::HTTPMethod::POST;
    req.body = API::Models::Requests::Auth::LoginRequest(
                   "doesnotexist@email.com", "password")
                   .ToString();
    app.handle_full(req, res);
    Result<std::string> result(res.body);
    REQUIRE(res.code == crow::status::INTERNAL_SERVER_ERROR);
    REQUIRE(result.GetMessage() == UserError::UserNotExist());
    REQUIRE(!res.body.empty());
  }

  SUBCASE("Login (wrong password) - 500 INTERNAL_SERVER_ERROR") {
    RegisterRequest registerReq("email@email.com", "password");
    authService->Register(registerReq);
    app.validate();
    crow::request req;
    crow::response res;
    req.url = "/public/login";
    req.method = crow::HTTPMethod::POST;
    req.body = API::Models::Requests::Auth::LoginRequest("email@email.com",
                                                         "wrongPassword")
                   .ToString();
    app.handle_full(req, res);
    Result<std::string> result(res.body);
    REQUIRE(res.code == crow::status::UNAUTHORIZED);
    REQUIRE(result.GetMessage() == UserError::WrongPassword());
    REQUIRE(!res.body.empty());
  }
}
