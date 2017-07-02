// TESTY DLA GRAFÓW NIESKIEROWANYCH
#include <gtest/gtest.h>
#include "../algolib/graphs/undirected_graph.hpp"

namespace algr = algolib::graphs;

class UndirectedSimpleGraphTest : public ::testing::Test
{
protected:
    algr::undirected_simple_graph test_object;

public:
    UndirectedSimpleGraphTest() : test_object{algr::undirected_simple_graph(10)}
    {
    }

    virtual ~UndirectedSimpleGraphTest()
    {
    }
};

TEST_F(UndirectedSimpleGraphTest, testGetVerticesNumber)
{
    size_t result = test_object.get_vertices_number();

    EXPECT_EQ(10, result);
}

TEST_F(UndirectedSimpleGraphTest, testGetVertices)
{
    std::vector<vertex_t> result = test_object.get_vertices();

    std::sort(result.begin(), result.end());

    EXPECT_EQ(std::vector<vertex_t>({0, 1, 2, 3, 4, 5, 6, 7, 8, 9}), result);
}

TEST_F(UndirectedSimpleGraphTest, testAddVertex)
{
    vertex_t result = test_object.add_vertex();

    EXPECT_EQ(10, result);
    EXPECT_EQ(11, test_object.get_vertices_number());
}

TEST_F(UndirectedSimpleGraphTest, testGetEdgesNumber)
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

    EXPECT_EQ(6, result);
}

TEST_F(UndirectedSimpleGraphTest, testGetEdges)
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
        std::vector<edge_t>({std::make_tuple(0, 8), std::make_tuple(1, 5), std::make_tuple(2, 4),
                             std::make_tuple(3, 6), std::make_tuple(3, 9), std::make_tuple(7, 7)}),
        result);
}

TEST_F(UndirectedSimpleGraphTest, testAddEdge)
{
    test_object.add_edge(1, 5);
    test_object.add_edge(1, 5);
    test_object.add_edge(5, 1);
    test_object.add_edge(1, 1);

    std::vector<vertex_t> result1 = test_object.get_neighbours(1);
    std::vector<vertex_t> result5 = test_object.get_neighbours(5);

    std::sort(result1.begin(), result1.end());
    std::sort(result5.begin(), result5.end());

    EXPECT_EQ(2, test_object.get_edges_number());
    EXPECT_EQ(std::vector<vertex_t>({1, 5}), result1);
    EXPECT_EQ(std::vector<vertex_t>({1}), result5);
}

TEST_F(UndirectedSimpleGraphTest, testGetNeighbours)
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

    EXPECT_EQ(std::vector<vertex_t>({1, 2, 3, 4, 6, 7, 9}), result);
}

TEST_F(UndirectedSimpleGraphTest, testGetOutdegree)
{
    test_object.add_edge(1, 1);
    test_object.add_edge(1, 3);
    test_object.add_edge(1, 4);
    test_object.add_edge(1, 7);
    test_object.add_edge(1, 9);
    test_object.add_edge(2, 1);
    test_object.add_edge(6, 1);

    size_t result = test_object.get_outdegree(1);

    EXPECT_EQ(7, result);
}

TEST_F(UndirectedSimpleGraphTest, testGetIndegree)
{
    test_object.add_edge(1, 1);
    test_object.add_edge(3, 1);
    test_object.add_edge(4, 1);
    test_object.add_edge(7, 1);
    test_object.add_edge(9, 1);
    test_object.add_edge(1, 2);
    test_object.add_edge(1, 6);

    size_t result = test_object.get_indegree(1);

    EXPECT_EQ(7, result);
}

TEST_F(UndirectedSimpleGraphTest, testAsDirected)
{
    test_object.add_edge(7, 7);
    test_object.add_edge(1, 5);
    test_object.add_edge(2, 4);
    test_object.add_edge(8, 0);
    test_object.add_edge(6, 3);
    test_object.add_edge(3, 6);
    test_object.add_edge(9, 3);
    test_object.add_edge(8, 0);

    algr::directed_simple_graph * result = test_object.as_directed();
    std::vector<vertex_t> expected_vertices = test_object.get_vertices();
    std::vector<vertex_t> result_vertices = result->get_vertices();
    std::vector<edge_t> result_edges = result->get_edges();

    std::sort(expected_vertices.begin(), expected_vertices.end());
    std::sort(result_vertices.begin(), result_vertices.end());
    std::sort(result_edges.begin(), result_edges.end());

    EXPECT_EQ(expected_vertices, result_vertices);
    EXPECT_EQ(
        std::vector<edge_t>({std::make_tuple(0, 8), std::make_tuple(1, 5), std::make_tuple(2, 4),
                             std::make_tuple(3, 6), std::make_tuple(3, 9), std::make_tuple(4, 2),
                             std::make_tuple(5, 1), std::make_tuple(6, 3), std::make_tuple(7, 7),
                             std::make_tuple(8, 0), std::make_tuple(9, 3)}),
        result_edges);

    delete result;
}
