/*!
 * \file minimal_spanning_tree_test.cpp
 * \brief Tests: Algorithms for minimal spanning tree.
 */
#include <algorithm>
#include <vector>
#include <gtest/gtest.h>
#include "algolib/graphs/algorithms/minimal_spanning_tree.hpp"

namespace algr = algolib::graphs;

class weighted_impl : public algr::weighted
{
public:
    explicit weighted_impl(weight_type weight = 0) : weighted(), weight_{weight}
    {
    }

    const weight_type & weight() const override
    {
        return weight_;
    }

private:
    weight_type weight_;
};

class MinimalSpanningTreeTest : public ::testing::Test
{
public:
    using graph_t = algr::undirected_simple_graph<size_t, std::nullptr_t, weighted_impl>;
    using graph_v = graph_t::vertex_type;
    using graph_e = graph_t::edge_type;

    MinimalSpanningTreeTest() : graph{graph_t({0, 1, 2, 3, 4})}
    {
        graph.add_edge_between(graph[0], graph[1], weighted_impl(-1));
        graph.add_edge_between(graph[0], graph[2], weighted_impl(4));
        graph.add_edge_between(graph[1], graph[2], weighted_impl(9));
        graph.add_edge_between(graph[1], graph[3], weighted_impl(7));
        graph.add_edge_between(graph[1], graph[4], weighted_impl(12));
        graph.add_edge_between(graph[2], graph[4], weighted_impl(6));
        graph.add_edge_between(graph[3], graph[4], weighted_impl(3));
    }

    ~MinimalSpanningTreeTest() override = default;

protected:
    graph_t graph;
};

TEST_F(MinimalSpanningTreeTest, kruskal_ThenMinimalSpanningTree)
{
    // given
    std::vector<graph_v> vertices = graph.vertices();
    // when
    graph_t result = algr::kruskal(graph);
    // then
    std::vector<graph_v> result_vertices = result.vertices();
    std::vector<graph_e> result_edges = result.edges();

    std::sort(vertices.begin(), vertices.end());
    std::sort(result_vertices.begin(), result_vertices.end());
    std::sort(result_edges.begin(), result_edges.end());

    EXPECT_EQ(vertices, result_vertices);
    EXPECT_EQ(
            std::vector<graph_e>(
                    {graph[std::make_pair(0, 1)], graph[std::make_pair(0, 2)],
                     graph[std::make_pair(2, 4)], graph[std::make_pair(3, 4)]}),
            result_edges);
}

TEST_F(MinimalSpanningTreeTest, prim_ThenMinimalSpanningTree)
{
    // given
    std::vector<graph_v> vertices = graph.vertices();
    // when
    graph_t result = algr::prim(graph, graph[0]);
    // then
    std::vector<graph_v> result_vertices = result.vertices();
    std::vector<graph_e> result_edges = result.edges();

    std::sort(vertices.begin(), vertices.end());
    std::sort(result_vertices.begin(), result_vertices.end());
    std::sort(result_edges.begin(), result_edges.end());

    EXPECT_EQ(vertices, result_vertices);
    EXPECT_EQ(
            std::vector<graph_e>(
                    {graph[std::make_pair(0, 1)], graph[std::make_pair(0, 2)],
                     graph[std::make_pair(2, 4)], graph[std::make_pair(3, 4)]}),
            result_edges);
}

TEST_F(MinimalSpanningTreeTest, prim_WhenDiffrentSources_ThenSameMinimalSpanningTree)
{
    // when
    graph_t result1 = algr::prim(graph, graph[1]);
    graph_t result4 = algr::prim(graph, graph[4]);
    // then
    std::vector<graph_e> result1_edges = result1.edges();
    std::vector<graph_e> result4_edges = result4.edges();

    std::sort(result1_edges.begin(), result1_edges.end());
    std::sort(result4_edges.begin(), result4_edges.end());

    EXPECT_EQ(result1.edges_count(), result4.edges_count());
    EXPECT_EQ(result1_edges, result4_edges);
}
