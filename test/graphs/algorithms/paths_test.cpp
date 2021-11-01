/**!
 * \file paths_test.cpp
 * \brief Tests: Algorithms for shortest paths in graph
 */
#include <vector>
#include <gtest/gtest.h>
#include "algolib/graphs/algorithms/paths.hpp"
#include "algolib/graphs/directed_graph.hpp"
#include "algolib/graphs/undirected_graph.hpp"

namespace algr = algolib::graphs;

class weighted_impl : public algr::weighted
{
public:
    explicit weighted_impl(weight_type weight = 0) : weighted(), weight_{weight}
    {
    }

    ~weighted_impl() override = default;

    const weight_type & weight() const override
    {
        return weight_;
    }

private:
    weight_type weight_;
};

class PathsTest : public ::testing::Test
{
public:
    using dgraph_t = algr::directed_simple_graph<size_t, algr::no_prop, weighted_impl>;
    using dgraph_v = dgraph_t::vertex_type;

    using ugraph_t = algr::undirected_simple_graph<size_t, algr::no_prop, weighted_impl>;
    using ugraph_v = ugraph_t::vertex_type;

    using weight_t = weighted_impl::weight_type;

    PathsTest()
        : directed_graph{dgraph_t({0, 1, 2, 3, 4, 5, 6, 7, 8, 9})},
          undirected_graph{ugraph_t({0, 1, 2, 3, 4, 5, 6, 7, 8, 9})}
    {
        directed_graph.add_edge_between(directed_graph[0], directed_graph[1], weighted_impl(4.0));
        directed_graph.add_edge_between(directed_graph[1], directed_graph[4], weighted_impl(7.0));
        directed_graph.add_edge_between(directed_graph[1], directed_graph[7], weighted_impl(12.0));
        directed_graph.add_edge_between(directed_graph[2], directed_graph[4], weighted_impl(6.0));
        directed_graph.add_edge_between(directed_graph[2], directed_graph[6], weighted_impl(8.0));
        directed_graph.add_edge_between(directed_graph[3], directed_graph[0], weighted_impl(3.0));
        directed_graph.add_edge_between(directed_graph[3], directed_graph[7], weighted_impl(5.0));
        directed_graph.add_edge_between(directed_graph[4], directed_graph[5], weighted_impl(1.0));
        directed_graph.add_edge_between(directed_graph[4], directed_graph[3], weighted_impl(10.0));
        directed_graph.add_edge_between(directed_graph[5], directed_graph[6], weighted_impl(4.0));
        directed_graph.add_edge_between(directed_graph[5], directed_graph[8], weighted_impl(2.0));
        directed_graph.add_edge_between(directed_graph[6], directed_graph[5], weighted_impl(7.0));
        directed_graph.add_edge_between(directed_graph[7], directed_graph[5], weighted_impl(2.0));
        directed_graph.add_edge_between(directed_graph[7], directed_graph[8], weighted_impl(6.0));
        directed_graph.add_edge_between(directed_graph[8], directed_graph[9], weighted_impl(10.0));
        directed_graph.add_edge_between(directed_graph[9], directed_graph[6], weighted_impl(3.0));

        undirected_graph.add_edge_between(undirected_graph[0], undirected_graph[1],
                                          weighted_impl(4.0));
        undirected_graph.add_edge_between(undirected_graph[1], undirected_graph[4],
                                          weighted_impl(7.0));
        undirected_graph.add_edge_between(undirected_graph[1], undirected_graph[7],
                                          weighted_impl(12.0));
        undirected_graph.add_edge_between(undirected_graph[2], undirected_graph[6],
                                          weighted_impl(8.0));
        undirected_graph.add_edge_between(undirected_graph[3], undirected_graph[0],
                                          weighted_impl(3.0));
        undirected_graph.add_edge_between(undirected_graph[3], undirected_graph[7],
                                          weighted_impl(5.0));
        undirected_graph.add_edge_between(undirected_graph[4], undirected_graph[5],
                                          weighted_impl(1.0));
        undirected_graph.add_edge_between(undirected_graph[4], undirected_graph[3],
                                          weighted_impl(10.0));
        undirected_graph.add_edge_between(undirected_graph[5], undirected_graph[8],
                                          weighted_impl(2.0));
        undirected_graph.add_edge_between(undirected_graph[7], undirected_graph[5],
                                          weighted_impl(2.0));
        undirected_graph.add_edge_between(undirected_graph[7], undirected_graph[8],
                                          weighted_impl(6.0));
        undirected_graph.add_edge_between(undirected_graph[9], undirected_graph[6],
                                          weighted_impl(3.0));
    }

    ~PathsTest() override = default;

protected:
    template <typename Graph>
    std::unordered_map<typename Graph::vertex_type, weight_t>
            from_list(const std::vector<weight_t> & distances, const Graph & graph)
    {
        std::unordered_map<typename Graph::vertex_type, weight_t> map;

        for(auto && vertex : graph.vertices())
            map.emplace(vertex, distances[vertex.id()]);

        return map;
    }

    template <typename Graph>
    std::unordered_map<std::pair<typename Graph::vertex_type, typename Graph::vertex_type>,
                       weight_t>
            from_matrix(const std::vector<std::vector<weight_t>> & distances, const Graph & graph)
    {
        std::unordered_map<std::pair<typename Graph::vertex_type, typename Graph::vertex_type>,
                           weight_t>
                map;

        for(auto && source : graph.vertices())
            for(auto && destination : graph.vertices())
                map.emplace(std::make_pair(source, destination),
                            distances[source.id()][destination.id()]);

        return map;
    }

    dgraph_t directed_graph;
    ugraph_t undirected_graph;

    weight_t inf = weighted_impl::infinity;
};

#pragma region bellman_ford

TEST_F(PathsTest, bellmanFord__WhenDirectedGraph)
{
    // given
    std::vector<weight_t> distances = {20, 0, inf, 17, 7, 8, 12, 12, 10, 20};
    auto expected = from_list(distances, directed_graph);

    directed_graph.add_edge_between(directed_graph[2], directed_graph[1], weighted_impl(-2));
    // when
    auto result = algr::bellman_ford(directed_graph, directed_graph[1]);
    // then
    EXPECT_EQ(expected, result);
}

TEST_F(PathsTest, bellmanFord__WhenUndirectedGraph)
{
    // given
    std::vector<weight_t> distances = {4, 0, inf, 7, 7, 8, inf, 10, 10, inf};
    auto expected = from_list(distances, undirected_graph);
    // when
    auto result = algr::bellman_ford(undirected_graph.as_directed(), undirected_graph[1]);
    // then
    EXPECT_EQ(expected, result);
}

TEST_F(PathsTest, bellmanFord__WhenNegativeCycle_ThenLogicError)
{
    // given
    directed_graph.add_edge_between(directed_graph[8], directed_graph[3], weighted_impl(-20.0));
    // when
    auto exec = [&]() { return algr::bellman_ford(directed_graph, directed_graph[1]); };
    // then
    EXPECT_THROW(exec(), std::logic_error);
}

#pragma endregion
#pragma region dijkstra

TEST_F(PathsTest, dijkstra__WhenDirectedGraph)
{
    // given
    std::vector<weight_t> distances = {20, 0, inf, 17, 7, 8, 12, 12, 10, 20};
    auto expected = from_list(distances, directed_graph);
    // when
    auto result = algr::dijkstra(directed_graph, directed_graph[1]);
    // then
    EXPECT_EQ(expected, result);
}

TEST_F(PathsTest, dijkstra__WhenUndirectedGraph)
{
    // given
    std::vector<weight_t> distances = {4, 0, inf, 7, 7, 8, inf, 10, 10, inf};
    auto expected = from_list(distances, undirected_graph);
    // when
    auto result = algr::dijkstra(undirected_graph, undirected_graph[1]);
    // then
    EXPECT_EQ(expected, result);
}

TEST_F(PathsTest, dijkstra__WhenNegativeEdge__ThenLogicError)
{
    // given
    directed_graph.add_edge_between(directed_graph[2], directed_graph[1], weighted_impl(-2));
    // when
    auto exec = [&]() { return algr::dijkstra(directed_graph, directed_graph[1]); };
    // then
    EXPECT_THROW(exec(), std::logic_error);
}

#pragma endregion
#pragma region floyd_warshall

TEST_F(PathsTest, floydWarshall__WhenDirectedGraph)
{
    // given
    std::vector<std::vector<weight_t>> distances = {
            {0, 4, inf, 21, 11, 12, 16, 16, 14, 24},
            {20, 0, inf, 17, 7, 8, 12, 12, 10, 20},
            {18, -2, 0, 15, 5, 6, 8, 10, 8, 18},
            {3, 7, inf, 0, 14, 7, 11, 5, 9, 19},
            {13, 17, inf, 10, 0, 1, 5, 15, 3, 13},
            {inf, inf, inf, inf, inf, 0, 4, inf, 2, 12},
            {inf, inf, inf, inf, inf, 7, 0, inf, 9, 19},
            {inf, inf, inf, inf, inf, 2, 6, 0, 4, 14},
            {inf, inf, inf, inf, inf, 20, 13, inf, 0, 10},
            {inf, inf, inf, inf, inf, 10, 3, inf, 12, 0},
    };
    auto expected = from_matrix(distances, directed_graph);

    directed_graph.add_edge_between(directed_graph[2], directed_graph[1], weighted_impl(-2));
    // when
    auto result = algr::floyd_warshall(directed_graph);
    // then
    EXPECT_EQ(expected, result);
}

TEST_F(PathsTest, floyd_warshall__WhenUndirectedGraph)
{
    // given
    std::vector<std::vector<weight_t>> distances = {{0, 4, inf, 3, 11, 10, inf, 8, 12, inf},
                                                    {4, 0, inf, 7, 7, 8, inf, 10, 10, inf},
                                                    {inf, inf, 0, inf, inf, inf, 8, inf, inf, 11},
                                                    {3, 7, inf, 0, 8, 7, inf, 5, 9, inf},
                                                    {11, 7, inf, 8, 0, 1, inf, 3, 3, inf},
                                                    {10, 8, inf, 7, 1, 0, inf, 2, 2, inf},
                                                    {inf, inf, 8, inf, inf, inf, 0, inf, inf, 3},
                                                    {8, 10, inf, 5, 3, 2, inf, 0, 4, inf},
                                                    {12, 10, inf, 9, 3, 2, inf, 4, 0, inf},
                                                    {inf, inf, 11, inf, inf, inf, 3, inf, inf, 0}};
    auto expected = from_matrix(distances, undirected_graph);
    // when
    auto result = algr::floyd_warshall(undirected_graph.as_directed());
    // then
    EXPECT_EQ(expected, result);
}

#pragma endregion
