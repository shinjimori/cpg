cmake_minimum_required(VERSION 2.8)

set(CMAKE_CXX_FLAGS "-g -std=c++11 -Wall")
# include_directories(${CMAKE_CURRENT_SOURCE_DIR}/../include)
# include_directories(${CMAKE_CURRENT_SOURCE_DIR})

# aux_source_directory(${CMAKE_CURRENT_SOURCE_DIR} source) 

add_library(libIntegrator STATIC
  Integrator.cpp
  )

add_library(libMeasureFile STATIC
  MeasureFile.cpp
  )
