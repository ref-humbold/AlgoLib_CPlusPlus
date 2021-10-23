/*!
 * \file multipartite_graph_test.cpp
 * \brief Tests: Structure of multipartite graph
 */
#include <gtest/gtest.h>
#include "algolib/graphs_new/multipartite_graph.hpp"

namespace algr = algolib::graphs;

class MultipartiteGraphTest : public ::testing::Test
{
public:
    using graph_t = algr::multipartite_graph<5, int, std::string, std::string>;
    using graph_vi = graph_t::vertex_id_type;
    using graph_v = graph_t::vertex_type;
    using graph_e = graph_t::edge_type;
    using graph_vp = graph_t::vertex_property_type;
    using graph_ep = graph_t::edge_property_type;

protected:
    graph_t test_object;

public:
    MultipartiteGraphTest()
        : test_object{graph_t({std::vector<graph_vi>({0, 1, 2}), std::vector<graph_vi>({3, 4}),
                               std::vector<graph_vi>({5, 6, 7, 8}), std::vector<graph_vi>({9}),
                               std::vector<graph_vi>()})}
    {
        test_object.add_edge_between(graph_v(0), graph_v(3));
        test_object.add_edge_between(graph_v(1), graph_v(5));
        test_object.add_edge_between(graph_v(2), graph_v(9));
        test_object.add_edge_between(graph_v(4), graph_v(6));
        test_object.add_edge_between(graph_v(7), graph_v(9));
    }

    ~MultipartiteGraphTest() override = default;
};

TEST_F(MultipartiteGraphTest, operatorBrackets_WhenVertexExists_ThenVertex)
{
    // given
    graph_vi vertex_id = 5;
    // when
    graph_v result = test_object[vertex_id];
    // then
    EXPECT_EQ(vertex_id, result.id());
}

TEST_F(MultipartiteGraphTest, operatorBrackets_WhenEdgeExists_ThenEdge)
{
    // given
    graph_v source(2), destination(9);
    // when
    graph_e result = test_object[std::make_pair(source, destination)];
    // then
    EXPECT_EQ(source, result.source());
    EXPECT_EQ(destination, result.destination());
}

TEST_F(MultipartiteGraphTest, propertiesOperatorBrackets_WhenSettingProperty_ThenProperty)
{
    // given
    graph_vp vertex_property = "x";
    graph_ep edge_property = "y";
    graph_v vertex(2);
    graph_e edge = test_object[std::make_pair(0, 3)];
    // when
    test_object.properties()[vertex] = vertex_property;
    test_object.properties()[edge] = edge_property;

    graph_vp result_vertex = test_object.properties()[vertex];
    graph_ep result_edge = test_object.properties()[edge];
    // then
    EXPECT_EQ(vertex_property, result_vertex);
    EXPECT_EQ(edge_property, result_edge);
}

TEST_F(MultipartiteGraphTest, verticesCount_ThenNumberOfVertices)
{
    // when
    size_t result = test_object.vertices_count();
    // then
    EXPECT_EQ(10, result);
}

TEST_F(MultipartiteGraphTest, edgesCount_ThenNumberOfEdges)
{
    // when
    size_t result = test_object.edges_count();
    // then
    EXPECT_EQ(5, result);
}

TEST_F(MultipartiteGraphTest, vertices_ThenAllVertices)
{
    // when
    std::vector<graph_v> result = test_object.vertices();
    // then
    std::sort(result.begin(), result.end());

    EXPECT_EQ(std::vector<graph_v>({graph_v(0), graph_v(1), graph_v(2), graph_v(3), graph_v(4),
                                    graph_v(5), graph_v(6), graph_v(7), graph_v(8), graph_v(9)}),
              result);
}

TEST_F(MultipartiteGraphTest, edges_ThenAllEdges)
{
    // when
    std::vector<graph_e> result = test_object.edges();
    // then
    std::sort(result.begin(), result.end());

    EXPECT_EQ(
            std::vector<graph_e>({graph_e(graph_v(0), graph_v(3)), graph_e(graph_v(1), graph_v(5)),
                                  graph_e(graph_v(2), graph_v(9)), graph_e(graph_v(4), graph_v(6)),
                                  graph_e(graph_v(7), graph_v(9))}),
            result);
}

TEST_F(MultipartiteGraphTest, neighbours_ThenDestinationVerticesOfOutgoingEdges)
{
    // when
    std::vector<graph_v> result = test_object.neighbours(graph_v(9));
    // then
    std::sort(result.begin(), result.end());

    EXPECT_EQ(std::vector<graph_v>({graph_v(2), graph_v(7)}), result);
}

TEST_F(MultipartiteGraphTest, adjacentEdges_ThenOutgoingEdges)
{
    // when
    std::vector<graph_e> result = test_object.adjacent_edges(graph_v(9));
    // then
    std::sort(result.begin(), result.end());

    EXPECT_EQ(std::vector<graph_e>(
                      {graph_e(graph_v(2), graph_v(9)), graph_e(graph_v(7), graph_v(9))}),
              result);
}

TEST_F(MultipartiteGraphTest, outputDegree_ThenNumberOfOutgoingEdges)
{
    // when
    size_t result = test_object.output_degree(graph_v(9));
    // then
    EXPECT_EQ(2, result);
}

TEST_F(MultipartiteGraphTest, inputDegree_ThenNumberOfIncomingEdges)
{
    // when
    size_t result = test_object.input_degree(graph_v(9));
    // then
    EXPECT_EQ(2, result);
}

TEST_F(MultipartiteGraphTest, addVertex_WhenNewVertex_ThenTrue)
{
    // given
    graph_vi new_vertex_id = 13;
    graph_vp vertex_property = "qwerty";
    // when
    graph_v result = test_object.add_vertex(4, new_vertex_id, vertex_property);
    // then
    ASSERT_EQ(new_vertex_id, result.id());
    EXPECT_EQ(11, test_object.vertices_count());
    EXPECT_EQ(std::vector<graph_v>(), test_object.neighbours(result));
    EXPECT_EQ(vertex_property, test_object.properties()[result]);
}

TEST_F(MultipartiteGraphTest, verticesFromGroup_WhenValidGroup_ThenVertices)
{
    // when
    std::vector<graph_v> result = test_object.vertices_from_group(2);
    // then
    std::sort(result.begin(), result.end());

    EXPECT_EQ(std::vector<graph_v>({graph_v(5), graph_v(6), graph_v(7), graph_v(8)}), result);
}

TEST_F(MultipartiteGraphTest, verticesFromGroup_WhenInvalidGroup_ThenOutOfRange)
{
    // when
    auto exec = [&]() { return test_object.vertices_from_group(14); };
    // then
    EXPECT_THROW(exec(), std::out_of_range);
}

TEST_F(MultipartiteGraphTest, addVertex_WhenExistingVertex_ThenInvalidArgument)
{
    // given
    graph_v vertex(6);
    graph_vp vertex_property = "qwerty";

    test_object.properties()[vertex] = vertex_property;
    // when
    auto exec = [&]() { return test_object.add_vertex(3, vertex, "xyz"); };
    // then
    ASSERT_THROW(exec(), std::invalid_argument);
    EXPECT_EQ(10, test_object.vertices_count());
    EXPECT_EQ(vertex_property, test_object.properties()[vertex]);
}

TEST_F(MultipartiteGraphTest, addVertex_WhenInvalidGroup_ThenOutOfRange)
{
    // when
    auto exec = [&]() { return test_object.add_vertex(-3, 19); };
    // then
    EXPECT_THROW(exec(), std::out_of_range);
}

TEST_F(MultipartiteGraphTest, addEdgeBetween_WhenNewEdge_ThenCreatedEdge)
{
    // given
    graph_v source(2), destination(8);
    graph_ep edge_property = "asdfgh";
    // when
    graph_e result = test_object.add_edge_between(source, destination, edge_property);
    // then
    ASSERT_EQ(source, result.source());
    ASSERT_EQ(destination, result.destination());
    EXPECT_EQ(edge_property, test_object.properties()[result]);
    EXPECT_EQ(std::vector<graph_v>({source}), test_object.neighbours(destination));
}

TEST_F(MultipartiteGraphTest, addEdgeBetween_WhenDuplicatedEdge_ThenInvalidArgument)
{
    // given
    graph_v source(8), destination(3);

    test_object.add_edge_between(source, destination);
    // when
    auto exec = [&]() { return test_object.add_edge_between(source, destination); };
    // then
    ASSERT_THROW(exec(), std::invalid_argument);
}

TEST_F(MultipartiteGraphTest, addEdgeBetween_When_sameGroup_ThenGraphPartitionError)
{
    // when
    auto exec = [&]() { return test_object.add_edge_between(graph_v(5), graph_v(8)); };
    // then
    EXPECT_THROW(exec(), algr::graph_partition_error);
}
