// TESTY DLA GRAFÓW SKIEROWANYCH
#include <gtest/gtest.h>
#include "../algolib/graphs/directed_graph.hpp"

namespace algr = algolib::graphs;

class DirectedSimpleGraphTest : public ::testing::Test
{
protected:
    algr::directed_simple_graph test_object;

public:
    DirectedSimpleGraphTest() : test_object{algr::directed_simple_graph(10)}
    {
    }

    virtual ~DirectedSimpleGraphTest()
    {
    }
};

TEST_F(DirectedSimpleGraphTest, testGetVerticesNumber)
{
    size_t result = test_object.get_vertices_number();

    EXPECT_EQ(10, result);
}

TEST_F(DirectedSimpleGraphTest, testGetVertices)
{
    std::vector<vertex_t> result = test_object.get_vertices();

    std::sort(result.begin(), result.end());

    EXPECT_EQ(std::vector<vertex_t>({0, 1, 2, 3, 4, 5, 6, 7, 8, 9}), result);
}

TEST_F(DirectedSimpleGraphTest, testAddVertex)
{
    vertex_t result = test_object.add_vertex();

    EXPECT_EQ(10, result);
    EXPECT_EQ(11, test_object.get_vertices_number());
}

TEST_F(DirectedSimpleGraphTest, testGetEdgesNumber)
{
    test_object.add_edge(7, 7);
    test_object.add_edge(1, 5);
    test_object.add_edge(2, 4);
    test_object.add_edge(8, 0);
    test_object.add_edge(6, 3);
    test_object.add_edge(3, 6);
    test_object.add_edge(9, 3);
    test_object.add_edge(8, 0);

    size_t result = test_object.get_edges_number();

    EXPECT_EQ(7, result);
}

TEST_F(DirectedSimpleGraphTest, testGetEdges)
{
    test_object.add_edge(7, 7);
    test_object.add_edge(1, 5);
    test_object.add_edge(2, 4);
    test_object.add_edge(8, 0);
    test_object.add_edge(6, 3);
    test_object.add_edge(3, 6);
    test_object.add_edge(9, 3);
    test_object.add_edge(8, 0);

    std::vector<edge_t> result = test_object.get_edges();

    std::sort(result.begin(), result.end());

    EXPECT_EQ(
        std::vector<edge_t>({std::make_tuple(1, 5), std::make_tuple(2, 4), std::make_tuple(3, 6),
                             std::make_tuple(6, 3), std::make_tuple(7, 7), std::make_pair(8, 0),
                             std::make_pair(9, 3)}),
        result);
}

TEST_F(DirectedSimpleGraphTest, testAddEdge)
{
    test_object.add_edge(1, 5);
    test_object.add_edge(1, 5);
    test_object.add_edge(1, 1);

    std::vector<vertex_t> result1 = test_object.get_neighbours(1);
    std::vector<vertex_t> result5 = test_object.get_neighbours(5);

    std::sort(result1.begin(), result1.end());
    std::sort(result5.begin(), result5.end());

    EXPECT_EQ(2, test_object.get_edges_number());
    EXPECT_EQ(std::vector<vertex_t>({1, 5}), result1);
    EXPECT_EQ(std::vector<vertex_t>(), result5);
}

TEST_F(DirectedSimpleGraphTest, testGetNeighbours)
{
    test_object.add_edge(1, 1);
    test_object.add_edge(1, 3);
    test_object.add_edge(1, 4);
    test_object.add_edge(1, 7);
    test_object.add_edge(1, 9);
    test_object.add_edge(2, 1);
    test_object.add_edge(6, 1);

    std::vector<vertex_t> result = test_object.get_neighbours(1);

    std::sort(result.begin(), result.end());

    EXPECT_EQ(std::vector<vertex_t>({1, 3, 4, 7, 9}), result);
}

TEST_F(DirectedSimpleGraphTest, testGetOutdegree)
{
    test_object.add_edge(1, 1);
    test_object.add_edge(1, 3);
    test_object.add_edge(1, 4);
    test_object.add_edge(1, 7);
    test_object.add_edge(1, 9);
    test_object.add_edge(2, 1);
    test_object.add_edge(6, 1);

    size_t result = test_object.get_outdegree(1);

    EXPECT_EQ(5, result);
}

TEST_F(DirectedSimpleGraphTest, testGetIndegree)
{
    test_object.add_edge(1, 1);
    test_object.add_edge(3, 1);
    test_object.add_edge(4, 1);
    test_object.add_edge(7, 1);
    test_object.add_edge(9, 1);
    test_object.add_edge(1, 2);
    test_object.add_edge(1, 6);

    size_t result = test_object.get_indegree(1);

    EXPECT_EQ(5, result);
}

TEST_F(DirectedSimpleGraphTest, testReverse)
{
    test_object.add_edge(1, 2);
    test_object.add_edge(3, 5);
    test_object.add_edge(4, 9);
    test_object.add_edge(5, 4);
    test_object.add_edge(5, 7);
    test_object.add_edge(6, 2);
    test_object.add_edge(6, 6);
    test_object.add_edge(7, 8);
    test_object.add_edge(9, 1);
    test_object.add_edge(9, 6);

    test_object.reverse();

    std::vector<edge_t> result = test_object.get_edges();

    std::sort(result.begin(), result.end());

    EXPECT_EQ(
        std::vector<edge_t>({std::make_tuple(1, 9), std::make_tuple(2, 1), std::make_tuple(2, 6),
                             std::make_tuple(4, 5), std::make_tuple(5, 3), std::make_tuple(6, 6),
                             std::make_tuple(6, 9), std::make_tuple(7, 5), std::make_tuple(8, 7),
                             std::make_tuple(9, 4)}),
        result);
}
