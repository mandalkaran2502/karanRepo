cmake_minimum_required(VERSION 3.16)

project(mini_redis
VERSION 1.0
LANGUAGES CXX
)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

add_executable(mini-redis
src/main.cpp
src/database.cpp
)

target_include_directories(mini-redis
PRIVATE
${PROJECT_SOURCE_DIR}/include
)

add_executable(database_test
tests/database_test.cpp
src/database.cpp
)

target_include_directories(database_test
PRIVATE
${PROJECT_SOURCE_DIR}/include
)

enable_testing()

add_test(
    Name database_test
    COMMAND database_test
)