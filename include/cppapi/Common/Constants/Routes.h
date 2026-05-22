#pragma once

/*
 * For public routes: /public/...
 * For private routes: /private/...
 * For user roles: /private/role...
 */

namespace API::Constants::Routes {
inline constexpr char RegisterRoute[] = "/public/register";
inline constexpr char LoginRoute[] = "/public/login";
inline constexpr char IsAuthenticatedRoute[] = "/private/authenticated";
} // namespace API::Constants::Routes
