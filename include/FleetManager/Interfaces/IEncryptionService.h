#pragma once
#include <sodium/core.h>
#include <string>

namespace Fleet::Interfaces {
struct IEncryptionService {
  virtual std::string EncryptPassword() = 0;
  virtual std::string DecryptPassword() = 0;
  virtual ~IEncryptionService() = default;
};
} // namespace Fleet::Interfaces
