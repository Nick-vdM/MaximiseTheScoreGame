cmake_minimum_required(VERSION 3.15)
project(2_balls)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_FLAGS "${CMAKE_C_FLAGS} -O3")

add_executable(2_balls main.cpp)
add_executable(holyShitThatWasAMess holyShitThatWasAMess.cpp)
add_executable(randomInput randomInputFileGenerator.cpp)
