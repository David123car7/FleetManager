#pragma once

/*
 * For public routes: /public/...
 * For private routes: /private/...
 * For admin routes: /private/admin/..
 * For user roles: /private/role...
 */

namespace API::Constants::Routes {
inline constexpr char RegisterRoute[] = "/public/register";
inline constexpr char LoginRoute[] = "/public/login";
inline constexpr char UpdatePassword[] = "/private/update/password";
inline constexpr char UpdateIsAdmin[] = "/private/admin/update/isAdmin";
} // namespace API::Constants::Routes
