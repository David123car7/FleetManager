add_library(Middlewares AuthMiddleware.cpp)

target_include_directories(Middlewares PRIVATE ../../include/)

target_link_libraries(Middlewares PRIVATE Crow::Crow libpqxx::pqxx) 
