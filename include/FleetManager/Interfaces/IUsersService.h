#pragma once

#include "FleetManager/Entitys/User.h"

class IUsersService {
public:
  virtual void Register(User &user) = 0;
  virtual ~IUsersService() = default;
};
