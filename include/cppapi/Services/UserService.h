#pragma once

#include "cppapi/Interfaces/IEncryptionService.h"
#include "cppapi/Interfaces/IJwtService.h"
#include "cppapi/Interfaces/IUserService.h"
#include <pqxx/pqxx>
#include <stdexcept>

using API::Interfaces::IEncryptionService;
using API::Interfaces::IJwtService;
using API::Interfaces::IUserService;

namespace API::Services {
class UserService : public IUserService {
private:
  std::shared_ptr<pqxx::connection> dbConnection = nullptr;
  std::shared_ptr<IEncryptionService> encryption = nullptr;
  std::shared_ptr<IJwtService> jwt = nullptr;

public:
  UserService(std::shared_ptr<pqxx::connection> &dbConnection,
              std::shared_ptr<IEncryptionService> encryptionService,
              std::shared_ptr<IJwtService> jwtService)
      : dbConnection{dbConnection}, encryption{encryptionService},
        jwt{jwtService} {
    if (dbConnection == nullptr)
      throw std::invalid_argument("Invalid dbConnection");
    if (encryptionService == nullptr)
      throw std::invalid_argument("Invalid encryption service");
    if (jwtService == nullptr)
      throw std::invalid_argument("Invalid jwt service");
  }
  Result<> UpdatePassword(std::string &token, std::string &password);
  Result<> UpdateIsAdmin(std::string &token, bool isAdmin);
};
} // namespace API::Services
