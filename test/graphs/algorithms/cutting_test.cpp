/*!
 * \file minimal_spanning_tree_test.cpp
 * \brief Tests: Algorithms for graph cutting (edge cut and vertex cut)
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
    graph.add_edge_between(0, 1);
    graph.add_edge_between(0, 2);
    graph.add_edge_between(0, 7);
    graph.add_edge_between(1, 2);
    graph.add_edge_between(1, 3);
    graph.add_edge_between(1, 4);
    graph.add_edge_between(3, 5);
    graph.add_edge_between(4, 5);
    graph.add_edge_between(5, 6);
    graph.add_edge_between(7, 8);
    graph.add_edge_between(7, 9);
    graph.add_edge_between(7, 11);
    graph.add_edge_between(8, 9);
    graph.add_edge_between(9, 10);
    graph.add_edge_between(9, 11);
    graph.add_edge_between(10, 11);
    // when
    std::vector<graph_e> result = find_edge_cut(graph);
    // then
    std::sort(result.begin(), result.end());

    EXPECT_EQ(std::vector<graph_e>({graph.get_edge(0, 7), graph.get_edge(5, 6)}), result);
}

TEST(CuttingTest, findEdgeCut_WhenNoBridges_ThenEmptyVector)
{
    // given
    algr::undirected_simple_graph<> graph({0, 1, 2, 3, 4, 5});
    graph.add_edge_between(0, 1);
    graph.add_edge_between(0, 2);
    graph.add_edge_between(1, 2);
    graph.add_edge_between(1, 3);
    graph.add_edge_between(1, 4);
    graph.add_edge_between(3, 5);
    graph.add_edge_between(4, 5);
    // when
    std::vector<graph_e> result = find_edge_cut(graph);
    // then
    EXPECT_EQ(std::vector<graph_e>(), result);
}

TEST(CuttingTest, findVertexSeparators_WhenPresentSeparators_ThenSeparators)
{
    // given
    algr::undirected_simple_graph<> graph({0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11});
    graph.add_edge_between(0, 1);
    graph.add_edge_between(0, 2);
    graph.add_edge_between(0, 7);
    graph.add_edge_between(1, 2);
    graph.add_edge_between(1, 3);
    graph.add_edge_between(1, 4);
    graph.add_edge_between(3, 5);
    graph.add_edge_between(4, 5);
    graph.add_edge_between(5, 6);
    graph.add_edge_between(7, 8);
    graph.add_edge_between(7, 9);
    graph.add_edge_between(7, 11);
    graph.add_edge_between(8, 9);
    graph.add_edge_between(9, 10);
    graph.add_edge_between(9, 11);
    graph.add_edge_between(10, 11);
    // when
    std::vector<graph_v> result = find_vertex_cut(graph);
    // then
    std::sort(result.begin(), result.end());

    EXPECT_EQ(std::vector<graph_v>({0, 1, 5, 7}), result);
}

TEST(CuttingTest, findVertexSeparators_WhenNoSeparators_ThenEmptyVector)
{
    // given
    algr::undirected_simple_graph<> graph({0, 1, 2, 3, 4, 5});
    graph.add_edge_between(0, 1);
    graph.add_edge_between(0, 2);
    graph.add_edge_between(1, 2);
    graph.add_edge_between(1, 3);
    graph.add_edge_between(1, 4);
    graph.add_edge_between(2, 3);
    graph.add_edge_between(3, 5);
    graph.add_edge_between(4, 5);
    // when
    std::vector<graph_v> result = find_vertex_cut(graph);
    // then
    EXPECT_EQ(std::vector<graph_v>(), result);
}
