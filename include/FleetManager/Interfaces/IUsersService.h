#pragma once

#include "FleetManager/Common/Entitys/User.h"

class IUsersService {
public:
  virtual void Register(User &user) = 0;
  virtual ~IUsersService() = default;
};
