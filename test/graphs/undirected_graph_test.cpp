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
    using graph_vi = graph_t::vertex_id_type;
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

TEST_F(UndirectedSimpleGraphTest, operatorBrackets_WhenVertexExists_ThenVertex)
{
    // given
    graph_vi vertex_id = 4;
    // when
    graph_v result = test_object[vertex_id];
    // then
    EXPECT_EQ(vertex_id, result.id());
}

TEST_F(UndirectedSimpleGraphTest, operatorBrackets_WhenVertexNotExists_ThenOutOfRange)
{
    // when
    auto exec = [&]() { return test_object[16]; };
    // then
    EXPECT_THROW(exec(), std::out_of_range);
}

TEST_F(UndirectedSimpleGraphTest, operatorBrackets_WhenEdgeInDirection_ThenEdge)
{
    // given
    graph_v source(9), destination(5);

    test_object.add_edge_between(source, destination);
    // when
    graph_e result = test_object[std::make_pair(source, destination)];
    // then
    EXPECT_EQ(source, result.source());
    EXPECT_EQ(destination, result.destination());
}

TEST_F(UndirectedSimpleGraphTest, operatorBrackets_WhenEdgeInReversedDirection_ThenEdge)
{
    // given
    graph_v source(9), destination(5);

    test_object.add_edge_between(source, destination);
    // when
    graph_e result = test_object[std::make_pair(destination, source)];
    // then
    EXPECT_EQ(source, result.source());
    EXPECT_EQ(destination, result.destination());
}

TEST_F(UndirectedSimpleGraphTest, operatorBrackets_WhenEdgeNotExists_ThenOutOfRange)
{
    // when
    auto exec = [&]() { return test_object[std::make_pair(1, 2)]; };
    // then
    EXPECT_THROW(exec(), std::out_of_range);
}

TEST_F(UndirectedSimpleGraphTest, propertiesOperatorBrackets_WhenSettingProperty_ThenProperty)
{
    // given
    graph_vp vertex_property = "x";
    graph_ep edge_property = "y";
    graph_v vertex(2);
    graph_e edge = test_object.add_edge_between(graph_v(0), graph_v(1));
    // when
    test_object.properties()[vertex] = vertex_property;
    test_object.properties()[edge] = edge_property;

    graph_vp result_vertex = test_object.properties()[vertex];
    graph_ep result_edge = test_object.properties()[edge];
    // then
    EXPECT_EQ(vertex_property, result_vertex);
    EXPECT_EQ(edge_property, result_edge);
}

TEST_F(UndirectedSimpleGraphTest, propertiesOperatorBrackets_WhenNoProperty_ThenDefault)
{
    // given
    graph_v vertex(4);
    graph_e edge = test_object.add_edge_between(graph_v(6), graph_v(7));
    // when
    graph_vp result_vertex = test_object.properties()[vertex];
    graph_ep result_edge = test_object.properties()[edge];
    // then
    EXPECT_EQ("", result_vertex);
    EXPECT_EQ("", result_edge);
}

TEST_F(UndirectedSimpleGraphTest, propertiesOperatorBrackets_WhenNotExisting_ThenInvalidArgument)
{
    // when
    auto exec_vertex = [&]() { return test_object.properties()[graph_v(14)]; };
    auto exec_edge1 = [&]() { return test_object.properties()[graph_e(graph_v(2), graph_v(8))]; };
    auto exec_edge2 = [&]() { return test_object.properties()[graph_e(graph_v(0), graph_v(-1))]; };
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

TEST_F(UndirectedSimpleGraphTest, edgesCount_ThenNumberOfEdges)
{
    // given
    test_object.add_edge_between(graph_v(7), graph_v(7));
    test_object.add_edge_between(graph_v(1), graph_v(5));
    test_object.add_edge_between(graph_v(2), graph_v(4));
    test_object.add_edge_between(graph_v(8), graph_v(0));
    test_object.add_edge_between(graph_v(6), graph_v(3));
    test_object.add_edge_between(graph_v(9), graph_v(3));
    // when
    size_t result = test_object.edges_count();
    // then
    EXPECT_EQ(6, result);
}

TEST_F(UndirectedSimpleGraphTest, vertices_ThenAllVertices)
{
    // when
    std::vector<graph_v> result = test_object.vertices();
    // then
    std::sort(result.begin(), result.end());

    EXPECT_EQ(std::vector<graph_v>({graph_v(0), graph_v(1), graph_v(2), graph_v(3), graph_v(4),
                                    graph_v(5), graph_v(6), graph_v(7), graph_v(8), graph_v(9)}),
              result);
}

TEST_F(UndirectedSimpleGraphTest, edges_ThenAllEdges)
{
    // given
    test_object.add_edge_between(graph_v(7), graph_v(7));
    test_object.add_edge_between(graph_v(1), graph_v(5));
    test_object.add_edge_between(graph_v(2), graph_v(4));
    test_object.add_edge_between(graph_v(8), graph_v(0));
    test_object.add_edge_between(graph_v(6), graph_v(3));
    test_object.add_edge_between(graph_v(9), graph_v(3));
    // when
    std::vector<graph_e> result = test_object.edges();
    // then
    std::sort(result.begin(), result.end());

    EXPECT_EQ(std::vector<graph_e>(
                      {graph_e(graph_v(1), graph_v(5)), graph_e(graph_v(2), graph_v(4)),
                       graph_e(graph_v(6), graph_v(3)), graph_e(graph_v(7), graph_v(7)),
                       graph_e(graph_v(8), graph_v(0)), graph_e(graph_v(9), graph_v(3))}),
              result);
}

TEST_F(UndirectedSimpleGraphTest, adjacentEdges_ThenOutgoingEdges)
{
    // given
    test_object.add_edge_between(graph_v(1), graph_v(1));
    test_object.add_edge_between(graph_v(1), graph_v(3));
    test_object.add_edge_between(graph_v(1), graph_v(4));
    test_object.add_edge_between(graph_v(1), graph_v(7));
    test_object.add_edge_between(graph_v(1), graph_v(9));
    test_object.add_edge_between(graph_v(2), graph_v(1));
    test_object.add_edge_between(graph_v(6), graph_v(1));
    // when
    std::vector<graph_e> result = test_object.adjacent_edges(graph_v(1));
    // then
    std::sort(result.begin(), result.end());

    EXPECT_EQ(
            std::vector<graph_e>({graph_e(graph_v(1), graph_v(1)), graph_e(graph_v(1), graph_v(3)),
                                  graph_e(graph_v(1), graph_v(4)), graph_e(graph_v(1), graph_v(7)),
                                  graph_e(graph_v(1), graph_v(9)), graph_e(graph_v(2), graph_v(1)),
                                  graph_e(graph_v(6), graph_v(1))}),
            result);
}

TEST_F(UndirectedSimpleGraphTest, neighbours_ThenDestinationVerticesOfOutgoingEdges)
{
    // given
    test_object.add_edge_between(graph_v(1), graph_v(1));
    test_object.add_edge_between(graph_v(1), graph_v(3));
    test_object.add_edge_between(graph_v(1), graph_v(4));
    test_object.add_edge_between(graph_v(1), graph_v(7));
    test_object.add_edge_between(graph_v(1), graph_v(9));
    test_object.add_edge_between(graph_v(2), graph_v(1));
    test_object.add_edge_between(graph_v(6), graph_v(1));
    // when
    std::vector<graph_v> result = test_object.neighbours(graph_v(1));
    // then
    std::sort(result.begin(), result.end());

    EXPECT_EQ(std::vector<graph_v>({graph_v(1), graph_v(2), graph_v(3), graph_v(4), graph_v(6),
                                    graph_v(7), graph_v(9)}),
              result);
}

TEST_F(UndirectedSimpleGraphTest, outputDegree_ThenNumberOfOutgoingEdges)
{
    // given
    test_object.add_edge_between(graph_v(1), graph_v(1));
    test_object.add_edge_between(graph_v(1), graph_v(3));
    test_object.add_edge_between(graph_v(1), graph_v(4));
    test_object.add_edge_between(graph_v(1), graph_v(7));
    test_object.add_edge_between(graph_v(1), graph_v(9));
    test_object.add_edge_between(graph_v(2), graph_v(1));
    test_object.add_edge_between(graph_v(6), graph_v(1));
    // when
    size_t result = test_object.output_degree(graph_v(1));
    // then
    EXPECT_EQ(7, result);
}

TEST_F(UndirectedSimpleGraphTest, inputDegree_ThenNumberOfIncomingEdges)
{
    // given
    test_object.add_edge_between(graph_v(1), graph_v(1));
    test_object.add_edge_between(graph_v(3), graph_v(1));
    test_object.add_edge_between(graph_v(4), graph_v(1));
    test_object.add_edge_between(graph_v(7), graph_v(1));
    test_object.add_edge_between(graph_v(9), graph_v(1));
    test_object.add_edge_between(graph_v(1), graph_v(2));
    test_object.add_edge_between(graph_v(1), graph_v(6));
    // when
    size_t result = test_object.input_degree(graph_v(1));
    // then
    EXPECT_EQ(7, result);
}

TEST_F(UndirectedSimpleGraphTest, addVertex_WhenNewVertex_ThenTrue)
{
    // given
    graph_vi new_vertex_id = 13;
    graph_vp vertex_property = "qwerty";
    // when
    graph_v result = test_object.add_vertex(new_vertex_id, vertex_property);
    // then
    ASSERT_EQ(new_vertex_id, result.id());
    EXPECT_EQ(11, test_object.vertices_count());
    EXPECT_EQ(std::vector<graph_v>(), test_object.neighbours(result));
    EXPECT_EQ(vertex_property, test_object.properties()[result]);
}

TEST_F(UndirectedSimpleGraphTest, addVertex_WhenExistingVertex_ThenInvalidArgument)
{
    // given
    graph_v vertex(6);
    graph_vp vertex_property = "qwerty";

    test_object.properties()[vertex] = vertex_property;
    // when
    auto exec = [&]() { return test_object.add_vertex(vertex, "abcdefg"); };
    // then
    ASSERT_THROW(exec(), std::invalid_argument);
    EXPECT_EQ(10, test_object.vertices_count());
    EXPECT_EQ(vertex_property, test_object.properties()[vertex]);
}

TEST_F(UndirectedSimpleGraphTest, addEdgeBetween_WhenNewEdge_ThenCreatedEdge)
{
    // given
    graph_v source(1), destination(5);
    graph_ep edge_property = "asdfgh";
    // when
    graph_e result = test_object.add_edge_between(source, destination, edge_property);

    test_object.add_edge_between(source, graph_v(1));
    // then
    std::vector<graph_v> result_neighbours = test_object.neighbours(source);

    std::sort(result_neighbours.begin(), result_neighbours.end());

    ASSERT_EQ(source, result.source());
    ASSERT_EQ(destination, result.destination());
    EXPECT_EQ(edge_property, test_object.properties()[result]);
    EXPECT_EQ(std::vector<graph_v>({source, destination}), result_neighbours);
    EXPECT_EQ(std::vector<graph_v>({source}), test_object.neighbours(destination));
}

TEST_F(UndirectedSimpleGraphTest, addEdgeBetween_WhenDuplicatedEdge_ThenInvalidArgument)
{
    // given
    graph_v source(3), destination(7);

    test_object.add_edge_between(source, destination);
    // when
    auto exec = [&]() { return test_object.add_edge_between(source, destination); };
    // then
    EXPECT_THROW(exec(), std::invalid_argument);
}

TEST_F(UndirectedSimpleGraphTest, asDirected_ThenDirectedGraph)
{
    // given
    graph_v vertex(5);
    graph_vp vertex_property = "123456";
    graph_ep edge_property = "zxcvb";
    graph_e edge = test_object.add_edge_between(graph_v(1), graph_v(5));

    test_object.add_edge_between(graph_v(7), graph_v(7));
    test_object.add_edge_between(graph_v(2), graph_v(4));
    test_object.add_edge_between(graph_v(8), graph_v(0));
    test_object.add_edge_between(graph_v(6), graph_v(3));
    test_object.add_edge_between(graph_v(9), graph_v(3));
    test_object.properties()[vertex] = vertex_property;
    test_object.properties()[edge] = edge_property;
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
    ASSERT_EQ(
            std::vector<graph_e>({graph_e(graph_v(0), graph_v(8)), graph_e(graph_v(1), graph_v(5)),
                                  graph_e(graph_v(2), graph_v(4)), graph_e(graph_v(3), graph_v(6)),
                                  graph_e(graph_v(3), graph_v(9)), graph_e(graph_v(4), graph_v(2)),
                                  graph_e(graph_v(5), graph_v(1)), graph_e(graph_v(6), graph_v(3)),
                                  graph_e(graph_v(7), graph_v(7)), graph_e(graph_v(8), graph_v(0)),
                                  graph_e(graph_v(9), graph_v(3))}),
            result_edges);
    EXPECT_EQ(vertex_property, result.properties()[vertex]);
    EXPECT_EQ("", result.properties()[graph_v(9)]);
    EXPECT_EQ(edge_property, result.properties()[result[std::make_pair(graph_v(1), graph_v(5))]]);
    EXPECT_EQ(edge_property, result.properties()[result[std::make_pair(graph_v(5), graph_v(1))]]);
    EXPECT_EQ("", result.properties()[result[std::make_pair(graph_v(8), graph_v(0))]]);
}
