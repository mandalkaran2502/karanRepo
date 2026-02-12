cmake_minimum_required(VERSION 3.14)
project(BankingSystem VERSION 1.0.0 LANGUAGES CXX)

# Set C++ standard
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Set output directories
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)

# Include directories
include_directories(${PROJECT_SOURCE_DIR}/include)

# Compiler warnings
if(MSVC)
    add_compile_options(/W4)
else()
    add_compile_options(-Wall -Wextra -Wpedantic)
endif()

# Source files
set(SOURCES
    src/Account.cpp
    src/Transaction.cpp
    src/FixedDeposit.cpp
    src/BankManager.cpp
    src/FileManager.cpp
)

# Create library
add_library(BankingLib STATIC ${SOURCES})

# Main executable
add_executable(BankingSystem src/main.cpp)
target_link_libraries(BankingSystem BankingLib)

# Enable testing
enable_testing()

# Add Google Test
include(FetchContent)
FetchContent_Declare(
    googletest
    GIT_REPOSITORY https://github.com/google/googletest.git
    GIT_TAG v1.14.0
)
# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

# Test executable
add_executable(BankingTests
    tests/test_account.cpp
    tests/test_fixed_deposit.cpp
    tests/test_bank_manager.cpp
    tests/test_file_manager.cpp
)

target_link_libraries(BankingTests
    BankingLib
    GTest::gtest_main
)

include(GoogleTest)
gtest_discover_tests(BankingTests)

# Installation
install(TARGETS BankingSystem DESTINATION bin)
install(DIRECTORY data/ DESTINATION share/banking/data)
