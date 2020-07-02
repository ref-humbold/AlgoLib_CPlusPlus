//! Tests: Tree graph structure
#include <gtest/gtest.h>
#include "algolib/graphs/tree_graph.hpp"

namespace algr = algolib::graphs;

class TreeGraphTest : public ::testing::Test
{
public:
    using graph_t = algr::tree_graph<int, std::string, std::string>;
    using graph_v = graph_t::vertex_type;
    using graph_e = graph_t::edge_type;
    using graph_vp = graph_t::vertex_property_type;
    using graph_ep = graph_t::edge_property_type;

protected:
    graph_t test_object;

public:
    TreeGraphTest() : test_object{graph_t(0)}
    {
        test_object.add_vertex(1, 0);
        test_object.add_vertex(2, 0);
        test_object.add_vertex(3, 0);
        test_object.add_vertex(4, 1);
        test_object.add_vertex(5, 1);
        test_object.add_vertex(6, 2);
        test_object.add_vertex(7, 2);
    }

    virtual ~TreeGraphTest() = default;
};

TEST_F(TreeGraphTest, operatorBrackets_whenSettingProperty_thenProperty)
{
    // given
    graph_vp vertex_property = "x";
    graph_ep edge_property = "y";
    graph_v vertex = 2;
    graph_e edge = test_object.get_edge(6, 2);
    // when
    test_object[vertex] = vertex_property;
    test_object[edge] = edge_property;

    graph_vp result_vertex = test_object[vertex];
    graph_ep result_edge = test_object[edge];
    // then
    EXPECT_EQ(vertex_property, result_vertex);
    EXPECT_EQ(edge_property, result_edge);
}

TEST_F(TreeGraphTest, verticesCount_thenNumberOfVertices)
{
    // when
    size_t result = test_object.vertices_count();
    // then
    EXPECT_EQ(8, result);
}

TEST_F(TreeGraphTest, vertices_thenAllVertices)
{
    // when
    std::vector<graph_v> result = test_object.vertices();
    // then
    std::sort(result.begin(), result.end());

    EXPECT_EQ(std::vector<graph_v>({0, 1, 2, 3, 4, 5, 6, 7}), result);
}

TEST_F(TreeGraphTest, addVertex_whenNewVertex_thenCreatedEdge)
{
    // given
    graph_v new_vertex = 13, neighbour = 5;
    graph_vp vertex_property = "qwerty";
    graph_ep edge_property = "asdfg";
    // when
    graph_e result = test_object.add_vertex(new_vertex, neighbour, vertex_property, edge_property);
    // then
    ASSERT_EQ(new_vertex, result.source());
    ASSERT_EQ(neighbour, result.destination());
    EXPECT_EQ(9, test_object.vertices_count());
    EXPECT_EQ(std::vector<graph_v>({5}), test_object.neighbours(new_vertex));
    EXPECT_EQ(vertex_property, test_object[new_vertex]);
    EXPECT_EQ(edge_property, test_object[result]);
}

TEST_F(TreeGraphTest, addVertex_whenExistingVertex_thenInvalidArgument)
{
    // given
    graph_v vertex = 6;
    graph_vp vertex_property = "qwerty";

    test_object[vertex] = vertex_property;
    // when
    auto exec = [&]() { return test_object.add_vertex(vertex, 3, "abcdefg", "xyz"); };
    // then
    ASSERT_THROW(exec(), std::invalid_argument);
    EXPECT_EQ(8, test_object.vertices_count());
    EXPECT_EQ(vertex_property, test_object[vertex]);
}

TEST_F(TreeGraphTest, edgesCount_thenNumberOfEdges)
{
    // when
    size_t result = test_object.edges_count();
    // then
    EXPECT_EQ(7, result);
}

TEST_F(TreeGraphTest, edges_thenAllEdges)
{
    // when
    std::vector<graph_e> result = test_object.edges();
    // then
    std::sort(result.begin(), result.end());

    EXPECT_EQ(std::vector<graph_e>({graph_e(1, 0), graph_e(2, 0), graph_e(3, 0), graph_e(4, 1),
                                    graph_e(5, 1), graph_e(6, 2), graph_e(7, 2)}),
              result);
}

TEST_F(TreeGraphTest, getEdge_whenInDirection_thenEdge)
{
    // given
    graph_v source = 7, destination = 2;
    // when
    graph_e result = test_object.get_edge(source, destination);
    // then
    EXPECT_EQ(source, result.source());
    EXPECT_EQ(destination, result.destination());
}

TEST_F(TreeGraphTest, neighbours_thenDestinationVerticesOfOutgoingEdges)
{
    // when
    std::vector<graph_v> result = test_object.neighbours(1);
    // then
    std::sort(result.begin(), result.end());

    EXPECT_EQ(std::vector<graph_v>({0, 4, 5}), result);
}

TEST_F(TreeGraphTest, adjacentEdges_thenOutgoingEdges)
{
    // when
    std::vector<graph_e> result = test_object.adjacent_edges(1);
    // then
    std::sort(result.begin(), result.end());

    EXPECT_EQ(std::vector<graph_e>({graph_e(1, 0), graph_e(4, 1), graph_e(5, 1)}), result);
}

TEST_F(TreeGraphTest, outputDegree_thenNumberOfOutgoingEdges)
{
    // when
    size_t result = test_object.output_degree(1);
    // then
    EXPECT_EQ(3, result);
}

TEST_F(TreeGraphTest, inputDegree_thenNumberOfIncomingEdges)
{
    // when
    size_t result = test_object.input_degree(1);
    // then
    EXPECT_EQ(3, result);
}
