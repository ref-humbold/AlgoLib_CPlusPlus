//! TESTY DLA ALGORYTMÓW SORTOWANIA TOPOLOGICZNEGO"""
#include <gtest/gtest.h>
#include "algolib/old_graphs/algorithms/topological_sorting.hpp"

namespace algr = algolib::graphs;

TEST(TopologicalSortingTest, sortTopological1_whenAcyclicGraph)
{
    algr::directed_simple_graph graph(
            6, std::vector<edge_t>({std::make_tuple(0, 2), std::make_tuple(0, 4),
                                    std::make_tuple(1, 0), std::make_tuple(1, 4),
                                    std::make_tuple(3, 1), std::make_tuple(3, 0),
                                    std::make_tuple(3, 2), std::make_tuple(5, 1),
                                    std::make_tuple(5, 2), std::make_tuple(5, 4)}));

    std::vector<vertex_t> result = sort_topological1(graph);

    EXPECT_EQ(std::vector<vertex_t>({3, 5, 1, 0, 2, 4}), result);
}

TEST(TopologicalSortingTest, sortTopological1_whenCyclicGraph)
{
    algr::directed_simple_graph graph(
            6, std::vector<edge_t>(
                       {std::make_tuple(0, 2), std::make_tuple(0, 4), std::make_tuple(1, 0),
                        std::make_tuple(1, 4), std::make_tuple(2, 1), std::make_tuple(3, 1),
                        std::make_tuple(3, 0), std::make_tuple(3, 2), std::make_tuple(5, 1),
                        std::make_tuple(5, 2), std::make_tuple(5, 4)}));

    EXPECT_THROW(sort_topological1(graph), algr::directed_cyclic_graph_exception);
}

TEST(TopologicalSortingTest, sortTopological1_whenEmptyGraph)
{
    algr::directed_simple_graph graph(6);

    std::vector<vertex_t> result = sort_topological1(graph);

    EXPECT_EQ(std::vector<vertex_t>({0, 1, 2, 3, 4, 5}), result);
}

TEST(TopologicalSortingTest, sortTopological2_whenAcyclicGraph)
{
    algr::directed_simple_graph graph(
            6, std::vector<edge_t>({std::make_tuple(0, 2), std::make_tuple(0, 4),
                                    std::make_tuple(1, 0), std::make_tuple(1, 4),
                                    std::make_tuple(3, 1), std::make_tuple(3, 0),
                                    std::make_tuple(3, 2), std::make_tuple(5, 1),
                                    std::make_tuple(5, 2), std::make_tuple(5, 4)}));

    std::vector<vertex_t> result = sort_topological2(graph);
    std::vector<std::vector<vertex_t>> expecteds = {
            std::vector<vertex_t>({3, 5, 1, 0, 2, 4}), std::vector<vertex_t>({5, 3, 1, 0, 2, 4}),
            std::vector<vertex_t>({3, 5, 1, 0, 4, 2}), std::vector<vertex_t>({5, 3, 1, 0, 4, 2})};

    EXPECT_TRUE(
            std::any_of(expecteds.begin(), expecteds.end(),
                        [&](const std::vector<vertex_t> expected) { return expected == result; }));
}

TEST(TopologicalSortingTest, sortTopological2_whenCyclicGraph)
{
    algr::directed_simple_graph graph(
            6, std::vector<edge_t>(
                       {std::make_tuple(0, 2), std::make_tuple(0, 4), std::make_tuple(1, 0),
                        std::make_tuple(1, 4), std::make_tuple(2, 1), std::make_tuple(3, 1),
                        std::make_tuple(3, 0), std::make_tuple(3, 2), std::make_tuple(5, 1),
                        std::make_tuple(5, 2), std::make_tuple(5, 4)}));

    EXPECT_THROW(sort_topological2(graph), algr::directed_cyclic_graph_exception);
}

TEST(TopologicalSortingTest, sortTopological2_whenEmptyGraph)
{
    algr::directed_simple_graph graph(6);

    std::vector<vertex_t> result = sort_topological2(graph);

    EXPECT_EQ(std::vector<vertex_t>({0, 1, 2, 3, 4, 5}), result);
}
