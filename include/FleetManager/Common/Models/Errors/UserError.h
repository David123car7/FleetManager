#pragma once

#include "FleetManager/Common/Models/Errors/Error.h"
#include <string_view>

namespace Fleet::Models::Errors {
struct UserError : Error {
private:
  UserError(std::string_view message) : Error{message} {}

public:
  UserError() = delete;
  static UserError InvalidEmail() { return UserError("invalid_email"); }
  static UserError InvalidPassword() { return UserError("invalid_password"); }
};
} // namespace Fleet::Models::Errors
