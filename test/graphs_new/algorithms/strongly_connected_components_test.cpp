/**!
 * \file strongly_connected_components_test.cpp
 * \brief Tests: Algorithm for strongly connected components
 */
#include <algorithm>
#include <gtest/gtest.h>
#include "algolib/graphs_new/algorithms/strongly_connected_components.hpp"

namespace algr = algolib::graphs;

using graph_t = algr::directed_simple_graph<>;
using graph_v = graph_t::vertex_type;

TEST(StronglyConnectedComponentsTest, findSCC_WhenManyComponents_ThenAllListed)
{
    // given
    graph_t graph({0, 1, 2, 3, 4, 5, 6, 7, 8, 9});
    graph.add_edge_between(graph[0], graph[4]);
    graph.add_edge_between(graph[0], graph[5]);
    graph.add_edge_between(graph[1], graph[0]);
    graph.add_edge_between(graph[2], graph[3]);
    graph.add_edge_between(graph[3], graph[1]);
    graph.add_edge_between(graph[4], graph[1]);
    graph.add_edge_between(graph[4], graph[3]);
    graph.add_edge_between(graph[6], graph[5]);
    graph.add_edge_between(graph[6], graph[9]);
    graph.add_edge_between(graph[7], graph[4]);
    graph.add_edge_between(graph[7], graph[6]);
    graph.add_edge_between(graph[8], graph[3]);
    graph.add_edge_between(graph[8], graph[7]);
    graph.add_edge_between(graph[9], graph[8]);

    std::vector<std::unordered_set<graph_v>> expected = {{graph[0], graph[1], graph[3], graph[4]},
                                                         {graph[2]},
                                                         {graph[5]},
                                                         {graph[6], graph[7], graph[8], graph[9]}};
    // when
    std::vector<std::unordered_set<graph_v>> result = algr::find_scc(graph);
    // then
    ASSERT_EQ(4, result.size());

    for(auto && scc : expected)
        EXPECT_TRUE(std::find(result.begin(), result.end(), scc) != result.end());
}

TEST(StronglyConnectedComponentsTest, findSCC_WhenSingeleComponent_ThenAllVertices)
{
    // given
    graph_t graph({0, 1, 2, 3, 4, 5, 6});

    graph.add_edge_between(graph[0], graph[1]);
    graph.add_edge_between(graph[1], graph[2]);
    graph.add_edge_between(graph[2], graph[3]);
    graph.add_edge_between(graph[3], graph[4]);
    graph.add_edge_between(graph[4], graph[5]);
    graph.add_edge_between(graph[5], graph[6]);
    graph.add_edge_between(graph[6], graph[0]);

    std::vector<std::unordered_set<graph_v>> expected = {
            {graph[0], graph[1], graph[2], graph[3], graph[4], graph[5], graph[6]}};
    // when
    std::vector<std::unordered_set<graph_v>> result = algr::find_scc(graph);
    // then
    ASSERT_EQ(1, result.size());
    EXPECT_EQ(expected, result);
}

TEST(StronglyConnectedComponentsTest, findSCC_WhenEmptyGraph_ThenEachVertexIsComponent)
{
    // given
    graph_t graph({0, 1, 2, 3});
    std::vector<std::unordered_set<graph_v>> expected = {
            {graph[0]}, {graph[1]}, {graph[2]}, {graph[3]}};
    // when
    std::vector<std::unordered_set<graph_v>> result = algr::find_scc(graph);
    // then
    ASSERT_EQ(4, result.size());

    for(auto && scc : expected)
        EXPECT_TRUE(std::find(result.begin(), result.end(), scc) != result.end());
}
