/*!
 * \file cutting_test.cpp
 * \brief Tests: Algorithms for graph cutting (edge cut and vertex cut).
 */
#include <algorithm>
#include <vector>
#include <gtest/gtest.h>
#include "algolib/graphs/algorithms/cutting.hpp"

namespace algr = algolib::graphs;

using graph_v = algr::undirected_simple_graph<>::vertex_type;
using graph_e = algr::undirected_simple_graph<>::edge_type;

TEST(CuttingTest, findEdgeCut_WhenPresentBridges_ThenBridges)
{
    // given
    algr::undirected_simple_graph<> graph({0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11});
    graph.add_edge_between(graph[0], graph[1]);
    graph.add_edge_between(graph[0], graph[2]);
    graph.add_edge_between(graph[0], graph[7]);
    graph.add_edge_between(graph[1], graph[2]);
    graph.add_edge_between(graph[1], graph[3]);
    graph.add_edge_between(graph[1], graph[4]);
    graph.add_edge_between(graph[3], graph[5]);
    graph.add_edge_between(graph[4], graph[5]);
    graph.add_edge_between(graph[5], graph[6]);
    graph.add_edge_between(graph[7], graph[8]);
    graph.add_edge_between(graph[7], graph[9]);
    graph.add_edge_between(graph[7], graph[11]);
    graph.add_edge_between(graph[8], graph[9]);
    graph.add_edge_between(graph[9], graph[10]);
    graph.add_edge_between(graph[9], graph[11]);
    graph.add_edge_between(graph[10], graph[11]);

    // when
    std::vector<graph_e> result = find_edge_cut(graph);

    // then
    std::sort(result.begin(), result.end());

    EXPECT_EQ(
            std::vector<graph_e>({graph[std::make_pair(0, 7)], graph[std::make_pair(5, 6)]}),
            result);
}

TEST(CuttingTest, findEdgeCut_WhenNoBridges_ThenEmptyVector)
{
    // given
    algr::undirected_simple_graph<> graph({0, 1, 2, 3, 4, 5});
    graph.add_edge_between(graph[0], graph[1]);
    graph.add_edge_between(graph[0], graph[2]);
    graph.add_edge_between(graph[1], graph[2]);
    graph.add_edge_between(graph[1], graph[3]);
    graph.add_edge_between(graph[1], graph[4]);
    graph.add_edge_between(graph[3], graph[5]);
    graph.add_edge_between(graph[4], graph[5]);

    // when
    std::vector<graph_e> result = find_edge_cut(graph);

    // then
    EXPECT_EQ(std::vector<graph_e>(), result);
}

TEST(CuttingTest, findVertexSeparators_WhenPresentSeparators_ThenSeparators)
{
    // given
    algr::undirected_simple_graph<> graph({0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11});
    graph.add_edge_between(graph[0], graph[1]);
    graph.add_edge_between(graph[0], graph[2]);
    graph.add_edge_between(graph[0], graph[7]);
    graph.add_edge_between(graph[1], graph[2]);
    graph.add_edge_between(graph[1], graph[3]);
    graph.add_edge_between(graph[1], graph[4]);
    graph.add_edge_between(graph[3], graph[5]);
    graph.add_edge_between(graph[4], graph[5]);
    graph.add_edge_between(graph[5], graph[6]);
    graph.add_edge_between(graph[7], graph[8]);
    graph.add_edge_between(graph[7], graph[9]);
    graph.add_edge_between(graph[7], graph[11]);
    graph.add_edge_between(graph[8], graph[9]);
    graph.add_edge_between(graph[9], graph[10]);
    graph.add_edge_between(graph[9], graph[11]);
    graph.add_edge_between(graph[10], graph[11]);

    // when
    std::vector<graph_v> result = find_vertex_cut(graph);

    // then
    std::sort(result.begin(), result.end());

    EXPECT_EQ(std::vector<graph_v>({graph[0], graph[1], graph[5], graph[7]}), result);
}

TEST(CuttingTest, findVertexSeparators_WhenNoSeparators_ThenEmptyVector)
{
    // given
    algr::undirected_simple_graph<> graph({0, 1, 2, 3, 4, 5});
    graph.add_edge_between(graph[0], graph[1]);
    graph.add_edge_between(graph[0], graph[2]);
    graph.add_edge_between(graph[1], graph[2]);
    graph.add_edge_between(graph[1], graph[3]);
    graph.add_edge_between(graph[1], graph[4]);
    graph.add_edge_between(graph[2], graph[3]);
    graph.add_edge_between(graph[3], graph[5]);
    graph.add_edge_between(graph[4], graph[5]);

    // when
    std::vector<graph_v> result = find_vertex_cut(graph);

    // then
    EXPECT_EQ(std::vector<graph_v>(), result);
}
