cmake_minimum_required(VERSION 3.10)

# SOURCES
set(ALGOLIB "algolib")
set(GEOMETRY "${ALGOLIB}/geometry")
set(GRAPHS "${ALGOLIB}/graphs")
set(MATHMAT "${ALGOLIB}/mathmat")
set(STRUCTURES "${ALGOLIB}/structures")
set(TEXT "${ALGOLIB}/text")
set(ALGOLIB_SOURCES
    "${ALGOLIB}/closest_points.cpp"
    "${ALGOLIB}/lis.cpp"
    "${ALGOLIB}/maximum_subarray.cpp"
    "${ALGOLIB}/vector_sorting.cpp")
set(GEOMETRY_SOURCES
    "${GEOMETRY}/convex_hull.cpp"
    "${GEOMETRY}/point2d.cpp"
    "${GEOMETRY}/points_sorting.cpp")
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
set(MATHMAT_SOURCES
    "${MATHMAT}/equation_system.cpp"
    "${MATHMAT}/fraction.cpp"
    "${MATHMAT}/maths.cpp"
    "${MATHMAT}/primes.cpp")
set(STRUCTURES_SOURCES
    "${STRUCTURES}/avl_tree.cpp"
    "${STRUCTURES}/disjoint_sets.cpp")
set(TEXT_SOURCES
    "${TEXT}/kmp.cpp"
    "${TEXT}/kmr.cpp"
    "${TEXT}/suffix_array.cpp")
set(SOURCES
    "${ALGOLIB_SOURCES}"
    "${GEOMETRY_SOURCES}"
    "${GRAPHS_SOURCES}"
    "${MATHMAT_SOURCES}"
    "${STRUCTURES_SOURCES}"
    "${TEXT_SOURCES}")

# OUTPUT
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${PROJECT_SOURCE_DIR}/bin")
add_library(algolib SHARED ${SOURCES})
