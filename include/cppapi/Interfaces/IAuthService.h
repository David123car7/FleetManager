#pragma once

#include "cppapi/Common/Entitys/User.h"
#include "cppapi/Common/Models/Requests/Auth/LoginRequest.h"
#include "cppapi/Common/Models/Requests/Auth/RegisterRequest.h"
#include "cppapi/Common/Models/Results/Result.h"

using API::Entitys::User;
using API::Models::Result;
using API::Models::Requests::Auth::LoginRequest;
using API::Models::Requests::Auth::RegisterRequest;

namespace API::Interfaces {
struct IAuthService {
  virtual Result<> Register(RegisterRequest &req) = 0;
  virtual Result<std::string> Login(LoginRequest req) = 0;
  virtual ~IAuthService() = default;
};
} // namespace API::Interfaces
