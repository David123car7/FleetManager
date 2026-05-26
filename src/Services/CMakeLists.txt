add_library(Services AuthService.cpp EncryptionService.cpp JwtService.cpp UserService.cpp)

target_include_directories(Services PRIVATE ../../include/)

target_link_libraries(Services PRIVATE nlohmann_json::nlohmann_json jwt-cpp::jwt-cpp Crow::Crow libpqxx::pqxx libsodium::libsodium) 
