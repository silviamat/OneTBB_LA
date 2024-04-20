cmake_minimum_required(VERSION 3.26)
project(tfg LANGUAGES CXX)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
# Set compiler options
set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -march=native")
# Enable GoogleTest Library
include(FetchContent)
FetchContent_Declare(
        googletest
        GIT_REPOSITORY https://github.com/google/googletest.git
        GIT_TAG v1.14.0
)
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)
# Enable GSL Library
FetchContent_Declare(GSL
        GIT_REPOSITORY "https://github.com/microsoft/GSL"
        GIT_TAG v4.0.0
        GIT_SHALLOW ON
)
FetchContent_MakeAvailable(GSL)

include_directories(PUBLIC .)
# Process cmake from sim and fluid directories
add_subdirectory(matrix)
# Unit tests and functional tests
enable_testing()
add_subdirectory(utest)

find_package(TBB)
add_executable(tfg main.cpp)
target_link_libraries(tfg TBB::tbb)