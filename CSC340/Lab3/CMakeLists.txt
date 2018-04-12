cmake_minimum_required(VERSION 3.9)
project(Lab3)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -Wpedantic")

add_executable(Lab3 dynamicArray-main.cpp dynamicArray.cpp dynamicArray.h)