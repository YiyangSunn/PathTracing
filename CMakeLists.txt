cmake_minimum_required(VERSION 3.21)

project(simple_ray_tracer)

set(CMAKE_CXX_STANDARD 11)

enable_testing()

if (NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Release)
    set(CMAKE_CXX_FLAGS "-O2")
    message(STATUS "Build in Release mode")
endif()

add_subdirectory(src)
add_subdirectory(test)
