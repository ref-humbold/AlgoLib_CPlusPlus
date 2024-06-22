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
    const std::vector<int> numbers = {10, 6, 14, 97, 24, 37, 2, 30, 45, 18, 51, 71, 68, 26};
    const std::vector<int> absent = {111, 140, 187, 253};
    std::vector<int> present;
    alst::disjoint_sets<int> test_object;

public:
    DisjointSetsTest()
    {
        std::vector<std::vector<int>> numbers_list;

        std::transform(
                numbers.begin(), numbers.end(), std::back_inserter(numbers_list),
                [](int n) { return std::vector<int>({n}); });

        test_object = alst::disjoint_sets<int>(numbers_list);

        for(auto && it = numbers.begin() + 2; it < numbers.end(); it += 3)
            present.push_back(*it);
    }

    ~DisjointSetsTest() override = default;
};

TEST_F(DisjointSetsTest, empty_WhenEmpty_ThenTrue)
{
    // when
    bool result = alst::disjoint_sets<int>().empty();

    // then
    EXPECT_TRUE(result);
}

TEST_F(DisjointSetsTest, empty_WhenNotEmpty_ThenFalse)
{
    // when
    bool result = test_object.empty();

    // then
    EXPECT_FALSE(result);
}

TEST_F(DisjointSetsTest, size_WhenEmpty_ThenZero)
{
    // when
    size_t result = alst::disjoint_sets<int>().size();

    // then
    EXPECT_EQ(0, result);
}

TEST_F(DisjointSetsTest, size_WhenNotEmpty_ThenNumberOfSets)
{
    // when
    size_t result = test_object.size();

    // then
    EXPECT_EQ(numbers.size(), result);
}

TEST_F(DisjointSetsTest, clear_WhenNotEmpty_ThenEmpty)
{
    // when
    test_object.clear();

    // then
    EXPECT_EQ(0, test_object.size());
}

#pragma region contains

TEST_F(DisjointSetsTest, contains_WhenEmpty_ThenFalse)
{
    // when
    bool result = alst::disjoint_sets<int>().contains(numbers[0]);

    // then
    EXPECT_FALSE(result);
}

TEST_F(DisjointSetsTest, contains_WhenPresentElement_ThenTrue)
{
    // when
    bool result = test_object.contains(present[0]);

    // then
    EXPECT_TRUE(result);
}

TEST_F(DisjointSetsTest, contains_WhenAbsentElement_ThenFalse)
{
    // when
    bool result = test_object.contains(absent[0]);

    // then
    EXPECT_FALSE(result);
}

#pragma endregion
#pragma region insert

TEST_F(DisjointSetsTest, insert_WhenEmpty_ThenNewSet)
{
    // given
    test_object = alst::disjoint_sets<int>();

    // when
    test_object.insert(numbers.begin(), numbers.end());

    // then
    for(auto && element : numbers)
    {
        ASSERT_TRUE(test_object.contains(element));
        EXPECT_EQ(numbers[0], test_object[element]);
    }

    EXPECT_EQ(1, test_object.size());
}

TEST_F(DisjointSetsTest, insert_WhenEmptyNewElements_ThenNoChanges)
{
    // when
    test_object.insert({});

    // then
    EXPECT_EQ(numbers.size(), test_object.size());
}

TEST_F(DisjointSetsTest, insert_WhenNewElements_ThenNewSet)
{
    // when
    test_object.insert(absent.begin(), absent.end());

    // then
    for(int element : absent)
    {
        ASSERT_TRUE(test_object.contains(element));
        EXPECT_EQ(absent[0], test_object[element]);
    }

    EXPECT_EQ(numbers.size() + 1, test_object.size());
}

TEST_F(DisjointSetsTest, insert_WhenPresentElements_ThenInvalidArgument)
{
    // when
    auto exec = [&]() { return test_object.insert(present.begin(), present.end()); };

    // then
    EXPECT_THROW(exec(), std::invalid_argument);
}

TEST_F(DisjointSetsTest, insert_WhenNewAndPresentElements_ThenInvalidArgument)
{
    // given
    std::vector<int> elements;

    elements.insert(elements.end(), absent.begin(), absent.end());
    elements.insert(elements.end(), present.begin(), present.end());

    // when
    auto exec = [&]() { return test_object.insert(elements.begin(), elements.end()); };

    // then
    EXPECT_THROW(exec(), std::invalid_argument);
}

TEST_F(DisjointSetsTest, insert_WhenEmptyNewElementsToPresentRepresent_ThenNoChanges)
{
    // when
    test_object.insert({}, present[0]);

    // then
    EXPECT_EQ(numbers.size(), test_object.size());
}

TEST_F(DisjointSetsTest, insert_WhenNewElementsToPresentRepresent_ThenAddedToExistingSet)
{
    // given
    int represent = present[0];

    // when
    test_object.insert(absent.begin(), absent.end(), represent);

    // then
    for(int element : absent)
    {
        ASSERT_TRUE(test_object.contains(element));
        EXPECT_EQ(test_object[represent], test_object[element]);
    }

    EXPECT_EQ(numbers.size(), test_object.size());
}

TEST_F(DisjointSetsTest, insert_WhenNewElementsToAbsentRepresent_ThenOutOfRange)
{
    // when
    auto exec = [&]() { return test_object.insert(absent.begin(), absent.end(), absent[0]); };

    // then
    EXPECT_THROW(exec(), std::out_of_range);
}

TEST_F(DisjointSetsTest, insert_WhenPresentElementsToAbsentRepresent_ThenInvalidArgument)
{
    // when
    auto exec = [&]() { return test_object.insert(present.begin(), present.end(), absent[0]); };

    // then
    EXPECT_THROW(exec(), std::invalid_argument);
}

#pragma endregion
#pragma region operatorBrackets & find_set

TEST_F(DisjointSetsTest, operatorBrackets_WhenEmpty_ThenOutOfRange)
{
    // when
    auto exec = [&]() { return alst::disjoint_sets<int>()[numbers[0]]; };

    // then
    EXPECT_THROW(exec(), std::out_of_range);
}

TEST_F(DisjointSetsTest, operatorBrackets_WhenPresent_ThenRepresent)
{
    // given
    int element = present[0];

    // when
    int result = test_object[element];

    // then
    EXPECT_EQ(element, result);
}

TEST_F(DisjointSetsTest, operatorBrackets_WhenAbsent_ThenOutOfRange)
{
    // when
    auto exec = [&]() { return test_object[absent[0]]; };

    // then
    EXPECT_THROW(exec(), std::out_of_range);
}

TEST_F(DisjointSetsTest, findSet_WhenPresent_ThenRepresent)
{
    // given
    int element = present[0];

    // when
    std::optional<int> result = test_object.find_set(element);

    // then
    ASSERT_TRUE(result);
    EXPECT_EQ(element, *result);
}

TEST_F(DisjointSetsTest, findSet_WhenAbsent_ThenDefaultValue)
{
    // given
    std::optional<int> result = test_object.find_set(absent[0]);

    // then
    EXPECT_FALSE(result);
}

#pragma endregion
#pragma region union_set

TEST_F(DisjointSetsTest, unionSet_WhenDifferentSets_ThenSameRepresent)
{
    // given
    int element1 = present[0], element2 = present[1];

    // when
    test_object.union_set(element1, element2);

    // then
    ASSERT_TRUE(test_object.is_same_set(element1, element2));
    EXPECT_EQ(test_object[element2], test_object[element1]);
    EXPECT_EQ(numbers.size() - 1, test_object.size());
}

TEST_F(DisjointSetsTest, unionSet_WhenSingleElement_ThenNoChanges)
{
    // given
    int element = present[0];

    // when
    test_object.union_set(element, element);

    // then
    EXPECT_EQ(numbers.size(), test_object.size());
}

TEST_F(DisjointSetsTest, unionSet_WhenSameSet_ThenSameRepresent)
{
    // given
    int element1 = present[0], element2 = present[1];

    test_object.union_set(element1, element2);

    // when
    test_object.union_set(element2, element1);

    // then
    ASSERT_TRUE(test_object.is_same_set(element1, element2));
    EXPECT_EQ(test_object[element2], test_object[element1]);
    EXPECT_EQ(numbers.size() - 1, test_object.size());
}

TEST_F(DisjointSetsTest, unionSet_WhenNewElementsInChain_ThenSameRepresent)
{
    // given
    int first = present[0], last = present[present.size() - 1];

    // when
    for(size_t i = 1; i < present.size(); ++i)
        test_object.union_set(present[i - 1], present[i]);

    // then
    ASSERT_TRUE(test_object.is_same_set(first, last));
    EXPECT_EQ(test_object[first], test_object[last]);
    EXPECT_EQ(numbers.size() - present.size() + 1, test_object.size());
}

#pragma endregion
#pragma region is_same_set

TEST_F(DisjointSetsTest, isSameSet_WhenDifferentSets_ThenFalse)
{
    // when
    bool result = test_object.is_same_set(present[0], present[1]);

    // then
    EXPECT_FALSE(result);
}

TEST_F(DisjointSetsTest, isSameSet_WhenSameElement_ThenTrue)
{
    // given
    int element = present[0];

    // when
    bool result = test_object.is_same_set(element, element);

    // then
    EXPECT_TRUE(result);
}

TEST_F(DisjointSetsTest, isSameSet_WhenSameSet_ThenTrue)
{
    // given
    int element1 = present[0], element2 = present[1];

    test_object.union_set(element1, element2);

    // when
    bool result = test_object.is_same_set(element2, element1);

    // then
    EXPECT_TRUE(result);
}

#pragma endregion
