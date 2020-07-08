/*!
 * \file topological_sorting_test.cpp
 * \brief Tests: Algorithms for topological sorting of a directed graph
 */
#include <gtest/gtest.h>
#include "algolib/graphs/algorithms/topological_sorting.hpp"

namespace algr = algolib::graphs;

using graph_t = algr::directed_simple_graph<>;
using graph_v = graph_t::vertex_type;

TEST(TopologicalSortingTest, sortTopological1_whenAcyclicGraph_thenTopologicalOrder)
{
    // given
    graph_t graph({0, 1, 2, 3, 4, 5});
    graph.add_edge_between(0, 2);
    graph.add_edge_between(0, 4), graph.add_edge_between(1, 0);
    graph.add_edge_between(1, 4);
    graph.add_edge_between(3, 1);
    graph.add_edge_between(3, 0);
    graph.add_edge_between(3, 2);
    graph.add_edge_between(5, 1);
    graph.add_edge_between(5, 2);
    graph.add_edge_between(5, 4);
    // when
    std::vector<graph_v> result = sort_topological1(graph);
    // then
    EXPECT_EQ(std::vector<graph_v>({3, 5, 1, 0, 2, 4}), result);
}

TEST(TopologicalSortingTest, sortTopological1_whenCyclicGraph_thenDirectedCyclicGraphError)
{
    // given
    graph_t graph({0, 1, 2, 3, 4, 5});
    graph.add_edge_between(0, 2);
    graph.add_edge_between(0, 4);
    graph.add_edge_between(1, 0);
    graph.add_edge_between(1, 4);
    graph.add_edge_between(2, 1);
    graph.add_edge_between(3, 1);
    graph.add_edge_between(3, 0);
    graph.add_edge_between(3, 2);
    graph.add_edge_between(5, 1);
    graph.add_edge_between(5, 2);
    graph.add_edge_between(5, 4);
    // when
    auto exec = [&]() { return sort_topological1(graph); };
    // then
    EXPECT_THROW(exec(), algr::directed_cyclic_graph_error);
}

TEST(TopologicalSortingTest, sortTopological1_whenEmptyGraph_thenNaturalOrder)
{
    // given
    graph_t graph({0, 1, 2, 3, 4, 5});
    // when
    std::vector<graph_v> result = sort_topological1(graph);
    // then
    EXPECT_EQ(graph.vertices(), result);
}

TEST(TopologicalSortingTest, sortTopological2_whenAcyclicGraph_thenTopologicalOrder)
{
    // given
    graph_t graph({0, 1, 2, 3, 4, 5});
    graph.add_edge_between(0, 2);
    graph.add_edge_between(0, 4);
    graph.add_edge_between(1, 0);
    graph.add_edge_between(1, 4);
    graph.add_edge_between(3, 1);
    graph.add_edge_between(3, 0);
    graph.add_edge_between(3, 2);
    graph.add_edge_between(5, 1);
    graph.add_edge_between(5, 2);
    graph.add_edge_between(5, 4);

    std::vector<std::vector<graph_v>> expecteds = {
            std::vector<graph_v>({3, 5, 1, 0, 2, 4}), std::vector<graph_v>({5, 3, 1, 0, 2, 4}),
            std::vector<graph_v>({3, 5, 1, 0, 4, 2}), std::vector<graph_v>({5, 3, 1, 0, 4, 2})};
    // when
    std::vector<graph_v> result = sort_topological2(graph);
    // then
    EXPECT_TRUE(
            std::any_of(expecteds.begin(), expecteds.end(),
                        [&](const std::vector<graph_v> expected) { return expected == result; }));
}

TEST(TopologicalSortingTest, sortTopological2_whenCyclicGraph_thenDirectedCyclicGraphError)
{
    // given
    graph_t graph({0, 1, 2, 3, 4, 5});
    graph.add_edge_between(0, 2);
    graph.add_edge_between(0, 4);
    graph.add_edge_between(1, 0);
    graph.add_edge_between(1, 4);
    graph.add_edge_between(2, 1);
    graph.add_edge_between(3, 1);
    graph.add_edge_between(3, 0);
    graph.add_edge_between(3, 2);
    graph.add_edge_between(5, 1);
    graph.add_edge_between(5, 2);
    graph.add_edge_between(5, 4);
    // when
    auto exec = [&]() { return sort_topological2(graph); };
    // then
    EXPECT_THROW(exec(), algr::directed_cyclic_graph_error);
}

TEST(TopologicalSortingTest, sortTopological2_whenEmptyGraph_thenNaturalOrder)
{
    // given
    algr::directed_simple_graph<> graph({0, 1, 2, 3, 4, 5});
    // when
    std::vector<graph_v> result = sort_topological2(graph);
    // then
    EXPECT_EQ(graph.vertices(), result);
}
