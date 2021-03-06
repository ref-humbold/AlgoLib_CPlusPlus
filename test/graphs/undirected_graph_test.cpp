/*!
 * \file undirected_graph_test.cpp
 * \brief Tests: Structure of undirected graph
 */
#include <gtest/gtest.h>
#include "algolib/graphs/undirected_graph.hpp"

namespace algr = algolib::graphs;

class UndirectedSimpleGraphTest : public ::testing::Test
{
public:
    using graph_t = algr::undirected_simple_graph<int, std::string, std::string>;
    using graph_v = graph_t::vertex_type;
    using graph_e = graph_t::edge_type;
    using graph_vp = graph_t::vertex_property_type;
    using graph_ep = graph_t::edge_property_type;

protected:
    graph_t test_object;

public:
    UndirectedSimpleGraphTest() : test_object{graph_t({0, 1, 2, 3, 4, 5, 6, 7, 8, 9})}
    {
    }

    ~UndirectedSimpleGraphTest() override = default;
};

TEST_F(UndirectedSimpleGraphTest, operatorBrackets_WhenSettingProperty_ThenProperty)
{
    // given
    graph_vp vertex_property = "x";
    graph_ep edge_property = "y";
    graph_v vertex = 2;
    graph_e edge = test_object.add_edge_between(0, 1);
    // when
    test_object[vertex] = vertex_property;
    test_object[edge] = edge_property;

    graph_vp result_vertex = test_object[vertex];
    graph_ep result_edge = test_object[edge];
    // then
    EXPECT_EQ(vertex_property, result_vertex);
    EXPECT_EQ(edge_property, result_edge);
}

TEST_F(UndirectedSimpleGraphTest, operatorBrackets_WhenNoProperty_ThenDefault)
{
    // given
    graph_e edge = test_object.add_edge_between(6, 7);
    // when
    graph_vp result_vertex = test_object[4];
    graph_ep result_edge = test_object[edge];
    // then
    EXPECT_EQ("", result_vertex);
    EXPECT_EQ("", result_edge);
}

TEST_F(UndirectedSimpleGraphTest, operatorBrackets_WhenNotExisting_ThenInvalidArgument)
{
    // when
    auto exec_vertex = [&]() { return test_object[14]; };
    auto exec_edge1 = [&]() { return test_object[graph_e(2, 8)]; };
    auto exec_edge2 = [&]() { return test_object[graph_e(0, -1)]; };
    // then
    EXPECT_THROW(exec_vertex(), std::invalid_argument);
    EXPECT_THROW(exec_edge1(), std::invalid_argument);
    EXPECT_THROW(exec_edge2(), std::invalid_argument);
}

TEST_F(UndirectedSimpleGraphTest, verticesCount_ThenNumberOfVertices)
{
    // when
    size_t result = test_object.vertices_count();
    // then
    EXPECT_EQ(10, result);
}

TEST_F(UndirectedSimpleGraphTest, vertices_ThenAllVertices)
{
    // when
    std::vector<graph_v> result = test_object.vertices();
    // then
    std::sort(result.begin(), result.end());

    EXPECT_EQ(std::vector<graph_v>({0, 1, 2, 3, 4, 5, 6, 7, 8, 9}), result);
}

TEST_F(UndirectedSimpleGraphTest, addVertex_WhenNewVertex_ThenTrue)
{
    // given
    graph_v new_vertex = 13;
    graph_vp vertex_property = "qwerty";
    // when
    bool result = test_object.add_vertex(new_vertex, vertex_property);
    // then
    ASSERT_TRUE(result);
    EXPECT_EQ(11, test_object.vertices_count());
    EXPECT_EQ(std::vector<graph_v>(), test_object.neighbours(new_vertex));
    EXPECT_EQ(vertex_property, test_object[new_vertex]);
}

TEST_F(UndirectedSimpleGraphTest, addVertex_WhenExistingVertex_ThenFalse)
{
    // given
    graph_v vertex = 6;
    graph_vp vertex_property = "qwerty";

    test_object[vertex] = vertex_property;
    // when
    bool result = test_object.add_vertex(vertex, "abcdefg");
    // then
    ASSERT_FALSE(result);
    EXPECT_EQ(10, test_object.vertices_count());
    EXPECT_EQ(vertex_property, test_object[vertex]);
}

TEST_F(UndirectedSimpleGraphTest, edgesCount_ThenNumberOfEdges)
{
    // given
    test_object.add_edge_between(7, 7);
    test_object.add_edge_between(1, 5);
    test_object.add_edge_between(2, 4);
    test_object.add_edge_between(8, 0);
    test_object.add_edge_between(6, 3);
    test_object.add_edge_between(3, 6);
    test_object.add_edge_between(9, 3);
    test_object.add_edge_between(8, 0);
    // when
    size_t result = test_object.edges_count();
    // then
    EXPECT_EQ(6, result);
}

TEST_F(UndirectedSimpleGraphTest, edges_ThenAllEdges)
{
    // given
    test_object.add_edge_between(7, 7);
    test_object.add_edge_between(1, 5);
    test_object.add_edge_between(2, 4);
    test_object.add_edge_between(8, 0);
    test_object.add_edge_between(6, 3);
    test_object.add_edge_between(3, 6);
    test_object.add_edge_between(9, 3);
    test_object.add_edge_between(8, 0);
    // when
    std::vector<graph_e> result = test_object.edges();
    // then
    std::sort(result.begin(), result.end());

    EXPECT_EQ(std::vector<graph_e>({graph_e(1, 5), graph_e(2, 4), graph_e(6, 3), graph_e(7, 7),
                                    graph_e(8, 0), graph_e(9, 3)}),
              result);
}

TEST_F(UndirectedSimpleGraphTest, getEdge_WhenInDirection_ThenEdge)
{
    // given
    graph_v source = 5, destination = 9;

    test_object.add_edge_between(source, destination);
    // when
    graph_e result = test_object.get_edge(source, destination);
    // then
    EXPECT_EQ(source, result.source());
    EXPECT_EQ(destination, result.destination());
}

TEST_F(UndirectedSimpleGraphTest, getEdge_WhenReversedDirection_ThenEdge)
{
    // given
    graph_v source = 9, destination = 5;

    test_object.add_edge_between(source, destination);
    // when
    graph_e result = test_object.get_edge(destination, source);
    // then
    EXPECT_EQ(source, result.source());
    EXPECT_EQ(destination, result.destination());
}

TEST_F(UndirectedSimpleGraphTest, getEdge_WhenNotExists_ThenOutOfRange)
{
    // when
    auto exec = [&]() { return test_object.get_edge(1, 2); };
    // then
    EXPECT_THROW(exec(), std::out_of_range);
}

TEST_F(UndirectedSimpleGraphTest, addEdgeBetween_WhenNewEdge_ThenCreatedEdge)
{
    // given
    graph_ep edge_property = "asdfgh";
    // when
    graph_e result = test_object.add_edge_between(1, 5, edge_property);

    test_object.add_edge_between(1, 1);
    // then
    std::vector<graph_v> result_neighbours = test_object.neighbours(1);

    std::sort(result_neighbours.begin(), result_neighbours.end());

    ASSERT_EQ(1, result.source());
    ASSERT_EQ(5, result.destination());
    EXPECT_EQ(edge_property, test_object[result]);
    EXPECT_EQ(std::vector<graph_v>({1, 5}), result_neighbours);
    EXPECT_EQ(std::vector<graph_v>({1}), test_object.neighbours(5));
}

TEST_F(UndirectedSimpleGraphTest, addEdgeBetween_WhenDuplicatedEdge_ThenExistingEdge)
{
    // given
    graph_v source = 3, destination = 7;
    graph_e expected = test_object.add_edge_between(source, destination);
    // when
    graph_e result = test_object.add_edge_between(source, destination);
    // then
    EXPECT_EQ(expected, result);
}

TEST_F(UndirectedSimpleGraphTest, adjacentEdges_ThenOutgoingEdges)
{
    // given
    test_object.add_edge_between(1, 1);
    test_object.add_edge_between(1, 3);
    test_object.add_edge_between(1, 4);
    test_object.add_edge_between(1, 7);
    test_object.add_edge_between(1, 9);
    test_object.add_edge_between(2, 1);
    test_object.add_edge_between(6, 1);
    // when
    std::vector<graph_e> result = test_object.adjacent_edges(1);
    // then
    std::sort(result.begin(), result.end());

    EXPECT_EQ(std::vector<graph_e>({graph_e(1, 1), graph_e(1, 3), graph_e(1, 4), graph_e(1, 7),
                                    graph_e(1, 9), graph_e(2, 1), graph_e(6, 1)}),
              result);
}

TEST_F(UndirectedSimpleGraphTest, neighbours_ThenDestinationVerticesOfOutgoingEdges)
{
    // given
    test_object.add_edge_between(1, 1);
    test_object.add_edge_between(1, 3);
    test_object.add_edge_between(1, 4);
    test_object.add_edge_between(1, 7);
    test_object.add_edge_between(1, 9);
    test_object.add_edge_between(2, 1);
    test_object.add_edge_between(6, 1);
    // when
    std::vector<graph_v> result = test_object.neighbours(1);
    // then
    std::sort(result.begin(), result.end());

    EXPECT_EQ(std::vector<graph_v>({1, 2, 3, 4, 6, 7, 9}), result);
}

TEST_F(UndirectedSimpleGraphTest, outputDegree_ThenNumberOfOutgoingEdges)
{
    // given
    test_object.add_edge_between(1, 1);
    test_object.add_edge_between(1, 3);
    test_object.add_edge_between(1, 4);
    test_object.add_edge_between(1, 7);
    test_object.add_edge_between(1, 9);
    test_object.add_edge_between(2, 1);
    test_object.add_edge_between(6, 1);
    // when
    size_t result = test_object.output_degree(1);
    // then
    EXPECT_EQ(7, result);
}

TEST_F(UndirectedSimpleGraphTest, inputDegree_ThenNumberOfIncomingEdges)
{
    // given
    test_object.add_edge_between(1, 1);
    test_object.add_edge_between(3, 1);
    test_object.add_edge_between(4, 1);
    test_object.add_edge_between(7, 1);
    test_object.add_edge_between(9, 1);
    test_object.add_edge_between(1, 2);
    test_object.add_edge_between(1, 6);
    // when
    size_t result = test_object.input_degree(1);
    // then
    EXPECT_EQ(7, result);
}

TEST_F(UndirectedSimpleGraphTest, asDirected_ThenDirectedGraph)
{
    // given
    graph_v vertex = 5;
    graph_vp vertex_property = "123456";
    graph_ep edge_property = "zxcvb";
    graph_e edge = test_object.add_edge_between(1, 5);

    test_object.add_edge_between(7, 7);
    test_object.add_edge_between(2, 4);
    test_object.add_edge_between(8, 0);
    test_object.add_edge_between(6, 3);
    test_object.add_edge_between(3, 6);
    test_object.add_edge_between(9, 3);
    test_object.add_edge_between(8, 0);
    test_object[vertex] = vertex_property;
    test_object[edge] = edge_property;
    // when
    algr::directed_simple_graph<int, std::string, std::string> result = test_object.as_directed();
    // then
    std::vector<graph_v> expected_vertices = test_object.vertices();
    std::vector<graph_v> result_vertices = result.vertices();
    std::vector<graph_e> result_edges = result.edges();

    std::sort(expected_vertices.begin(), expected_vertices.end());
    std::sort(result_vertices.begin(), result_vertices.end());
    std::sort(result_edges.begin(), result_edges.end());

    ASSERT_EQ(expected_vertices, result_vertices);
    ASSERT_EQ(std::vector<graph_e>({graph_e(0, 8), graph_e(1, 5), graph_e(2, 4), graph_e(3, 6),
                                    graph_e(3, 9), graph_e(4, 2), graph_e(5, 1), graph_e(6, 3),
                                    graph_e(7, 7), graph_e(8, 0), graph_e(9, 3)}),
              result_edges);
    EXPECT_EQ(vertex_property, result[vertex]);
    EXPECT_EQ("", result[9]);
    EXPECT_EQ(edge_property, result[result.get_edge(1, 5)]);
    EXPECT_EQ(edge_property, result[result.get_edge(5, 1)]);
    EXPECT_EQ("", result[result.get_edge(8, 0)]);
}
