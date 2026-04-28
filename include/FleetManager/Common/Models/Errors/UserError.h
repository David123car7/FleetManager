#pragma once

#include "FleetManager/Common/Models/Errors/Error.h"

namespace Fleet::Models::Errors {
struct UserError : Error {
private:
  UserError(std::string message) : Error{message} {}

public:
  UserError() = delete;
  static UserError EmailAllreadyExists() { return UserError("email_exists"); }
  static UserError InvalidEmail() { return UserError("invalid_email"); }
  static UserError InvalidPassword() { return UserError("invalid_password"); }
  static UserError WrongPassword() { return UserError("wrong_password"); }
  static UserError UserNotExist() { return UserError("user_not_exist"); }
};
} // namespace Fleet::Models::Errors
