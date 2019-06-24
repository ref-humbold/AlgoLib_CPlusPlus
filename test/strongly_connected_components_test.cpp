/**!
 * \file scc_test.cpp
 * \brief TESTY DLA ALGORYTMU SILNIE SPÓLJNYCH SKŁADOWYCH W GRAFIE SKIEROWANYM
 */
#include <algorithm>
#include <gtest/gtest.h>
#include "algolib/graphs/strongly_connected_components.hpp"

namespace algr = algolib::graphs;

TEST(SCCTest, findSCC_whenGraphHasManyComponents_thenReturnsAllComponents)
{
    algr::directed_simple_graph graph(
            10, std::vector<edge_t>(
                        {std::make_tuple(0, 4), std::make_tuple(0, 5), std::make_tuple(1, 0),
                         std::make_tuple(2, 3), std::make_tuple(3, 1), std::make_tuple(4, 1),
                         std::make_tuple(4, 3), std::make_tuple(6, 5), std::make_tuple(6, 9),
                         std::make_tuple(7, 4), std::make_tuple(7, 6), std::make_tuple(8, 3),
                         std::make_tuple(8, 7), std::make_tuple(9, 8)}));

    std::vector<std::set<vertex_t>> result = find_scc(graph);

    ASSERT_EQ(4, result.size());
    EXPECT_NE(std::find(result.begin(), result.end(), std::set<vertex_t>({5})), result.end());
    EXPECT_NE(std::find(result.begin(), result.end(), std::set<vertex_t>({2})), result.end());
    EXPECT_NE(std::find(result.begin(), result.end(), std::set<vertex_t>({0, 1, 3, 4})),
              result.end());
    EXPECT_NE(std::find(result.begin(), result.end(), std::set<vertex_t>({6, 7, 8, 9})),
              result.end());
}
