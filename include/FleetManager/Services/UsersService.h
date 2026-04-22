#pragma once

#include "FleetManager/Common/Entitys/User.h"
#include "FleetManager/Interfaces/IUsersService.h"
#include "memory"
#include "pqxx/pqxx"
#include <memory>

using Fleet::Interfaces::IUsersService;

namespace Fleet::Services {
class UsersService : public IUsersService {
private:
  std::shared_ptr<pqxx::connection> dbConnection = nullptr;

public:
  UsersService(std::shared_ptr<pqxx::connection> transaction);
  void Register(Fleet::Entitys::User &user);
};
} // namespace Fleet::Services
