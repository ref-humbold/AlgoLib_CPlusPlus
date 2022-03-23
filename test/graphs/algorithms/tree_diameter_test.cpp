/*!
 * \file tree_diameter_test.cpp
 * \brief Tests: Algorithm for counting diameter of a tree
 */
#include <gtest/gtest.h>
#include "algolib/graphs/algorithms/tree_diameter.hpp"

namespace algr = algolib::graphs;

class weighted_impl : public algr::weighted
{
public:
    explicit weighted_impl(weight_type weight = 0) : weighted(), weight_{weight}
    {
    }

    ~weighted_impl() override = default;

    const weight_type & weight() const override
    {
        return weight_;
    }

private:
    weight_type weight_;
};

TEST(TreeDiameterTest, countDiameter_WhenOneVertex_ThenZero)
{
    // given
    algr::tree_graph<size_t, std::nullptr_t, weighted_impl> tree(0);
    // when
    double result = algr::count_diameter(tree);
    // then
    EXPECT_EQ(0, result);
}

TEST(TreeDiameterTest, countDiameter_WhenAllWeightsEqual_ThenDiameterLength)
{
    // given
    weighted_impl weight(1);
    algr::tree_graph<size_t, std::nullptr_t, weighted_impl> tree(0);
    tree.add_vertex(1, tree[0], nullptr, weight);
    tree.add_vertex(2, tree[0], nullptr, weight);
    tree.add_vertex(3, tree[1], nullptr, weight);
    tree.add_vertex(4, tree[1], nullptr, weight);
    tree.add_vertex(5, tree[1], nullptr, weight);
    tree.add_vertex(6, tree[2], nullptr, weight);
    tree.add_vertex(7, tree[4], nullptr, weight);
    tree.add_vertex(8, tree[6], nullptr, weight);
    tree.add_vertex(9, tree[6], nullptr, weight);
    // when
    double result = algr::count_diameter(tree);
    // then
    EXPECT_EQ(6, result);
}

TEST(TreeDiameterTest, countDiameter_WhenEdgeWithBigWeight_ThenLongestPath)
{
    // given
    algr::tree_graph<size_t, std::nullptr_t, weighted_impl> tree(0);
    tree.add_vertex(1, tree[0], nullptr, weighted_impl(1000));
    tree.add_vertex(2, tree[1], nullptr, weighted_impl(10));
    tree.add_vertex(3, tree[1], nullptr, weighted_impl(10));
    tree.add_vertex(4, tree[2], nullptr, weighted_impl(5));
    tree.add_vertex(5, tree[3], nullptr, weighted_impl(5));
    // when
    double result = algr::count_diameter(tree);
    // then
    EXPECT_EQ(1015, result);
}
