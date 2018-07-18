cmake_minimum_required(VERSION 3.5)

# SOURCES
include_directories("${PROJECT_SOURCE_DIR}/include")
set(ALGOLIB "algolib")
set(GRAPHS "${ALGOLIB}/graphs")
set(MATHS "${ALGOLIB}/math")
set(STRUCTURES "${ALGOLIB}/structures")
set(ALGOLIB_SOURCES
    "${ALGOLIB}/closest_points.cpp"
    "${ALGOLIB}/convex_hull.cpp"
    "${ALGOLIB}/kmp.cpp"
    "${ALGOLIB}/kmr.cpp"
    "${ALGOLIB}/lis.cpp"
    "${ALGOLIB}/maximum_subarray.cpp"
    "${ALGOLIB}/sorting.cpp"
    "${ALGOLIB}/two_sat.cpp")
set(GRAPHS_SOURCES
    "${GRAPHS}/cutting.cpp"
    "${GRAPHS}/dinic.cpp"
    "${GRAPHS}/directed_graph.cpp"
    "${GRAPHS}/edmonds.cpp"
    "${GRAPHS}/forest_graph.cpp"
    "${GRAPHS}/graph.cpp"
    "${GRAPHS}/lca.cpp"
    "${GRAPHS}/matching.cpp"
    "${GRAPHS}/mst.cpp"
    "${GRAPHS}/multipartite_graph.cpp"
    "${GRAPHS}/paths.cpp"
    "${GRAPHS}/scc.cpp"
    "${GRAPHS}/searching.cpp"
    "${GRAPHS}/topological_sorting.cpp"
    "${GRAPHS}/undirected_graph.cpp")
set(MATHS_SOURCES
    "${MATHS}/fraction.cpp"
    "${MATHS}/maths.cpp"
    "${MATHS}/primes.cpp")
set(STRUCTURES_SOURCES
    "${STRUCTURES}/avl_tree.cpp"
    "${STRUCTURES}/disjoint_sets.cpp"
    "${STRUCTURES}/equation_system.cpp")
set(SOURCES
    "${ALGOLIB_SOURCES}"
    "${GRAPHS_SOURCES}"
    "${MATHS_SOURCES}"
    "${STRUCTURES_SOURCES}")

# OUTPUT
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${PROJECT_SOURCE_DIR}/lib")
add_library(algolib SHARED ${SOURCES})
