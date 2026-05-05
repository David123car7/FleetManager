#pragma once

#include "FleetManager/Interfaces/IEncryptionService.h"
#include <string>

using Fleet::Interfaces::IEncryptionService;

class EncryptionService : public IEncryptionService {
private:
public:
  std::string EncryptPassword();
  std::string DecryptPassword();
};
