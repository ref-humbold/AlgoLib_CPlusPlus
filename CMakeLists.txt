cmake_minimum_required(VERSION 3.10)
project(AlgoLib_CPlusPlus VERSION 0.0)

# PROPERTIES
set(LIB_NAME algolib)

set(INCLUDE_DIR "${PROJECT_SOURCE_DIR}/include")
set(SRC_DIR "${PROJECT_SOURCE_DIR}/src")
set(TEST_DIR "${PROJECT_SOURCE_DIR}/test")
set(OUTPUT_DIR "${PROJECT_SOURCE_DIR}/buildOut")
set(TEST_EXE_OUTPUT_DIR "${OUTPUT_DIR}/test")
set(LIB_OUTPUT_DIR "${OUTPUT_DIR}/dist")
set(DOCS_OUTPUT_DIR "${OUTPUT_DIR}/docs")

# COMPILER
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -Wno-unknown-pragmas -O2")

# PACKAGES
find_package(GTest)
find_package(Doxygen)

# DIRECTORY STRUCTURE
set(ALGOLIB "algolib")
set(GEOMETRY "${ALGOLIB}/geometry")
set(GEOMETRY_DIM2 "${GEOMETRY}/dim2")
set(GEOMETRY_DIM3 "${GEOMETRY}/dim3")
set(GRAPHS "${ALGOLIB}/graphs")
set(GRAPHS_ALGORITHMS "${GRAPHS}/algorithms")
set(MATHS "${ALGOLIB}/maths")
set(SEQUENCES "${ALGOLIB}/sequences")
set(STRUCTURES "${ALGOLIB}/structures")
set(STRUCTURES_HEAPS "${STRUCTURES}/heaps")
set(TEXT "${ALGOLIB}/text")

# SOURCES
include_directories(${INCLUDE_DIR})

# OUTPUT
add_subdirectory(${SRC_DIR})

if(GTEST_FOUND)
    message(STATUS "GTest found")
    include(CTest)
    add_subdirectory(${TEST_DIR})
else()
    message(WARNING "GTest not found - skipping tests")
endif()

# DOCS
if(DOXYGEN_FOUND)
    message(STATUS "Doxygen found (version ${DOXYGEN_VERSION})")
    set(DOXYGEN_OUTPUT_DIRECTORY ${DOCS_OUTPUT_DIR})
    doxygen_add_docs(docs ${INCLUDE_DIR})
else()
    message(WARNING "Doxygen not found - skipping docs")
endif()
