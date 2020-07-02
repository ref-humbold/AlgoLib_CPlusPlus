/*!
 * \file minimal_spanning_tree_test.cpp
 * \brief Tests: Algorithms for minimal spanning tree
 */
#include <algorithm>
#include <vector>
#include <gtest/gtest.h>
#include "algolib/graphs/algorithms/minimal_spanning_tree.hpp"

namespace algr = algolib::graphs;

class weighted
{
public:
    explicit weighted(double weight = 0) : weight_{weight}
    {
    }

    double weight() const
    {
        return weight_;
    }

private:
    double weight_;
};

class MinimalSpanningTreeTest : public ::testing::Test
{
public:
    using graph_t = algr::undirected_simple_graph<size_t, algr::no_prop, weighted>;
    using graph_v = graph_t::vertex_type;
    using graph_e = graph_t::edge_type;

protected:
    graph_t graph;

public:
    MinimalSpanningTreeTest() : graph{graph_t({0, 1, 2, 3, 4})}
    {
        graph.add_edge_between(0, 1, weighted(-1));
        graph.add_edge_between(0, 2, weighted(4));
        graph.add_edge_between(1, 2, weighted(9));
        graph.add_edge_between(1, 3, weighted(7));
        graph.add_edge_between(1, 4, weighted(12));
        graph.add_edge_between(2, 4, weighted(6));
        graph.add_edge_between(3, 4, weighted(3));
    }

    ~MinimalSpanningTreeTest() override = default;
};

TEST_F(MinimalSpanningTreeTest, kruskal_thenMST)
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
    EXPECT_EQ(std::vector<graph_e>({graph.get_edge(0, 1), graph.get_edge(0, 2),
                                    graph.get_edge(2, 4), graph.get_edge(3, 4)}),
              result_edges);
}

TEST_F(MinimalSpanningTreeTest, prim_thenMST)
{
    // given
    std::vector<graph_v> vertices = graph.vertices();
    // when
    graph_t result = algr::prim(graph, 0);
    // then
    std::vector<graph_v> result_vertices = result.vertices();
    std::vector<graph_e> result_edges = result.edges();

    std::sort(vertices.begin(), vertices.end());
    std::sort(result_vertices.begin(), result_vertices.end());
    std::sort(result_edges.begin(), result_edges.end());

    EXPECT_EQ(vertices, result_vertices);
    EXPECT_EQ(std::vector<graph_e>({graph.get_edge(0, 1), graph.get_edge(0, 2),
                                    graph.get_edge(2, 4), graph.get_edge(3, 4)}),
              result_edges);
}

TEST_F(MinimalSpanningTreeTest, prim_whenDiffrentSources_thenSameMST)
{
    // when
    graph_t result1 = algr::prim(graph, 1);
    graph_t result4 = algr::prim(graph, 4);
    // then
    std::vector<graph_e> result1_edges = result1.edges();
    std::vector<graph_e> result4_edges = result4.edges();

    std::sort(result1_edges.begin(), result1_edges.end());
    std::sort(result4_edges.begin(), result4_edges.end());

    EXPECT_EQ(result1.edges_count(), result4.edges_count());
    EXPECT_EQ(result1_edges, result4_edges);
}
