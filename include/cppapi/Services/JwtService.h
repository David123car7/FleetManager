#pragma once

#include "cppapi/Interfaces/IJwtService.h"

using API::Interfaces::IJwtService;

namespace API::Services {
class JwtService : public IJwtService {
public:
  std::string CreateJwtToken(std::string &userId);
  bool IsJwtTokenValid(std::string &token);
};
} // namespace API::Services
