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
        : dgraph{dgraph_t({0, 1, 2, 3, 4, 5, 6, 7, 8, 9})},
          ugraph{ugraph_t({0, 1, 2, 3, 4, 5, 6, 7, 8, 9})}
    {
        dgraph.add_edge_between(0, 1, weighted_impl(4.0));
        dgraph.add_edge_between(1, 4, weighted_impl(7.0));
        dgraph.add_edge_between(1, 7, weighted_impl(12.0));
        dgraph.add_edge_between(2, 4, weighted_impl(6.0));
        dgraph.add_edge_between(2, 6, weighted_impl(8.0));
        dgraph.add_edge_between(3, 0, weighted_impl(3.0));
        dgraph.add_edge_between(3, 7, weighted_impl(5.0));
        dgraph.add_edge_between(4, 5, weighted_impl(1.0));
        dgraph.add_edge_between(4, 3, weighted_impl(10.0));
        dgraph.add_edge_between(5, 6, weighted_impl(4.0));
        dgraph.add_edge_between(5, 8, weighted_impl(2.0));
        dgraph.add_edge_between(6, 5, weighted_impl(7.0));
        dgraph.add_edge_between(7, 5, weighted_impl(2.0));
        dgraph.add_edge_between(7, 8, weighted_impl(6.0));
        dgraph.add_edge_between(8, 9, weighted_impl(10.0));
        dgraph.add_edge_between(9, 6, weighted_impl(3.0));

        ugraph.add_edge_between(0, 1, weighted_impl(4.0));
        ugraph.add_edge_between(1, 4, weighted_impl(7.0));
        ugraph.add_edge_between(1, 7, weighted_impl(12.0));
        ugraph.add_edge_between(2, 6, weighted_impl(8.0));
        ugraph.add_edge_between(3, 0, weighted_impl(3.0));
        ugraph.add_edge_between(3, 7, weighted_impl(5.0));
        ugraph.add_edge_between(4, 5, weighted_impl(1.0));
        ugraph.add_edge_between(4, 3, weighted_impl(10.0));
        ugraph.add_edge_between(5, 8, weighted_impl(2.0));
        ugraph.add_edge_between(7, 5, weighted_impl(2.0));
        ugraph.add_edge_between(7, 8, weighted_impl(6.0));
        ugraph.add_edge_between(9, 6, weighted_impl(3.0));
    }

    ~PathsTest() override = default;

protected:
    std::unordered_map<dgraph_v, weight_t> from_list(const std::vector<weight_t> & distances)
    {
        std::unordered_map<dgraph_v, weight_t> map;

        for(size_t i = 0; i < distances.size(); ++i)
            map.emplace(i, distances[i]);

        return map;
    }

    std::unordered_map<std::pair<dgraph_v, dgraph_v>, weight_t, typename dgraph_t::vertex_pair_hash>
            from_matrix(const std::vector<std::vector<weight_t>> & distances)
    {
        std::unordered_map<std::pair<dgraph_v, dgraph_v>, weight_t,
                           typename dgraph_t::vertex_pair_hash>
                map;

        for(size_t i = 0; i < distances.size(); ++i)
            for(size_t j = 0; j < distances[i].size(); ++j)
                map.emplace(std::make_pair(i, j), distances[i][j]);

        return map;
    }

    dgraph_t dgraph;
    ugraph_t ugraph;

    weight_t inf = weighted_impl::infinity;
};

TEST_F(PathsTest, bellmanFord__WhenDirectedGraph)
{
    // given
    std::vector<weight_t> distances = {20, 0, inf, 17, 7, 8, 12, 12, 10, 20};
    auto expected = from_list(distances);

    dgraph.add_edge_between(2, 1, weighted_impl(-2));
    // when
    auto result = bellman_ford(dgraph, 1);
    // then
    EXPECT_EQ(expected, result);
}

TEST_F(PathsTest, bellmanFord__WhenUndirectedGraph)
{
    // given
    std::vector<weight_t> distances = {4, 0, inf, 7, 7, 8, inf, 10, 10, inf};
    auto expected = from_list(distances);
    // when
    auto result = bellman_ford(ugraph.as_directed(), 1);
    // then
    EXPECT_EQ(expected, result);
}

TEST_F(PathsTest, bellmanFord__WhenNegativeCycle_ThenLogicError)
{
    // given
    dgraph.add_edge_between(8, 3, weighted_impl(-20.0));
    // when
    auto exec = [&]() { return bellman_ford(dgraph, 1); };
    // then
    EXPECT_THROW(exec(), std::logic_error);
}

TEST_F(PathsTest, dijkstra__When_directed_graph)
{
    // given
    std::vector<weight_t> distances = {20, 0, inf, 17, 7, 8, 12, 12, 10, 20};
    auto expected = from_list(distances);
    // when
    auto result = dijkstra(dgraph, 1);
    // then
    EXPECT_EQ(expected, result);
}

TEST_F(PathsTest, dijkstra__When_undirected_graph)
{
    // given
    std::vector<weight_t> distances = {4, 0, inf, 7, 7, 8, inf, 10, 10, inf};
    auto expected = from_list(distances);
    // when
    auto result = dijkstra(ugraph, 1);
    // then
    EXPECT_EQ(expected, result);
}

TEST_F(PathsTest, dijkstra__When_negative_edge__Then_value_error)
{
    // given
    dgraph.add_edge_between(2, 1, weighted_impl(-2));
    // when
    auto exec = [&]() { return dijkstra(dgraph, 1); };
    // then
    EXPECT_THROW(exec(), std::logic_error);
}

TEST_F(PathsTest, floyd_warshall__When_directed_graph)
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
    auto expected = from_matrix(distances);
    dgraph.add_edge_between(2, 1, weighted_impl(-2));
    // when
    auto result = floyd_warshall(dgraph);
    // then
    EXPECT_EQ(expected, result);
}

TEST_F(PathsTest, floyd_warshall__When_undirected_graph)
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
    auto expected = from_matrix(distances);
    // when
    auto result = floyd_warshall(ugraph.as_directed());
    // then
    EXPECT_EQ(expected, result);
}
