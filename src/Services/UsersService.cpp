#include "FleetManager/Services/UsersService.h"
#include "FleetManager/Common/Entitys/User.h"
#include "FleetManager/Controllers/UsersController.h"
#include "FleetManager/Interfaces/IUsersService.h"
#include <crow/common.h>
#include <exception>
#include <string>

using Fleet::Entitys::User;

namespace Fleet::Services {
Result<> UsersService::Register(User &user) {
  pqxx::work tx{*dbConnection};
  try {
    tx.exec("INSERT INTO Users (email, password) VALUES ($1, $2)",
            pqxx::params{user.email, user.password});
    tx.commit();
  } catch (pqxx::sql_error sql_error) {
    if (sql_error.sqlstate() == "23505")
      return {UserError::EmailAllreadyExists(), crow::status::CONFLICT};
  } catch (std::exception e) {
    throw e;
  }
  return {crow::status::OK};
}

Result<std::string> UsersService::Login(LoginRequest req) {
  pqxx::work tx{*dbConnection};
  try {
    std::string storedPassword = tx.query_value<std::string>(
        "SELECT password FROM Users WHERE email = $1", pqxx::params{req.email});
    if (storedPassword == req.password) {
      return {"token", "", crow::status::OK};
    } else
      return {"", UserError::WrongPassword(), crow::status::UNAUTHORIZED};
  } catch (pqxx::unexpected_rows &) {
    return {"", UserError::UserNotExist(), crow::status::INTERNAL_SERVER_ERROR};
  } catch (std::exception &e) {
    return {"", e.what(), crow::status::INTERNAL_SERVER_ERROR};
  }
}
} // namespace Fleet::Services
