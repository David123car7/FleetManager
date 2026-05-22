#pragma once

#include "FleetManager/Interfaces/IJwtService.h"

using Fleet::Interfaces::IJwtService;

namespace Fleet::Services {
class JwtService : public IJwtService {
public:
  std::string CreateJwtToken(std::string &userId);
  bool VerifyJwtToken(std::string &token);
};
} // namespace Fleet::Services
