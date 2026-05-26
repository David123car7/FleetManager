#pragma once

#include "cppapi/Common/Models/Errors/Error.h"

namespace API::Models::Errors {
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
  static UserError EmptyEmail() { return UserError("empty_email"); }
  static UserError EmptyPassword() { return UserError("empty_password"); }
  static UserError PasswordEqualsOldPassword() {
    return UserError("password_equals_old_password");
  }

  friend bool operator==(const std::string &msg, const UserError &userError) {
    return userError.message == msg;
  }
};
} // namespace API::Models::Errors
