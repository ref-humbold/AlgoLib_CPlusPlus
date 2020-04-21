/*!
 * \file disjoint_sets_test.c4pp
 * \brief Tests: Disjoint sets structure (union-find)
 */
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

    ~DisjointSetsTest() override = default;
};

TEST_F(DisjointSetsTest, empty_whenNotEmpty_thenFalse)
{
    bool result = test_object.empty();

    EXPECT_FALSE(result);
}

TEST_F(DisjointSetsTest, empty_whenEmpty_thenTrue)
{
    test_object = alst::disjoint_sets<int>();

    bool result = test_object.empty();

    EXPECT_TRUE(result);
}

TEST_F(DisjointSetsTest, contains_whenElementIsInside_thenTrue)
{
    bool result = test_object.contains(4);

    EXPECT_TRUE(result);
}

TEST_F(DisjointSetsTest, contains_whenElementIsNotInside_thenFalse)
{
    bool result = test_object.contains(17);

    EXPECT_FALSE(result);
}

TEST_F(DisjointSetsTest, insert_whenNewElementAsSingleton)
{
    int elem = 20;

    EXPECT_NO_THROW(test_object.insert(elem));

    ASSERT_TRUE(test_object.contains(elem));
    EXPECT_EQ(elem, test_object[elem]);
    EXPECT_EQ(11, test_object.size());
}

TEST_F(DisjointSetsTest, insert_whenNewElementToPresentSet)
{
    int elem = 20;
    int repr = 7;

    EXPECT_NO_THROW(test_object.insert(elem, repr));

    ASSERT_TRUE(test_object.contains(elem));
    EXPECT_EQ(repr, test_object[elem]);
    EXPECT_EQ(10, test_object.size());
}

TEST_F(DisjointSetsTest, insert_whenPresentElement)
{
    int elem = 7;

    EXPECT_THROW(test_object.insert(elem), std::invalid_argument);
}

TEST_F(DisjointSetsTest, insert_whenNotPresentRepresent)
{
    int elem = 20;
    int repr = 14;

    EXPECT_THROW(test_object.insert(elem, repr), std::invalid_argument);
}

TEST_F(DisjointSetsTest, insert_whenManyElementsAsSingletons)
{
    std::vector<int> elems = {20, 22, 24, 26};

    EXPECT_NO_THROW(test_object.insert(elems.begin(), elems.end()));

    for(int e : elems)
    {
        ASSERT_TRUE(test_object.contains(e));
        EXPECT_EQ(e, test_object[e]);
    }
}

TEST_F(DisjointSetsTest, insert_whenManyElementsToPresentSet)
{
    std::vector<int> elems = {20, 22, 24, 26};
    int repr = 3;

    EXPECT_NO_THROW(test_object.insert(elems.begin(), elems.end(), repr));

    for(int e : elems)
    {
        ASSERT_TRUE(test_object.contains(e));
        EXPECT_EQ(repr, test_object[e]);
    }
}

TEST_F(DisjointSetsTest, getItem_whenPresent_thenRepresent)
{
    int elem = 4;
    int result = test_object[elem];

    EXPECT_EQ(elem, result);
}

TEST_F(DisjointSetsTest, getItem_whenPresent_thenOutOfRange)
{
    EXPECT_THROW(test_object[17], std::out_of_range);
}

TEST_F(DisjointSetsTest, findSet_whenPresent_thenRepresent)
{
    int elem = 4;
    int result = test_object.find_set(elem, 10);

    EXPECT_EQ(elem, result);
}

TEST_F(DisjointSetsTest, findSet_whenAbsent_thenDefaultValue)
{
    int default_value = 10;

    int result = test_object.find_set(22, default_value);

    EXPECT_EQ(default_value, result);
}

TEST_F(DisjointSetsTest, unionSet_whenDifferentSets)
{
    int elem1 = 4;
    int elem2 = 6;

    test_object.union_set(elem1, elem2);

    EXPECT_TRUE(test_object.is_same_set(elem1, elem2));
}

TEST_F(DisjointSetsTest, unionSet_whenSameSets1)
{
    int elem = 4;

    test_object.union_set(elem, elem);

    EXPECT_TRUE(test_object.is_same_set(elem, elem));
}

TEST_F(DisjointSetsTest, unionSet_whenSameSets2)
{
    int elem1 = 3;
    int elem2 = 8;

    test_object.union_set(elem1, elem2);
    test_object.union_set(elem1, elem2);

    EXPECT_TRUE(test_object.is_same_set(elem1, elem2));
}

TEST_F(DisjointSetsTest, isSameSet_whenDifferentSets)
{
    int elem1 = 4;
    int elem2 = 6;

    bool result = test_object.is_same_set(elem1, elem2);

    EXPECT_FALSE(result);
}

TEST_F(DisjointSetsTest, isSameSet_whenSameSets1)
{
    int elem = 4;

    bool result = test_object.is_same_set(elem, elem);

    EXPECT_TRUE(result);
}

TEST_F(DisjointSetsTest, isSameSet_whenSameSets2)
{
    int elem1 = 3;
    int elem2 = 8;

    test_object.union_set(elem1, elem2);

    bool result = test_object.is_same_set(elem1, elem2);

    EXPECT_TRUE(result);
}
