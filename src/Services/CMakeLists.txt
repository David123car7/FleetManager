add_library(Services UsersService.cpp)

target_include_directories(Services PRIVATE ../../include/)

target_link_libraries(Services PRIVATE Crow::Crow libpqxx::pqxx) 
