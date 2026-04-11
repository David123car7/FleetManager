#include "FleetManager/Services/UsersService.h"
#include "FleetManager/Entitys/User.h"

void UsersService::Register(User &user) {
  std::cout << user.email << " " << user.password;
}
