cmake_minimum_required(VERSION 2.8)

set(CMAKE_CXX_FLAGS "-g -std=c++11 -Wall")

add_executable(matsuoka matsuoka.cpp)
target_link_libraries(matsuoka libIntegrator libMeasureFile)
