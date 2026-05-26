# cpp-rest-api

A C++ REST API that provides a solid foundation for building http applications. It includes JWT-based authentication, password encryption, login and registration with database connectivity, making it a good base/template for new projects.

# How to run

### Install packages

```bash
conan install . --output-folder=build --build=missing
```

### Build

```bash
cmake -S . -B build -DCMAKE_TOOLCHAIN_FILE=build/build/Release/generators/conan_toolchain.cmake -DCMAKE_BUILD_TYPE=Release
cmake --build build
```

### Run database 

```bash
sudo docker compose -f docker-compose.yml up
```

### Run API

```bash
./build/cpp-rest-api
```

### Run TESTS

```bash
./build/tests/cpp-rest-api-tests
```

# Librarys

- [Crow](https://github.com/CrowCpp/Crow) - HTTP server framework 
- [libpqxx](https://github.com/jtv/libpqxx) - PostgreSQL client for database access.
- [LibSodium](https://github.com/jedisct1/libsodium) - Password hashing and crypto utilities.
- [jwt-cpp](https://github.com/Thalhammer/jwt-cpp) - JWT creation and validation.
- [nlohmann_json](https://github.com/nlohmann/json) - JSON parsing and serialization.
- [doctest](https://github.com/doctest/doctest/tree/master) - Testing framework

  
