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
        : tree{algr::tree_graph<>(0)}, test_object{algr::lowest_common_ancestor<>(tree, tree[0])}
    {
        tree.add_vertex(1, tree[0]);
        tree.add_vertex(2, tree[0]);
        tree.add_vertex(3, tree[1]);
        tree.add_vertex(4, tree[1]);
        tree.add_vertex(5, tree[1]);
        tree.add_vertex(6, tree[2]);
        tree.add_vertex(7, tree[4]);
        tree.add_vertex(8, tree[6]);
        tree.add_vertex(9, tree[6]);
    }

    ~LowestCommonAncestorTest() override = default;
};

TEST_F(LowestCommonAncestorTest, find_WhenSameVertex_ThenVertexIsLCA)
{
    // given
    vertex_t vertex = tree[6];
    // when
    vertex_t result = test_object.find(vertex, vertex);
    // then
    EXPECT_EQ(vertex, result);
}

TEST_F(LowestCommonAncestorTest, find_WhenVerticesInDifferentSubtrees_ThenLCA)
{
    // when
    vertex_t result = test_object.find(tree[5], tree[7]);
    // then
    EXPECT_EQ(tree[1], result);
}

TEST_F(LowestCommonAncestorTest, find_WhenVerticesSwapped_ThenSameLCA)
{
    // when
    vertex_t result1 = test_object.find(tree[5], tree[7]);
    vertex_t result2 = test_object.find(tree[7], tree[5]);
    // then
    EXPECT_EQ(tree[1], result1);
    EXPECT_EQ(result1, result2);
}

TEST_F(LowestCommonAncestorTest, find_WhenRootIsCommonAncestor_ThenRoot)
{
    // when
    vertex_t result = test_object.find(tree[3], tree[9]);
    // then
    EXPECT_EQ(test_object.root(), result);
}

TEST_F(LowestCommonAncestorTest, find_WhenVerticesAreOnSamePathFromRoot_ThenLCAIsCloserToRoot)
{
    // given
    vertex_t vertex1 = tree[8], vertex2 = tree[2];
    // when
    vertex_t result = test_object.find(vertex1, vertex2);
    // then
    EXPECT_EQ(vertex2, result);
}

TEST_F(LowestCommonAncestorTest, find_WhenRootIsOneOfVertices_ThenRoot)
{
    // when
    vertex_t result = test_object.find(tree[4], test_object.root());
    // then
    EXPECT_EQ(test_object.root(), result);
}
