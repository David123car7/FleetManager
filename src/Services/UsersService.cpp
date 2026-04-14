#include "FleetManager/Services/UsersService.h"
#include "FleetManager/Entitys/User.h"

UsersService::UsersService(std::shared_ptr<pqxx::connection> connection)
    : dbConnection{connection} {
  if (connection == nullptr)
    throw 0;
}

void UsersService::Register(User &user) {}
