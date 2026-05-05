#include "FleetManager/Services/EncryptionService.h"
#include <sodium.h>
#include <sodium/crypto_pwhash.h>

std::string EncryptionService::EncryptPassword() {
  std::string password = "kazzio";
  unsigned char out[crypto_box_SEEDBYTES];
  unsigned char salt[crypto_pwhash_SALTBYTES];
  randombytes_buf(salt, sizeof salt);
  crypto_pwhash(out, sizeof out, password.c_str(), password.size(), salt,
                crypto_pwhash_OPSLIMIT_INTERACTIVE,
                crypto_pwhash_MEMLIMIT_INTERACTIVE, crypto_pwhash_ALG_DEFAULT);
  return std::string(reinterpret_cast<char *>(out), sizeof out);
}

std::string EncryptionService::DecryptPassword() { return {}; }
