cmake_minimum_required(VERSION 3.3)
project(grids)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -std=c++11 -lallegro -lallegro_primitives")

set(SOURCE_FILES Grid.cpp RobotReadings.cpp main.cpp)
add_executable(grids ${SOURCE_FILES})


