#pragma once

#include "FleetManager/Common/Entitys/User.h"
#include "FleetManager/Common/Models/Requests/Users/LoginRequest.h"
#include "FleetManager/Common/Models/Results/Result.h"

using Fleet::Entitys::User;
using Fleet::Models::Result;
using Fleet::Models::Requests::Users::LoginRequest;

namespace Fleet::Interfaces {
struct IAuthService {
  virtual Result<> Register(User &user) = 0;
  virtual Result<std::string> Login(LoginRequest req) = 0;
  virtual ~IAuthService() = default;
};
} // namespace Fleet::Interfaces
