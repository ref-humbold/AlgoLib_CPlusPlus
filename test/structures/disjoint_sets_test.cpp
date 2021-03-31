/*!
 * \file disjoint_sets_test.cpp
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
    DisjointSetsTest() : test_object{0, 1, 2, 3, 4, 5, 6, 7, 8, 9}
    {
    }

    ~DisjointSetsTest() override = default;
};

TEST_F(DisjointSetsTest, empty_WhenNotEmpty_ThenFalse)
{
    // when
    bool result = test_object.empty();
    // then
    EXPECT_FALSE(result);
}

TEST_F(DisjointSetsTest, empty_WhenEmpty_ThenTrue)
{
    // given
    test_object = alst::disjoint_sets<int>();
    // when
    bool result = test_object.empty();
    // then
    EXPECT_TRUE(result);
}

TEST_F(DisjointSetsTest, contains_WhenElementIsInside_ThenTrue)
{
    // when
    bool result = test_object.contains(4);
    // then
    EXPECT_TRUE(result);
}

TEST_F(DisjointSetsTest, contains_WhenElementIsNotInside_ThenFalse)
{
    // when
    bool result = test_object.contains(17);
    // then
    EXPECT_FALSE(result);
}

TEST_F(DisjointSetsTest, insert_WhenNewElementAsSingleton)
{
    // given
    int elem = 20;
    // when
    EXPECT_NO_THROW(test_object.insert(elem));
    // then
    ASSERT_TRUE(test_object.contains(elem));
    EXPECT_EQ(elem, test_object[elem]);
    EXPECT_EQ(11, test_object.size());
}

TEST_F(DisjointSetsTest, insert_WhenNewElementToPresentSet)
{
    // given
    int elem = 20, repr = 7;
    // when
    EXPECT_NO_THROW(test_object.insert(elem, repr));
    // then
    ASSERT_TRUE(test_object.contains(elem));
    EXPECT_EQ(repr, test_object[elem]);
    EXPECT_EQ(10, test_object.size());
}

TEST_F(DisjointSetsTest, insert_WhenPresentElement)
{
    // given
    auto exec = [&]() { test_object.insert(7); };
    // then
    EXPECT_THROW(exec(), std::invalid_argument);
}

TEST_F(DisjointSetsTest, insert_WhenNotPresentRepresent)
{
    // when
    auto exec = [&]() { test_object.insert(20, 14); };
    // then
    EXPECT_THROW(exec(), std::invalid_argument);
}

TEST_F(DisjointSetsTest, insert_WhenManyElementsAsSingletons)
{
    // given
    std::vector<int> elems = {20, 22, 24, 26};
    // when
    EXPECT_NO_THROW(test_object.insert(elems.begin(), elems.end()));
    // then
    for(int e : elems)
    {
        ASSERT_TRUE(test_object.contains(e));
        EXPECT_EQ(e, test_object[e]);
    }
}

TEST_F(DisjointSetsTest, insert_WhenManyElementsToPresentSet)
{
    // given
    std::vector<int> elems = {20, 22, 24, 26};
    int repr = 3;
    // when
    EXPECT_NO_THROW(test_object.insert(elems.begin(), elems.end(), repr));
    // then
    for(int e : elems)
    {
        ASSERT_TRUE(test_object.contains(e));
        EXPECT_EQ(repr, test_object[e]);
    }
}

TEST_F(DisjointSetsTest, getItem_WhenPresent_ThenRepresent)
{
    // given
    int elem = 4;
    // when
    int result = test_object[elem];
    // then
    EXPECT_EQ(elem, result);
}

TEST_F(DisjointSetsTest, getItem_WhenPresent_ThenOutOfRange)
{
    // when
    auto exec = [&]() { return test_object[17]; };
    // then
    EXPECT_THROW(exec(), std::out_of_range);
}

TEST_F(DisjointSetsTest, findSet_WhenPresent_ThenRepresent)
{
    // given
    int elem = 4;
    // when
    std::optional<int> result = test_object.find_set(elem);
    // then
    ASSERT_TRUE(result);
    EXPECT_EQ(elem, *result);
}

TEST_F(DisjointSetsTest, findSet_WhenAbsent_ThenDefaultValue)
{
    // given
    std::optional<int> result = test_object.find_set(22);
    // then
    EXPECT_FALSE(result);
}

TEST_F(DisjointSetsTest, unionSet_WhenDifferentSets)
{
    // given
    int elem1 = 4, elem2 = 6;
    // when
    test_object.union_set(elem1, elem2);
    // then
    EXPECT_TRUE(test_object.is_same_set(elem1, elem2));
}

TEST_F(DisjointSetsTest, unionSet_WhenSameSets1)
{
    // given
    int elem = 4;
    // when
    test_object.union_set(elem, elem);
    // then
    EXPECT_TRUE(test_object.is_same_set(elem, elem));
}

TEST_F(DisjointSetsTest, unionSet_WhenSameSets2)
{
    // given
    int elem1 = 3, elem2 = 8;
    // when
    test_object.union_set(elem1, elem2);
    test_object.union_set(elem1, elem2);
    // then
    EXPECT_TRUE(test_object.is_same_set(elem1, elem2));
}

TEST_F(DisjointSetsTest, isSameSet_WhenDifferentSets)
{
    // when
    bool result = test_object.is_same_set(4, 6);
    // then
    EXPECT_FALSE(result);
}

TEST_F(DisjointSetsTest, isSameSet_WhenSameSets1)
{
    // given
    int elem = 4;
    // when
    bool result = test_object.is_same_set(elem, elem);
    // then
    EXPECT_TRUE(result);
}

TEST_F(DisjointSetsTest, isSameSet_WhenSameSets2)
{
    // given
    int elem1 = 3, elem2 = 8;

    test_object.union_set(elem1, elem2);
    // when
    bool result = test_object.is_same_set(elem1, elem2);
    // then
    EXPECT_TRUE(result);
}
