cmake_minimum_required(VERSION 3.16)

project(mini_redis
    VERSION 1.0
    LANGUAGES CXX
)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

#--------------------------
# Database Library
#--------------------------

add_library(database
    src/database.cpp
)

target_include_directories(database
    PUBLIC
        ${PROJECT_SOURCE_DIR}/include
)

# -------------------------
# Main application
# -------------------------

add_executable(mini-redis
    src/main.cpp
)

target_link_libraries(mini-redis
    PRIVATE
        database
)

# -------------------------
# Tests
# -------------------------

enable_testing()

add_executable(database_test
    tests/database_test.cpp
)

target_link_libraries(database_test
    PRIVATE
        database
)

add_test(
    NAME database_test
    COMMAND database_test
)