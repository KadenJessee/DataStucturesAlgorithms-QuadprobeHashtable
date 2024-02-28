cmake_minimum_required(VERSION 3.14)
project(hashtable)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_BUILD_TYPE Debug)

include_directories(inc)

add_executable(hashtable
        inc/Hashtable.h
        src/Hashtable.cpp
        src/HashtableTest.cpp)
