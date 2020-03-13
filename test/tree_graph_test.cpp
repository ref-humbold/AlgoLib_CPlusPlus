//! Tests: Tree graph structure
#include <gtest/gtest.h>
#include "algolib/graphs/tree_graph.hpp"

namespace algr = algolib::graphs;

class TreeGraphTest : public ::testing::Test
{
protected:
    algr::tree_graph test_object;

public:
    TreeGraphTest()
        : test_object{algr::tree_graph(
                10, {std::make_pair(0, 6), std::make_pair(1, 2), std::make_pair(2, 3),
                     std::make_pair(3, 4), std::make_pair(4, 5), std::make_pair(6, 4),
                     std::make_pair(7, 3), std::make_pair(8, 3), std::make_pair(9, 7)})}
    {
    }

    virtual ~TreeGraphTest() = default;
};

TEST_F(TreeGraphTest, addVertex_whenOneNeighbour_thenAdded)
{
    // when
    vertex_t result = test_object.add_vertex({2});
    // then
    ASSERT_EQ(10, result);
    EXPECT_EQ(std::vector<vertex_t>({2}), test_object.get_neighbours(result));
}

TEST_F(TreeGraphTest, addVertex_whenNoNeighbours_thenNotConnectedException)
{
    // when - then
    EXPECT_THROW(test_object.add_vertex({}), algr::not_connected_exception);
}

TEST_F(TreeGraphTest, addVertex_whenManyNeighbours_thenCycleException)
{
    // when - then
    EXPECT_THROW(test_object.add_vertex({2, 9, 5}), algr::cycle_exception);
}

TEST_F(TreeGraphTest, addEdge_whenConnectsExistingVertices_thenCycleException)
{
    // when - then
    EXPECT_THROW(test_object.add_edge(5, 1), algr::cycle_exception);
}
