cmake_minimum_required(VERSION 3.10)

# PACKAGES
set(CMAKE_THREAD_PREFER_PTHREAD true)
set(THREADS_PREFER_PTHREAD_FLAG true)
find_package(Threads REQUIRED)

find_package(GTest REQUIRED)
include_directories(${GTEST_INCLUDE_DIRS})
enable_testing()

# SOURCES
include_directories("${PROJECT_SOURCE_DIR}/include")
set(SOURCES
    "avl_tree_test.cpp"
    "directed_graph_test.cpp"
    "disjoint_sets_test.cpp"
    "fraction_test.cpp"
    "kmp_test.cpp"
    "lca_test.cpp"
    "maths_test.cpp"
    "maximum_subarray_test.cpp"
    "mst_test.cpp"
    "paths_test.cpp"
    "primes_test.cpp"
    "scc_test.cpp"
    "sorting_test.cpp"
    "topological_sorting_test.cpp"
    "undirected_graph_test.cpp")

# OUTPUT
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "bin")
foreach(testsource ${SOURCES})
    get_filename_component(testexec ${testsource} NAME_WE)
    add_executable(${testexec} ${testsource})
    target_link_libraries(${testexec}
                          ${GTEST_LIBRARY}
                          ${GTEST_MAIN_LIBRARY}
                          Threads::Thread)
    add_test(NAME ${testexec} COMMAND ${testexec})
endforeach(testsource ${SOURCES})

