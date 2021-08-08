cmake_minimum_required(VERSION 3.10)

# PACKAGES
find_package(GTest REQUIRED)
include_directories(${GTEST_INCLUDE_DIRS})

set(CMAKE_THREAD_PREFER_PTHREAD true)
set(THREADS_PREFER_PTHREAD_FLAG true)
find_package(Threads REQUIRED)

# SOURCES
set(GEOMETRY_TEST "geometry")
set(GEOMETRY_PLANE_TEST "${GEOMETRY_TEST}/dim2")
set(GEOMETRY_SPACE_TEST "${GEOMETRY_TEST}/dim3")
set(GRAPHS_TEST "graphs")
set(GRAPHS_ALGORITHMS_TEST "${GRAPHS_TEST}/algorithms")
set(MATHMAT_TEST "mathmat")
set(SEQUENCES_TEST "sequences")
set(STRUCTURES_TEST "structures")
set(TEXT_TEST "text")

set(GEOMETRY_PLANE_TEST_SOURCES
    "${GEOMETRY_PLANE_TEST}/closest_points_test.cpp"
    "${GEOMETRY_PLANE_TEST}/convex_hull_test.cpp"
    "${GEOMETRY_PLANE_TEST}/geometry_2d_test.cpp"
    "${GEOMETRY_PLANE_TEST}/vector_2d_test.cpp")
set(GEOMETRY_SPACE_TEST_SOURCES
    "${GEOMETRY_SPACE_TEST}/geometry_3d_test.cpp"
    "${GEOMETRY_SPACE_TEST}/vector_3d_test.cpp")
set(GRAPHS_TEST_SOURCES
    "${GRAPHS_TEST}/directed_graph_test.cpp"
    "${GRAPHS_TEST}/multipartite_graph_test.cpp"
    "${GRAPHS_TEST}/tree_graph_test.cpp"
    "${GRAPHS_TEST}/undirected_graph_test.cpp")
set(GRAPHS_ALGORITHMS_TEST_SOURCES
    "${GRAPHS_ALGORITHMS_TEST}/cutting_test.cpp"
    "${GRAPHS_ALGORITHMS_TEST}/lowest_common_ancestor_test.cpp"
    "${GRAPHS_ALGORITHMS_TEST}/matching_test.cpp"
    "${GRAPHS_ALGORITHMS_TEST}/minimal_spanning_tree_test.cpp"
    "${GRAPHS_ALGORITHMS_TEST}/paths_test.cpp"
    "${GRAPHS_ALGORITHMS_TEST}/searching_test.cpp"
    "${GRAPHS_ALGORITHMS_TEST}/strongly_connected_components_test.cpp"
    "${GRAPHS_ALGORITHMS_TEST}/topological_sorting_test.cpp")
set(MATHMAT_TEST_SOURCES
    "${MATHMAT_TEST}/equation_test.cpp"
    "${MATHMAT_TEST}/equation_system_test.cpp"
    "${MATHMAT_TEST}/fraction_test.cpp"
    "${MATHMAT_TEST}/maths_test.cpp"
    "${MATHMAT_TEST}/primes_test.cpp")
set(SEQUENCES_TEST_SOURCES
    "${SEQUENCES_TEST}/sorting_test.cpp"
    "${SEQUENCES_TEST}/subsequences_test.cpp")
set(STRUCTURES_TEST_SOURCES
    "${STRUCTURES_TEST}/avl_tree_test.cpp"
    "${STRUCTURES_TEST}/disjoint_sets_test.cpp"
    "${STRUCTURES_TEST}/double_heap_test.cpp")
set(TEXT_TEST_SOURCES
    "${TEXT_TEST}/base_words_map_test.cpp"
    "${TEXT_TEST}/kmp_test.cpp"
    "${TEXT_TEST}/suffix_array_test.cpp"
    "${TEXT_TEST}/trie_test.cpp")

set(TEST_SOURCES
    "${GEOMETRY_PLANE_TEST_SOURCES}"
    "${GEOMETRY_SPACE_TEST_SOURCES}"
    "${GRAPHS_TEST_SOURCES}"
    "${GRAPHS_ALGORITHMS_TEST_SOURCES}"
    "${MATHMAT_TEST_SOURCES}"
    "${SEQUENCES_TEST_SOURCES}"
    "${STRUCTURES_TEST_SOURCES}"
    "${TEXT_TEST_SOURCES}")

# OUTPUT
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${EXE_OUTPUT_DIR}/test")
foreach(testsource ${TEST_SOURCES})
    get_filename_component(testexec ${testsource} NAME_WE)
    add_executable(${testexec} ${testsource})
    target_link_libraries(${testexec}
                          GTest::GTest
                          GTest::Main
                          ${LIB_NAME})
    gtest_add_tests(TARGET ${testexec})
endforeach(testsource ${TEST_SOURCES})
