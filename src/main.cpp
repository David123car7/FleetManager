#include "FleetManager/Controllers/UsersController.h"
#include "FleetManager/Services/UsersService.h"
#include <crow/app.h>
#include <memory>
#include <pqxx/pqxx>

int main() {
  pqxx::connection cx{
      "postgresql://cutlass:black@localhost:5432/fleet-manager-db"};

  auto usersService = std::make_shared<UsersService>();
  UsersController usersController(usersService);

  pqxx::work tx{cx};

  crow::SimpleApp app;

  usersController.Start(app);

  app.port(18080).run();

  return 0;
}
