#pragma once

#include <string>

namespace Fleet::Interfaces {
struct IJwtService {
  virtual std::string CreateJwtToken(std::string &userId) = 0;
  virtual bool VerifyJwtToken(std::string &token) = 0;
  virtual ~IJwtService() = default;
};
} // namespace Fleet::Interfaces
