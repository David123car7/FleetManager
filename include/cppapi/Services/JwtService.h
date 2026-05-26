#pragma once

#include "cppapi/Common/Models/Results/Result.h"
#include "cppapi/Interfaces/IJwtService.h"

using API::Interfaces::IJwtService;
using API::Models::Result;

namespace API::Services {
class JwtService : public IJwtService {
public:
  std::string CreateJwtToken(std::string &userId, bool isAdmin);
  bool IsJwtTokenValid(std::string &token, bool isAdmin);
  Result<std::string> GetUserId(std::string &token);
};
} // namespace API::Services
