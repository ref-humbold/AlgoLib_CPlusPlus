//! TESTY DLA ALGORYTMÓW MINIMALNEGO DRZEWA SPINAJĄCEGO
#include <gtest/gtest.h>
#include "algolib/graphs/minimal_spanning_tree.hpp"

namespace algr = algolib::graphs;

class MSTTest : public ::testing::Test
{
protected:
    algr::undirected_weighted_simple_graph graph;

public:
    MSTTest()
        : graph{algr::undirected_weighted_simple_graph(
              5, std::vector<wedge_t>({std::make_tuple(0, 1, -1), std::make_tuple(0, 2, 4),
                                       std::make_tuple(1, 2, 9), std::make_tuple(1, 3, 7),
                                       std::make_tuple(1, 4, 12), std::make_tuple(2, 4, 6),
                                       std::make_tuple(3, 4, 3)}))}
    {
    }

    virtual ~MSTTest()
    {
    }
};

TEST_F(MSTTest, testKruskal)
{
    double result = kruskal(graph);

    EXPECT_EQ(12.0, result);
}

TEST_F(MSTTest, testPrim)
{
    double result = prim(graph, 0);

    EXPECT_EQ(12.0, result);
}

TEST_F(MSTTest, testPrimWhenDiffrentSources)
{
    double result1 = prim(graph, 1);
    double result4 = prim(graph, 4);

    EXPECT_EQ(12.0, result1);
    EXPECT_EQ(12.0, result4);
}
