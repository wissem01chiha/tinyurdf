cmake_minimum_required(VERSION 3.22.1 FATAL_ERROR)


find_package(Yaml_cpp QUIET)

if(Yaml_cpp_FOUND)
    message(STATUS "Yaml-cpp found  : ${YAMEL_CPP_DIR}")
else()
    message(STATUS "Yaml-cpp not found. Downloading and building from source...  ")
    include(FetchContent)
    FetchContent_Declare(
        yaml-cpp
        GIT_REPOSITORY https://github.com/jbeder/yaml-cpp.git
        GIT_TAG <0.6.0> 
    )
    FetchContent_MakeAvailable(yaml-cpp)
endif()