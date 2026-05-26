#include "cppapi/Services/JwtService.h"
#include "cppapi/Common/Models/Errors/AuthError.h"
#include <exception>
#include <ios>
#include <jwt-cpp/jwt.h>
#include <jwt-cpp/traits/nlohmann-json/traits.h>
#include <stdexcept>
#include <string>

using API::Models::Errors::AuthError;

namespace API::Services {
std::string JwtService::CreateJwtToken(std::string &userId, bool isAdmin) {
  const auto time = jwt::date::clock::now();
  return jwt::create<jwt::traits::nlohmann_json>()
      .set_type("JWT")
      .set_subject(userId)
      .set_payload_claim("admin", isAdmin)
      .set_issued_at(time)
      .set_expires_at(time + std::chrono::minutes{60})
      .sign(jwt::algorithm::hs256{"secret"});
}

bool JwtService::IsJwtTokenValid(std::string &token, bool isAdmin) {
  try {
    auto decoded = jwt::decode<jwt::traits::nlohmann_json>(token);
    jwt::verify<jwt::traits::nlohmann_json>()
        .allow_algorithm(jwt::algorithm::hs256{"secret"})
        .verify(decoded);
    if (isAdmin) {
      // This is not perfect in case the admin role is removed the token
      // generated before that will work meaning the user will be admin until
      // that token expires, so it should also check de database
      return decoded.get_payload_claim("admin").as_boolean();
    }
  } catch (std::exception &e) {
    return false;
  }
  return true;
}

Result<std::string> JwtService::GetUserId(std::string &token) {
  try {
    auto decoded = jwt::decode<jwt::traits::nlohmann_json>(token);
    return Result<std::string>::Sucess(200, decoded.get_subject());
  } catch (std::invalid_argument &e) {
    return Result<std::string>::Failure(AuthError::InvalidAuthToken());
  }
}
} // namespace API::Services
