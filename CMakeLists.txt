cmake_minimum_required(VERSION 3.14)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_EXTENSIONS OFF) # use -std=c++... instead of -std=gnu++..

project(MultiObjectiveOptimization CXX)

set(CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/cmake ${CMAKE_MODULE_PATH})

add_executable(moo src/GridBuilder.cpp
                   src/Solver.cpp
                   src/Main.cpp)

target_include_directories(moo PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)