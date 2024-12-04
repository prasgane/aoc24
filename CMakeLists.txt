cmake_minimum_required(VERSION 3.10)

project(AdventofCode2024)

# Set compiler flags
set(CMAKE_CXX_FLAGS "-std=c++20 -Wall -Wextra")

# Add source files for the executable
add_executable(aoc_day1 day01.cpp)

add_executable(aoc_day2 day02.cpp)

add_executable(aoc_day3 day03.cpp)