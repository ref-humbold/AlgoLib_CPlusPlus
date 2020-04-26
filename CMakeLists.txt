cmake_minimum_required(VERSION 3.10)
project(AlgoLib_CPlusPlus VERSION 0.0)

# PROPERTIES
set(INCLUDE_DIR "${PROJECT_SOURCE_DIR}/include")
set(SRC_DIR "${PROJECT_SOURCE_DIR}/src")
set(TEST_DIR "${PROJECT_SOURCE_DIR}/test")
set(EXE_OUTPUT_DIR "${PROJECT_SOURCE_DIR}/bin")
set(LIB_OUTPUT_DIR "${PROJECT_SOURCE_DIR}/dist")
set(DOCS_OUTPUT_DIR "${PROJECT_SOURCE_DIR}/docs")

# COMPILER
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -Wno-unknown-pragmas -O2")

# PACKAGES
find_package(GTest)
find_package(Doxygen)

# SOURCES
include_directories("${INCLUDE_DIR}")

# DOCS
if(DOXYGEN_FOUND)
    set(DOXYGEN_OUTPUT_DIRECTORY "${DOCS_OUTPUT_DIR}")
    doxygen_add_docs(docs "${INCLUDE_DIR}")
endif()

# OUTPUT
add_subdirectory("${SRC_DIR}")

if(GTEST_FOUND)
    include(CTest)
    add_subdirectory("${TEST_DIR}")
endif()
