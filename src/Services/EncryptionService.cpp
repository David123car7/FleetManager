#include "FleetManager/Services/EncryptionService.h"
#include <sodium.h>
#include <sodium/crypto_pwhash.h>
#include <stdexcept>

std::string EncryptionService::EncryptPassword(const std::string &password) {
  char hashed_password[crypto_pwhash_STRBYTES];
  if (crypto_pwhash_str(hashed_password, password.c_str(), password.size(),
                        crypto_pwhash_OPSLIMIT_SENSITIVE,
                        crypto_pwhash_MEMLIMIT_SENSITIVE) != 0) {
    throw std::runtime_error("Out of memory while hashing password");
  }
  return std::string(hashed_password, sizeof hashed_password);
}

bool EncryptionService::IsPasswordValid(const std::string &hashedPassword,
                                        const std::string &password) {
  return !crypto_pwhash_str_verify(hashedPassword.c_str(), password.c_str(),
                                   password.size());
}
