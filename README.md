# FleetManager
A Star Citizen fleet manager application developed with c++.

# How to run

## Install packages

```bash
conan install . --output-folder=build --build=missing
```

## Build

```bash
cmake -S . -B build -DCMAKE_TOOLCHAIN_FILE=build/build/Release/generators/conan_toolchain.cmake -DCMAKE_BUILD_TYPE=Release
cmake --build build
```

# Librarys

- [Crow](https://github.com/CrowCpp/Crow)
- [libpqxx](https://github.com/jtv/libpqxx)
