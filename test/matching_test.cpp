/**!
 * \file matching.hpp
 * \brief Tests: Hopcroft-Karp algorithm for matching in bipartite graph
 */
#include <gtest/gtest.h>
#include "algolib/graphs/algorithms/matching.hpp"

namespace algr = algolib::graphs;

using graph_t = algr::multipartite_graph<2>;
using graph_v = graph_t::vertex_type;

TEST(MatchingTest, match_whenMatchingExists_thenMaximalMatching)
{
    // given
    graph_t graph({{0, 2, 4, 6}, {1, 3, 5, 7}});
    graph.add_edge_between(0, 3);
    graph.add_edge_between(0, 5);
    graph.add_edge_between(1, 2);
    graph.add_edge_between(3, 4);
    graph.add_edge_between(3, 6);
    graph.add_edge_between(6, 7);

    std::unordered_map<graph_v, graph_v> expected = {{0, 5}, {1, 2}, {2, 1}, {3, 4},
                                                     {4, 3}, {5, 0}, {6, 7}, {7, 6}};
    // when
    std::unordered_map<graph_v, graph_v> result = algr::match(graph);
    // then
    EXPECT_EQ(expected, result);
}

TEST(MatchingTest, match_whenVerticesOnlyInGroup0_thenEmpty)
{
    // given
    graph_t graph({{0, 1, 2, 3, 4}});
    // when
    std::unordered_map<graph_v, graph_v> result = algr::match(graph);
    // then
    EXPECT_TRUE(result.empty());
}

TEST(MatchingTest, match_whenVerticesOnlyInGroup1__thenEmpty)
{
    // given
    graph_t graph({{}, {0, 1, 2, 3, 4}});
    // when
    std::unordered_map<graph_v, graph_v> result = algr::match(graph);
    // then
    EXPECT_TRUE(result.empty());
}
