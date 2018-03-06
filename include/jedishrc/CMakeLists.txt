cmake_minimum_required(VERSION 2.8)
project(jedishrc)

if (CMAKE_VERSION VERSION_LESS "3")
    add_definitions(-std=c++11)
else ()
    cmake_policy(SET CMP0042 NEW)
    set(CMAKE_CXX_STANDARD 11)
    set(CMAKE_CXX_STANDARD_REQUIRED ON)
endif ()

set(MURMURHASH_FILES murmurhash/murmurhash.h murmurhash/murmurhash.cpp)
set(SOURCE_FILES ${MURMURHASH_FILES} config.h jedishrc.h)

add_library(jedishrc SHARED ${SOURCE_FILES})
target_compile_options(jedishrc PRIVATE -pipe -W -Wall -Wno-unused-parameter -fPIC -fno-omit-frame-pointer)