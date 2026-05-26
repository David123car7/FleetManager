#pragma once

#include "cppapi/Common/Models/Results/Result.h"

using API::Models::Result;

namespace API::Interfaces {
struct IUserService {
  virtual Result<> UpdatePassword(std::string &token,
                                  std::string &password) = 0;
  virtual Result<> UpdateIsAdmin(std::string &token, bool isAdmin) = 0;
  virtual ~IUserService() = default;
};
} // namespace API::Interfaces
