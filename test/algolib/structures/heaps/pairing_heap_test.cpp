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

TEST_F(PairingHeapTest, empty_WhenEmpty_ThenTrue)
{
    // when
    bool result = alsth::pairing_heap<int>().empty();

    // then
    EXPECT_TRUE(result);
}

TEST_F(PairingHeapTest, empty_WhenNotEmpty_ThenFalse)
{
    // when
    bool result = test_object.empty();

    // then
    EXPECT_FALSE(result);
}

TEST_F(PairingHeapTest, size_WhenEmpty_ThenZero)
{
    // when
    size_t result = alsth::pairing_heap<int>().size();

    // then
    EXPECT_EQ(0, result);
}

TEST_F(PairingHeapTest, size_WhenNotEmpty_ThenNumberOfElements)
{
    // when
    size_t result = test_object.size();

    // then
    EXPECT_EQ(numbers.size(), result);
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
    int element = numbers[0];

    test_object = alsth::pairing_heap<int>();

    // when
    test_object.push(element);

    // then
    ASSERT_EQ(1, test_object.size());
    EXPECT_EQ(element, test_object.top());
}

TEST_F(PairingHeapTest, push_WhenNewElementLessThanMaximum_ThenAdded)
{
    // when
    test_object.push(maximum - 3);

    // then
    ASSERT_EQ(numbers.size() + 1, test_object.size());
    EXPECT_EQ(maximum, test_object.top());
}

TEST_F(PairingHeapTest, push_WhenNewElementGreaterThanMaximum_ThenNewMaximum)
{
    // given
    int element = maximum + 3;

    // when
    test_object.push(element);

    // then
    ASSERT_EQ(numbers.size() + 1, test_object.size());
    EXPECT_EQ(element, test_object.top());
}

TEST_F(PairingHeapTest, emplace_WhenNewElementLessThanMaximum_ThenAdded)
{
    // when
    test_object.emplace(maximum - 3);

    // then
    ASSERT_EQ(numbers.size() + 1, test_object.size());
    EXPECT_EQ(maximum, test_object.top());
}

TEST_F(PairingHeapTest, emplace_WhenNewElementGreaterThanMaximum_ThenNewMaximum)
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
#pragma region top

TEST_F(PairingHeapTest, top_WhenEmpty_ThenOutOfRange)
{
    // when
    auto exec = [&]() { alsth::pairing_heap<int>().top(); };

    // then
    EXPECT_THROW(exec(), std::out_of_range);
}

TEST_F(PairingHeapTest, top_WhenSingleElement_ThenThisElement)
{
    // given
    int element = numbers[0];

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
    test_object = {numbers[0]};

    // when
    test_object.pop();

    // then
    EXPECT_TRUE(test_object.empty());
    EXPECT_THROW(test_object.top(), std::out_of_range);
}

TEST_F(PairingHeapTest, pop_WhenMultipleElements_ThenMaximalElementRemoved)
{
    // when
    test_object.pop();

    // then
    EXPECT_EQ(numbers.size() - 1, test_object.size());
    EXPECT_NE(maximum, test_object.top());
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

    alsth::pairing_heap<int> other(numbers.begin(), numbers.end());

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

TEST_F(PairingHeapTest, operatorPlusEqual_WhenOtherHasGreaterMaximum_ThenNewMaximum)
{
    // given
    std::vector<int> elements = {maximum + 3, maximum - 5, maximum - 13, maximum - 20};
    alsth::pairing_heap<int> other(elements.begin(), elements.end());

    // when
    test_object += other;

    // then
    EXPECT_EQ(numbers.size() + other.size(), test_object.size());
    EXPECT_EQ(*std::max_element(elements.begin(), elements.end()), test_object.top());
}

TEST_F(PairingHeapTest, operatorPlusEqual_WhenSharedInnerHeap_ThenChangedOnlyMergingHeap)
{
    // given
    std::vector<int> first_elements = {4, 8};
    std::vector<int> second_elements = {10, 20};
    std::vector<int> all_elements;

    all_elements.insert(all_elements.end(), first_elements.begin(), first_elements.end());
    all_elements.insert(all_elements.end(), second_elements.begin(), second_elements.end());
    test_object = alsth::pairing_heap<int>();

    alsth::pairing_heap<int> first(first_elements.begin(), first_elements.end());
    alsth::pairing_heap<int> second(second_elements.begin(), second_elements.end());

    // when
    test_object += first;
    test_object += second;

    // then
    std::sort(first_elements.rbegin(), first_elements.rend());
    std::sort(second_elements.rbegin(), second_elements.rend());
    std::sort(all_elements.rbegin(), all_elements.rend());

    EXPECT_EQ(all_elements[0], test_object.top());
    EXPECT_EQ(to_vector(test_object), all_elements);
    EXPECT_EQ(to_vector(first), first_elements);
    EXPECT_EQ(to_vector(second), second_elements);
}

#pragma endregion
#pragma region operatorPlus

TEST_F(PairingHeapTest, operatorPlus_WhenEmptyAndNotEmpty_ThenSameAsOther)
{
    // given
    test_object = alsth::pairing_heap<int>();

    alsth::pairing_heap<int> other(numbers.begin(), numbers.end());

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

TEST_F(PairingHeapTest, operatorPlus_WhenOtherHasGreaterMaximum_ThenNewMaximum)
{
    // given
    std::vector<int> elements = {maximum + 3, maximum - 5, maximum - 13, maximum - 20};
    alsth::pairing_heap<int> other(elements.begin(), elements.end());

    // when
    alsth::pairing_heap<int> result = test_object + other;

    // then
    EXPECT_EQ(numbers.size() + other.size(), result.size());
    EXPECT_EQ(*max_element(elements.begin(), elements.end()), result.top());
}

TEST_F(PairingHeapTest, operatorPlus_WhenSharedInnerHeap_ThenChangedOnlyMergingHeap)
{
    // given
    std::vector<int> first_elements = {4, 8};
    std::vector<int> second_elements = {10, 20};
    std::vector<int> all_elements;

    all_elements.insert(all_elements.end(), first_elements.begin(), first_elements.end());
    all_elements.insert(all_elements.end(), second_elements.begin(), second_elements.end());
    test_object = alsth::pairing_heap<int>();

    alsth::pairing_heap<int> first(first_elements.begin(), first_elements.end());
    alsth::pairing_heap<int> second(second_elements.begin(), second_elements.end());

    // when
    alsth::pairing_heap<int> result1 = test_object + first;
    alsth::pairing_heap<int> result2 = result1 + second;

    // then
    std::sort(first_elements.rbegin(), first_elements.rend());
    std::sort(second_elements.rbegin(), second_elements.rend());
    std::sort(all_elements.rbegin(), all_elements.rend());

    EXPECT_EQ(*max_element(first_elements.begin(), first_elements.end()), result1.top());
    EXPECT_EQ(to_vector(result1), first_elements);
    EXPECT_EQ(*max_element(second_elements.begin(), second_elements.end()), result2.top());
    EXPECT_EQ(to_vector(result2), all_elements);
    EXPECT_TRUE(test_object.empty());
    EXPECT_EQ(to_vector(first), first_elements);
    EXPECT_EQ(to_vector(second), second_elements);
}

#pragma endregion
