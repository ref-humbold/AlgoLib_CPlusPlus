/*!
 * \file multipartite_graph_test.cpp
 * \brief Tests: Structure of multipartite graph
 */
#include <gtest/gtest.h>
#include "algolib/graphs/multipartite_graph.hpp"

namespace algr = algolib::graphs;

class MultipartiteGraphTest : public ::testing::Test
{
public:
    using graph_t = algr::multipartite_graph<5, int, std::string, std::string>;
    using graph_v = graph_t::vertex_type;
    using graph_e = graph_t::edge_type;
    using graph_vp = graph_t::vertex_property_type;
    using graph_ep = graph_t::edge_property_type;

protected:
    graph_t test_object;

public:
    MultipartiteGraphTest() : test_object{graph_t({{0, 1, 2}, {3, 4}, {5, 6, 7, 8}, {9}})}
    {
        test_object.add_edge_between(0, 3);
        test_object.add_edge_between(1, 5);
        test_object.add_edge_between(2, 9);
        test_object.add_edge_between(4, 6);
        test_object.add_edge_between(7, 9);
    }

    ~MultipartiteGraphTest() override = default;
};

TEST_F(MultipartiteGraphTest, operatorBrackets_whenSettingProperty_thenProperty)
{
    // given
    graph_vp vertex_property = "x";
    graph_ep edge_property = "y";
    graph_v vertex = 2;
    graph_e edge = test_object.get_edge(0, 3);
    // when
    test_object[vertex] = vertex_property;
    test_object[edge] = edge_property;

    graph_vp result_vertex = test_object[vertex];
    graph_ep result_edge = test_object[edge];
    // then
    EXPECT_EQ(vertex_property, result_vertex);
    EXPECT_EQ(edge_property, result_edge);
}

TEST_F(MultipartiteGraphTest, verticesCount_thenNumberOfVertices)
{
    // when
    size_t result = test_object.vertices_count();
    // then
    EXPECT_EQ(10, result);
}

TEST_F(MultipartiteGraphTest, vertices_thenAllVertices)
{
    // when
    std::vector<graph_v> result = test_object.vertices();
    // then
    std::sort(result.begin(), result.end());

    EXPECT_EQ(std::vector<graph_v>({0, 1, 2, 3, 4, 5, 6, 7, 8, 9}), result);
}

TEST_F(MultipartiteGraphTest, get_verticesFromGroup_whenValidGroup_thenVertices)
{
    // when
    std::vector<graph_v> result = test_object.vertices_from_group(2);
    // then
    std::sort(result.begin(), result.end());

    EXPECT_EQ(std::vector<graph_v>({5, 6, 7, 8}), result);
}

TEST_F(MultipartiteGraphTest, verticesFromGroup_whenInvalidGroup_thenOutOfRange)
{
    // when
    auto execution = [&]() { return test_object.vertices_from_group(14); };
    // then
    EXPECT_THROW(execution(), std::out_of_range);
}

TEST_F(MultipartiteGraphTest, addVertex_whenNewVertex_thenTrue)
{
    // given
    graph_v new_vertex = 13;
    graph_vp vertex_property = "qwerty";
    // when
    bool result = test_object.add_vertex(4, new_vertex, vertex_property);
    // then
    ASSERT_TRUE(result);
    EXPECT_EQ(11, test_object.vertices_count());
    EXPECT_EQ(std::vector<graph_v>(), test_object.neighbours(new_vertex));
    EXPECT_EQ(vertex_property, test_object[new_vertex]);
}

TEST_F(MultipartiteGraphTest, addVertex_whenExistingVertex_thenFalse)
{
    // given
    graph_v vertex = 6;
    graph_vp vertex_property = "qwerty";

    test_object[vertex] = vertex_property;
    // when
    bool result = test_object.add_vertex(3, vertex, "xyz");
    // then
    ASSERT_FALSE(result);
    EXPECT_EQ(10, test_object.vertices_count());
    EXPECT_EQ(vertex_property, test_object[vertex]);
}

TEST_F(MultipartiteGraphTest, addVertex_whenInvalidGroup_thenOutOfRange)
{
    // when
    auto execution = [&]() { return test_object.add_vertex(-3, 19); };
    // then
    EXPECT_THROW(execution(), std::out_of_range);
}

TEST_F(MultipartiteGraphTest, edgesCount_thenNumberOfEdges)
{
    // when
    size_t result = test_object.edges_count();
    // then
    EXPECT_EQ(5, result);
}

TEST_F(MultipartiteGraphTest, edges_thenAllEdges)
{
    // when
    std::vector<graph_e> result = test_object.edges();
    // then
    std::sort(result.begin(), result.end());

    EXPECT_EQ(std::vector<graph_e>(
                      {graph_e(0, 3), graph_e(1, 5), graph_e(2, 9), graph_e(4, 6), graph_e(7, 9)}),
              result);
}

TEST_F(MultipartiteGraphTest, getEdge_whenExists_thenEdge)
{
    // given
    graph_v source = 2, destination = 9;
    // when
    graph_e result = test_object.get_edge(source, destination);
    // then
    EXPECT_EQ(source, result.source());
    EXPECT_EQ(destination, result.destination());
}

TEST_F(MultipartiteGraphTest, addEdgeBetween_whenNewEdge_thenCreatedEdge)
{
    // given
    graph_v vertex1 = 2, vertex2 = 8;
    graph_ep edge_property = "asdfgh";
    // when
    graph_e result = test_object.add_edge_between(vertex1, vertex2, edge_property);
    // then
    ASSERT_EQ(vertex1, result.source());
    ASSERT_EQ(vertex2, result.destination());
    EXPECT_EQ(edge_property, test_object[result]);
    EXPECT_EQ(std::vector<graph_v>({vertex1}), test_object.neighbours(vertex2));
}

TEST_F(MultipartiteGraphTest, addEdgeBetween_whenDuplicatedEdge_thenExistingEdge)
{
    // given
    graph_v source = 8, destination = 3;
    graph_e expected = test_object.add_edge_between(source, destination);
    // when
    graph_e result = test_object.add_edge_between(source, destination);
    // then
    EXPECT_EQ(expected, result);
}

TEST_F(MultipartiteGraphTest, addEdgeBetween_when_sameGroup_thenGraphPartitionError)
{
    // when
    auto execution = [&]() { return test_object.add_edge_between(5, 8); };
    // then
    EXPECT_THROW(execution(), algr::graph_partition_error);
}

TEST_F(MultipartiteGraphTest, neighbours_thenDestinationVerticesOfOutgoingEdges)
{
    // when
    std::vector<graph_v> result = test_object.neighbours(9);
    // then
    std::sort(result.begin(), result.end());

    EXPECT_EQ(std::vector<graph_v>({2, 7}), result);
}

TEST_F(MultipartiteGraphTest, adjacentEdges_thenOutgoingEdges)
{
    // when
    std::vector<graph_e> result = test_object.adjacent_edges(9);
    // then
    std::sort(result.begin(), result.end());

    EXPECT_EQ(std::vector<graph_e>({graph_e(2, 9), graph_e(7, 9)}), result);
}

TEST_F(MultipartiteGraphTest, outputDegree_thenNumberOfOutgoingEdges)
{
    // when
    size_t result = test_object.output_degree(9);
    // then
    EXPECT_EQ(2, result);
}

TEST_F(MultipartiteGraphTest, inputDegree_thenNumberOfIncomingEdges)
{
    // when
    size_t result = test_object.input_degree(9);
    // then
    EXPECT_EQ(2, result);
}
