#pragma once
#include <sodium/core.h>
#include <string>

namespace Fleet::Interfaces {
struct IEncryptionService {
  virtual std::string EncryptPassword(const std::string &password) = 0;
  virtual bool IsPasswordValid(const std::string &hashedPassword,
                               const std::string &password) = 0;
  virtual ~IEncryptionService() = default;
};
} // namespace Fleet::Interfaces
