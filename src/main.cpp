#include "cppapi/Controllers/AuthController.h"
#include "cppapi/Controllers/UserController.h"
#include "cppapi/Middlewares/AuthMiddleware.h"
#include "cppapi/Services/AuthService.h"
#include "cppapi/Services/EncryptionService.h"
#include "cppapi/Services/JwtService.h"
#include "cppapi/Services/UserService.h"
#include <crow/app.h>
#include <memory>
#include <pqxx/pqxx>
#include <sodium.h>
#include <sodium/core.h>
#include <stdexcept>

using API::Controllers::AuthController;
using API::Controllers::UserController;
using API::Middlewares::AuthMiddleware;
using API::Services::AuthService;
using API::Services::JwtService;
using API::Services::UserService;

int main() {
  auto dbConnection = std::make_shared<pqxx::connection>(
      "postgresql://david123car7:kazzio@localhost:5432/cpp-rest-api-db");

  auto encryptionService = std::make_shared<EncryptionService>();
  if (sodium_init() < 0)
    throw std::runtime_error("Failed sodium");

  auto jwtService = std::make_shared<JwtService>();

  auto authService = std::make_shared<AuthService>(
      dbConnection, encryptionService, jwtService);

  auto userService = std::make_shared<UserService>(
      dbConnection, encryptionService, jwtService);

  AuthController authController(authService);
  UserController userController(userService);

  crow::App<AuthMiddleware> app;
  app.get_middleware<AuthMiddleware>() = AuthMiddleware(jwtService);

  authController.Start(app);
  userController.Start(app);

  app.port(18080).run();

  return 0;
}
