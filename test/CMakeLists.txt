cmake_minimum_required(VERSION 3.10)

# PACKAGES
find_package(GTest REQUIRED)
include_directories(${GTEST_INCLUDE_DIRS})

set(CMAKE_THREAD_PREFER_PTHREAD true)
set(THREADS_PREFER_PTHREAD_FLAG true)
find_package(Threads REQUIRED)

# SOURCES
set(GEOMETRY_DIM2_TEST_SOURCES
    "${GEOMETRY_DIM2}/closest_points_test.cpp"
    "${GEOMETRY_DIM2}/convex_hull_test.cpp"
    "${GEOMETRY_DIM2}/geometry_2d_test.cpp"
    "${GEOMETRY_DIM2}/vector_2d_test.cpp")
set(GEOMETRY_DIM3_TEST_SOURCES
    "${GEOMETRY_DIM3}/geometry_3d_test.cpp"
    "${GEOMETRY_DIM3}/vector_3d_test.cpp")
set(GRAPHS_TEST_SOURCES
    "${GRAPHS}/directed_graph_test.cpp"
    "${GRAPHS}/multipartite_graph_test.cpp"
    "${GRAPHS}/tree_graph_test.cpp"
    "${GRAPHS}/undirected_graph_test.cpp")
set(GRAPHS_ALGORITHMS_TEST_SOURCES
    "${GRAPHS_ALGORITHMS}/cutting_test.cpp"
    "${GRAPHS_ALGORITHMS}/lowest_common_ancestor_test.cpp"
    "${GRAPHS_ALGORITHMS}/matching_test.cpp"
    "${GRAPHS_ALGORITHMS}/minimal_spanning_tree_test.cpp"
    "${GRAPHS_ALGORITHMS}/searching_test.cpp"
    "${GRAPHS_ALGORITHMS}/shortest_paths_test.cpp"
    "${GRAPHS_ALGORITHMS}/strongly_connected_components_test.cpp"
    "${GRAPHS_ALGORITHMS}/topological_sorting_test.cpp"
    "${GRAPHS_ALGORITHMS}/tree_diameter_test.cpp")
set(MATHS_TEST_SOURCES
    "${MATHS}/equation_test.cpp"
    "${MATHS}/equation_system_test.cpp"
    "${MATHS}/fraction_test.cpp"
    "${MATHS}/integers_test.cpp"
    "${MATHS}/primes_searching_test.cpp"
    "${MATHS}/primes_testing_test.cpp")
set(SEQUENCES_TEST_SOURCES
    "${SEQUENCES}/longest_common_subsequence_test.cpp"
    "${SEQUENCES}/longest_increasing_subsequence_test.cpp"
    "${SEQUENCES}/maximum_subarray_test.cpp"
    "${SEQUENCES}/sorting_test.cpp")
set(STRUCTURES_TEST_SOURCES
    "${STRUCTURES}/avl_tree_test.cpp"
    "${STRUCTURES}/disjoint_sets_test.cpp")
set(STRUCTURES_HEAPS_TEST_SOURCES
    "${STRUCTURES_HEAPS}/double_heap_test.cpp"
    "${STRUCTURES_HEAPS}/leftist_heap_test.cpp"
    "${STRUCTURES_HEAPS}/pairing_heap_test.cpp")
set(TEXT_TEST_SOURCES
    "${TEXT}/base_words_map_test.cpp"
    "${TEXT}/edit_distance_test.cpp"
    "${TEXT}/knuth_morris_pratt_test.cpp"
    "${TEXT}/suffix_array_test.cpp"
    "${TEXT}/trie_test.cpp")

set(TEST_SOURCES
    "${GEOMETRY_DIM2_TEST_SOURCES}"
    "${GEOMETRY_DIM3_TEST_SOURCES}"
    "${GRAPHS_TEST_SOURCES}"
    "${GRAPHS_ALGORITHMS_TEST_SOURCES}"
    "${MATHS_TEST_SOURCES}"
    "${SEQUENCES_TEST_SOURCES}"
    "${STRUCTURES_TEST_SOURCES}"
    "${STRUCTURES_HEAPS_TEST_SOURCES}"
    "${TEXT_TEST_SOURCES}")

# OUTPUT
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${TEST_EXE_OUTPUT_DIR}")
foreach(testsource ${TEST_SOURCES})
    get_filename_component(testexec ${testsource} NAME_WE)
    add_executable(${testexec} ${testsource})
    target_link_libraries(${testexec}
                          GTest::GTest
                          GTest::Main
                          ${LIB_NAME})
    gtest_discover_tests(${testexec})
endforeach(testsource ${TEST_SOURCES})
