#include "FleetManager/Services/UsersService.h"
#include "FleetManager/Common/Entitys/User.h"
#include "FleetManager/Controllers/UsersController.h"
#include "FleetManager/Interfaces/IUsersService.h"
#include <crow/common.h>
#include <exception>

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
      return {UserError::EmailAllreadyExists(), crow::status::CONFLICT, false};
  } catch (std::exception e) {
    throw e;
  }
  return {true};
}

Result<std::string> UsersService::Login(LoginRequest req) {}
} // namespace Fleet::Services
