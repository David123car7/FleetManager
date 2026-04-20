#include "FleetManager/Controllers/UsersController.h"
#include <crow/app.h>
#include <crow/common.h>
#include <crow/http_connection.h>
#include <crow/http_request.h>
#include <crow/http_response.h>
#include <crow/json.h>
#include <memory>

UsersController::UsersController(std::shared_ptr<IUsersService> usersService)
    : usersService{usersService} {
  if (usersService == nullptr)
    throw 0;
}
