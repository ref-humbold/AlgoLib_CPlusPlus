/*!
 * \file double_heap_test.cpp
 * \brief Tests: Structure of double heap
 */
#include <gtest/gtest.h>
#include "algolib/structures/double_heap.hpp"

namespace alst = algolib::structures;

class DoubleHeapTest : public ::testing::Test
{
protected:
    const std::vector<int> numbers = {10, 6, 14, 97, 24, 37, 2, 30, 45, 18, 51, 71, 68, 26};
    const int minimum, maximum;
    alst::double_heap<int> test_object;

public:
    DoubleHeapTest()
        : minimum{*std::min_element(numbers.begin(), numbers.end())},
          maximum{*std::max_element(numbers.begin(), numbers.end())},
          test_object{numbers.begin(), numbers.end()}
    {
    }

    ~DoubleHeapTest() override = default;
};

TEST_F(DoubleHeapTest, empty_WhenNotEmpty_ThenFalse)
{
    // when
    bool result = test_object.empty();
    // then
    EXPECT_FALSE(result);
}

TEST_F(DoubleHeapTest, empty_WhenEmpty_ThenTrue)
{
    // given
    test_object = alst::double_heap<int>();
    // when
    bool result = test_object.empty();
    // then
    EXPECT_TRUE(result);
}

TEST_F(DoubleHeapTest, size_WhenNotEmpty_ThenNumberOfElements)
{
    // when
    size_t result = test_object.size();
    // then
    EXPECT_EQ(numbers.size(), result);
}

TEST_F(DoubleHeapTest, size_WhenEmpty_ThenZero)
{
    // given
    test_object = alst::double_heap<int>();
    // when
    size_t result = test_object.size();
    // then
    EXPECT_EQ(0, result);
}

TEST_F(DoubleHeapTest, min_WhenEmpty_ThenOutOfRange)
{
    // given
    test_object = alst::double_heap<int>();
    // when
    auto exec = [&]() { test_object.min(); };
    // then
    EXPECT_THROW(exec(), std::out_of_range);
}

TEST_F(DoubleHeapTest, min_WhenNotEmpty_ThenMinimalElement)
{
    // when
    int result = test_object.min();
    // then
    EXPECT_EQ(minimum, result);
}

TEST_F(DoubleHeapTest, max_WhenEmpty_ThenOutOfRange)
{
    // given
    test_object = alst::double_heap<int>();
    // when
    auto exec = [&]() { test_object.max(); };
    // then
    EXPECT_THROW(exec(), std::out_of_range);
}

TEST_F(DoubleHeapTest, max_WhenSingleElement_ThenThisElement)
{
    // given
    int element = 19;

    test_object = alst::double_heap<int>(std::less<int>(), {element});
    // when
    int result = test_object.max();
    // then
    EXPECT_EQ(element, result);
}

TEST_F(DoubleHeapTest, max_WhenMultipleElements_ThenMaximalElement)
{
    // when
    int result = test_object.max();
    // then
    EXPECT_EQ(maximum, result);
}

TEST_F(DoubleHeapTest, push_WhenEmpty_ThenAdded)
{
    // given
    int element = 19;

    test_object = alst::double_heap<int>();
    // when
    test_object.push(element);
    // then
    ASSERT_EQ(1, test_object.size());
    EXPECT_EQ(element, test_object.min());
    EXPECT_EQ(element, test_object.max());
}

TEST_F(DoubleHeapTest, push_WhenNewElementIsLess_ThenAddedToMin)
{
    // given
    int element = minimum - 1;
    // when
    test_object.push(element);
    // then
    ASSERT_EQ(numbers.size() + 1, test_object.size());
    EXPECT_EQ(element, test_object.min());
}

TEST_F(DoubleHeapTest, push_WhenNewElementIsGreater_ThenAddedToMax)
{
    // given
    int element = maximum + 1;
    // when
    test_object.push(element);
    // then
    ASSERT_EQ(numbers.size() + 1, test_object.size());
    EXPECT_EQ(element, test_object.max());
}

TEST_F(DoubleHeapTest, emplace_WhenNewElementIsLess_ThenAddedToMin)
{
    // given
    int element = minimum - 1;
    // when
    test_object.emplace(element);
    // then
    ASSERT_EQ(numbers.size() + 1, test_object.size());
    EXPECT_EQ(element, test_object.min());
}

TEST_F(DoubleHeapTest, emplace_WhenNewElementIsGreater_ThenAddedToMax)
{
    // given
    int element = maximum + 1;
    // when
    test_object.emplace(element);
    // then
    ASSERT_EQ(numbers.size() + 1, test_object.size());
    EXPECT_EQ(element, test_object.max());
}

TEST_F(DoubleHeapTest, push_WhenNewElement_ThenAdded)
{
    // when
    test_object.push(46);
    // then
    ASSERT_EQ(numbers.size() + 1, test_object.size());
    EXPECT_EQ(minimum, test_object.min());
    EXPECT_EQ(maximum, test_object.max());
}

TEST_F(DoubleHeapTest, popMin_WhenEmpty_ThenOutOfRange)
{
    // given
    test_object = alst::double_heap<int>();
    // when
    auto exec = [&]() { test_object.pop_min(); };
    // then
    EXPECT_THROW(exec(), std::out_of_range);
}

TEST_F(DoubleHeapTest, popMin_WhenNotEmpty_ThenMinimalElementRemoved)
{
    // when
    test_object.pop_min();
    // then
    EXPECT_EQ(numbers.size() - 1, test_object.size());
}

TEST_F(DoubleHeapTest, popMin_WhenSingleElement_ThenThisElementRemoved)
{
    // given
    test_object = alst::double_heap<int>(std::less<int>(), {19});
    // when
    test_object.pop_min();
    // then
    EXPECT_EQ(0, test_object.size());
}

TEST_F(DoubleHeapTest, popMin_WhenMultipleCalls_ThenSortedAscending)
{
    // given
    std::vector<int> expected = numbers;

    std::sort(expected.begin(), expected.end());
    // when
    std::vector<int> result;

    while(!test_object.empty())
    {
        result.push_back(test_object.min());
        test_object.pop_min();
    }
    // then
    EXPECT_EQ(expected, result);
}

TEST_F(DoubleHeapTest, popMax_WhenEmpty_ThenOutOfRange)
{
    // given
    test_object = alst::double_heap<int>();
    // when
    auto exec = [&]() { test_object.pop_max(); };
    // then
    EXPECT_THROW(exec(), std::out_of_range);
}

TEST_F(DoubleHeapTest, popMax_WhenSingleElement_ThenThisElementRemoved)
{
    // given
    test_object = alst::double_heap<int>(std::less<int>(), {19});
    // when
    test_object.pop_max();
    // then
    EXPECT_EQ(0, test_object.size());
}

TEST_F(DoubleHeapTest, popMax_WhenMultipleElements_ThenMaximalElementRemoved)
{
    // when
    test_object.pop_max();
    // then
    EXPECT_EQ(numbers.size() - 1, test_object.size());
}

TEST_F(DoubleHeapTest, popMax_WhenMultipleCalls_ThenSortedDescending)
{
    // given
    std::vector<int> expected = numbers;

    std::sort(expected.rbegin(), expected.rend());
    // when
    std::vector<int> result;

    while(!test_object.empty())
    {
        result.push_back(test_object.max());
        test_object.pop_max();
    }
    // then
    EXPECT_EQ(expected, result);
}

TEST_F(DoubleHeapTest, clear_WhenNotEmpty_ThenEmpty)
{
    // when
    test_object.clear();
    // then
    EXPECT_TRUE(test_object.empty());
}
