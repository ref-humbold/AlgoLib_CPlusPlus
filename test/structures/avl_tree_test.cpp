/*!
 * \file avl_tree_test.cpp
 * \brief Tests: Structure of AVL tree
 */
#include <gtest/gtest.h>
#include "algolib/structures/avl_tree.hpp"

namespace alst = algolib::structures;

class AVLTreeTest : public ::testing::Test
{
protected:
    const std::vector<int> numbers = {10, 6, 14, 97, 24, 37, 2, 30, 45, 18, 51, 71, 68, 26};
    alst::avl_tree<int> test_object;
    const alst::avl_tree<int> const_test_object;

public:
    AVLTreeTest()
        : test_object{numbers.begin(), numbers.end()},
          const_test_object{numbers.begin(), numbers.end()}
    {
    }

    ~AVLTreeTest() override = default;
};

TEST_F(AVLTreeTest, copyConstructor)
{
    alst::avl_tree<int> copy_object = test_object;

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

TEST_F(AVLTreeTest, moveConstructor)
{
    alst::avl_tree<int> move_object = std::move(test_object);

    ASSERT_EQ(numbers.size(), move_object.size());

    for(const auto & e : numbers)
        EXPECT_TRUE(move_object.find(e) != move_object.end());
}

TEST_F(AVLTreeTest, copyAssignment)
{
    alst::avl_tree<int> copy_object = {119};

    ASSERT_TRUE(copy_object.find(119) != copy_object.end());

    copy_object = test_object;

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

TEST_F(AVLTreeTest, moveAssignment)
{
    alst::avl_tree<int> move_object = {119};

    ASSERT_TRUE(move_object.find(119) != move_object.end());

    move_object = std::move(test_object);

    ASSERT_EQ(numbers.size(), move_object.size());

    for(const auto & e : numbers)
        EXPECT_TRUE(move_object.find(e) != move_object.end());
}

TEST_F(AVLTreeTest, copyAssignment_WhenSelfAssignment_ThenObjectUnchanged)
{
    test_object = test_object;

    ASSERT_EQ(numbers.size(), test_object.size());

    for(const auto & e : numbers)
        EXPECT_TRUE(test_object.find(e) != test_object.end());
}

TEST_F(AVLTreeTest, empty_WhenNotEmpty_ThenFalse)
{
    // when
    bool result = test_object.empty();
    // then
    EXPECT_FALSE(result);
}

TEST_F(AVLTreeTest, empty_WhenEmpty_ThenTrue)
{
    // given
    test_object = alst::avl_tree<int>();
    // when
    bool result = test_object.empty();
    // then
    EXPECT_TRUE(result);
}

TEST_F(AVLTreeTest, size_WhenNotEmpty_ThenNumberOfElements)
{
    // when
    size_t result = test_object.size();
    // then
    EXPECT_EQ(numbers.size(), result);
}

TEST_F(AVLTreeTest, size_WhenEmpty_ThenZero)
{
    // given
    test_object = alst::avl_tree<int>();
    // when
    size_t result = test_object.size();
    // then
    EXPECT_EQ(0, result);
}

TEST_F(AVLTreeTest, iterator_WhenIterativeForLoop_ThenSortedElements)
{
    std::vector<int> result;
    std::vector<int> sorted_numbers = numbers;

    for(auto && it = test_object.begin(); it != test_object.end(); ++it)
        result.push_back(*it);

    std::sort(sorted_numbers.begin(), sorted_numbers.end());

    EXPECT_EQ(sorted_numbers, result);
}

TEST_F(AVLTreeTest, iterator_WhenRangeBasedForLoop_ThenSortedElements)
{
    std::vector<int> result;
    std::vector<int> sorted_numbers = numbers;

    for(const auto & e : test_object)
        result.push_back(e);

    std::sort(sorted_numbers.begin(), sorted_numbers.end());

    EXPECT_EQ(sorted_numbers, result);
}

TEST_F(AVLTreeTest, iterator_WhenEmpty_ThenNoElements)
{
    // given
    test_object = alst::avl_tree<int>();
    std::vector<int> result;
    // when
    for(auto && it = test_object.begin(); it != test_object.end(); ++it)
        result.push_back(*it);
    // then
    EXPECT_EQ(std::vector<int>(), result);
}

TEST_F(AVLTreeTest, constIterator_WhenAccessElement_ThenSortedElements)
{
    std::vector<int> sorted_numbers = numbers;
    auto test_it = test_object.cbegin();

    std::sort(sorted_numbers.begin(), sorted_numbers.end());

    for(size_t i = 0; i < test_object.size(); ++i)
    {
        int result = *test_it;

        ++test_it;

        EXPECT_EQ(sorted_numbers[i], result);
    }
}

TEST_F(AVLTreeTest, reverseIterator_WhenIterativeForLoop_ThenReverseSortedElements)
{
    std::vector<int> result;
    std::vector<int> reversed_numbers = numbers;

    for(auto && it = test_object.rbegin(); it != test_object.rend(); ++it)
        result.push_back(*it);

    std::sort(reversed_numbers.rbegin(), reversed_numbers.rend());

    EXPECT_EQ(reversed_numbers, result);
}

TEST_F(AVLTreeTest, reverseIterator_WhenIterativeForLoopForConstObject_ThenReverseSortedElements)
{
    std::vector<int> result;
    std::vector<int> reversed_numbers = numbers;

    for(auto && it = const_test_object.rbegin(); it != const_test_object.rend(); ++it)
        result.push_back(*it);

    std::sort(reversed_numbers.rbegin(), reversed_numbers.rend());

    EXPECT_EQ(reversed_numbers, result);
}

TEST_F(AVLTreeTest, reverseIterator_WhenEmpty_ThenNoElements)
{
    // given
    test_object = alst::avl_tree<int>();
    std::vector<int> result;
    // when
    for(auto && it = test_object.rbegin(); it != test_object.rend(); ++it)
        result.push_back(*it);
    // then
    EXPECT_EQ(std::vector<int>(), result);
}

TEST_F(AVLTreeTest, constReverseIterator_WhenAccessElement_ThenReverseSortedElements)
{
    std::vector<int> sorted_numbers = numbers;
    auto test_it = test_object.crbegin();

    std::sort(sorted_numbers.rbegin(), sorted_numbers.rend());

    for(size_t i = 0; i < test_object.size(); ++i)
    {
        int result = *test_it;

        ++test_it;

        EXPECT_EQ(sorted_numbers[i], result);
    }
}

TEST_F(AVLTreeTest, find_WhenPresentElement_ThenIteratorNotEnd)
{
    for(auto i : numbers)
    {
        auto result = test_object.find(i);

        EXPECT_TRUE(result != test_object.end());
    }
}

TEST_F(AVLTreeTest, find_WhenAbsentElement_ThenIteratorEnd)
{
    std::vector<int> elems = {111, 140, 187};

    for(auto i : elems)
    {
        auto result = test_object.find(i);

        EXPECT_FALSE(result != test_object.end());
    }
}

TEST_F(AVLTreeTest, find_WhenConstObjectAndPresentElement_ThenIteratorNotEnd)
{
    for(auto i : numbers)
    {
        auto result = const_test_object.find(i);

        EXPECT_TRUE(result != const_test_object.end());
    }
}

TEST_F(AVLTreeTest, find_WhenConstObjectAndAbsentElement_ThenIteratorEnd)
{
    std::vector<int> elems = {111, 140, 187};

    for(auto i : elems)
    {
        auto result = const_test_object.find(i);

        EXPECT_FALSE(result != const_test_object.end());
    }
}

TEST_F(AVLTreeTest, insert_WhenNewElement_ThenIteratorNotEndAndTrue)
{
    std::vector<int> elems = {111, 140, 187};

    for(auto i : elems)
    {
        auto result = test_object.insert(i);

        ASSERT_TRUE(result.second);
        EXPECT_TRUE(result.first != test_object.end());
        EXPECT_EQ(i, *result.first);
        EXPECT_TRUE(test_object.find(i) != test_object.end());
    }

    EXPECT_EQ(numbers.size() + elems.size(), test_object.size());
}

TEST_F(AVLTreeTest, insert_WhenPresentElement_ThenIteratorEndAndFalse)
{
    std::vector<int> elems = {14, 24, 30, 45};

    for(auto i : elems)
    {
        auto result = test_object.insert(i);

        ASSERT_FALSE(result.second);
        EXPECT_TRUE(result.first != test_object.end());
        EXPECT_EQ(i, *result.first);
        EXPECT_TRUE(test_object.find(i) != test_object.end());
    }

    EXPECT_EQ(numbers.size(), test_object.size());
}

TEST_F(AVLTreeTest, emplace_WhenNewElement_ThenIteratorNotEndAndTrue)
{
    std::vector<int> elems = {111, 140, 187};

    for(auto i : elems)
    {
        auto result = test_object.emplace(i);

        ASSERT_TRUE(result.second);
        EXPECT_TRUE(result.first != test_object.end());
        EXPECT_EQ(i, *result.first);
        EXPECT_TRUE(test_object.find(i) != test_object.end());
    }

    EXPECT_EQ(numbers.size() + elems.size(), test_object.size());
}

TEST_F(AVLTreeTest, emplace_WhenPresentElement_ThenIteratorEndAndFalse)
{
    std::vector<int> elems = {14, 24, 30, 45};

    for(auto i : elems)
    {
        auto result = test_object.emplace(i);

        ASSERT_FALSE(result.second);
        EXPECT_TRUE(result.first != test_object.end());
        EXPECT_EQ(i, *result.first);
        EXPECT_TRUE(test_object.find(i) != test_object.end());
    }

    EXPECT_EQ(numbers.size(), test_object.size());
}

TEST_F(AVLTreeTest, erase_WhenPresentElement_ThenNotFound)
{
    std::vector<int> elems = {14, 24, 30, 45};

    for(auto i : elems)
    {
        size_t result = test_object.erase(i);

        EXPECT_EQ(1, result);
        EXPECT_TRUE(test_object.find(i) == test_object.end());
    }

    EXPECT_EQ(numbers.size() - elems.size(), test_object.size());
}

TEST_F(AVLTreeTest, erase_WhenErasingRootFromTwoElements_ThenOneElementRemoved_1)
{
    int root = 27;
    int elem = 11;

    test_object = alst::avl_tree<int>({root, elem});

    size_t result = test_object.erase(root);

    EXPECT_EQ(1, result);
    EXPECT_TRUE(test_object.find(root) == test_object.end());
    EXPECT_TRUE(test_object.find(elem) != test_object.end());
    EXPECT_EQ(1, test_object.size());
}

TEST_F(AVLTreeTest, erase_WhenErasingRootFromTwoElements_ThenOneElementRemoved_2)
{
    int root = 11;
    int elem = 27;

    test_object = alst::avl_tree<int>({root, elem});

    size_t result = test_object.erase(root);

    EXPECT_EQ(1, result);
    EXPECT_TRUE(test_object.find(root) == test_object.end());
    EXPECT_TRUE(test_object.find(elem) != test_object.end());
    EXPECT_EQ(1, test_object.size());
}

TEST_F(AVLTreeTest, erase_WhenOneElement_ThenOneElementRemovedAndEmptyTree)
{
    int root = 0;

    test_object = alst::avl_tree<int>({root});

    size_t result = test_object.erase(root);

    EXPECT_EQ(1, result);
    EXPECT_TRUE(test_object.find(root) == test_object.end());
    EXPECT_TRUE(test_object.empty());
    EXPECT_EQ(0, test_object.size());
}

TEST_F(AVLTreeTest, erase_WhenEmpty_ThenZeroElementsRemovedAndEmptyTree)
{
    test_object = alst::avl_tree<int>();

    size_t result = test_object.erase(0);

    EXPECT_EQ(0, result);
    EXPECT_TRUE(test_object.empty());
    EXPECT_EQ(0, test_object.size());
}

TEST_F(AVLTreeTest, erase_WhenAbsentElement_ThenZeroElementsRemoved)
{
    std::vector<int> elems = {111, 140, 187};

    for(auto i : elems)
    {
        size_t result = test_object.erase(i);

        EXPECT_EQ(0, result);
        EXPECT_TRUE(test_object.find(i) == test_object.end());
    }

    EXPECT_EQ(numbers.size(), test_object.size());
}

TEST_F(AVLTreeTest, clear_WhenNotEmpty_ThenEmpty)
{
    test_object.clear();

    EXPECT_TRUE(test_object.empty());
    EXPECT_EQ(0, test_object.size());
}
