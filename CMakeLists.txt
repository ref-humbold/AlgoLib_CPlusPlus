cmake_minimum_required(VERSION 3.5)

# PROJECT
project(algolib VERSION 0.3)

# COMPILER
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra")

# OUTPUT
add_subdirectory(src)
#add_subdirectory(test)