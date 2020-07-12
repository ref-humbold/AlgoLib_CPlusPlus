/**!
 * \file strongly_connected_components_test.cpp
 * \brief Tests: Algorithm for strongly connected components
 */
#include <algorithm>
#include <gtest/gtest.h>
#include "algolib/graphs/algorithms/strongly_connected_components.hpp"

namespace algr = algolib::graphs;

using graph_t = algr::directed_simple_graph<>;
using graph_v = graph_t::vertex_type;

TEST(StronglyConnectedComponentsTest, findSCC_whenManyComponents_thenAllListed)
{
    // given
    graph_t graph({0, 1, 2, 3, 4, 5, 6, 7, 8, 9});
    graph.add_edge_between(0, 4);
    graph.add_edge_between(0, 5);
    graph.add_edge_between(1, 0);
    graph.add_edge_between(2, 3);
    graph.add_edge_between(3, 1);
    graph.add_edge_between(4, 1);
    graph.add_edge_between(4, 3);
    graph.add_edge_between(6, 5);
    graph.add_edge_between(6, 9);
    graph.add_edge_between(7, 4);
    graph.add_edge_between(7, 6);
    graph.add_edge_between(8, 3);
    graph.add_edge_between(8, 7);
    graph.add_edge_between(9, 8);

    std::vector<std::unordered_set<graph_v>> expected = {{0, 1, 3, 4}, {2}, {5}, {6, 7, 8, 9}};
    // when
    std::vector<std::unordered_set<graph_v>> result = find_scc(graph);
    // then
    ASSERT_EQ(4, result.size());

    for(auto && scc : expected)
        EXPECT_NE(result.end(), std::find(std::begin(result), std::end(result), scc));
}

TEST(StronglyConnectedComponentsTest, findSCC_whenSingeleComponent_thenAllVertices)
{
    // given
    graph_t graph({0, 1, 2, 3, 4, 5, 6});

    graph.add_edge_between(0, 1);
    graph.add_edge_between(1, 2);
    graph.add_edge_between(2, 3);
    graph.add_edge_between(3, 4);
    graph.add_edge_between(4, 5);
    graph.add_edge_between(5, 6);
    graph.add_edge_between(6, 0);

    std::vector<std::unordered_set<graph_v>> expected = {{0, 1, 2, 3, 4, 5, 6}};
    // when
    std::vector<std::unordered_set<graph_v>> result = find_scc(graph);
    // then
    ASSERT_EQ(1, result.size());
    EXPECT_EQ(expected, result);
}

TEST(StronglyConnectedComponentsTest, findSCC_whenEmptyGraph_thenEachVertexIsComponent)
{
    // given
    graph_t graph({0, 1, 2, 3});
    std::vector<std::unordered_set<graph_v>> expected = {{0}, {1}, {2}, {3}};
    // when
    std::vector<std::unordered_set<graph_v>> result = find_scc(graph);
    // then
    ASSERT_EQ(4, result.size());

    for(auto && scc : expected)
        EXPECT_NE(result.end(), std::find(std::begin(result), std::end(result), scc));
}
