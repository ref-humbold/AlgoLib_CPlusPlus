cmake_minimum_required(VERSION 3.10)

#SOURCES
set(ALGOLIB "algolib")
set(GEOMETRY "${ALGOLIB}/geometry")
set(GRAPHS "${ALGOLIB}/old_graphs")
set(GRAPHS_ALGORITHMS "${GRAPHS}/algorithms")
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
    "${GRAPHS}/directed_graph.cpp"
    "${GRAPHS}/graph.cpp"
    "${GRAPHS}/multipartite_graph.cpp"
    "${GRAPHS}/tree_graph.cpp"
    "${GRAPHS}/undirected_graph.cpp")
set(GRAPHS_ALGORITHMS_SOURCES
    "${GRAPHS_ALGORITHMS}/cutting.cpp"
    "${GRAPHS_ALGORITHMS}/dinic.cpp"
    "${GRAPHS_ALGORITHMS}/edmonds.cpp"
    "${GRAPHS_ALGORITHMS}/lowest_common_ancestor.cpp"
    "${GRAPHS_ALGORITHMS}/matching.cpp"
    "${GRAPHS_ALGORITHMS}/minimal_spanning_tree.cpp"
    "${GRAPHS_ALGORITHMS}/paths.cpp"
    "${GRAPHS_ALGORITHMS}/strongly_connected_components.cpp"
    "${GRAPHS_ALGORITHMS}/searching.cpp"
    "${GRAPHS_ALGORITHMS}/searching_strategy.cpp"
    "${GRAPHS_ALGORITHMS}/topological_sorting.cpp")
set(MATHMAT_SOURCES
    "${MATHMAT}/equation.cpp"
    "${MATHMAT}/equation_system.cpp"
    "${MATHMAT}/fraction.cpp"
    "${MATHMAT}/maths.cpp"
    "${MATHMAT}/primes.cpp")
set(SEQUENCES_SOURCES
    "${SEQUENCES}/sorting.cpp"
    "${SEQUENCES}/subsequences.cpp")
set(STRUCTURES_SOURCES
    "${STRUCTURES}/avl_tree.cpp"
    "${STRUCTURES}/disjoint_sets.cpp"
    "${STRUCTURES}/double_heap.cpp")
set(TEXT_SOURCES
    "${TEXT}/kmp.cpp"
    "${TEXT}/kmr.cpp"
    "${TEXT}/suffix_array.cpp")

set(SOURCES
    "${GEOMETRY_SOURCES}"
    "${GRAPHS_SOURCES}"
    "${GRAPHS_ALGORITHMS_SOURCES}"
    "${MATHMAT_SOURCES}"
    "${SEQUENCES_SOURCES}"
    "${STRUCTURES_SOURCES}"
    "${TEXT_SOURCES}")

# OUTPUT
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${LIB_OUTPUT_DIR}")
add_library(algolib SHARED ${SOURCES})
