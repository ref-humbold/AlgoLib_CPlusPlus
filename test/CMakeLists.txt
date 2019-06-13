cmake_minimum_required(VERSION 3.10)

# PACKAGES
set(CMAKE_THREAD_PREFER_PTHREAD true)
set(THREADS_PREFER_PTHREAD_FLAG true)
find_package(Threads REQUIRED)

find_package(GTest REQUIRED)
include_directories(${GTEST_INCLUDE_DIRS})

# SOURCES
set(TEST "${PROJECT_SOURCE_DIR}/test")
set(SOURCES
    "${TEST}/avl_tree_test.cpp"
    "${TEST}/directed_graph_test.cpp"
    "${TEST}/disjoint_sets_test.cpp"
    "${TEST}/fraction_test.cpp"
    "${TEST}/kmp_test.cpp"
    "${TEST}/lca_test.cpp"
    "${TEST}/maths_test.cpp"
    "${TEST}/mst_test.cpp"
    "${TEST}/paths_test.cpp"
    "${TEST}/points_sorting_test.cpp"
    "${TEST}/primes_test.cpp"
    "${TEST}/scc_test.cpp"
    "${TEST}/subseqs_test.cpp"
    "${TEST}/suffix_array_test.cpp"
    "${TEST}/topological_sorting_test.cpp"
    "${TEST}/undirected_graph_test.cpp")

# OUTPUT
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${PROJECT_SOURCE_DIR}/bin/test")
foreach(testsource ${SOURCES})
    get_filename_component(testexec ${testsource} NAME_WE)
    add_executable(${testexec} ${testsource})
    target_link_libraries(${testexec}
                          GTest::GTest
                          GTest::Main
                          "${PROJECT_SOURCE_DIR}/bin/libalgolib.so")
    gtest_discover_tests(${testexec})
endforeach(testsource ${SOURCES})
