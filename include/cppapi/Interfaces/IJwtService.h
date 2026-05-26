#pragma once

#include "cppapi/Common/Models/Results/Result.h"
#include <string>

using API::Models::Result;

namespace API::Interfaces {
struct IJwtService {
  virtual std::string CreateJwtToken(std::string &userId, bool isAdmin) = 0;
  virtual bool IsJwtTokenValid(std::string &token, bool isAdmin) = 0;
  virtual Result<std::string> GetUserId(std::string &token) = 0;
  virtual ~IJwtService() = default;
};
} // namespace API::Interfaces
