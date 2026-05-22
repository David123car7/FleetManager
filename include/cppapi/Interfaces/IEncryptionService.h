#pragma once
#include <string>

namespace API::Interfaces {
struct IEncryptionService {
  virtual std::string HashPassword(const std::string &password) = 0;
  virtual bool IsPasswordValid(const std::string &hashedPassword,
                               const std::string &password) = 0;
  virtual ~IEncryptionService() = default;
};
} // namespace API::Interfaces
