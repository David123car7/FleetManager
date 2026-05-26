#pragma once

#include "cppapi/Common/Entitys/User.h"
#include "cppapi/Interfaces/IAuthService.h"
#include "cppapi/Interfaces/IEncryptionService.h"
#include "cppapi/Interfaces/IJwtService.h"
#include "memory"
#include <memory>
#include <pqxx/pqxx>
#include <stdexcept>

using API::Interfaces::IAuthService;
using API::Interfaces::IEncryptionService;
using API::Interfaces::IJwtService;

namespace API::Services {
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
  Result<> Register(RegisterRequest &req);
  Result<std::string> Login(LoginRequest &req);
};
} // namespace API::Services
