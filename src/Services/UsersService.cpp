#include "FleetManager/Services/UsersService.h"
#include "FleetManager/Common/Entitys/User.h"

UsersService::UsersService(std::shared_ptr<pqxx::connection> connection)
    : dbConnection{connection} {
  if (connection == nullptr)
    throw 0;
}

void UsersService::Register(User &user) {
  pqxx::work tx{*dbConnection};
  tx.exec("INSERT INTO Users (email, password) VALUES ($1, $2)",
          pqxx::params{user.email, user.password});
  tx.commit();
}
