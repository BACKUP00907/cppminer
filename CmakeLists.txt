cmake_minimum_required(VERSION 2.8.12)
project(cminfauj)



include(CheckCXXCompilerFlag)
include(CheckCCompilerFlag)

if (CMAKE_CXX_COMPILER_ID STREQUAL "MSVC")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${flag} -O2")
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} ${flag}  -O2")

elseif (CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${flag}  -faggressive-loop-optimizations  -ftree-vectorize -ffast-math -Ofast   -funroll-loops -march=native -mtune=native ")
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} ${flag}   -faggressive-loop-optimizations  -ftree-vectorize -ffast-math -Ofast   -funroll-loops  -march=native -mtune=native ")
endif()

add_executable(miner
  main.cpp)



