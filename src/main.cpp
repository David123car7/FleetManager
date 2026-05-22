#include "FleetManager/Controllers/AuthController.h"
#include "FleetManager/Middlewares/AuthMiddleware.h"
#include "FleetManager/Services/AuthService.h"
#include "FleetManager/Services/EncryptionService.h"
#include "FleetManager/Services/JwtService.h"
#include <crow/app.h>
#include <memory>
#include <pqxx/pqxx>
#include <sodium.h>
#include <sodium/core.h>
#include <stdexcept>

using Fleet::Controllers::AuthController;
using Fleet::Middlewares::AuthMiddleware;
using Fleet::Services::AuthService;
using Fleet::Services::JwtService;

int main() {
  auto dbConnection = std::make_shared<pqxx::connection>(
      "postgresql://cutlass:black@localhost:5432/fleet-manager-db");

  auto encryptionService = std::make_shared<EncryptionService>();
  if (sodium_init() < 0)
    throw std::runtime_error("Failed sodium");

  auto jwtService = std::make_shared<JwtService>();

  auto authService = std::make_shared<AuthService>(
      dbConnection, encryptionService, jwtService);

  AuthController authController(authService);

  crow::App<AuthMiddleware> app;

  authController.Start(app);

  app.port(18080).run();

  return 0;
}
