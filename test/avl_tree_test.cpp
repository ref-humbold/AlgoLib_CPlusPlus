/*!
 * \file avl_tree_test.cpp
 * \brief TEST: AVL tree
 */
#include <gtest/gtest.h>
#include "refhumbold/algolib/structures/avl_tree.hpp"

namespace alst = algolib::structures;

class AVLTreeTest : public ::testing::Test
{
protected:
    alst::avl_tree<int> test_object;
    const alst::avl_tree<int> const_test_object;
    const std::vector<int> numbers = {10, 6, 14, 97, 24, 37, 2, 30, 45, 18, 51, 71, 68, 26};

public:
    AVLTreeTest()
        : test_object{alst::avl_tree<int>({10, 6, 14, 97, 24, 37, 2, 30, 45, 18, 51, 71, 68, 26})},
          const_test_object{
                  alst::avl_tree<int>({10, 6, 14, 97, 24, 37, 2, 30, 45, 18, 51, 71, 68, 26})}
    {
    }

    virtual ~AVLTreeTest() = default;
};

TEST_F(AVLTreeTest, testCopyConstructor)
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

TEST_F(AVLTreeTest, testMoveConstructor)
{
    alst::avl_tree<int> move_object = std::move(test_object);

    ASSERT_EQ(numbers.size(), move_object.size());

    for(const auto & e : numbers)
        EXPECT_NE(move_object.end(), move_object.find(e));
}

TEST_F(AVLTreeTest, testCopyAssignment)
{
    alst::avl_tree<int> copy_object({119});

    ASSERT_NE(copy_object.end(), copy_object.find(119));

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

TEST_F(AVLTreeTest, testMoveAssignment)
{
    alst::avl_tree<int> move_object({119});

    ASSERT_NE(move_object.end(), move_object.find(119));

    move_object = std::move(test_object);

    ASSERT_EQ(numbers.size(), move_object.size());

    for(const auto & e : numbers)
        EXPECT_NE(move_object.end(), move_object.find(e));
}

TEST_F(AVLTreeTest, testSelfAssignment)
{
    test_object = test_object;

    ASSERT_EQ(numbers.size(), test_object.size());

    for(const auto & e : numbers)
        EXPECT_NE(test_object.end(), test_object.find(e));
}

TEST_F(AVLTreeTest, testEmptyWhenEmpty)
{
    test_object = alst::avl_tree<int>();

    bool result = test_object.empty();

    EXPECT_TRUE(result);
}

TEST_F(AVLTreeTest, testIsEmptyWhenNotEmpty)
{
    bool result = test_object.empty();

    EXPECT_FALSE(result);
}

TEST_F(AVLTreeTest, testSizeWhenEmpty)
{
    test_object = alst::avl_tree<int>();

    int result = test_object.size();

    EXPECT_EQ(0, result);
}

TEST_F(AVLTreeTest, testSizeWhenNotEmpty)
{
    int result = test_object.size();

    EXPECT_EQ(numbers.size(), result);
}

TEST_F(AVLTreeTest, testFindWhenPresentElement)
{
    for(auto i : numbers)
    {
        auto result = test_object.find(i);

        EXPECT_NE(test_object.end(), result);
    }
}

TEST_F(AVLTreeTest, testFindWhenOuterElement)
{
    std::vector<int> elems = {111, 140, 187};

    for(auto i : elems)
    {
        auto result = test_object.find(i);

        EXPECT_EQ(test_object.end(), result);
    }
}

TEST_F(AVLTreeTest, testFindWhenConstObjectAndPresentElement)
{
    for(auto i : numbers)
    {
        auto result = const_test_object.find(i);

        EXPECT_NE(const_test_object.end(), result);
    }
}

TEST_F(AVLTreeTest, testFindWhenConstObjectAndOuterElement)
{
    std::vector<int> elems = {111, 140, 187};

    for(auto i : elems)
    {
        auto result = const_test_object.find(i);

        EXPECT_EQ(const_test_object.end(), result);
    }
}

TEST_F(AVLTreeTest, testIteratorWhenFullForLoop)
{
    std::vector<int> result;
    std::vector<int> sorted_numbers = numbers;

    for(auto it = test_object.begin(); it != test_object.end(); ++it)
        result.push_back(*it);

    std::sort(sorted_numbers.begin(), sorted_numbers.end());

    EXPECT_EQ(sorted_numbers, result);
}

TEST_F(AVLTreeTest, testIteratorWhenRangeBasedForLoop)
{
    std::vector<int> result;
    std::vector<int> sorted_numbers = numbers;

    for(const auto & e : test_object)
        result.push_back(e);

    std::sort(sorted_numbers.begin(), sorted_numbers.end());

    EXPECT_EQ(sorted_numbers, result);
}

TEST_F(AVLTreeTest, testConstIteratorWhenAccessElement)
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

TEST_F(AVLTreeTest, testReverseIterator)
{
    std::vector<int> result;
    std::vector<int> reversed_numbers = numbers;

    for(auto it = test_object.rbegin(); it != test_object.rend(); ++it)
        result.push_back(*it);

    std::sort(reversed_numbers.rbegin(), reversed_numbers.rend());

    EXPECT_EQ(reversed_numbers, result);
}

TEST_F(AVLTreeTest, testReverseIteratorWhenConstObject)
{
    std::vector<int> result;
    std::vector<int> reversed_numbers = numbers;

    for(auto it = const_test_object.rbegin(); it != const_test_object.rend(); ++it)
        result.push_back(*it);

    std::sort(reversed_numbers.rbegin(), reversed_numbers.rend());

    EXPECT_EQ(reversed_numbers, result);
}

TEST_F(AVLTreeTest, testConstReverseIteratorWhenAccessElement)
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

TEST_F(AVLTreeTest, testInsertWhenNewElement)
{
    std::vector<int> elems = {111, 140, 187};

    for(auto i : elems)
    {
        auto result = test_object.insert(i);

        ASSERT_TRUE(result.second);
        EXPECT_NE(test_object.end(), result.first);
        EXPECT_EQ(i, *result.first);
        EXPECT_NE(test_object.end(), test_object.find(i));
    }
}

TEST_F(AVLTreeTest, testInsertWhenPresentElement)
{
    std::vector<int> elems = {14, 24, 30, 45};

    for(auto i : elems)
    {
        auto result = test_object.insert(i);

        ASSERT_FALSE(result.second);
        EXPECT_NE(test_object.end(), result.first);
        EXPECT_EQ(i, *result.first);
        EXPECT_NE(test_object.end(), test_object.find(i));
    }
}

TEST_F(AVLTreeTest, testEraseWhenPresentElement)
{
    std::vector<int> elems = {14, 24, 30, 45};

    for(auto i : elems)
    {
        size_t result = test_object.erase(i);

        EXPECT_EQ(1, result);
        EXPECT_EQ(test_object.end(), test_object.find(i));
    }
}

TEST_F(AVLTreeTest, testEraseRootWhenTwoElements1)
{
    int root = 27;
    int elem = 11;

    test_object = alst::avl_tree<int>({root, elem});

    size_t result = test_object.erase(root);

    EXPECT_EQ(1, result);
    EXPECT_EQ(test_object.end(), test_object.find(root));
    EXPECT_NE(test_object.end(), test_object.find(elem));
}

TEST_F(AVLTreeTest, testEraseRootWhenTwoElements2)
{
    int root = 11;
    int elem = 27;

    test_object = alst::avl_tree<int>({root, elem});

    size_t result = test_object.erase(root);

    EXPECT_EQ(1, result);
    EXPECT_EQ(test_object.end(), test_object.find(root));
    EXPECT_NE(test_object.end(), test_object.find(elem));
}

TEST_F(AVLTreeTest, testEraseRootWhenOneElement)
{
    int root = 0;

    test_object = alst::avl_tree<int>({root});

    size_t result = test_object.erase(root);

    EXPECT_EQ(1, result);
    EXPECT_EQ(test_object.end(), test_object.find(root));
    EXPECT_TRUE(test_object.empty());
}

TEST_F(AVLTreeTest, testEraseWhenEmpty)
{
    test_object = alst::avl_tree<int>();

    size_t result = test_object.erase(0);

    EXPECT_EQ(0, result);
    EXPECT_TRUE(test_object.empty());
}

TEST_F(AVLTreeTest, testEraseWhenOuterElement)
{
    std::vector<int> elems = {111, 140, 187};

    for(auto i : elems)
    {
        size_t result = test_object.erase(i);

        EXPECT_EQ(0, result);
        EXPECT_EQ(test_object.end(), test_object.find(i));
    }
}

TEST_F(AVLTreeTest, testClear)
{
    test_object.clear();

    EXPECT_TRUE(test_object.empty());
    EXPECT_EQ(0, test_object.size());
}
