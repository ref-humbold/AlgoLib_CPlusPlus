cmake_minimum_required(VERSION 3.10)
project(AlgoLib_CPlusPlus VERSION 0.5.190615 LANGUAGES CXX)

# COMPILER
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -Wno-unknown-pragmas")

# SOURCES
include_directories("include")

set(ALGOLIB "src/algolib")
set(GEOMETRY "${ALGOLIB}/geometry")
set(GRAPHS "${ALGOLIB}/graphs")
set(MATHMAT "${ALGOLIB}/mathmat")
set(SEQUENCES "${ALGOLIB}/sequences")
set(STRUCTURES "${ALGOLIB}/structures")
set(TEXT "${ALGOLIB}/text")

set(GEOMETRY_SOURCES
    "${GEOMETRY}/closest_points.cpp"
    "${GEOMETRY}/convex_hull.cpp"
    "${GEOMETRY}/point2d.cpp"
    "${GEOMETRY}/points_sorting.cpp")
set(GRAPHS_SOURCES
    "${GRAPHS}/cutting.cpp"
    "${GRAPHS}/dinic.cpp"
    "${GRAPHS}/directed_graph.cpp"
    "${GRAPHS}/edmonds.cpp"
    "${GRAPHS}/graph.cpp"
    "${GRAPHS}/lowest_common_ancestor.cpp"
    "${GRAPHS}/matching.cpp"
    "${GRAPHS}/minimal_spanning_tree.cpp"
    "${GRAPHS}/multipartite_graph.cpp"
    "${GRAPHS}/paths.cpp"
    "${GRAPHS}/strongly_connected_components.cpp"
    "${GRAPHS}/searching.cpp"
    "${GRAPHS}/topological_sorting.cpp"
    "${GRAPHS}/tree_graph.cpp"
    "${GRAPHS}/undirected_graph.cpp")
set(MATHMAT_SOURCES
    "${MATHMAT}/equation_system.cpp"
    "${MATHMAT}/fraction.cpp"
    "${MATHMAT}/maths.cpp"
    "${MATHMAT}/primes.cpp")
set(SEQUENCES_SOURCES
    "${SEQUENCES}/subseqs.cpp"
    "${SEQUENCES}/vector_sorting.cpp")
set(STRUCTURES_SOURCES
    "${STRUCTURES}/avl_tree.cpp"
    "${STRUCTURES}/disjoint_sets.cpp")
set(TEXT_SOURCES
    "${TEXT}/kmp.cpp"
    "${TEXT}/kmr.cpp"
    "${TEXT}/suffix_array.cpp")

set(SOURCES
    "${GEOMETRY_SOURCES}"
    "${GRAPHS_SOURCES}"
    "${MATHMAT_SOURCES}"
    "${SEQUENCES_SOURCES}"
    "${STRUCTURES_SOURCES}"
    "${TEXT_SOURCES}")

# TESTS
include(CTest)

# OUTPUT
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${PROJECT_SOURCE_DIR}/bin")
add_library(algolib SHARED ${SOURCES})

add_subdirectory(test)
