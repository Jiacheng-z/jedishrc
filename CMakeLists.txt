cmake_minimum_required(VERSION 2.8)
project(jedishrc_base)

if (CMAKE_VERSION VERSION_LESS "3")
    add_definitions(-std=c++11)
else ()
    cmake_policy(SET CMP0042 NEW)
    set(CMAKE_CXX_STANDARD 11)
    set(CMAKE_CXX_STANDARD_REQUIRED ON)
endif ()

add_subdirectory(include/jedishrc)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)

add_subdirectory(example)
