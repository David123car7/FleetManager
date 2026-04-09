#include <crow/app.h>
#include <pqxx/pqxx>

int main() {
  pqxx::connection cx{
      "postgresql://cutlass:black@localhost:5432/fleet-manager-db"};

  crow::SimpleApp app;

  app.port(18080).run();

  return 0;
}
