/*!
 * \file pairing_heap_test.cpp
 * \brief Tests: Structure of pairing heap.
 */
#include <array>
#include <gtest/gtest.h>
#include "algolib/structures/heaps/pairing_heap.hpp"

namespace alsth = algolib::structures::heaps;

std::vector<int> to_vector(alsth::pairing_heap<int> heap)
{
    std::vector<int> result;

    while(!heap.empty())
    {
        result.push_back(heap.top());
        heap.pop();
    }

    return result;
}

class PairingHeapTest : public ::testing::Test
{
protected:
    const std::vector<int> numbers = {10, 6, 14, 97, 24, 37, 2, 30, 45, 18, 51, 71, 68, 26};
    const int maximum;
    alsth::pairing_heap<int> test_object;

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
    test_object = alsth::pairing_heap<int>();
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
    test_object = alsth::pairing_heap<int>();
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

#pragma region top

TEST_F(PairingHeapTest, top_WhenEmpty_ThenOutOfRange)
{
    // given
    test_object = alsth::pairing_heap<int>();
    // when
    auto exec = [&]() { test_object.top(); };
    // then
    EXPECT_THROW(exec(), std::out_of_range);
}

TEST_F(PairingHeapTest, top_WhenSingleElement_ThenThisElement)
{
    // given
    int element = 19;

    test_object = {element};
    // when
    int result = test_object.top();
    // then
    EXPECT_EQ(element, result);
}

TEST_F(PairingHeapTest, top_WhenMultipleElements_ThenMaximalElement)
{
    // when
    int result = test_object.top();
    // then
    EXPECT_EQ(maximum, result);
}

#pragma endregion
#pragma region push & emplace

TEST_F(PairingHeapTest, push_WhenEmpty_ThenAdded)
{
    // given
    int element = 19;

    test_object = alsth::pairing_heap<int>();
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

TEST_F(PairingHeapTest, emplace_WhenNewElement_ThenAdded)
{
    // when
    test_object.emplace(46);
    // then
    ASSERT_EQ(numbers.size() + 1, test_object.size());
    EXPECT_EQ(maximum, test_object.top());
}

TEST_F(PairingHeapTest, emplace_WhenNewElementIsGreaterThanMaximum_ThenNewMaximum)
{
    // given
    int element = maximum + 3;
    // when
    test_object.emplace(element);
    // then
    ASSERT_EQ(numbers.size() + 1, test_object.size());
    EXPECT_EQ(element, test_object.top());
}

#pragma endregion
#pragma region pop

TEST_F(PairingHeapTest, pop_WhenEmpty_ThenOutOfRange)
{
    // given
    test_object = alsth::pairing_heap<int>();
    // when
    auto exec = [&]() { test_object.pop(); };
    // then
    EXPECT_THROW(exec(), std::out_of_range);
}

TEST_F(PairingHeapTest, pop_WhenSingleElement_ThenThisElementRemoved)
{
    // given
    test_object = {19};
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
#pragma region operatorPlusEqual

TEST_F(PairingHeapTest, operatorPlusEqual_WhenEmptyAndNotEmpty_ThenSameAsOther)
{
    // given
    test_object = alsth::pairing_heap<int>();

    alsth::pairing_heap<int> other = alsth::pairing_heap<int>(numbers.begin(), numbers.end());
    // when
    test_object += other;
    // then
    EXPECT_EQ(other.size(), test_object.size());
    EXPECT_EQ(other.top(), test_object.top());
}

TEST_F(PairingHeapTest, operatorPlusEqual_WhenNotEmptyAndEmpty_ThenNoChanges)
{
    // when
    test_object += alsth::pairing_heap<int>();
    // then
    EXPECT_EQ(numbers.size(), test_object.size());
    EXPECT_EQ(maximum, test_object.top());
}

TEST_F(PairingHeapTest, operatorPlusEqual_WhenOtherHasGreaterMaximum_ThenNewMaximum)
{
    // given
    int new_maximum = maximum + 4;
    alsth::pairing_heap<int> other = {new_maximum, maximum - 5, maximum - 13, maximum - 20};
    // when
    test_object += other;
    // then
    EXPECT_EQ(numbers.size() + other.size(), test_object.size());
    EXPECT_EQ(new_maximum, test_object.top());
}

TEST_F(PairingHeapTest, operatorPlusEqual_WhenOtherHasLessMaximum_ThenMaximumRemains)
{
    // given
    alsth::pairing_heap<int> other = {maximum - 5, maximum - 13, maximum - 20};
    // when
    test_object += other;
    // then
    EXPECT_EQ(numbers.size() + other.size(), test_object.size());
    EXPECT_EQ(maximum, test_object.top());
}

TEST_F(PairingHeapTest, operatorPlusEqual_WhenSharedInnerHeap_ThenChangedOnlyMergingHeap)
{
    // given
    test_object = alsth::pairing_heap<int>();

    alsth::pairing_heap<int> first = {4, 8};
    alsth::pairing_heap<int> second = {10, 20};
    // when
    test_object += first;
    test_object += second;
    // then
    EXPECT_EQ(20, test_object.top());
    EXPECT_EQ(to_vector(test_object), std::vector<int>({20, 10, 8, 4}));
    EXPECT_EQ(to_vector(first), std::vector<int>({8, 4}));
    EXPECT_EQ(to_vector(second), std::vector<int>({20, 10}));
}

#pragma endregion
#pragma region operatorPlus

TEST_F(PairingHeapTest, operatorPlus_WhenEmptyAndNotEmpty_ThenSameAsOther)
{
    // given
    test_object = alsth::pairing_heap<int>();

    alsth::pairing_heap<int> other = alsth::pairing_heap<int>(numbers.begin(), numbers.end());
    // when
    alsth::pairing_heap<int> result = test_object + other;
    // then
    EXPECT_EQ(other.size(), result.size());
    EXPECT_EQ(other.top(), result.top());
}

TEST_F(PairingHeapTest, operatorPlus_WhenNotEmptyAndEmpty_ThenNoChanges)
{
    // when
    alsth::pairing_heap<int> result = test_object + alsth::pairing_heap<int>();
    // then
    EXPECT_EQ(numbers.size(), result.size());
    EXPECT_EQ(maximum, result.top());
}

TEST_F(PairingHeapTest, operatorPlus_WhenOtherHasGreaterMaximum_ThenNewMaximum)
{
    // given
    int new_maximum = maximum + 4;
    alsth::pairing_heap<int> other = {new_maximum, maximum - 5, maximum - 13, maximum - 20};
    // when
    alsth::pairing_heap<int> result = test_object + other;
    // then
    EXPECT_EQ(numbers.size() + other.size(), result.size());
    EXPECT_EQ(new_maximum, result.top());
}

TEST_F(PairingHeapTest, operatorPlus_WhenOtherHasLessMaximum_ThenMaximumRemains)
{
    // given
    alsth::pairing_heap<int> other = {maximum - 5, maximum - 13, maximum - 20};
    // when
    alsth::pairing_heap<int> result = test_object + other;
    // then
    EXPECT_EQ(numbers.size() + other.size(), result.size());
    EXPECT_EQ(maximum, result.top());
}

TEST_F(PairingHeapTest, operatorPlus_WhenSharedInnerHeap_ThenChangedOnlyMergingHeap)
{
    // given
    test_object = alsth::pairing_heap<int>();

    alsth::pairing_heap<int> first = {4, 8};
    alsth::pairing_heap<int> second = {10, 20};
    // when
    alsth::pairing_heap<int> result1 = test_object + first;
    alsth::pairing_heap<int> result2 = result1 + second;
    // then
    EXPECT_EQ(8, result1.top());
    EXPECT_EQ(to_vector(result1), std::vector<int>({8, 4}));
    EXPECT_EQ(20, result2.top());
    EXPECT_EQ(to_vector(result2), std::vector<int>({20, 10, 8, 4}));
    EXPECT_EQ(to_vector(test_object), std::vector<int>());
    EXPECT_EQ(to_vector(first), std::vector<int>({8, 4}));
    EXPECT_EQ(to_vector(second), std::vector<int>({20, 10}));
}

#pragma endregion
