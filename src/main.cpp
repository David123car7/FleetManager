#include "cppapi/Controllers/AuthController.h"
#include "cppapi/Middlewares/AuthMiddleware.h"
#include "cppapi/Services/AuthService.h"
#include "cppapi/Services/EncryptionService.h"
#include "cppapi/Services/JwtService.h"
#include <crow/app.h>
#include <memory>
#include <pqxx/pqxx>
#include <sodium.h>
#include <sodium/core.h>
#include <stdexcept>

using API::Controllers::AuthController;
using API::Middlewares::AuthMiddleware;
using API::Services::AuthService;
using API::Services::JwtService;

int main() {
  auto dbConnection = std::make_shared<pqxx::connection>(
      "postgresql://cutlass:black@localhost:5432/cpp-rest-api-db");

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

  app.port(18080).run();

  return 0;
}
