#pragma once

#include "FleetManager/Entitys/User.h"
#include "FleetManager/Interfaces/IUsersService.h"

class UsersService : public IUsersService {
public:
  void Register(User &user);

private:
};
