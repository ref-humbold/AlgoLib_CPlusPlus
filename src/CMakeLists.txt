cmake_minimum_required(VERSION 3.10)

#SOURCES
set(GEOMETRY_SOURCES
    "${GEOMETRY}/geometry_object.cpp")
set(GEOMETRY_DIM2_SOURCES
    "${GEOMETRY_DIM2}/closest_points.cpp"
    "${GEOMETRY_DIM2}/convex_hull.cpp"
    "${GEOMETRY_DIM2}/geometry_2d.cpp"
    "${GEOMETRY_DIM2}/point_2d.cpp"
    "${GEOMETRY_DIM2}/vector_2d.cpp")
set(GEOMETRY_DIM3_SOURCES
    "${GEOMETRY_DIM3}/geometry_3d.cpp"
    "${GEOMETRY_DIM3}/point_3d.cpp"
    "${GEOMETRY_DIM3}/vector_3d.cpp")
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
    "${GRAPHS_ALGORITHMS}/shortest_paths.cpp"
    "${GRAPHS_ALGORITHMS}/searching_strategy.cpp"
    "${GRAPHS_ALGORITHMS}/strongly_connected_components.cpp"
    "${GRAPHS_ALGORITHMS}/topological_sorting.cpp"
    "${GRAPHS_ALGORITHMS}/tree_diameter.cpp")
set(MATHS_SOURCES
    "${MATHS}/equation.cpp"
    "${MATHS}/equation_system.cpp"
    "${MATHS}/fraction.cpp"
    "${MATHS}/maths.cpp"
    "${MATHS}/primes_searching.cpp"
    "${MATHS}/primes_testing.cpp")
set(SEQUENCES_SOURCES
    "${SEQUENCES}/longest_common_subsequence.cpp"
    "${SEQUENCES}/longest_increasing_subsequence.cpp"
    "${SEQUENCES}/maximum_subarray.cpp"
    "${SEQUENCES}/sorting.cpp")
set(STRUCTURES_SOURCES
    "${STRUCTURES}/avl_tree.cpp"
    "${STRUCTURES}/disjoint_sets.cpp")
set(STRUCTURES_HEAPS_SOURCES
    "${STRUCTURES_HEAPS}/double_heap.cpp"
    "${STRUCTURES_HEAPS}/pairing_heap.cpp")
set(TEXT_SOURCES
    "${TEXT}/base_words_map.cpp"
    "${TEXT}/edit_distance.cpp"
    "${TEXT}/knuth_morris_pratt.cpp"
    "${TEXT}/suffix_array.cpp"
    "${TEXT}/trie.cpp")

set(SOURCES
    "${GEOMETRY_SOURCES}"
    "${GEOMETRY_DIM2_SOURCES}"
    "${GEOMETRY_DIM3_SOURCES}"
    "${GRAPHS_SOURCES}"
    "${GRAPHS_ALGORITHMS_SOURCES}"
    "${MATHS_SOURCES}"
    "${SEQUENCES_SOURCES}"
    "${STRUCTURES_SOURCES}"
    "${STRUCTURES_HEAPS_SOURCES}"
    "${TEXT_SOURCES}")

# OUTPUT
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${LIB_OUTPUT_DIR})
add_library(${LIB_NAME} SHARED ${SOURCES})
