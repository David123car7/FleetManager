#include "cppapi/Services/UserService.h"
#include "cppapi/Common/Models/Errors/UserError.h"
#include <crow/common.h>

using API::Models::Errors::UserError;
using API::Services::UserService;

Result<> UserService::UpdatePassword(std::string &token,
                                     std::string &password) {
  auto userIdRes = jwt->GetUserId(token);
  if (userIdRes.GetHttpCode() != 200)
    return Result<>::Failure(userIdRes.GetMessage(), userIdRes.GetHttpCode());
  std::string userId = userIdRes.GetData();
  try {
    pqxx::work tx{*dbConnection};
    auto storedPasswordHash = tx.query_value<std::string>(
        "SELECT password FROM users WHERE id = $1", pqxx::params(userId));
    if (encryption->IsPasswordValid(storedPasswordHash, password))
      return Result<>::Failure(UserError::PasswordEqualsOldPassword(),
                               crow::status::BAD_REQUEST);
    auto hashPassword = encryption->HashPassword(password);
    tx.exec("UPDATE users SET password = $1 WHERE id = $2",
            pqxx::params(hashPassword, userId));
    tx.commit();
  } catch (std::exception &e) {
    return Result<>::Failure(e.what(), crow::status::INTERNAL_SERVER_ERROR);
  }
  return Result<>::Sucess();
}

Result<> UserService::UpdateIsAdmin(std::string &token, bool isAdmin) {
  auto userIdRes = jwt->GetUserId(token);
  if (userIdRes.GetHttpCode() != 200)
    return Result<>::Failure(userIdRes.GetMessage(), userIdRes.GetHttpCode());
  std::string userId = userIdRes.GetData();
  try {
    pqxx::work tx{*dbConnection};
    tx.exec("UPDATE users SET isAdmin = $1 WHERE id = $2",
            pqxx::params(isAdmin, userId));
    tx.commit();
  } catch (std::exception &e) {
    return Result<>::Failure(e.what(), crow::status::INTERNAL_SERVER_ERROR);
  }
  return Result<>::Sucess();
}
