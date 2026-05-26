add_executable(cpp-rest-api-tests tests.cpp AuthTests.cpp UserTests.cpp)
target_include_directories(cpp-rest-api-tests PRIVATE ../include/)
target_link_libraries(cpp-rest-api-tests PRIVATE doctest::doctest nlohmann_json::nlohmann_json jwt-cpp::jwt-cpp libsodium::libsodium gssapi_krb5 libpqxx::pqxx Crow::Crow Middlewares Services) 
