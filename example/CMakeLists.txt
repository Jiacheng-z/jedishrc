cmake_minimum_required(VERSION 2.8)
project(jedishrc_simple)

if (CMAKE_VERSION VERSION_LESS "3")
    add_definitions(-std=c++11)
else ()
    cmake_policy(SET CMP0042 NEW)
    set(CMAKE_CXX_STANDARD 11)
    set(CMAKE_CXX_STANDARD_REQUIRED ON)
endif ()

add_executable(jedishrc_simple simple.cpp)
target_link_libraries(jedishrc_simple jedishrc)
