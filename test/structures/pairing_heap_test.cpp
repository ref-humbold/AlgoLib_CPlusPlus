/*!
 * \file pairing_heap_test.cpp
 * \brief Tests: Structure of pairing heap
 */
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
}
