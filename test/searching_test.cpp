//! Tests: Graph searching algorithms
#include <vector>
#include <gtest/gtest.h>
#include "algolib/graphs/directed_graph.hpp"
#include "algolib/graphs/searching.hpp"
#include "algolib/graphs/searching_strategy.hpp"

namespace algr = algolib::graphs;

struct searching_test_strategy : public algr::searching_strategy
{
    void preprocess(vertex_t vertex) override
    {
        visited.push_back(vertex);
    }

    void for_neighbour(vertex_t vertex, vertex_t neighbour) override
    {
    }

    void postprocess(vertex_t vertex) override
    {
    }

    void on_cycle(vertex_t vertex, vertex_t neighbour) override
    {
    }

    std::vector<int> visited;
};

class SearchingTest : public ::testing::Test
{
protected:
    searching_test_strategy strategy;
    algr::directed_simple_graph digraph;
    algr::undirected_simple_graph ugraph;

public:
    SearchingTest()
        : digraph{algr::directed_simple_graph(
                10, std::vector<edge_t>(
                            {std::make_tuple(0, 1), std::make_tuple(1, 4), std::make_tuple(1, 7),
                             std::make_tuple(2, 4), std::make_tuple(2, 6), std::make_tuple(3, 0),
                             std::make_tuple(3, 7), std::make_tuple(4, 5), std::make_tuple(4, 3),
                             std::make_tuple(5, 6), std::make_tuple(5, 8), std::make_tuple(6, 5),
                             std::make_tuple(7, 5), std::make_tuple(7, 8), std::make_tuple(8, 9),
                             std::make_tuple(9, 6)}))},
          ugraph{algr::undirected_simple_graph(
                  10,
                  std::vector<edge_t>(
                          {std::make_tuple(0, 1), std::make_tuple(1, 4), std::make_tuple(1, 7),
                           std::make_tuple(2, 6), std::make_tuple(3, 0), std::make_tuple(3, 7),
                           std::make_tuple(4, 5), std::make_tuple(4, 3), std::make_tuple(5, 8),
                           std::make_tuple(7, 5), std::make_tuple(7, 8), std::make_tuple(9, 6)}))}
    {
    }

    ~SearchingTest() override = default;
};

TEST_F(SearchingTest, bfs_whenUndirectedGraphAndSingleRoot_thenNotAllVisited)
{
    std::vector<bool> result = algr::bfs(ugraph, strategy, {0});
    std::vector<int> visited = strategy.visited;

    std::sort(visited.begin(), visited.end());

    EXPECT_EQ(std::vector<bool>({true, true, false, true, true, true, false, true, true, false}),
              result);
    EXPECT_EQ(std::vector<int>({0, 1, 3, 4, 5, 7, 8}), visited);
}

TEST_F(SearchingTest, bfs_whenUndirectedGraphAndManyRoots_thenAllVisited)
{
    std::vector<bool> result = algr::bfs(ugraph, strategy, {0, 6});
    std::vector<int> visited = strategy.visited;

    std::sort(visited.begin(), visited.end());

    EXPECT_EQ(std::vector<bool>({true, true, true, true, true, true, true, true, true, true}),
              result);
    EXPECT_EQ(std::vector<int>({0, 1, 2, 3, 4, 5, 6, 7, 8, 9}), visited);
}

TEST_F(SearchingTest, bfs_whenUndirectedGraphAndNoRoots_thenNoVisited)
{
    std::vector<bool> result = algr::bfs(ugraph, strategy, {});
    std::vector<int> visited = strategy.visited;

    EXPECT_EQ(std::vector<bool>(
                      {false, false, false, false, false, false, false, false, false, false}),
              result);
    EXPECT_TRUE(visited.empty());
}

TEST_F(SearchingTest, bfs_whenDirectedGraphAndSingleRoot_thenNotAllVisited)
{
    std::vector<bool> result = algr::bfs(digraph, strategy, {1});
    std::vector<int> visited = strategy.visited;

    std::sort(visited.begin(), visited.end());

    EXPECT_EQ(std::vector<bool>({true, true, false, true, true, true, true, true, true, true}),
              result);
    EXPECT_EQ(std::vector<int>({0, 1, 3, 4, 5, 6, 7, 8, 9}), visited);
}

TEST_F(SearchingTest, dfsI_whenUndirectedGraphAndSingleRoot_thenNotAllVisited)
{
    std::vector<bool> result = algr::dfsI(ugraph, strategy, {0});
    std::vector<int> visited = strategy.visited;

    std::sort(visited.begin(), visited.end());

    EXPECT_EQ(std::vector<bool>({true, true, false, true, true, true, false, true, true, false}),
              result);
    EXPECT_EQ(std::vector<int>({0, 1, 3, 4, 5, 7, 8}), visited);
}

TEST_F(SearchingTest, dfsI_whenUndirectedGraphAndManyRoots_thenAllVisited)
{
    std::vector<bool> result = algr::dfsI(ugraph, strategy, {0, 6});
    std::vector<int> visited = strategy.visited;

    std::sort(visited.begin(), visited.end());

    EXPECT_EQ(std::vector<bool>({true, true, true, true, true, true, true, true, true, true}),
              result);
    EXPECT_EQ(std::vector<int>({0, 1, 2, 3, 4, 5, 6, 7, 8, 9}), visited);
}

TEST_F(SearchingTest, dfsI_whenUndirectedGraphAndNoRoots_thenNoVisited)
{
    std::vector<bool> result = algr::dfsI(ugraph, strategy, {});
    std::vector<int> visited = strategy.visited;

    EXPECT_EQ(std::vector<bool>(
                      {false, false, false, false, false, false, false, false, false, false}),
              result);
    EXPECT_TRUE(visited.empty());
}

TEST_F(SearchingTest, dfsI_whenDirectedGraphAndSingleRoot_thenNotAllVisited)
{
    std::vector<bool> result = algr::dfsI(digraph, strategy, {1});
    std::vector<int> visited = strategy.visited;

    std::sort(visited.begin(), visited.end());

    EXPECT_EQ(std::vector<bool>({true, true, false, true, true, true, true, true, true, true}),
              result);
    EXPECT_EQ(std::vector<int>({0, 1, 3, 4, 5, 6, 7, 8, 9}), visited);
}

TEST_F(SearchingTest, dfsR_whenUndirectedGraphAndSingleRoot_thenNotAllVisited)
{
    std::vector<bool> result = algr::dfsR(ugraph, strategy, {0});
    std::vector<int> visited = strategy.visited;

    std::sort(visited.begin(), visited.end());

    EXPECT_EQ(std::vector<bool>({true, true, false, true, true, true, false, true, true, false}),
              result);
    EXPECT_EQ(std::vector<int>({0, 1, 3, 4, 5, 7, 8}), visited);
}

TEST_F(SearchingTest, dfsR_whenUndirectedGraphAndManyRoots_thenAllVisited)
{
    std::vector<bool> result = algr::dfsR(ugraph, strategy, {0, 6});
    std::vector<int> visited = strategy.visited;

    std::sort(visited.begin(), visited.end());

    EXPECT_EQ(std::vector<bool>({true, true, true, true, true, true, true, true, true, true}),
              result);
    EXPECT_EQ(std::vector<int>({0, 1, 2, 3, 4, 5, 6, 7, 8, 9}), visited);
}

TEST_F(SearchingTest, dfsR_whenUndirectedGraphAndNoRoots_thenNoVisited)
{
    std::vector<bool> result = algr::dfsR(ugraph, strategy, {});
    std::vector<int> visited = strategy.visited;

    EXPECT_EQ(std::vector<bool>(
                      {false, false, false, false, false, false, false, false, false, false}),
              result);
    EXPECT_TRUE(visited.empty());
}

TEST_F(SearchingTest, dfsR_whenDirectedGraphAndSingleRoot_thenNotAllVisited)
{
    std::vector<bool> result = algr::dfsR(digraph, strategy, {1});
    std::vector<int> visited = strategy.visited;

    std::sort(visited.begin(), visited.end());

    EXPECT_EQ(std::vector<bool>({true, true, false, true, true, true, true, true, true, true}),
              result);
    EXPECT_EQ(std::vector<int>({0, 1, 3, 4, 5, 6, 7, 8, 9}), visited);
}
