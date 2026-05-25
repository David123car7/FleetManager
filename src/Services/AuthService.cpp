#include "cppapi/Services/AuthService.h"
#include "cppapi/Common/Entitys/User.h"
#include "cppapi/Common/Models/Errors/UserError.h"
#include "cppapi/Interfaces/IAuthService.h"
#include <crow/common.h>
#include <exception>
#include <string>

using API::Entitys::User;
using API::Models::Errors::UserError;

namespace API::Services {
Result<> AuthService::Register(User &user) {
  pqxx::work tx{*dbConnection};
  std::string hashedPassword = encryption->HashPassword(user.password);
  try {
    tx.exec("INSERT INTO Users (email, password) VALUES ($1, $2)",
            pqxx::params{user.email, hashedPassword});
    tx.commit();
  } catch (pqxx::sql_error sql_error) {
    if (sql_error.sqlstate() == "23505")
      return Result<>::Failure(UserError::EmailAllreadyExists(),
                               crow::status::CONFLICT);
  } catch (std::exception e) {
    throw e;
  }
  tx.commit();
  return Result<>::Sucess();
}

Result<std::string> AuthService::Login(LoginRequest req) {
  try {
    pqxx::work tx{*dbConnection};
    User user{
        tx.exec("SELECT * FROM Users WHERE email = $1", pqxx::params{req.email})
            .one_row()};
    if (encryption->IsPasswordValid(user.password, req.password)) {
      std::string token = jwt->CreateJwtToken(user.id, user.isAdmin);
      return Result<std::string>::Sucess(200, token);
    } else
      return Result<std::string>::Failure(UserError::WrongPassword(),
                                          crow::status::UNAUTHORIZED);
  } catch (pqxx::unexpected_rows &) {
    return Result<std::string>::Failure(UserError::UserNotExist(),
                                        crow::status::INTERNAL_SERVER_ERROR);
  } catch (std::exception &e) {
    return Result<std::string>::Failure(e.what(),
                                        crow::status::INTERNAL_SERVER_ERROR);
  }
}
} // namespace API::Services
