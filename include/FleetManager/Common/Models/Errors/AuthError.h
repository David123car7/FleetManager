#pragma once

#include "FleetManager/Common/Models/Errors/Error.h"

namespace Fleet::Models::Errors {
struct AuthError : Error {
private:
  AuthError(std::string message) : Error{message} {}

public:
  AuthError() = delete;
  static AuthError AuthHeaderMissing() {
    return AuthError("auth_header_missing");
  }

  static AuthError InvalidAuthToken() {
    return AuthError("invalid_auth_token");
  }
};
} // namespace Fleet::Models::Errors
