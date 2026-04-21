add_library(Controllers UsersController.cpp)

target_include_directories(Controllers PRIVATE ../../include/)

target_link_libraries(Controllers PRIVATE Crow::Crow libpqxx::pqxx) 


