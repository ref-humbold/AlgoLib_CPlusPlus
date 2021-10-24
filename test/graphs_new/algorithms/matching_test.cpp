/**!
 * \file matching_test.hpp
 * \brief Tests: Hopcroft-Karp algorithm for matching in bipartite graph
 */
#include <gtest/gtest.h>
#include "algolib/graphs_new/algorithms/matching.hpp"

namespace algr = algolib::graphs;

using graph_t = algr::multipartite_graph<2>;
using graph_vi = graph_t::vertex_id_type;
using graph_v = graph_t::vertex_type;

TEST(MatchingTest, match_WhenMatchingExists_ThenMaximalMatching)
{
    // given
    graph_t graph({std::vector<graph_vi>({0, 2, 4, 6}), std::vector<graph_vi>({1, 3, 5, 7})});
    graph.add_edge_between(graph[0], graph[3]);
    graph.add_edge_between(graph[0], graph[5]);
    graph.add_edge_between(graph[1], graph[2]);
    graph.add_edge_between(graph[3], graph[4]);
    graph.add_edge_between(graph[3], graph[6]);
    graph.add_edge_between(graph[6], graph[7]);

    std::unordered_map<graph_v, graph_v> expected = {
            {graph[0], graph[5]}, {graph[1], graph[2]}, {graph[2], graph[1]}, {graph[3], graph[4]},
            {graph[4], graph[3]}, {graph[5], graph[0]}, {graph[6], graph[7]}, {graph[7], graph[6]}};
    // when
    std::unordered_map<graph_v, graph_v> result = algr::match(graph);
    // then
    EXPECT_EQ(expected, result);
}

TEST(MatchingTest, match_WhenVerticesOnlyInGroup0_ThenEmpty)
{
    // given
    graph_t graph({std::vector<graph_vi>({0, 1, 2, 3, 4}), {}});
    // when
    std::unordered_map<graph_v, graph_v> result = algr::match(graph);
    // then
    EXPECT_TRUE(result.empty());
}

TEST(MatchingTest, match_WhenVerticesOnlyInGroup1__ThenEmpty)
{
    // given
    graph_t graph({std::vector<graph_vi>(), std::vector<graph_vi>({0, 1, 2, 3, 4})});
    // when
    std::unordered_map<graph_v, graph_v> result = algr::match(graph);
    // then
    EXPECT_TRUE(result.empty());
}
