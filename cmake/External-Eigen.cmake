cmake_minimum_required(VERSION 3.22.1 FATAL_ERROR)

find_package(Eigen3 QUIET)

if(Eigen3_FOUND)
    message(STATUS "Eigen3 found: ${EIGEN3_INCLUDE_DIR}")
else()
    message(STATUS "Eigen3 not found. Downloading and building from source...")
    include(FetchContent)
    FetchContent_Declare(
        eigen
        URL https://gitlab.com/libeigen/eigen/-/archive/3.4.0/eigen-3.4.0.tar.gz
    )
    FetchContent_GetProperties(Eigen)
    set(BUILD_TESTING OFF CACHE BOOL "Disable Eigen tests")
    FetchContent_MakeAvailable(Eigen)
    include_directories(SYSTEM ${eigen_SOURCE_DIR}/eigen-3.4.0)
    message(STATUS "Eigen3 has been fetched and is available at ${eigen_SOURCE_DIR}/eigen-3.4.0")
endif()