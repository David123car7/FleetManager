#include "FleetManager/Controllers/UsersController.h"
#include "FleetManager/Middlewares/AuthMiddleware.h"
#include "FleetManager/Services/EncryptionService.h"
#include "FleetManager/Services/UsersService.h"
#include <crow/app.h>
#include <memory>
#include <pqxx/pqxx>
#include <sodium.h>
#include <sodium/core.h>
#include <stdexcept>

using Fleet::Controllers::UsersController;
using Fleet::Middlewares::AuthMiddleware;
using Fleet::Services::UsersService;

int main() {
  auto dbConnection = std::make_shared<pqxx::connection>(
      "postgresql://cutlass:black@localhost:5432/fleet-manager-db");

  auto encryptionService = std::make_shared<EncryptionService>();
  if (sodium_init() < 0)
    throw std::runtime_error("Failed sodium");

  auto usersService =
      std::make_shared<UsersService>(dbConnection, encryptionService);

  UsersController usersController(usersService);

  crow::App<AuthMiddleware> app;

  usersController.Start(app);

  app.port(18080).run();

  return 0;
}
