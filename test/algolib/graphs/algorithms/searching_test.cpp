/**!
 * \file searching_test.cpp
 * \brief Tests: Algorithms for graph searching.
 */
#include <vector>
#include <gtest/gtest.h>
#include "algolib/graphs/algorithms/searching.hpp"
#include "algolib/graphs/directed_graph.hpp"
#include "algolib/graphs/undirected_graph.hpp"

namespace algr = algolib::graphs;

template <typename Vertex>
struct test_strategy : public algr::dfs_strategy<Vertex>
{
    void for_root(const Vertex &) override
    {
    }

    void on_entry(const Vertex & vertex) override
    {
        this->entries.push_back(vertex);
    }

    void on_next_vertex(const Vertex &, const Vertex &) override
    {
    }

    void on_exit(const Vertex & vertex) override
    {
        this->exits.push_back(vertex);
    }

    void on_edge_to_visited(const Vertex &, const Vertex &) override
    {
    }

    std::vector<Vertex> entries;
    std::vector<Vertex> exits;
};

class SearchingTest : public ::testing::Test
{
public:
    using dgraph_t = algr::directed_simple_graph<>;
    using dgraph_v = dgraph_t::vertex_type;

    using ugraph_t = algr::undirected_simple_graph<>;
    using ugraph_v = ugraph_t::vertex_type;

protected:
    algr::empty_strategy<ugraph_v> eu_strategy;
    algr::empty_strategy<dgraph_v> ed_strategy;
    test_strategy<dgraph_v> d_strategy;
    test_strategy<ugraph_v> u_strategy;
    dgraph_t directed_graph;
    ugraph_t undirected_graph;

public:
    SearchingTest()
        : directed_graph{dgraph_t({0, 1, 2, 3, 4, 5, 6, 7, 8, 9})},
          undirected_graph{ugraph_t({0, 1, 2, 3, 4, 5, 6, 7, 8, 9})}
    {
        directed_graph.add_edge_between(directed_graph[0], directed_graph[1]);
        directed_graph.add_edge_between(directed_graph[1], directed_graph[3]);
        directed_graph.add_edge_between(directed_graph[1], directed_graph[7]);
        directed_graph.add_edge_between(directed_graph[3], directed_graph[4]);
        directed_graph.add_edge_between(directed_graph[4], directed_graph[0]);
        directed_graph.add_edge_between(directed_graph[5], directed_graph[4]);
        directed_graph.add_edge_between(directed_graph[5], directed_graph[8]);
        directed_graph.add_edge_between(directed_graph[6], directed_graph[2]);
        directed_graph.add_edge_between(directed_graph[6], directed_graph[9]);
        directed_graph.add_edge_between(directed_graph[8], directed_graph[5]);

        undirected_graph.add_edge_between(undirected_graph[0], undirected_graph[1]);
        undirected_graph.add_edge_between(undirected_graph[0], undirected_graph[4]);
        undirected_graph.add_edge_between(undirected_graph[1], undirected_graph[3]);
        undirected_graph.add_edge_between(undirected_graph[1], undirected_graph[7]);
        undirected_graph.add_edge_between(undirected_graph[2], undirected_graph[6]);
        undirected_graph.add_edge_between(undirected_graph[3], undirected_graph[4]);
        undirected_graph.add_edge_between(undirected_graph[4], undirected_graph[5]);
        undirected_graph.add_edge_between(undirected_graph[5], undirected_graph[8]);
        undirected_graph.add_edge_between(undirected_graph[6], undirected_graph[9]);
    }

    ~SearchingTest() override = default;
};

#pragma region bfs

TEST_F(SearchingTest, bfs_WhenUndirectedGraphAndSingleRoot_ThenVisitedVertices)
{
    //when
    std::vector<ugraph_v> result = algr::bfs(undirected_graph, eu_strategy, {undirected_graph[0]});

    // then
    std::sort(result.begin(), result.end());

    EXPECT_EQ(
            std::vector<ugraph_v>(
                    {undirected_graph[0], undirected_graph[1], undirected_graph[3],
                     undirected_graph[4], undirected_graph[5], undirected_graph[7],
                     undirected_graph[8]}),
            result);
}

TEST_F(SearchingTest, bfs_WhenUndirectedGraphAndManyRoots_ThenAllVisited)
{
    // given
    std::vector<ugraph_v> vertices = undirected_graph.vertices();

    // when
    std::vector<ugraph_v> result =
            algr::bfs(undirected_graph, u_strategy, {undirected_graph[0], undirected_graph[6]});

    // then
    std::sort(vertices.begin(), vertices.end());
    std::sort(u_strategy.entries.begin(), u_strategy.entries.end());
    std::sort(u_strategy.exits.begin(), u_strategy.exits.end());
    std::sort(result.begin(), result.end());

    ASSERT_EQ(vertices, result);
    EXPECT_EQ(vertices, u_strategy.entries);
    EXPECT_EQ(vertices, u_strategy.exits);
}

TEST_F(SearchingTest, bfs_WhenUndirectedGraphAndNoRoots_ThenNoVisited)
{
    // when
    std::vector<ugraph_v> result = algr::bfs(undirected_graph, eu_strategy, {});

    // then
    EXPECT_TRUE(result.empty());
}

TEST_F(SearchingTest, bfs_WhenDirectedGraphAndSingleRoot_ThenVisitedVertices)
{
    // when
    std::vector<dgraph_v> result = algr::bfs(directed_graph, ed_strategy, {directed_graph[1]});

    // then
    std::sort(result.begin(), result.end());

    EXPECT_EQ(
            std::vector<dgraph_v>(
                    {directed_graph[0], directed_graph[1], directed_graph[3], directed_graph[4],
                     directed_graph[7]}),
            result);
}

TEST_F(SearchingTest, bfs_WhenDirectedGraphAndManyRoots_ThenAllVisited)
{
    // given
    std::vector<ugraph_v> vertices = directed_graph.vertices();

    // when
    std::vector<dgraph_v> result =
            algr::bfs(directed_graph, d_strategy, {directed_graph[8], directed_graph[6]});

    // then
    std::sort(vertices.begin(), vertices.end());
    std::sort(d_strategy.entries.begin(), d_strategy.entries.end());
    std::sort(d_strategy.exits.begin(), d_strategy.exits.end());
    std::sort(result.begin(), result.end());

    ASSERT_EQ(vertices, result);
    EXPECT_EQ(vertices, d_strategy.entries);
    EXPECT_EQ(vertices, d_strategy.exits);
}

#pragma endregion
#pragma region dfs_iterative

TEST_F(SearchingTest, dfsIterative_WhenUndirectedGraphAndSingleRoot_ThenVisitedVisited)
{
    // when
    std::vector<ugraph_v> result =
            algr::dfs_iterative(undirected_graph, eu_strategy, {undirected_graph[0]});

    // then
    std::sort(result.begin(), result.end());

    EXPECT_EQ(
            std::vector<ugraph_v>(
                    {undirected_graph[0], undirected_graph[1], undirected_graph[3],
                     undirected_graph[4], undirected_graph[5], undirected_graph[7],
                     undirected_graph[8]}),
            result);
}

TEST_F(SearchingTest, dfsIterative_WhenUndirectedGraphAndManyRoots_ThenAllVisited)
{
    // given
    std::vector<ugraph_v> vertices = undirected_graph.vertices();

    // when
    std::vector<ugraph_v> result = algr::dfs_iterative(
            undirected_graph, u_strategy, {undirected_graph[0], undirected_graph[6]});

    // then
    std::sort(vertices.begin(), vertices.end());
    std::sort(u_strategy.entries.begin(), u_strategy.entries.end());
    std::sort(u_strategy.exits.begin(), u_strategy.exits.end());
    std::sort(result.begin(), result.end());

    ASSERT_EQ(vertices, result);
    EXPECT_EQ(vertices, u_strategy.entries);
    EXPECT_EQ(vertices, u_strategy.exits);
}

TEST_F(SearchingTest, dfsIterative_WhenUndirectedGraphAndNoRoots_ThenNoVisited)
{
    // when
    std::vector<ugraph_v> result = algr::dfs_iterative(undirected_graph, eu_strategy, {});

    // then
    EXPECT_TRUE(result.empty());
}

TEST_F(SearchingTest, dfsIterative_WhenDirectedGraphAndSingleRoot_ThenVisitedVisited)
{
    // when
    std::vector<dgraph_v> result =
            algr::dfs_iterative(directed_graph, ed_strategy, {directed_graph[1]});

    // then
    std::sort(result.begin(), result.end());

    EXPECT_EQ(
            std::vector<dgraph_v>(
                    {directed_graph[0], directed_graph[1], directed_graph[3], directed_graph[4],
                     directed_graph[7]}),
            result);
}

TEST_F(SearchingTest, dfsIterative_WhenDirectedGraphAndManyRoots_ThenAllVisited)
{
    // given
    std::vector<ugraph_v> vertices = undirected_graph.vertices();

    // when
    std::vector<dgraph_v> result =
            algr::dfs_iterative(directed_graph, d_strategy, {directed_graph[8], directed_graph[6]});

    // then
    std::sort(vertices.begin(), vertices.end());
    std::sort(d_strategy.entries.begin(), d_strategy.entries.end());
    std::sort(d_strategy.exits.begin(), d_strategy.exits.end());
    std::sort(result.begin(), result.end());

    ASSERT_EQ(vertices, result);
    EXPECT_EQ(vertices, d_strategy.entries);
    EXPECT_EQ(vertices, d_strategy.exits);
}

#pragma endregion
#pragma region dfs_recursive

TEST_F(SearchingTest, dfsRecursive_WhenUndirectedGraphAndSingleRoot_ThenVisitedVisited)
{
    // when
    std::vector<ugraph_v> result =
            algr::dfs_recursive(undirected_graph, eu_strategy, {undirected_graph[0]});

    // then
    std::sort(result.begin(), result.end());

    EXPECT_EQ(
            std::vector<ugraph_v>(
                    {undirected_graph[0], undirected_graph[1], undirected_graph[3],
                     undirected_graph[4], undirected_graph[5], undirected_graph[7],
                     undirected_graph[8]}),
            result);
}

TEST_F(SearchingTest, dfsRecursive_WhenUndirectedGraphAndManyRoots_ThenAllVisited)
{
    // given
    std::vector<ugraph_v> vertices = undirected_graph.vertices();

    // when
    std::vector<ugraph_v> result = algr::dfs_recursive(
            undirected_graph, u_strategy, {undirected_graph[0], undirected_graph[6]});

    // then
    std::sort(vertices.begin(), vertices.end());
    std::sort(u_strategy.entries.begin(), u_strategy.entries.end());
    std::sort(u_strategy.exits.begin(), u_strategy.exits.end());
    std::sort(result.begin(), result.end());

    ASSERT_EQ(vertices, result);
    EXPECT_EQ(vertices, u_strategy.entries);
    EXPECT_EQ(vertices, u_strategy.exits);
}

TEST_F(SearchingTest, dfsRecursive_WhenUndirectedGraphAndNoRoots_ThenNoVisited)
{
    // when
    std::vector<ugraph_v> result = algr::dfs_recursive(undirected_graph, eu_strategy, {});

    // then
    EXPECT_TRUE(result.empty());
}

TEST_F(SearchingTest, dfsRecursive_WhenDirectedGraphAndSingleRoot_ThenVisitedVisited)
{
    // when
    std::vector<dgraph_v> result =
            algr::dfs_recursive(directed_graph, ed_strategy, {directed_graph[1]});

    // then
    std::sort(result.begin(), result.end());

    EXPECT_EQ(
            std::vector<dgraph_v>(
                    {directed_graph[0], directed_graph[1], directed_graph[3], directed_graph[4],
                     directed_graph[7]}),
            result);
}

TEST_F(SearchingTest, dfsRecursive_WhenDirectedGraphAndManyRoots_ThenAllVisited)
{
    // given
    std::vector<ugraph_v> vertices = undirected_graph.vertices();

    // when
    std::vector<dgraph_v> result =
            algr::dfs_recursive(directed_graph, d_strategy, {directed_graph[8], directed_graph[6]});

    // then
    std::sort(vertices.begin(), vertices.end());
    std::sort(d_strategy.entries.begin(), d_strategy.entries.end());
    std::sort(d_strategy.exits.begin(), d_strategy.exits.end());
    std::sort(result.begin(), result.end());

    ASSERT_EQ(vertices, result);
    EXPECT_EQ(vertices, d_strategy.entries);
    EXPECT_EQ(vertices, d_strategy.exits);
}

#pragma endregion
