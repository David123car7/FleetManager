#pragma once

#include "cppapi/Interfaces/IJwtService.h"

using API::Interfaces::IJwtService;

namespace API::Services {
class JwtService : public IJwtService {
public:
  std::string CreateJwtToken(std::string &userId, bool isAdmin);
  bool IsJwtTokenValid(std::string &token, bool isAdmin);
};
} // namespace API::Services
