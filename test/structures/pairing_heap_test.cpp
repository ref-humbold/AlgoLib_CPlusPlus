/*!
 * \file pairing_heap_test.cpp
 * \brief Tests: Structure of pairing heap
 */
#include <array>
#include <gtest/gtest.h>
#include "algolib/structures/pairing_heap.hpp"

namespace alst = algolib::structures;

class PairingHeapTest : public ::testing::Test
{
protected:
    const std::vector<int> numbers = {10, 6, 14, 97, 24, 37, 2, 30, 45, 18, 51, 71, 68, 26};
    const int maximum;
    alst::pairing_heap<int> test_object;

public:
    PairingHeapTest()
        : maximum{*std::max_element(numbers.begin(), numbers.end())},
          test_object{numbers.begin(), numbers.end()}
    {
    }

    ~PairingHeapTest() override = default;
};

TEST_F(PairingHeapTest, empty_WhenNotEmpty_ThenFalse)
{
    // when
    bool result = test_object.empty();
    // then
    EXPECT_FALSE(result);
}

TEST_F(PairingHeapTest, empty_WhenEmpty_ThenTrue)
{
    // given
    test_object = alst::pairing_heap<int>();
    // when
    bool result = test_object.empty();
    // then
    EXPECT_TRUE(result);
}

TEST_F(PairingHeapTest, size_WhenNotEmpty_ThenNumberOfElements)
{
    // when
    size_t result = test_object.size();
    // then
    EXPECT_EQ(numbers.size(), result);
}

TEST_F(PairingHeapTest, size_WhenEmpty_ThenZero)
{
    // given
    test_object = alst::pairing_heap<int>();
    // when
    size_t result = test_object.size();
    // then
    EXPECT_EQ(0, result);
}

TEST_F(PairingHeapTest, clear_WhenNotEmpty_ThenEmpty)
{
    // when
    test_object.clear();
    // then
    EXPECT_TRUE(test_object.empty());
    EXPECT_EQ(0, test_object.size());
}

#pragma region push & emplace

TEST_F(PairingHeapTest, push_WhenEmpty_ThenAdded)
{
    // given
    int element = 19;

    test_object = alst::pairing_heap<int>();
    // when
    test_object.push(element);
    // then
    ASSERT_EQ(1, test_object.size());
    EXPECT_EQ(element, test_object.top());
}

TEST_F(PairingHeapTest, push_WhenNewElement_ThenAdded)
{
    // when
    test_object.push(46);
    // then
    ASSERT_EQ(numbers.size() + 1, test_object.size());
    EXPECT_EQ(maximum, test_object.top());
}

TEST_F(PairingHeapTest, push_WhenNewElementIsGreaterThanMaximum_ThenNewMaximum)
{
    // given
    int element = maximum + 3;
    // when
    test_object.push(element);
    // then
    ASSERT_EQ(numbers.size() + 1, test_object.size());
    EXPECT_EQ(element, test_object.top());
}

#pragma endregion
#pragma region pop

TEST_F(PairingHeapTest, pop_WhenEmpty_ThenOutOfRange)
{
    // given
    test_object = alst::pairing_heap<int>();
    // when
    auto exec = [&]() { test_object.pop(); };
    // then
    EXPECT_THROW(exec(), std::out_of_range);
}

TEST_F(PairingHeapTest, pop_WhenSingleElement_ThenThisElementRemoved)
{
    // given
    std::array<int, 1> elements = {19};

    test_object = alst::pairing_heap<int>(elements.begin(), elements.end());
    // when
    test_object.pop();
    // then
    EXPECT_EQ(0, test_object.size());
}

TEST_F(PairingHeapTest, pop_WhenMultipleElements_ThenMaximalElementRemoved)
{
    // when
    test_object.pop();
    // then
    EXPECT_EQ(numbers.size() - 1, test_object.size());
}

TEST_F(PairingHeapTest, pop_WhenMultipleCalls_ThenSortedDescending)
{
    // given
    std::vector<int> expected = numbers;

    std::sort(expected.rbegin(), expected.rend());
    // when
    std::vector<int> result;

    while(!test_object.empty())
    {
        result.push_back(test_object.top());
        test_object.pop();
    }
    // then
    EXPECT_EQ(expected, result);
}

#pragma endregion
