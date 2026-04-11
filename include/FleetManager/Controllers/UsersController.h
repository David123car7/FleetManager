#pragma once

#include "FleetManager/Interfaces/IUsersService.h"
#include <crow/app.h>
#include <memory>

class UsersController {
private:
  std::shared_ptr<IUsersService> usersService = nullptr;
  void Register(crow::SimpleApp &app);

public:
  UsersController(std::shared_ptr<IUsersService> usersService);
  void Start(crow::SimpleApp &app);
};
