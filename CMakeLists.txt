cmake_minimum_required(VERSION 3.22.1 FATAL_ERROR)

project(tinyurdf VERSION 1.0.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(BUILD_SHARED_LIBS  OFF)
set(BUILD_TESTS ON)

if (CMAKE_CXX_COMPILER_ID STREQUAL "GNU" OR CMAKE_CXX_COMPILER_ID STREQUAL "Clang")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O3")
elseif (CMAKE_CXX_COMPILER_ID STREQUAL "MSVC")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /O2")
endif()

set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake" ${CMAKE_MODULE_PATH})
include(External-Eigen)
include(External-GTest)
add_subdirectory(extern/loguru)
add_subdirectory(extern/tinyxml2)

set(TINYURDF_LIBRARY_SOURCES
    src/color.cpp
    src/pose.cpp
    src/link.cpp
    src/joint.cpp
    src/joint_parser.cpp
    #src/joint.cpp
    #src/world.cpp
    #src/sensor.cpp
    #src/check_urdf.cpp
)

set(TINYURDF_INCLUDE_DIRECTORIES
    ${CMAKE_SOURCE_DIR}/include/tinyurdf
    ${CMAKE_SOURCE_DIR}/extern
)

add_library(tinyurdf ${TINYURDF_LIBRARY_SOURCES})

target_include_directories(tinyurdf PUBLIC ${TINYURDF_INCLUDE_DIRECTORIES})
target_link_libraries(tinyurdf PUBLIC Eigen3::Eigen loguru tinyxml2)
if (BUILD_SHARED_LIBS)
    set_target_properties(tinyurdf PROPERTIES WINDOWS_EXPORT_ALL_SYMBOLS ON)
endif()

if (BUILD_TESTS)
    enable_testing()

    set(TINYURDF_TEST_SOURCES
        test/color_test.cxx
        test/urdf_utilities_test.cxx
    )

    foreach(TEST_SOURCE_FILE IN LISTS TINYURDF_TEST_SOURCES)
        get_filename_component(TEST_EXECUTABLE_NAME ${TEST_SOURCE_FILE} NAME_WE)
        add_executable(${TEST_EXECUTABLE_NAME} ${TEST_SOURCE_FILE})
        target_include_directories(${TEST_EXECUTABLE_NAME} PRIVATE ${TINYURDF_INCLUDE_DIRECTORIES})
        target_link_libraries(${TEST_EXECUTABLE_NAME} PRIVATE GTest::gtest_main tinyurdf)
        add_dependencies(${TEST_EXECUTABLE_NAME} tinyurdf)
        include(GoogleTest)
        gtest_discover_tests(${TEST_EXECUTABLE_NAME})
    endforeach()
endif()