cmake_minimum_required(VERSION 3.10)
project(cpp-rest-api)
set(CMAKE_CXX_STANDARD_20)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON) #for the nvim lsp see cmake 

find_package(Crow REQUIRED)
find_package(libpqxx REQUIRED)
find_package(PostgreSQL REQUIRED)
find_package(libsodium REQUIRED)
find_package(jwt-cpp REQUIRED)
find_package(nlohmann_json REQUIRED)
find_package(doctest REQUIRED)

add_subdirectory(src/Middlewares)
add_subdirectory(src/Services)
add_subdirectory(tests)
add_executable(cpp-rest-api src/main.cpp)

target_include_directories(cpp-rest-api PRIVATE include) 
target_link_libraries(cpp-rest-api PRIVATE doctest::doctest nlohmann_json::nlohmann_json jwt-cpp::jwt-cpp libsodium::libsodium gssapi_krb5 libpqxx::pqxx Crow::Crow Middlewares Services) 


