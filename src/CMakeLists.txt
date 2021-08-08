cmake_minimum_required(VERSION 3.10)

#SOURCES
set(ALGOLIB "algolib")
set(GEOMETRY "${ALGOLIB}/geometry")
set(GEOMETRY_PLANE "${GEOMETRY}/dim2")
set(GEOMETRY_SPACE "${GEOMETRY}/dim3")
set(GRAPHS "${ALGOLIB}/graphs")
set(GRAPHS_ALGORITHMS "${GRAPHS}/algorithms")
set(MATHMAT "${ALGOLIB}/mathmat")
set(SEQUENCES "${ALGOLIB}/sequences")
set(STRUCTURES "${ALGOLIB}/structures")
set(TEXT "${ALGOLIB}/text")

set(GEOMETRY_SOURCES
    "${GEOMETRY}/geometry_object.cpp")
set(GEOMETRY_PLANE_SOURCES
    "${GEOMETRY_PLANE}/closest_points.cpp"
    "${GEOMETRY_PLANE}/convex_hull.cpp"
    "${GEOMETRY_PLANE}/geometry_2d.cpp"
    "${GEOMETRY_PLANE}/point_2d.cpp"
    "${GEOMETRY_PLANE}/vector_2d.cpp")
set(GEOMETRY_SPACE_SOURCES
    "${GEOMETRY_SPACE}/geometry_3d.cpp"
    "${GEOMETRY_SPACE}/point_3d.cpp"
    "${GEOMETRY_SPACE}/vector_3d.cpp")
set(GRAPHS_SOURCES
    "${GRAPHS}/directed_graph.cpp"
    "${GRAPHS}/edge.cpp"
    "${GRAPHS}/graph.cpp"
    "${GRAPHS}/simple_graph.cpp"
    "${GRAPHS}/multipartite_graph.cpp"
    "${GRAPHS}/properties.cpp"
    "${GRAPHS}/tree_graph.cpp"
    "${GRAPHS}/undirected_graph.cpp")
set(GRAPHS_ALGORITHMS_SOURCES
    "${GRAPHS_ALGORITHMS}/cutting.cpp"
    "${GRAPHS_ALGORITHMS}/lowest_common_ancestor.cpp"
    "${GRAPHS_ALGORITHMS}/matching.cpp"
    "${GRAPHS_ALGORITHMS}/minimal_spanning_tree.cpp"
    "${GRAPHS_ALGORITHMS}/searching.cpp"
    "${GRAPHS_ALGORITHMS}/searching_strategy.cpp"
    "${GRAPHS_ALGORITHMS}/strongly_connected_components.cpp"
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
    "${TEXT}/base_words_map.cpp"
    "${TEXT}/kmp.cpp"
    "${TEXT}/suffix_array.cpp"
    "${TEXT}/trie.cpp")

set(SOURCES
    "${GEOMETRY_SOURCES}"
    "${GEOMETRY_PLANE_SOURCES}"
    "${GEOMETRY_SPACE_SOURCES}"
    "${GRAPHS_SOURCES}"
    "${GRAPHS_ALGORITHMS_SOURCES}"
    "${MATHMAT_SOURCES}"
    "${SEQUENCES_SOURCES}"
    "${STRUCTURES_SOURCES}"
    "${TEXT_SOURCES}")

# OUTPUT
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${LIB_OUTPUT_DIR})
add_library(${LIB_NAME} SHARED ${SOURCES})
