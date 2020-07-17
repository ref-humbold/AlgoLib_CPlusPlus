//! Tests: Graph searching algorithms
#include <vector>
#include <gtest/gtest.h>
#include "algolib/graphs/algorithms/searching.hpp"
#include "algolib/graphs/directed_graph.hpp"
#include "algolib/graphs/undirected_graph.hpp"

namespace algr = algolib::graphs;

template <typename V>
struct test_strategy : public algr::dfs_strategy<V>
{
    void for_root(const V &) override
    {
    }

    void on_entry(const V & vertex) override
    {
        this->entries.push_back(vertex);
    }

    void on_next_vertex(const V &, const V &) override
    {
    }

    void on_exit(const V & vertex) override
    {
        this->exits.push_back(vertex);
    }

    void on_edge_to_visited(const V &, const V &) override
    {
    }

    std::vector<V> entries;
    std::vector<V> exits;
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
        directed_graph.add_edge_between(0, 1);
        directed_graph.add_edge_between(1, 3);
        directed_graph.add_edge_between(1, 7);
        directed_graph.add_edge_between(3, 4);
        directed_graph.add_edge_between(4, 0);
        directed_graph.add_edge_between(5, 4);
        directed_graph.add_edge_between(5, 8);
        directed_graph.add_edge_between(6, 2);
        directed_graph.add_edge_between(6, 9);
        directed_graph.add_edge_between(8, 5);

        undirected_graph.add_edge_between(0, 1);
        undirected_graph.add_edge_between(0, 4);
        undirected_graph.add_edge_between(1, 3);
        undirected_graph.add_edge_between(1, 7);
        undirected_graph.add_edge_between(2, 6);
        undirected_graph.add_edge_between(3, 4);
        undirected_graph.add_edge_between(4, 5);
        undirected_graph.add_edge_between(5, 8);
        undirected_graph.add_edge_between(6, 9);
    }

    ~SearchingTest() override = default;
};

#pragma region bfs

TEST_F(SearchingTest, bfs_whenUndirectedGraphAndSingleRoot_thenVisitedVertices)
{
    //when
    std::vector<ugraph_v> result = algr::bfs(undirected_graph, eu_strategy, {0});
    // then
    std::sort(result.begin(), result.end());

    EXPECT_EQ(std::vector<ugraph_v>({0, 1, 3, 4, 5, 7, 8}), result);
}

TEST_F(SearchingTest, bfs_whenUndirectedGraphAndManyRoots_thenAllVisited)
{
    // given
    std::vector<ugraph_v> vertices = undirected_graph.vertices();
    // when
    std::vector<ugraph_v> result = algr::bfs(undirected_graph, u_strategy, {0, 6});
    // then
    std::sort(vertices.begin(), vertices.end());
    std::sort(u_strategy.entries.begin(), u_strategy.entries.end());
    std::sort(u_strategy.exits.begin(), u_strategy.exits.end());
    std::sort(result.begin(), result.end());

    ASSERT_EQ(vertices, result);
    EXPECT_EQ(vertices, u_strategy.entries);
    EXPECT_EQ(vertices, u_strategy.exits);
}

TEST_F(SearchingTest, bfs_whenUndirectedGraphAndNoRoots_thenNoVisited)
{
    // when
    std::vector<ugraph_v> result = algr::bfs(undirected_graph, eu_strategy, {});
    // then
    EXPECT_TRUE(result.empty());
}

TEST_F(SearchingTest, bfs_whenDirectedGraphAndSingleRoot_thenVisitedVertices)
{
    // when
    std::vector<dgraph_v> result = algr::bfs(directed_graph, ed_strategy, {1});
    // then
    std::sort(result.begin(), result.end());

    EXPECT_EQ(std::vector<dgraph_v>({0, 1, 3, 4, 7}), result);
}

TEST_F(SearchingTest, bfs_whenDirectedGraphAndManyRoots_thenAllVisited)
{
    // given
    std::vector<ugraph_v> vertices = undirected_graph.vertices();
    // when
    std::vector<dgraph_v> result = algr::bfs(directed_graph, d_strategy, {8, 6});
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

TEST_F(SearchingTest, dfsIterative_whenUndirectedGraphAndSingleRoot_thenVisitedVisited)
{
    // when
    std::vector<ugraph_v> result = algr::dfs_iterative(undirected_graph, eu_strategy, {0});
    // then
    std::sort(result.begin(), result.end());

    EXPECT_EQ(std::vector<ugraph_v>({0, 1, 3, 4, 5, 7, 8}), result);
}

TEST_F(SearchingTest, dfsIterative_whenUndirectedGraphAndManyRoots_thenAllVisited)
{
    // given
    std::vector<ugraph_v> vertices = undirected_graph.vertices();
    // when
    std::vector<ugraph_v> result = algr::dfs_iterative(undirected_graph, u_strategy, {0, 6});
    // then
    std::sort(vertices.begin(), vertices.end());
    std::sort(u_strategy.entries.begin(), u_strategy.entries.end());
    std::sort(u_strategy.exits.begin(), u_strategy.exits.end());
    std::sort(result.begin(), result.end());

    ASSERT_EQ(vertices, result);
    EXPECT_EQ(vertices, u_strategy.entries);
    EXPECT_EQ(vertices, u_strategy.exits);
}

TEST_F(SearchingTest, dfsIterative_whenUndirectedGraphAndNoRoots_thenNoVisited)
{
    // when
    std::vector<ugraph_v> result = algr::dfs_iterative(undirected_graph, eu_strategy, {});
    // then
    EXPECT_TRUE(result.empty());
}

TEST_F(SearchingTest, dfsIterative_whenDirectedGraphAndSingleRoot_thenVisitedVisited)
{
    // when
    std::vector<dgraph_v> result = algr::dfs_iterative(directed_graph, ed_strategy, {1});
    // then
    std::sort(result.begin(), result.end());

    EXPECT_EQ(std::vector<dgraph_v>({0, 1, 3, 4, 7}), result);
}

TEST_F(SearchingTest, dfsIterative_whenDirectedGraphAndManyRoots_thenAllVisited)
{
    // given
    std::vector<ugraph_v> vertices = undirected_graph.vertices();
    // when
    std::vector<dgraph_v> result = algr::dfs_iterative(directed_graph, d_strategy, {8, 6});
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

TEST_F(SearchingTest, dfsRecursive_whenUndirectedGraphAndSingleRoot_thenVisitedVisited)
{
    // when
    std::vector<ugraph_v> result = algr::dfs_recursive(undirected_graph, eu_strategy, {0});
    // then
    std::sort(result.begin(), result.end());

    EXPECT_EQ(std::vector<ugraph_v>({0, 1, 3, 4, 5, 7, 8}), result);
}

TEST_F(SearchingTest, dfsRecursive_whenUndirectedGraphAndManyRoots_thenAllVisited)
{
    // given
    std::vector<ugraph_v> vertices = undirected_graph.vertices();
    // when
    std::vector<ugraph_v> result = algr::dfs_recursive(undirected_graph, u_strategy, {0, 6});
    // then
    std::sort(vertices.begin(), vertices.end());
    std::sort(u_strategy.entries.begin(), u_strategy.entries.end());
    std::sort(u_strategy.exits.begin(), u_strategy.exits.end());
    std::sort(result.begin(), result.end());

    ASSERT_EQ(vertices, result);
    EXPECT_EQ(vertices, u_strategy.entries);
    EXPECT_EQ(vertices, u_strategy.exits);
}

TEST_F(SearchingTest, dfsRecursive_whenUndirectedGraphAndNoRoots_thenNoVisited)
{
    // when
    std::vector<ugraph_v> result = algr::dfs_recursive(undirected_graph, eu_strategy, {});
    // then
    EXPECT_TRUE(result.empty());
}

TEST_F(SearchingTest, dfsRecursive_whenDirectedGraphAndSingleRoot_thenVisitedVisited)
{
    // when
    std::vector<dgraph_v> result = algr::dfs_recursive(directed_graph, ed_strategy, {1});
    // then
    std::sort(result.begin(), result.end());

    EXPECT_EQ(std::vector<dgraph_v>({0, 1, 3, 4, 7}), result);
}

TEST_F(SearchingTest, dfsRecursive_whenDirectedGraphAndManyRoots_thenAllVisited)
{
    // given
    std::vector<ugraph_v> vertices = undirected_graph.vertices();
    // when
    std::vector<dgraph_v> result = algr::dfs_recursive(directed_graph, d_strategy, {8, 6});
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
