// TESTY DLA STRUKTURY ZBIORÓW ROZŁĄCZNYCH
#include <gtest/gtest.h>
#include "algolib/structures/disjoint_sets.hpp"

namespace alst = algolib::structures;

class DisjointSetsTest : public ::testing::Test
{
protected:
    alst::disjoint_sets<int> test_object;

public:
    DisjointSetsTest() : test_object{alst::disjoint_sets<int>({0, 1, 2, 3, 4, 5, 6, 7, 8, 9})}
    {
    }

    virtual ~DisjointSetsTest() = default;
};

TEST_F(DisjointSetsTest, testSize)
{
    size_t result = test_object.size();

    EXPECT_EQ(10, result);
}

TEST_F(DisjointSetsTest, testContainsWhenContains)
{
    bool result = test_object.contains(4);

    EXPECT_TRUE(result);
}

TEST_F(DisjointSetsTest, testContainsWhenNotContains)
{
    bool result = test_object.contains(17);

    EXPECT_FALSE(result);
}

TEST_F(DisjointSetsTest, testInsertWhenNewElementAsSingleton)
{
    int elem = 20;

    EXPECT_NO_THROW(test_object.insert(elem));

    ASSERT_TRUE(test_object.contains(elem));
    EXPECT_EQ(elem, test_object.find_set(elem));
}

TEST_F(DisjointSetsTest, testInsertWhenNewElementToPresentSet)
{
    int elem = 20;
    int repr = 7;

    EXPECT_NO_THROW(test_object.insert(elem, repr));

    ASSERT_TRUE(test_object.contains(elem));
    EXPECT_EQ(repr, test_object.find_set(elem));
}

TEST_F(DisjointSetsTest, testInsertWhenPresentElement)
{
    int elem = 7;

    EXPECT_THROW(test_object.insert(elem), std::invalid_argument);
}

TEST_F(DisjointSetsTest, testInsertWhenNotPresentRepresent)
{
    int elem = 20;
    int repr = 14;

    EXPECT_THROW(test_object.insert(elem, repr), std::invalid_argument);
}

TEST_F(DisjointSetsTest, testInsertManyElementsAsSingletons)
{
    std::vector<int> elems = {20, 22, 24, 26};

    EXPECT_NO_THROW(test_object.insert(elems.begin(), elems.end()));

    for(int e : elems)
    {
        ASSERT_TRUE(test_object.contains(e));
        EXPECT_EQ(e, test_object.find_set(e));
    }
}

TEST_F(DisjointSetsTest, testInsertManyElementsToPresentSet)
{
    std::vector<int> elems = {20, 22, 24, 26};
    int repr = 3;

    EXPECT_NO_THROW(test_object.insert(elems.begin(), elems.end(), repr));

    for(int e : elems)
    {
        ASSERT_TRUE(test_object.contains(e));
        EXPECT_EQ(repr, test_object.find_set(e));
    }
}

TEST_F(DisjointSetsTest, testFindSet)
{
    int elem = 4;
    int result = test_object.find_set(elem);

    EXPECT_EQ(elem, result);
}

TEST_F(DisjointSetsTest, testUnionSetWhenDifferentSets)
{
    int elem1 = 4;
    int elem2 = 6;

    test_object.union_set(elem1, elem2);

    EXPECT_TRUE(test_object.is_same_set(elem1, elem2));
}

TEST_F(DisjointSetsTest, testUnionSetWhenSameSets1)
{
    int elem = 4;

    test_object.union_set(elem, elem);

    EXPECT_TRUE(test_object.is_same_set(elem, elem));
}

TEST_F(DisjointSetsTest, testUnionSetWhenSameSets2)
{
    int elem1 = 3;
    int elem2 = 8;

    test_object.union_set(elem1, elem2);
    test_object.union_set(elem1, elem2);

    EXPECT_TRUE(test_object.is_same_set(elem1, elem2));
}

TEST_F(DisjointSetsTest, testIsSameSetWhenDifferentSets)
{
    int elem1 = 4;
    int elem2 = 6;

    bool result = test_object.is_same_set(elem1, elem2);

    EXPECT_FALSE(result);
}

TEST_F(DisjointSetsTest, testIsSameSetWhenSameSets1)
{
    int elem = 4;

    bool result = test_object.is_same_set(elem, elem);

    EXPECT_TRUE(result);
}

TEST_F(DisjointSetsTest, testIsSameSetWhenSameSets2)
{
    int elem1 = 3;
    int elem2 = 8;

    test_object.union_set(elem1, elem2);

    bool result = test_object.is_same_set(elem1, elem2);

    EXPECT_TRUE(result);
}
