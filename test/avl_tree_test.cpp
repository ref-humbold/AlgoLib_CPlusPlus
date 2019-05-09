// TESTY DLA DRZEWA AVL
#include <gtest/gtest.h>
#include "algolib/structures/avl_tree.hpp"

namespace alst = algolib::structures;

class AVLTreeTest : public ::testing::Test
{
protected:
    alst::avl_tree<int> test_object;
    const std::vector<int> numbers = {10, 6, 14, 97, 24, 37, 2, 30, 45, 18, 51, 71, 68, 26};

public:
    AVLTreeTest()
        : test_object{alst::avl_tree<int>({10, 6, 14, 97, 24, 37, 2, 30, 45, 18, 51, 71, 68, 26})}
    {
    }

    virtual ~AVLTreeTest() = default;
};

TEST_F(AVLTreeTest, testCopyConstructor)
{
    alst::avl_tree<int> copy_object = test_object;

    ASSERT_EQ(test_object.size(), copy_object.size());

    for(const auto & e : test_object)
        EXPECT_NE(copy_object.end(), copy_object.find(e));
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

    for(const auto & e : test_object)
        EXPECT_NE(copy_object.end(), copy_object.find(e));
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

TEST_F(AVLTreeTest, testConstIterator)
{
    std::vector<int> result;
    std::vector<int> sorted_numbers = numbers;

    for(auto it = test_object.cbegin(); it != test_object.cend(); ++it)
        result.push_back(*it);

    std::sort(sorted_numbers.begin(), sorted_numbers.end());

    EXPECT_EQ(sorted_numbers, result);
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

TEST_F(AVLTreeTest, testConstReverseIterator)
{
    std::vector<int> result;
    std::vector<int> reversed_numbers = numbers;

    for(auto it = test_object.crbegin(); it != test_object.crend(); ++it)
        result.push_back(*it);

    std::sort(reversed_numbers.rbegin(), reversed_numbers.rend());

    EXPECT_EQ(reversed_numbers, result);
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
        test_object.erase(i);

        EXPECT_EQ(test_object.end(), test_object.find(i));
    }
}

TEST_F(AVLTreeTest, testEraseRootWhenTwoElements1)
{
    int root = 27;
    int elem = 11;

    test_object = alst::avl_tree<int>({root, elem});

    test_object.erase(root);

    EXPECT_EQ(test_object.end(), test_object.find(root));
    EXPECT_NE(test_object.end(), test_object.find(elem));
}

TEST_F(AVLTreeTest, testEraseRootWhenTwoElements2)
{
    int root = 11;
    int elem = 27;

    test_object = alst::avl_tree<int>({root, elem});

    test_object.erase(root);

    EXPECT_EQ(test_object.end(), test_object.find(root));
    EXPECT_NE(test_object.end(), test_object.find(elem));
}

TEST_F(AVLTreeTest, testEraseRootWhenOneElement)
{
    int root = 0;

    test_object = alst::avl_tree<int>({root});

    test_object.erase(root);

    EXPECT_EQ(test_object.end(), test_object.find(root));
    EXPECT_TRUE(test_object.empty());
}

TEST_F(AVLTreeTest, testEraseWhenEmpty)
{
    test_object = alst::avl_tree<int>();

    test_object.erase(0);

    EXPECT_TRUE(test_object.empty());
}

TEST_F(AVLTreeTest, testEraseWhenOuterElement)
{
    std::vector<int> elems = {111, 140, 187};

    for(auto i : elems)
    {
        test_object.erase(i);

        EXPECT_EQ(test_object.end(), test_object.find(i));
    }
}

TEST_F(AVLTreeTest, testClear)
{
    test_object.clear();

    EXPECT_TRUE(test_object.empty());
    EXPECT_EQ(0, test_object.size());
}
