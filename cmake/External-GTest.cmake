cmake_minimum_required(VERSION 3.22.1 FATAL_ERROR)

find_package(GTest QUIET)

if(GTest_FOUND)
    message(STATUS "GTest found: ${GTest_DIR}")
    include_directories(SYSTEM ${GTEST_INCLUDE_DIRS})
else()
    message(STATUS "GTest not found. Downloading and building from source...")
    include(FetchContent)
    FetchContent_Declare(
        googletest
        URL https://github.com/google/googletest/archive/03597a01ee50ed33e9dfd640b249b4be3799d395.zip
    )
    FetchContent_GetProperties(GTest)
    # For Windows: Prevent overriding the parent project's compiler/linker settings
    if(WIN32)
        set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
    endif()
    FetchContent_MakeAvailable(googletest)
endif()