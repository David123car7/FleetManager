#include "FleetManager/Controllers/UsersController.h"
#include "FleetManager/Middlewares/AuthMiddleware.h"
#include "FleetManager/Services/UsersService.h"
#include <crow/app.h>
#include <memory>
#include <pqxx/pqxx>

using Fleet::Controllers::UsersController;
using Fleet::Middlewares::AuthMiddleware;
using Fleet::Services::UsersService;

int main() {
  auto dbConnection = std::make_shared<pqxx::connection>(
      "postgresql://cutlass:black@localhost:5432/fleet-manager-db");

  auto usersService = std::make_shared<UsersService>(dbConnection);

  UsersController usersController(usersService);

  crow::App<AuthMiddleware> app;

  usersController.Start(app);

  app.port(18080).run();

  return 0;
}
