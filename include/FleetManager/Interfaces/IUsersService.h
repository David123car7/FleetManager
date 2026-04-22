#pragma once

#include "FleetManager/Common/Entitys/User.h"

using Fleet::Entitys::User;

namespace Fleet::Interfaces {
class IUsersService {
public:
  virtual void Register(User &user) = 0;
  virtual ~IUsersService() = default;
};
} // namespace Fleet::Interfaces
