#pragma once

#include "FleetManager/Common/Entitys/User.h"
#include "FleetManager/Interfaces/IEncryptionService.h"
#include "FleetManager/Interfaces/IUsersService.h"
#include "memory"
#include "pqxx/pqxx"
#include <memory>
#include <stdexcept>

using Fleet::Interfaces::IEncryptionService;
using Fleet::Interfaces::IUsersService;

namespace Fleet::Services {
class UsersService : public IUsersService {
private:
  std::shared_ptr<pqxx::connection> dbConnection = nullptr;
  std::shared_ptr<IEncryptionService> encryption = nullptr;

public:
  UsersService(std::shared_ptr<pqxx::connection> connection,
               std::shared_ptr<IEncryptionService> encryption)
      : dbConnection{connection} {
    if (connection == nullptr)
      throw std::invalid_argument("Invalid connection");
    if (encryption == nullptr)
      throw std::invalid_argument("Invalid encryption service");
  }
  Result<> Register(Fleet::Entitys::User &user);
  Result<std::string> Login(LoginRequest req);
};
} // namespace Fleet::Services
