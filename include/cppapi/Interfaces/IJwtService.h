#pragma once

#include <string>

namespace API::Interfaces {
struct IJwtService {
  virtual std::string CreateJwtToken(std::string &userId, bool isAdmin) = 0;
  virtual bool IsJwtTokenValid(std::string &token, bool isAdmin) = 0;
  virtual ~IJwtService() = default;
};
} // namespace API::Interfaces
