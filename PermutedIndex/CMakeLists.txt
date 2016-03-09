cmake_minimum_required(VERSION 3.3)
project(PermutedIndex)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES main.cpp indexEntry.cpp indexEntry.h index.cpp index.h)
add_executable(PermutedIndex ${SOURCE_FILES})