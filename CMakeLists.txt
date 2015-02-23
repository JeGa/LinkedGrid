cmake_minimum_required(VERSION 2.8)
project(LinkedGrid)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -Wall -g")

add_subdirectory(src)
add_subdirectory(test)