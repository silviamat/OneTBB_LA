cmake_minimum_required(VERSION 3.26)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

add_compile_options(-Wall -Wextra -Werror -pedantic -pedantic-errors)

# Executable for all unit tests with list of sources
add_executable(utest utest.cpp)
# Library dependencies
target_link_libraries (utest
        matrix
        GTest::gtest_main
        Microsoft.GSL::GSL)
# Discover all tests and add them to the test driver
include(GoogleTest)
gtest_discover_tests(utest)