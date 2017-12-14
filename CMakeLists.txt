cmake_minimum_required(VERSION 2.8)

project(cpg)

set(CMAKE_CXX_FLAGS "-g -std=c++11 -Wall")
#add_subdirectory(matsuoka)
add_subdirectory(lib)
add_subdirectory(src)

#add_executable(matsuoka matsuoka/matsuoka.cpp)
#target_link_libraries(matsuoka lib_runge lib_measurement)

