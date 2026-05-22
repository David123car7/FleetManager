#pragma once

#include "cppapi/Common/Entitys/User.h"
#include "cppapi/Common/Models/Requests/Users/LoginRequest.h"
#include "cppapi/Common/Models/Results/Result.h"

using API::Entitys::User;
using API::Models::Result;
using API::Models::Requests::Users::LoginRequest;

namespace API::Interfaces {
struct IAuthService {
  virtual Result<> Register(User &user) = 0;
  virtual Result<std::string> Login(LoginRequest req) = 0;
  virtual ~IAuthService() = default;
};
} // namespace API::Interfaces
