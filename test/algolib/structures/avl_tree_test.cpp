/*!
 * \file avl_tree_test.cpp
 * \brief Tests: Structure of AVL tree.
 */
#include <gtest/gtest.h>
#include "algolib/structures/avl_tree.hpp"

namespace alst = algolib::structures;

class AvlTreeTest : public ::testing::Test
{
protected:
    const std::vector<int> numbers = {10, 6, 14, 97, 24, 37, 2, 30, 45, 18, 51, 71, 68, 26};
    alst::avl_tree<int> test_object;
    const alst::avl_tree<int> const_test_object;

public:
    AvlTreeTest()
        : test_object{numbers.begin(), numbers.end()},
          const_test_object{numbers.begin(), numbers.end()}
    {
    }

    ~AvlTreeTest() override = default;
};

#pragma region constructors & assignments

TEST_F(AvlTreeTest, copyConstructor)
{
    // when
    alst::avl_tree<int> copy_object = test_object;
    // then
    ASSERT_EQ(test_object.size(), copy_object.size());

    auto test_it = test_object.cbegin();
    auto copy_it = copy_object.cbegin();

    while(test_it != test_object.cend() && copy_it != copy_object.cend())
    {
        EXPECT_EQ(*test_it, *copy_it);
        EXPECT_NE(&(*test_it), &(*copy_it));

        ++test_it;
        ++copy_it;
    }
}

TEST_F(AvlTreeTest, moveConstructor)
{
    // when
    alst::avl_tree<int> move_object = std::move(test_object);
    // then
    ASSERT_EQ(numbers.size(), move_object.size());

    for(auto && e : numbers)
        EXPECT_TRUE(move_object.find(e) != move_object.end());
}

TEST_F(AvlTreeTest, copyAssignment)
{
    // given
    alst::avl_tree<int> copy_object = {119};

    ASSERT_TRUE(copy_object.find(119) != copy_object.end());
    // when
    copy_object = test_object;
    // then
    ASSERT_EQ(test_object.size(), copy_object.size());

    auto test_it = test_object.cbegin();
    auto copy_it = copy_object.cbegin();

    while(test_it != test_object.cend() && copy_it != copy_object.cend())
    {
        EXPECT_EQ(*test_it, *copy_it);
        EXPECT_NE(&(*test_it), &(*copy_it));

        ++test_it;
        ++copy_it;
    }
}

TEST_F(AvlTreeTest, moveAssignment)
{
    // given
    alst::avl_tree<int> move_object = {119};

    ASSERT_TRUE(move_object.find(119) != move_object.end());
    // when
    move_object = std::move(test_object);
    // then
    ASSERT_EQ(numbers.size(), move_object.size());

    for(auto && e : numbers)
        EXPECT_TRUE(move_object.find(e) != move_object.end());
}

TEST_F(AvlTreeTest, copyAssignment_WhenSelfAssignment_ThenObjectUnchanged)
{
    // when
    test_object = test_object;
    // then
    ASSERT_EQ(numbers.size(), test_object.size());

    for(auto && e : numbers)
        EXPECT_TRUE(test_object.find(e) != test_object.end());
}

#pragma endregion

TEST_F(AvlTreeTest, empty_WhenNotEmpty_ThenFalse)
{
    // when
    bool result = test_object.empty();
    // then
    EXPECT_FALSE(result);
}

TEST_F(AvlTreeTest, empty_WhenEmpty_ThenTrue)
{
    // given
    test_object = alst::avl_tree<int>();
    // when
    bool result = test_object.empty();
    // then
    EXPECT_TRUE(result);
}

TEST_F(AvlTreeTest, size_WhenNotEmpty_ThenNumberOfElements)
{
    // when
    size_t result = test_object.size();
    // then
    EXPECT_EQ(numbers.size(), result);
}

TEST_F(AvlTreeTest, size_WhenEmpty_ThenZero)
{
    // given
    test_object = alst::avl_tree<int>();
    // when
    size_t result = test_object.size();
    // then
    EXPECT_EQ(0, result);
}

TEST_F(AvlTreeTest, clear_WhenNotEmpty_ThenEmpty)
{
    // when
    test_object.clear();
    // then
    EXPECT_TRUE(test_object.empty());
    EXPECT_EQ(0, test_object.size());
}

#pragma region iterator & const iterator

TEST_F(AvlTreeTest, iterator_WhenEmpty_ThenNoElements)
{
    // given
    test_object = alst::avl_tree<int>();
    // when
    auto it_begin = test_object.begin();
    auto it_end = test_object.end();
    // then
    EXPECT_EQ(it_begin, it_end);
}

TEST_F(AvlTreeTest, iterator_WhenSingleElement_ThenThisElementOnly)
{
    // given
    int element = 17;

    test_object = {element};
    // when
    auto iterator = test_object.begin();
    // then
    EXPECT_NE(iterator, test_object.end());
    EXPECT_EQ(*iterator, element);
    EXPECT_EQ(++iterator, test_object.end());
}

TEST_F(AvlTreeTest, iterator_WhenMultipleElements_ThenSortedElements)
{
    // given
    std::vector<int> sorted_numbers = numbers;

    std::sort(sorted_numbers.begin(), sorted_numbers.end());
    // when
    std::vector<int> result;

    std::copy(test_object.begin(), test_object.end(), std::back_inserter(result));
    // then
    EXPECT_EQ(sorted_numbers, result);
}

TEST_F(AvlTreeTest, iterator_WhenIncrementAndDecrement_ThenElements)
{
    // when
    auto iterator = test_object.begin();
    // then
    EXPECT_NE(iterator, test_object.end());
    EXPECT_EQ(*iterator, 2);
    EXPECT_EQ(*(++iterator), 6);
    EXPECT_EQ(*(++iterator), 10);
    EXPECT_EQ(*(--iterator), 6);
    EXPECT_EQ(*(--iterator), 2);
    EXPECT_EQ(iterator, test_object.begin());
}

TEST_F(AvlTreeTest, iterator_WhenMultipleElementsForConstObject_ThenSortedElements)
{
    // given
    std::vector<int> sorted_numbers = numbers;

    std::sort(sorted_numbers.begin(), sorted_numbers.end());
    // when
    std::vector<int> result;

    std::copy(const_test_object.begin(), const_test_object.end(), std::back_inserter(result));
    // then
    EXPECT_EQ(sorted_numbers, result);
}

TEST_F(AvlTreeTest, constIterator_WhenEmpty_ThenNoElements)
{
    // given
    test_object = alst::avl_tree<int>();
    // when
    auto it_begin = test_object.cbegin();
    auto it_end = test_object.cend();
    // then
    EXPECT_EQ(it_begin, it_end);
}

TEST_F(AvlTreeTest, constIterator_WhenSingleElement_ThenThisElementOnly)
{
    // given
    int element = 17;

    test_object = {element};
    // when
    auto iterator = test_object.cbegin();
    // then
    EXPECT_NE(iterator, test_object.cend());
    EXPECT_EQ(*iterator, element);
    EXPECT_EQ(++iterator, test_object.cend());
}

TEST_F(AvlTreeTest, constIterator_WhenMultipleElements_ThenSortedElements)
{
    // given
    std::vector<int> sorted_numbers = numbers;

    std::sort(sorted_numbers.begin(), sorted_numbers.end());
    // when
    std::vector<int> result;

    std::copy(test_object.cbegin(), test_object.cend(), std::back_inserter(result));
    // then
    EXPECT_EQ(sorted_numbers, result);
}

#pragma endregion
#pragma region reverse iterator & const reverse iterator

TEST_F(AvlTreeTest, reverseIterator_WhenEmpty_ThenNoElements)
{
    // given
    test_object = alst::avl_tree<int>();
    // when
    auto it_begin = test_object.rbegin();
    auto it_end = test_object.rend();
    // then
    EXPECT_EQ(it_begin, it_end);
}

TEST_F(AvlTreeTest, reverseIterator_WhenSingleElement_ThenThisElementOnly)
{
    // given
    int element = 17;

    test_object = {element};
    // when
    auto iterator = test_object.rbegin();
    // then
    EXPECT_NE(iterator, test_object.rend());
    EXPECT_EQ(*iterator, element);
    EXPECT_EQ(++iterator, test_object.rend());
}

TEST_F(AvlTreeTest, reverseIterator_WhenMultipleElements_ThenSortedElements)
{
    // given
    std::vector<int> sorted_numbers = numbers;

    std::sort(sorted_numbers.rbegin(), sorted_numbers.rend());
    // when
    std::vector<int> result;

    std::copy(test_object.rbegin(), test_object.rend(), std::back_inserter(result));
    // then
    EXPECT_EQ(sorted_numbers, result);
}

TEST_F(AvlTreeTest, reverseIterator_WhenIncrementAndDecrement_ThenElements)
{
    // when
    auto iterator = test_object.rbegin();
    // then
    EXPECT_NE(iterator, test_object.rend());
    EXPECT_EQ(*iterator, 97);
    EXPECT_EQ(*(++iterator), 71);
    EXPECT_EQ(*(++iterator), 68);
    EXPECT_EQ(*(--iterator), 71);
    EXPECT_EQ(*(--iterator), 97);
    EXPECT_EQ(iterator, test_object.rbegin());
}

TEST_F(AvlTreeTest, reverseIterator_WhenMultipleElementsForConstObject_ThenSortedElements)
{
    // given
    std::vector<int> sorted_numbers = numbers;

    std::sort(sorted_numbers.rbegin(), sorted_numbers.rend());
    // when
    std::vector<int> result;

    std::copy(const_test_object.rbegin(), const_test_object.rend(), std::back_inserter(result));
    // then
    EXPECT_EQ(sorted_numbers, result);
}

TEST_F(AvlTreeTest, constReverseIterator_WhenEmpty_ThenNoElements)
{
    // given
    test_object = alst::avl_tree<int>();
    // when
    auto it_begin = test_object.crbegin();
    auto it_end = test_object.crend();
    // then
    EXPECT_EQ(it_begin, it_end);
}

TEST_F(AvlTreeTest, constReverseIterator_WhenSingleElement_ThenThisElementOnly)
{
    // given
    int element = 17;

    test_object = {element};
    // when
    auto iterator = test_object.crbegin();
    // then
    EXPECT_NE(iterator, test_object.crend());
    EXPECT_EQ(*iterator, element);
    EXPECT_EQ(++iterator, test_object.crend());
}

TEST_F(AvlTreeTest, constReverseIterator_WhenMultipleElements_ThenSortedElements)
{
    // given
    std::vector<int> sorted_numbers = numbers;

    std::sort(sorted_numbers.rbegin(), sorted_numbers.rend());
    // when
    std::vector<int> result;

    std::copy(test_object.crbegin(), test_object.crend(), std::back_inserter(result));
    // then
    EXPECT_EQ(sorted_numbers, result);
}

#pragma endregion
#pragma region find

TEST_F(AvlTreeTest, find_WhenPresentElement_ThenIteratorNotEnd)
{
    for(auto && i : numbers)
    {
        // when
        auto result = test_object.find(i);
        // then
        EXPECT_TRUE(result != test_object.end());
    }
}

TEST_F(AvlTreeTest, find_WhenAbsentElement_ThenIteratorEnd)
{
    // given
    std::vector<int> elements = {111, 140, 187};

    for(auto && i : elements)
    {
        // when
        auto result = test_object.find(i);
        // then
        EXPECT_FALSE(result != test_object.end());
    }
}

TEST_F(AvlTreeTest, find_WhenConstObjectAndPresentElement_ThenIteratorNotEnd)
{
    for(auto && i : numbers)
    {
        // when
        auto result = const_test_object.find(i);
        // then
        EXPECT_TRUE(result != const_test_object.end());
    }
}

TEST_F(AvlTreeTest, find_WhenConstObjectAndAbsentElement_ThenIteratorEnd)
{
    // given
    std::vector<int> elements = {111, 140, 187};

    for(auto && i : elements)
    {
        // when
        auto result = const_test_object.find(i);
        // then
        EXPECT_FALSE(result != const_test_object.end());
    }
}

#pragma endregion
#pragma region insert & emplace

TEST_F(AvlTreeTest, insert_WhenNewElement_ThenIteratorNotEndAndTrue)
{
    // given
    std::vector<int> elements = {111, 140, 187};

    for(auto && i : elements)
    {
        // when
        auto result = test_object.insert(i);
        // then
        ASSERT_TRUE(result.second);
        EXPECT_TRUE(result.first != test_object.end());
        EXPECT_EQ(i, *result.first);
        EXPECT_TRUE(test_object.find(i) != test_object.end());
    }

    EXPECT_EQ(numbers.size() + elements.size(), test_object.size());
}

TEST_F(AvlTreeTest, insert_WhenPresentElement_ThenIteratorEndAndFalse)
{
    // given
    std::vector<int> elements = {14, 24, 30, 45};

    for(auto && i : elements)
    {
        // when
        auto result = test_object.insert(i);
        // then
        ASSERT_FALSE(result.second);
        EXPECT_TRUE(result.first != test_object.end());
        EXPECT_EQ(i, *result.first);
        EXPECT_TRUE(test_object.find(i) != test_object.end());
    }

    EXPECT_EQ(numbers.size(), test_object.size());
}

TEST_F(AvlTreeTest, emplace_WhenNewElement_ThenIteratorNotEndAndTrue)
{
    // given
    std::vector<int> elements = {111, 140, 187};

    for(auto && i : elements)
    {
        // when
        auto result = test_object.emplace(i);
        // then
        ASSERT_TRUE(result.second);
        EXPECT_TRUE(result.first != test_object.end());
        EXPECT_EQ(i, *result.first);
        EXPECT_TRUE(test_object.find(i) != test_object.end());
    }

    EXPECT_EQ(numbers.size() + elements.size(), test_object.size());
}

TEST_F(AvlTreeTest, emplace_WhenPresentElement_ThenIteratorEndAndFalse)
{
    // given
    std::vector<int> elements = {14, 24, 30, 45};

    for(auto && i : elements)
    {
        // when
        auto result = test_object.emplace(i);
        // then
        ASSERT_FALSE(result.second);
        EXPECT_TRUE(result.first != test_object.end());
        EXPECT_EQ(i, *result.first);
        EXPECT_TRUE(test_object.find(i) != test_object.end());
    }

    EXPECT_EQ(numbers.size(), test_object.size());
}

#pragma endregion
#pragma region erase

TEST_F(AvlTreeTest, erase_WhenPresentElement_ThenNotFound)
{
    // given
    std::vector<int> elements = {14, 24, 30, 45};

    for(auto && i : elements)
    {
        // when
        size_t result = test_object.erase(i);
        // then
        EXPECT_EQ(1, result);
        EXPECT_TRUE(test_object.find(i) == test_object.end());
    }

    EXPECT_EQ(numbers.size() - elements.size(), test_object.size());
}

TEST_F(AvlTreeTest, erase_WhenErasingRootFromTwoElements_ThenOneElementRemoved_1)
{
    // given
    int root = 27, element = 11;

    test_object = {root, element};
    // when
    size_t result = test_object.erase(root);
    // then
    EXPECT_EQ(1, result);
    EXPECT_TRUE(test_object.find(root) == test_object.end());
    EXPECT_TRUE(test_object.find(element) != test_object.end());
    EXPECT_EQ(1, test_object.size());
}

TEST_F(AvlTreeTest, erase_WhenErasingRootFromTwoElements_ThenOneElementRemoved_2)
{
    // given
    int root = 11, element = 27;

    test_object = {root, element};
    // when
    size_t result = test_object.erase(root);
    // then
    EXPECT_EQ(1, result);
    EXPECT_TRUE(test_object.find(root) == test_object.end());
    EXPECT_TRUE(test_object.find(element) != test_object.end());
    EXPECT_EQ(1, test_object.size());
}

TEST_F(AvlTreeTest, erase_WhenOneElement_ThenOneElementRemovedAndEmptyTree)
{
    // given
    int root = 0;

    test_object = {root};
    // when
    size_t result = test_object.erase(root);
    // then
    EXPECT_EQ(1, result);
    EXPECT_TRUE(test_object.find(root) == test_object.end());
    EXPECT_TRUE(test_object.empty());
    EXPECT_EQ(0, test_object.size());
}

TEST_F(AvlTreeTest, erase_WhenEmpty_ThenZeroElementsRemovedAndEmptyTree)
{
    // given
    test_object = alst::avl_tree<int>();
    // when
    size_t result = test_object.erase(0);
    // then
    EXPECT_EQ(0, result);
    EXPECT_TRUE(test_object.empty());
    EXPECT_EQ(0, test_object.size());
}

TEST_F(AvlTreeTest, erase_WhenAbsentElement_ThenZeroElementsRemoved)
{
    // given
    std::vector<int> elements = {111, 140, 187};

    for(auto && i : elements)
    {
        // when
        size_t result = test_object.erase(i);
        // then
        EXPECT_EQ(0, result);
        EXPECT_TRUE(test_object.find(i) == test_object.end());
    }

    EXPECT_EQ(numbers.size(), test_object.size());
}

#pragma endregion
