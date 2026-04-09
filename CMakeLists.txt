cmake_minimum_required(VERSION 3.10)
project(FleetManager)
set(CMAKE_CXX_STANDARD_20)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON) #for the nvim lsp see cmake 
add_executable(FleetManager src/main.cpp)

include(FetchContent)
FetchContent_Declare(
  libpqxx
  GIT_REPOSITORY https://github.com/jtv/libpqxx.git
  GIT_TAG        8.0.1 
)
FetchContent_Declare(
  crow
  GIT_REPOSITORY git@github.com:CrowCpp/Crow.git
  GIT_TAG 1.3.2
)

target_include_directories(FleetManager PRIVATE src) 
target_link_libraries(FleetManager PRIVATE pqxx)
