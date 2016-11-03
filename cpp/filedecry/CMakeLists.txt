cmake_minimum_required(VERSION 3.6)
project(filedecry)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES main.cpp DecryFile.cpp DecryFile.h)
add_executable(filedecry ${SOURCE_FILES})