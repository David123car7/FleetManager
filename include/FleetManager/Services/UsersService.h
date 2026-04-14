#pragma once

#include "FleetManager/Entitys/User.h"
#include "FleetManager/Interfaces/IUsersService.h"
#include "memory"
#include "pqxx/pqxx"
#include <memory>

class UsersService : public IUsersService {
private:
  std::shared_ptr<pqxx::connection> dbConnection = nullptr;

public:
  UsersService(std::shared_ptr<pqxx::connection> transaction);
  void Register(User &user);
};
