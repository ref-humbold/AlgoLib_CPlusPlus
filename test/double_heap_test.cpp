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
    alst::double_heap<int> test_object;
    const std::vector<int> numbers = {10, 6, 14, 97, 24, 37, 2, 30, 45, 18, 51, 71, 68, 26};
    const int minimum;
    const int maximum;

public:
    DoubleHeapTest()
        : test_object{alst::double_heap<int>(
                {10, 6, 14, 97, 24, 37, 2, 30, 45, 18, 51, 71, 68, 26})},
          minimum{*std::min_element(numbers.begin(), numbers.end())},
          maximum{*std::max_element(numbers.begin(), numbers.end())}
    {
    }

    ~DoubleHeapTest() override = default;
};

TEST_F(DoubleHeapTest, empty_whenNotEmpty_thenFalse)
{
    // when
    bool result = test_object.empty();
    // then
    EXPECT_FALSE(result);
}

TEST_F(DoubleHeapTest, empty_whenEmpty_thenTrue)
{
    // given
    test_object = alst::double_heap<int>();
    // when
    bool result = test_object.empty();
    // then
    EXPECT_TRUE(result);
}

TEST_F(DoubleHeapTest, size_whenNotEmpty_thenNumberOfElements)
{
    // when
    size_t result = test_object.size();
    // then
    EXPECT_EQ(numbers.size(), result);
}

TEST_F(DoubleHeapTest, size_whenEmpty_thenZero)
{
    // given
    test_object = alst::double_heap<int>();
    // when
    size_t result = test_object.size();
    // then
    EXPECT_EQ(0, result);
}

TEST_F(DoubleHeapTest, front_whenEmpty_thenOutOfRange)
{
    // given
    test_object = alst::double_heap<int>();
    // when - then
    EXPECT_THROW(test_object.front(), std::out_of_range);
}

TEST_F(DoubleHeapTest, front_whenNotEmpty_thenMinimalElement)
{
    // when
    int result = test_object.front();
    // then
    EXPECT_EQ(minimum, result);
}

TEST_F(DoubleHeapTest, back_whenEmpty_thenOutOfRange)
{
    // given
    test_object = alst::double_heap<int>();
    // then
    EXPECT_THROW(test_object.back(), std::out_of_range);
}

TEST_F(DoubleHeapTest, back_whenSingleElement_thenThisElement)
{
    // given
    int element = 19;

    test_object = alst::double_heap<int>({element});
    // when
    int result = test_object.back();
    // then
    EXPECT_EQ(element, result);
}

TEST_F(DoubleHeapTest, back_whenMultipleElements_thenMaximalElement)
{
    // when
    int result = test_object.back();
    // then
    EXPECT_EQ(maximum, result);
}

TEST_F(DoubleHeapTest, push_whenEmpty_thenAdded)
{
    // given
    int element = 19;

    test_object = alst::double_heap<int>();
    // when
    test_object.push(element);
    // then
    ASSERT_EQ(1, test_object.size());
    EXPECT_EQ(element, test_object.front());
    EXPECT_EQ(element, test_object.back());
}

TEST_F(DoubleHeapTest, push_whenNewElementIsLess_thenAddedToFront)
{
    // given
    int element = minimum - 1;
    // when
    test_object.push(element);
    // then
    ASSERT_EQ(numbers.size() + 1, test_object.size());
    EXPECT_EQ(element, test_object.front());
}

TEST_F(DoubleHeapTest, push_whenNewElementIsGreater_thenAddedToBack)
{
    // given
    int element = maximum + 1;
    // when
    test_object.push(element);
    // then
    ASSERT_EQ(numbers.size() + 1, test_object.size());
    EXPECT_EQ(element, test_object.back());
}

TEST_F(DoubleHeapTest, push_whenNewElement_thenAdded)
{
    // when
    test_object.push(46);
    // then
    ASSERT_EQ(numbers.size() + 1, test_object.size());
    EXPECT_EQ(minimum, test_object.front());
    EXPECT_EQ(maximum, test_object.back());
}

TEST_F(DoubleHeapTest, popFront_whenEmpty_thenOutOfRange)
{
    // given
    test_object = alst::double_heap<int>();
    // when - then
    EXPECT_THROW(test_object.pop_front(), std::out_of_range);
}

TEST_F(DoubleHeapTest, popFront_whenNotEmpty_thenMinimalElementRemoved)
{
    // when
    test_object.pop_front();
    // then
    EXPECT_EQ(numbers.size() - 1, test_object.size());
}

TEST_F(DoubleHeapTest, popFront_whenSingleElement_thenThisElementRemoved)
{
    // given
    test_object = alst::double_heap<int>({19});
    // when
    test_object.pop_front();
    // then
    EXPECT_EQ(0, test_object.size());
}

TEST_F(DoubleHeapTest, popBack_whenEmpty_thenOutOfRange)
{
    // given
    test_object = alst::double_heap<int>();
    // when - then
    EXPECT_THROW(test_object.pop_back(), std::out_of_range);
}

TEST_F(DoubleHeapTest, popBack_whenSingleElement_thenThisElementRemoved)
{
    // given
    test_object = alst::double_heap<int>({19});
    // when
    test_object.pop_back();
    // then
    EXPECT_EQ(0, test_object.size());
}

TEST_F(DoubleHeapTest, popBack_whenMultipleElements_thenMaximalElementRemoved)
{
    // when
    test_object.pop_back();
    // then
    EXPECT_EQ(numbers.size() - 1, test_object.size());
}

TEST_F(DoubleHeapTest, clear_whenNotEmpty_thenEmpty)
{
    // when
    test_object.clear();
    // then
    EXPECT_TRUE(test_object.empty());
}
