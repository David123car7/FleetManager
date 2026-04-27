#pragma once

#include "FleetManager/Common/Entitys/User.h"
#include "FleetManager/Interfaces/IUsersService.h"
#include "memory"
#include "pqxx/pqxx"
#include <memory>
#include <stdexcept>

using Fleet::Interfaces::IUsersService;

namespace Fleet::Services {
class UsersService : public IUsersService {
private:
  std::shared_ptr<pqxx::connection> dbConnection = nullptr;

public:
  UsersService(std::shared_ptr<pqxx::connection> connection)
      : dbConnection{connection} {
    if (connection == nullptr)
      throw std::invalid_argument("Invalid connection");
  }
  Result<> Register(Fleet::Entitys::User &user);
  Result<std::string> Login(LoginRequest req);
};
} // namespace Fleet::Services
