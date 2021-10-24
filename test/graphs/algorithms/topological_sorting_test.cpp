/*!
 * \file topological_sorting_test.cpp
 * \brief Tests: Algorithms for topological sorting of a directed graph
 */
#include <gtest/gtest.h>
#include "algolib/graphs/algorithms/topological_sorting.hpp"

namespace algr = algolib::graphs;

using graph_t = algr::directed_simple_graph<>;
using graph_v = graph_t::vertex_type;

TEST(TopologicalSortingTest, sortTopologicalByInputs_WhenAcyclicGraph_ThenTopologicalOrder)
{
    // given
    graph_t graph({0, 1, 2, 3, 4, 5});
    graph.add_edge_between(graph[0], graph[2]);
    graph.add_edge_between(graph[0], graph[4]);
    graph.add_edge_between(graph[1], graph[0]);
    graph.add_edge_between(graph[1], graph[4]);
    graph.add_edge_between(graph[3], graph[0]);
    graph.add_edge_between(graph[3], graph[1]);
    graph.add_edge_between(graph[3], graph[2]);
    graph.add_edge_between(graph[5], graph[1]);
    graph.add_edge_between(graph[5], graph[2]);
    graph.add_edge_between(graph[5], graph[4]);
    // when
    std::vector<graph_v> result = algr::sort_topological_by_inputs(graph);
    // then
    EXPECT_EQ(std::vector<graph_v>({graph[3], graph[5], graph[1], graph[0], graph[2], graph[4]}),
              result);
}

TEST(TopologicalSortingTest, sortTopologicalByInputs_WhenCyclicGraph_ThenDirectedCyclicGraphError)
{
    // given
    graph_t graph({0, 1, 2, 3, 4, 5});
    graph.add_edge_between(graph[0], graph[2]);
    graph.add_edge_between(graph[0], graph[4]);
    graph.add_edge_between(graph[1], graph[0]);
    graph.add_edge_between(graph[1], graph[4]);
    graph.add_edge_between(graph[2], graph[1]);
    graph.add_edge_between(graph[3], graph[0]);
    graph.add_edge_between(graph[3], graph[1]);
    graph.add_edge_between(graph[3], graph[2]);
    graph.add_edge_between(graph[5], graph[1]);
    graph.add_edge_between(graph[5], graph[2]);
    graph.add_edge_between(graph[5], graph[4]);
    // when
    auto exec = [&]() { return algr::sort_topological_by_inputs(graph); };
    // then
    EXPECT_THROW(exec(), algr::directed_cyclic_graph_error);
}

TEST(TopologicalSortingTest, sortTopologicalByInputs_WhenEmptyGraph_ThenVertices)
{
    // given
    graph_t graph({0, 1, 2, 3, 4, 5});
    // when
    std::vector<graph_v> result = algr::sort_topological_by_inputs(graph);
    // then
    EXPECT_EQ(graph.vertices(), result);
}

TEST(TopologicalSortingTest, sortTopologicalByDFS_WhenAcyclicGraph_ThenTopologicalOrder)
{
    // given
    graph_t graph({0, 1, 2, 3, 4, 5});
    graph.add_edge_between(graph[0], graph[2]);
    graph.add_edge_between(graph[0], graph[4]);
    graph.add_edge_between(graph[1], graph[0]);
    graph.add_edge_between(graph[1], graph[4]);
    graph.add_edge_between(graph[3], graph[1]);
    graph.add_edge_between(graph[3], graph[0]);
    graph.add_edge_between(graph[3], graph[2]);
    graph.add_edge_between(graph[5], graph[1]);
    graph.add_edge_between(graph[5], graph[2]);
    graph.add_edge_between(graph[5], graph[4]);

    std::vector<std::vector<graph_v>> expecteds = {
            std::vector<graph_v>({graph[3], graph[5], graph[1], graph[0], graph[2], graph[4]}),
            std::vector<graph_v>({graph[5], graph[3], graph[1], graph[0], graph[2], graph[4]}),
            std::vector<graph_v>({graph[3], graph[5], graph[1], graph[0], graph[4], graph[2]}),
            std::vector<graph_v>({graph[5], graph[3], graph[1], graph[0], graph[4], graph[2]})};
    // when
    std::vector<graph_v> result = algr::sort_topological_by_dfs(graph);
    // then
    EXPECT_TRUE(
            std::any_of(expecteds.begin(), expecteds.end(),
                        [&](const std::vector<graph_v> & expected) { return expected == result; }));
}

TEST(TopologicalSortingTest, sortTopologicalByDFS_WhenCyclicGraph_ThenDirectedCyclicGraphError)
{
    // given
    graph_t graph({0, 1, 2, 3, 4, 5});
    graph.add_edge_between(graph[0], graph[2]);
    graph.add_edge_between(graph[0], graph[4]);
    graph.add_edge_between(graph[1], graph[0]);
    graph.add_edge_between(graph[1], graph[4]);
    graph.add_edge_between(graph[2], graph[1]);
    graph.add_edge_between(graph[3], graph[1]);
    graph.add_edge_between(graph[3], graph[0]);
    graph.add_edge_between(graph[3], graph[2]);
    graph.add_edge_between(graph[5], graph[1]);
    graph.add_edge_between(graph[5], graph[2]);
    graph.add_edge_between(graph[5], graph[4]);
    // when
    auto exec = [&]() { return algr::sort_topological_by_dfs(graph); };
    // then
    EXPECT_THROW(exec(), algr::directed_cyclic_graph_error);
}

TEST(TopologicalSortingTest, sortTopologicalByDFS_WhenEmptyGraph_ThenVertices)
{
    // given
    algr::directed_simple_graph<> graph({0, 1, 2, 3, 4, 5});
    // when
    std::vector<graph_v> result = algr::sort_topological_by_dfs(graph);
    // then
    EXPECT_EQ(graph.vertices(), result);
}
