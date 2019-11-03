//! TESTY DLA ALGORYTMU NAJNIŻSZEGO WSPÓLNEGO PRZODKA
#include <gtest/gtest.h>
#include "algolib/graphs/lowest_common_ancestor.hpp"

namespace algr = algolib::graphs;

class LCATest : public ::testing::Test
{
protected:
    algr::forest_graph trees;

public:
    LCATest()
        : trees{algr::forest_graph(
                12, std::vector<edge_t>({std::make_pair(0, 1), std::make_pair(0, 2),
                                         std::make_pair(1, 3), std::make_pair(1, 4),
                                         std::make_pair(1, 5), std::make_pair(2, 6),
                                         std::make_pair(4, 7), std::make_pair(6, 8),
                                         std::make_pair(6, 9), std::make_pair(10, 11)}))}
    {
    }

    ~LCATest() override = default;
};

TEST_F(LCATest, findLCA_whenVerticesNotInSameTree)
{
    vertex_t vertex1 = 1;
    vertex_t vertex2 = 11;

    EXPECT_THROW(algr::find_lca(trees, vertex1, vertex2), std::invalid_argument);
}

TEST_F(LCATest, findLCA_whenRootNotInSameTree)
{
    vertex_t vertex1 = 1;
    vertex_t vertex2 = 9;
    vertex_t root = 10;

    EXPECT_THROW(algr::find_lca(trees, vertex1, vertex2, root), std::invalid_argument);
}

TEST_F(LCATest, findLCA_whenSameVertex)
{
    vertex_t vertex = 6;

    vertex_t result = algr::find_lca(trees, vertex, vertex);

    EXPECT_EQ(vertex, result);
}

TEST_F(LCATest, findLCA_whenVerticesChanged)
{
    vertex_t vertex1 = 5;
    vertex_t vertex2 = 7;

    vertex_t result1 = algr::find_lca(trees, vertex1, vertex2);
    vertex_t result2 = algr::find_lca(trees, vertex2, vertex1);

    EXPECT_EQ(1, result1);
    EXPECT_EQ(1, result2);
}

TEST_F(LCATest, findLCA_whenVerticesInDifferentSubtrees)
{
    vertex_t vertex1 = 5;
    vertex_t vertex2 = 7;

    vertex_t result = algr::find_lca(trees, vertex1, vertex2);

    EXPECT_EQ(1, result);
}

TEST_F(LCATest, findLCA_whenRootIsLCA)
{
    vertex_t vertex1 = 3;
    vertex_t vertex2 = 9;
    vertex_t root = 0;

    vertex_t result = algr::find_lca(trees, vertex1, vertex2, root);

    EXPECT_EQ(root, result);
}

TEST_F(LCATest, findLCA_whenVerticesAreOffsprings)
{
    vertex_t vertex1 = 8;
    vertex_t vertex2 = 2;

    vertex_t result = algr::find_lca(trees, vertex1, vertex2);

    EXPECT_EQ(vertex2, result);
}

TEST_F(LCATest, findLCARootIsOneOfVertices1)
{
    vertex_t vertex1 = 11;
    vertex_t vertex2 = 10;

    vertex_t result = algr::find_lca(trees, vertex1, vertex2, vertex1);

    EXPECT_EQ(vertex1, result);
}

TEST_F(LCATest, findLCA_whenRootIsOneOfVertices2)
{
    vertex_t vertex1 = 4;
    vertex_t vertex2 = 0;

    vertex_t result = algr::find_lca(trees, vertex1, vertex2, vertex2);

    EXPECT_EQ(vertex2, result);
}