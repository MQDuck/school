cmake_minimum_required(VERSION 3.9)
project(Lab1)

set(CMAKE_CXX_STANDARD 17)
set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -Wpedantic")

add_executable(Lab1 main.cpp)