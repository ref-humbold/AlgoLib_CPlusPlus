/*!
 * \file disjoint_sets_test.cpp
 * \brief Tests: Structure of disjoint sets (union-find).
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

TEST_F(DisjointSetsTest, contains_WhenPresentElement_ThenTrue)
{
    // when
    bool result = test_object.contains(4);
    // then
    EXPECT_TRUE(result);
}

TEST_F(DisjointSetsTest, contains_WhenAbsentElement_ThenFalse)
{
    // when
    bool result = test_object.contains(17);
    // then
    EXPECT_FALSE(result);
}

TEST_F(DisjointSetsTest, insert_WhenNewElement_ThenNewSingletonSet)
{
    // given
    int element = 20;
    // when
    EXPECT_NO_THROW(test_object.insert(element));
    // then
    ASSERT_TRUE(test_object.contains(element));
    EXPECT_EQ(element, test_object[element]);
    EXPECT_EQ(11, test_object.size());
}

TEST_F(DisjointSetsTest, insert_WhenNewElementWithRepresent_ThenAddedToExistingSet)
{
    // given
    int element = 20, represent = 7;
    // when
    EXPECT_NO_THROW(test_object.insert(element, represent));
    // then
    ASSERT_TRUE(test_object.contains(element));
    EXPECT_EQ(represent, test_object[element]);
    EXPECT_EQ(10, test_object.size());
}

TEST_F(DisjointSetsTest, insert_WhenPresentElement_ThenInvalidArgument)
{
    // when
    auto exec = [&]() { test_object.insert(7); };
    // then
    EXPECT_THROW(exec(), std::invalid_argument);
}

TEST_F(DisjointSetsTest, insert_WhenNotPresentRepresent_ThenOutOfRange)
{
    // when
    auto exec = [&]() { test_object.insert(20, 14); };
    // then
    EXPECT_THROW(exec(), std::out_of_range);
}

TEST_F(DisjointSetsTest, insert_WhenManyNewElements_ThenNewSingletonSets)
{
    // given
    std::vector<int> elements = {20, 22, 24, 26};
    // when
    EXPECT_NO_THROW(test_object.insert(elements.begin(), elements.end()));
    // then
    for(auto && e : elements)
    {
        ASSERT_TRUE(test_object.contains(e));
        EXPECT_EQ(e, test_object[e]);
    }
}

TEST_F(DisjointSetsTest, insert_WhenManyNewElementsToPresentSet_ThenAddedToExistingSet)
{
    // given
    std::vector<int> elements = {20, 22, 24, 26};
    int represent = 3;
    // when
    EXPECT_NO_THROW(test_object.insert(elements.begin(), elements.end(), represent));
    // then
    for(auto && e : elements)
    {
        ASSERT_TRUE(test_object.contains(e));
        EXPECT_EQ(represent, test_object[e]);
    }
}

TEST_F(DisjointSetsTest, operatorBrackets_WhenPresent_ThenRepresent)
{
    // given
    int element = 4;
    // when
    int result = test_object[element];
    // then
    EXPECT_EQ(element, result);
}

TEST_F(DisjointSetsTest, operatorBrackets_WhenPresent_ThenOutOfRange)
{
    // when
    auto exec = [&]() { return test_object[17]; };
    // then
    EXPECT_THROW(exec(), std::out_of_range);
}

TEST_F(DisjointSetsTest, findSet_WhenPresent_ThenRepresent)
{
    // given
    int element = 4;
    // when
    std::optional<int> result = test_object.find_set(element);
    // then
    ASSERT_TRUE(result);
    EXPECT_EQ(element, *result);
}

TEST_F(DisjointSetsTest, findSet_WhenAbsent_ThenDefaultValue)
{
    // given
    std::optional<int> result = test_object.find_set(22);
    // then
    EXPECT_FALSE(result);
}

TEST_F(DisjointSetsTest, unionSet_WhenDifferentSets_ThenSameRepresent)
{
    // given
    int element1 = 4, element2 = 6;
    // when
    test_object.union_set(element1, element2);
    // then
    EXPECT_TRUE(test_object.is_same_set(element1, element2));
}

TEST_F(DisjointSetsTest, unionSet_WhenSingleElement_ThenSameRepresent)
{
    // given
    int element = 4;
    // when
    test_object.union_set(element, element);
    // then
    EXPECT_TRUE(test_object.is_same_set(element, element));
}

TEST_F(DisjointSetsTest, unionSet_WhenSameSet_ThenSameRepresent)
{
    // given
    int element1 = 3, element2 = 8;

    test_object.union_set(element1, element2);
    // when
    test_object.union_set(element2, element1);
    // then
    EXPECT_TRUE(test_object.is_same_set(element1, element2));
}

TEST_F(DisjointSetsTest, isSameSet_WhenDifferentSets_ThenFalse)
{
    // when
    bool result = test_object.is_same_set(4, 6);
    // then
    EXPECT_FALSE(result);
}

TEST_F(DisjointSetsTest, isSameSet_WhenSameElement_ThenTrue)
{
    // given
    int element = 4;
    // when
    bool result = test_object.is_same_set(element, element);
    // then
    EXPECT_TRUE(result);
}

TEST_F(DisjointSetsTest, isSameSet_WhenSameSet_ThenTrue)
{
    // given
    int element1 = 3, element2 = 8;

    test_object.union_set(element1, element2);
    // when
    bool result = test_object.is_same_set(element2, element1);
    // then
    EXPECT_TRUE(result);
}
