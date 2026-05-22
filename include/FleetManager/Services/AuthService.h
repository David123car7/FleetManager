#pragma once

#include "FleetManager/Common/Entitys/User.h"
#include "FleetManager/Interfaces/IAuthService.h"
#include "FleetManager/Interfaces/IEncryptionService.h"
#include "FleetManager/Interfaces/IJwtService.h"
#include "memory"
#include <memory>
#include <pqxx/pqxx>
#include <stdexcept>

using Fleet::Interfaces::IAuthService;
using Fleet::Interfaces::IEncryptionService;
using Fleet::Interfaces::IJwtService;

namespace Fleet::Services {
class AuthService : public IAuthService {
private:
  std::shared_ptr<pqxx::connection> dbConnection = nullptr;
  std::shared_ptr<IEncryptionService> encryption = nullptr;
  std::shared_ptr<IJwtService> jwt = nullptr;

public:
  AuthService(std::shared_ptr<pqxx::connection> connection,
              std::shared_ptr<IEncryptionService> encryption,
              std::shared_ptr<IJwtService> jwt)
      : dbConnection{connection}, encryption{encryption}, jwt{jwt} {
    if (connection == nullptr)
      throw std::invalid_argument("Invalid connection");
    if (encryption == nullptr)
      throw std::invalid_argument("Invalid encryption service");
    if (jwt == nullptr)
      throw std::invalid_argument("Invalid jwt service");
  }
  Result<> Register(Fleet::Entitys::User &user);
  Result<std::string> Login(LoginRequest req);
  bool IsAuthenticated(std::string &token);
};
} // namespace Fleet::Services
