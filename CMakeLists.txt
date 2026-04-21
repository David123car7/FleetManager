cmake_minimum_required(VERSION 3.10)
project(FleetManager)
set(CMAKE_CXX_STANDARD_20)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON) #for the nvim lsp see cmake 

find_package(Crow REQUIRED)
find_package(libpqxx REQUIRED)
find_package(PostgreSQL REQUIRED)

add_subdirectory(src/Controllers)
add_subdirectory(src/Middlewares)
add_subdirectory(src/Services)
add_executable(FleetManager src/main.cpp)

target_include_directories(FleetManager PRIVATE include) 
target_link_libraries(FleetManager PRIVATE gssapi_krb5 libpqxx::pqxx Crow::Crow Controllers Middlewares Services) 
