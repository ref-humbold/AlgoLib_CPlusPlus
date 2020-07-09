/*!
 * \file lowest_common_ancestor_test.cpp
 * \brief Tests: Algorithm for lowest common ancestor
 */
#include <gtest/gtest.h>
#include "algolib/graphs/algorithms/lowest_common_ancestor.hpp"

namespace algr = algolib::graphs;

class LowestCommonAncestorTest : public ::testing::Test
{
public:
    using vertex_t = algr::lowest_common_ancestor<>::vertex_type;

protected:
    algr::tree_graph<> tree;
    algr::lowest_common_ancestor<> test_object;

public:
    LowestCommonAncestorTest()
        : tree{algr::tree_graph<>(0)}, test_object{algr::lowest_common_ancestor<>(tree, 0)}
    {
        tree.add_vertex(1, 0);
        tree.add_vertex(2, 0);
        tree.add_vertex(3, 1);
        tree.add_vertex(4, 1);
        tree.add_vertex(5, 1);
        tree.add_vertex(6, 2);
        tree.add_vertex(7, 4);
        tree.add_vertex(8, 6);
        tree.add_vertex(9, 6);
    }

    ~LowestCommonAncestorTest() override = default;
};

TEST_F(LowestCommonAncestorTest, find_whenSameVertex_thenVertexIsLCA)
{
    // given
    vertex_t vertex = 6;
    // when
    vertex_t result = test_object.find(vertex, vertex);
    // then
    EXPECT_EQ(vertex, result);
}

TEST_F(LowestCommonAncestorTest, find_whenVerticesInDifferentSubtrees_thenLCA)
{
    // when
    vertex_t result = test_object.find(5, 7);
    // then
    EXPECT_EQ(1, result);
}

TEST_F(LowestCommonAncestorTest, find_whenVerticesSwapped_thenSameLCA)
{
    // when
    vertex_t result1 = test_object.find(5, 7);
    vertex_t result2 = test_object.find(7, 5);
    // then
    EXPECT_EQ(1, result1);
    EXPECT_EQ(result1, result2);
}

TEST_F(LowestCommonAncestorTest, find_whenRootIsCommonAncestor_thenRoot)
{
    // when
    vertex_t result = test_object.find(3, 9);
    // then
    EXPECT_EQ(test_object.root(), result);
}

TEST_F(LowestCommonAncestorTest, find_whenVerticesAreOnSamePathFromRoot_thenLCAIsCloserToRoot)
{
    // given
    vertex_t vertex1 = 8, vertex2 = 2;
    // when
    vertex_t result = test_object.find(vertex1, vertex2);
    // then
    EXPECT_EQ(vertex2, result);
}

TEST_F(LowestCommonAncestorTest, find_whenRootIsOneOfVertices_thenRoot)
{
    // when
    vertex_t result = test_object.find(4, test_object.root());
    // then
    EXPECT_EQ(test_object.root(), result);
}
