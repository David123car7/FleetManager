#pragma once

#include "FleetManager/Interfaces/IEncryptionService.h"
#include <string>

using Fleet::Interfaces::IEncryptionService;

class EncryptionService : public IEncryptionService {
private:
public:
  std::string EncryptPassword(const std::string &password);
  bool IsPasswordValid(const std::string &hashedPassword,
                       const std::string &password);
};
