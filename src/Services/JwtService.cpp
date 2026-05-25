#include "cppapi/Services/JwtService.h"
#include <exception>
#include <jwt-cpp/jwt.h>
#include <jwt-cpp/traits/nlohmann-json/traits.h>
#include <string>

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
      return decoded.get_payload_claim("admin").as_boolean();
    }
  } catch (std::exception &e) {
    return false;
  }
  return true;
}
} // namespace API::Services
