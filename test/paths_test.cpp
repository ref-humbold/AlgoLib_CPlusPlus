//! TESTY DLA ALGORYTMÓW WYZNACZANIA NAJKRÓTSZYCH ŚCIEŻEK
#include <gtest/gtest.h>
#include "algolib/graphs/directed_graph.hpp"
#include "algolib/graphs/paths.hpp"
#include "algolib/graphs/undirected_graph.hpp"

namespace algr = algolib::graphs;

TEST(PathsTest, bellmanFord_whenDirectedGraph)
{
    algr::directed_weighted_simple_graph diwgraph(
            10, std::vector<wedge_t>({std::make_tuple(0, 1, 4.0), std::make_tuple(1, 4, 7.0),
                                      std::make_tuple(1, 7, 12.0), std::make_tuple(2, 1, -2.0),
                                      std::make_tuple(2, 4, 6.0), std::make_tuple(2, 6, 8.0),
                                      std::make_tuple(3, 0, 3.0), std::make_tuple(3, 7, 5.0),
                                      std::make_tuple(4, 5, 1.0), std::make_tuple(4, 3, 10.0),
                                      std::make_tuple(5, 6, 4.0), std::make_tuple(5, 8, 2.0),
                                      std::make_tuple(6, 5, 7.0), std::make_tuple(7, 5, 2.0),
                                      std::make_tuple(7, 8, 6.0), std::make_tuple(8, 9, 10.0),
                                      std::make_tuple(9, 6, 3.0)}));

    int source = 1;

    std::vector<double> result = algr::bellman_ford(diwgraph, source);

    EXPECT_EQ(std::vector<double>(
                      {20.0, 0.0, algr::graph::INF, 17.0, 7.0, 8.0, 12.0, 12.0, 10.0, 20.0}),
              result);
}

TEST(PathsTest, bellmanFord_whenUndirectedGraph)
{
    algr::undirected_weighted_simple_graph uwgraph(
            10, std::vector<wedge_t>({std::make_tuple(0, 1, 4.0), std::make_tuple(1, 4, 7.0),
                                      std::make_tuple(1, 7, 12.0), std::make_tuple(2, 6, 8.0),
                                      std::make_tuple(3, 0, 3.0), std::make_tuple(3, 7, 5.0),
                                      std::make_tuple(4, 5, 1.0), std::make_tuple(4, 3, 10.0),
                                      std::make_tuple(5, 8, 2.0), std::make_tuple(7, 5, 2.0),
                                      std::make_tuple(7, 8, 6.0), std::make_tuple(9, 6, 3.0)}));
    int source = 1;

    std::vector<double> result = algr::bellman_ford(uwgraph, source);
    double i = algr::graph::INF;

    EXPECT_EQ(std::vector<double>({4.0, 0.0, i, 7.0, 7.0, 8.0, i, 10.0, 10.0, i}), result);
}

TEST(PathsTest, bellmanFord_whenNegativeCycle)
{
    algr::directed_weighted_simple_graph diwgraph(
            10, std::vector<wedge_t>({std::make_tuple(0, 1, 4.0), std::make_tuple(1, 4, 7.0),
                                      std::make_tuple(1, 7, 12.0), std::make_tuple(8, 3, -20.0),
                                      std::make_tuple(2, 4, 6.0), std::make_tuple(2, 6, 8.0),
                                      std::make_tuple(3, 0, 3.0), std::make_tuple(3, 7, 5.0),
                                      std::make_tuple(4, 5, 1.0), std::make_tuple(4, 3, 10.0),
                                      std::make_tuple(5, 6, 4.0), std::make_tuple(5, 8, 2.0),
                                      std::make_tuple(6, 5, 7.0), std::make_tuple(7, 5, 2.0),
                                      std::make_tuple(7, 8, 6.0), std::make_tuple(8, 9, 10.0),
                                      std::make_tuple(9, 6, 3.0)}));
    int source = 1;

    EXPECT_THROW(algr::bellman_ford(diwgraph, source), std::logic_error);
}

TEST(PathsTest, dijkstra_whenDirectedGraph)
{
    algr::directed_weighted_simple_graph diwgraph(
            10, std::vector<wedge_t>({std::make_tuple(0, 1, 4.0), std::make_tuple(1, 4, 7.0),
                                      std::make_tuple(1, 7, 12.0), std::make_tuple(2, 4, 6.0),
                                      std::make_tuple(2, 6, 8.0), std::make_tuple(3, 0, 3.0),
                                      std::make_tuple(3, 7, 5.0), std::make_tuple(4, 5, 1.0),
                                      std::make_tuple(4, 3, 10.0), std::make_tuple(5, 6, 4.0),
                                      std::make_tuple(5, 8, 2.0), std::make_tuple(6, 5, 7.0),
                                      std::make_tuple(7, 5, 2.0), std::make_tuple(7, 8, 6.0),
                                      std::make_tuple(8, 9, 10.0), std::make_tuple(9, 6, 3.0)}));
    int source = 1;

    std::vector<double> result = algr::dijkstra(diwgraph, source);

    EXPECT_EQ(std::vector<double>(
                      {20.0, 0.0, algr::graph::INF, 17.0, 7.0, 8.0, 12.0, 12.0, 10.0, 20.0}),
              result);
}

TEST(PathsTest, dijkstra_whenUndirectedGraph)
{
    algr::undirected_weighted_simple_graph uwgraph(
            10, std::vector<wedge_t>({std::make_tuple(0, 1, 4.0), std::make_tuple(1, 4, 7.0),
                                      std::make_tuple(1, 7, 12.0), std::make_tuple(2, 6, 8.0),
                                      std::make_tuple(3, 0, 3.0), std::make_tuple(3, 7, 5.0),
                                      std::make_tuple(4, 5, 1.0), std::make_tuple(4, 3, 10.0),
                                      std::make_tuple(5, 8, 2.0), std::make_tuple(7, 5, 2.0),
                                      std::make_tuple(7, 8, 6.0), std::make_tuple(9, 6, 3.0)}));
    int source = 1;

    std::vector<double> result = algr::dijkstra(uwgraph, source);
    double i = algr::graph::INF;

    EXPECT_EQ(std::vector<double>({4.0, 0.0, i, 7.0, 7.0, 8.0, i, 10.0, 10.0, i}), result);
}

TEST(PathsTest, dijkstra_whenNegativeEdge)
{
    algr::directed_weighted_simple_graph diwgraph(
            10, std::vector<wedge_t>({std::make_tuple(0, 1, 4.0), std::make_tuple(1, 4, 7.0),
                                      std::make_tuple(1, 7, 12.0), std::make_tuple(2, 4, 6.0),
                                      std::make_tuple(2, 6, 8.0), std::make_tuple(3, 0, 3.0),
                                      std::make_tuple(3, 7, 5.0), std::make_tuple(4, 5, 1.0),
                                      std::make_tuple(4, 3, 10.0), std::make_tuple(5, 6, 4.0),
                                      std::make_tuple(5, 8, 2.0), std::make_tuple(6, 5, 7.0),
                                      std::make_tuple(7, 5, 2.0), std::make_tuple(7, 8, 6.0),
                                      std::make_tuple(8, 9, 10.0), std::make_tuple(9, 6, 3.0),
                                      std::make_tuple(2, 1, -2.0)}));
    int source = 1;

    EXPECT_THROW(algr::dijkstra(diwgraph, source), std::logic_error);
}

TEST(PathsTest, floydWarshall_whenDirectedGraph)
{
    algr::directed_weighted_simple_graph diwgraph(
            10, std::vector<wedge_t>({std::make_tuple(0, 1, 4.0), std::make_tuple(1, 4, 7.0),
                                      std::make_tuple(1, 7, 12.0), std::make_tuple(2, 4, 6.0),
                                      std::make_tuple(2, 6, 8.0), std::make_tuple(3, 0, 3.0),
                                      std::make_tuple(3, 7, 5.0), std::make_tuple(4, 5, 1.0),
                                      std::make_tuple(4, 3, 10.0), std::make_tuple(5, 6, 4.0),
                                      std::make_tuple(5, 8, 2.0), std::make_tuple(6, 5, 7.0),
                                      std::make_tuple(7, 5, 2.0), std::make_tuple(7, 8, 6.0),
                                      std::make_tuple(8, 9, 10.0), std::make_tuple(9, 6, 3.0),
                                      std::make_tuple(2, 1, -2.0)}));

    std::vector<std::vector<double>> result = algr::floyd_warshall(diwgraph);
    double i = algr::graph::INF;

    EXPECT_EQ(std::vector<std::vector<double>>(
                      {std::vector<double>({0.0, 4.0, i, 21.0, 11.0, 12.0, 16.0, 16.0, 14.0, 24.0}),
                       std::vector<double>({20.0, 0.0, i, 17.0, 7.0, 8.0, 12.0, 12.0, 10.0, 20.0}),
                       std::vector<double>({18.0, -2.0, 0.0, 15.0, 5.0, 6.0, 8.0, 10.0, 8.0, 18.0}),
                       std::vector<double>({3.0, 7.0, i, 0.0, 14.0, 7.0, 11.0, 5.0, 9.0, 19.0}),
                       std::vector<double>({13.0, 17.0, i, 10.0, 0.0, 1.0, 5.0, 15.0, 3.0, 13.0}),
                       std::vector<double>({i, i, i, i, i, 0.0, 4.0, i, 2.0, 12.0}),
                       std::vector<double>({i, i, i, i, i, 7.0, 0, i, 9.0, 19.0}),
                       std::vector<double>({i, i, i, i, i, 2.0, 6.0, 0.0, 4.0, 14.0}),
                       std::vector<double>({i, i, i, i, i, 20.0, 13.0, i, 0.0, 10.0}),
                       std::vector<double>({i, i, i, i, i, 10.0, 3.0, i, 12.0, 0.0})}),
              result);
}

TEST(PathsTest, floydWarshall_whenUndirectedGraph)
{
    algr::undirected_weighted_simple_graph uwgraph(
            10, std::vector<wedge_t>({std::make_tuple(0, 1, 4.0), std::make_tuple(1, 4, 7.0),
                                      std::make_tuple(1, 7, 12.0), std::make_tuple(2, 6, 8.0),
                                      std::make_tuple(3, 0, 3.0), std::make_tuple(3, 7, 5.0),
                                      std::make_tuple(4, 5, 1.0), std::make_tuple(4, 3, 10.0),
                                      std::make_tuple(5, 8, 2.0), std::make_tuple(7, 5, 2.0),
                                      std::make_tuple(7, 8, 6.0), std::make_tuple(9, 6, 3.0)}));

    std::vector<std::vector<double>> result = algr::floyd_warshall(uwgraph);
    double i = algr::graph::INF;

    EXPECT_EQ(std::vector<std::vector<double>>(
                      {std::vector<double>({0.0, 4.0, i, 3.0, 11.0, 10.0, i, 8.0, 12.0, i}),
                       std::vector<double>({4.0, 0.0, i, 7.0, 7.0, 8.0, i, 10.0, 10.0, i}),
                       std::vector<double>({i, i, 0.0, i, i, i, 8.0, i, i, 11.0}),
                       std::vector<double>({3.0, 7.0, i, 0.0, 8.0, 7.0, i, 5.0, 9.0, i}),
                       std::vector<double>({11.0, 7.0, i, 8.0, 0.0, 1.0, i, 3.0, 3.0, i}),
                       std::vector<double>({10.0, 8.0, i, 7.0, 1.0, 0.0, i, 2.0, 2.0, i}),
                       std::vector<double>({i, i, 8.0, i, i, i, 0.0, i, i, 3.0}),
                       std::vector<double>({8.0, 10.0, i, 5.0, 3.0, 2.0, i, 0.0, 4.0, i}),
                       std::vector<double>({12.0, 10.0, i, 9.0, 3.0, 2.0, i, 4.0, 0.0, i}),
                       std::vector<double>({i, i, 11.0, i, i, i, 3.0, i, i, 0.0})}),
              result);
}
