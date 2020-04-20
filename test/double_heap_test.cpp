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

public:
    DoubleHeapTest()
        : test_object{
                alst::double_heap<int>({10, 6, 14, 97, 24, 37, 2, 30, 45, 18, 51, 71, 68, 26})}
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
