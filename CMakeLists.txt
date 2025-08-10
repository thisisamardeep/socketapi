cmake_minimum_required(VERSION 3.28)
project(socketapi)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

option(SOCKPP_BUILD_SHARED "Build shared library" ON)
option(SOCKPP_BUILD_STATIC "Build static library" OFF)
option(SOCKPP_BUILD_EXAMPLES "Build example applications" ON)
option(SOCKPP_BUILD_TESTS "Build unit tests" ON)
option(SOCKPP_BUILD_DOCUMENTATION "Create Doxygen reference documentation" OFF)


option(SOCKPP_WITH_UNIX_SOCKETS "Include support for UNIX-domain sockets" ON)


set(SOCKPP_INCLUDE_DIR ${PROJECT_SOURCE_DIR}/include)
set(SOCKPP_GENERATED_DIR ${CMAKE_CURRENT_BINARY_DIR}/generated)

if(${SOCKPP_BUILD_SHARED})
    list(APPEND SOCKPP_TARGETS sockpp-shared)
endif()

if(${SOCKPP_BUILD_STATIC})
    list(APPEND SOCKPP_TARGETS sockpp-static)
endif()

if(NOT SOCKPP_TARGETS)
    message(FATAL_ERROR "No targets are specified")
endif()