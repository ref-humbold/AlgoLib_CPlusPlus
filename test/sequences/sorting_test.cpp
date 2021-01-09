/*!
 * \file sorting_test.cpp
 * \brief Tests: Algorithms for sorting vectors
 */
#include <algorithm>
#include <gtest/gtest.h>
#include "algolib/sequences/sorting.hpp"

namespace alse = algolib::sequences;

class SortingTest : public ::testing::Test
{
protected:
    std::vector<int> sequence;
    std::vector<int> sorted_sequence;

public:
    SortingTest() : sequence{3, 17, -6, 0, 9, -12, 7, 4, 2}, sorted_sequence{sequence}
    {
    }

    ~SortingTest() override = default;
};

TEST_F(SortingTest, heapSort_ThenSortedAscending)
{
    // given
    std::sort(sorted_sequence.begin(), sorted_sequence.end());
    // when
    alse::heap_sort(sequence);
    // then
    EXPECT_EQ(sorted_sequence, sequence);
}

TEST_F(SortingTest, heapSort_WhenIndices_ThenSubsequenceSortedAscending)
{
    // given
    size_t index_begin = 2, index_end = 7;
    std::sort(sorted_sequence.begin() + index_begin, sorted_sequence.begin() + index_end);
    // when
    alse::heap_sort(sequence, index_begin, index_end);
    // then
    EXPECT_EQ(sorted_sequence, sequence);
}

TEST_F(SortingTest, topDownMergeSort_ThenSortedAscending)
{
    // given
    std::sort(sorted_sequence.begin(), sorted_sequence.end());
    // when
    alse::top_down_merge_sort(sequence);
    // then
    EXPECT_EQ(sorted_sequence, sequence);
}

TEST_F(SortingTest, topDownMergeSort_WhenIndices_ThenSubsequenceSortedAscending)
{
    // given
    size_t index_begin = 2, index_end = 7;
    std::sort(sorted_sequence.begin() + index_begin, sorted_sequence.begin() + index_end);
    // when
    alse::top_down_merge_sort(sequence, index_begin, index_end);
    // then
    EXPECT_EQ(sorted_sequence, sequence);
}

TEST_F(SortingTest, topDownMergeSort_WhenInvalidIndex_ThenSubsequenceSortedAscending)
{
    // when
    auto exec = [&]() { alse::top_down_merge_sort(sequence, 0, 20); };
    // then
    EXPECT_THROW(exec(), std::out_of_range);
}

TEST_F(SortingTest, bottomUpMergeSort_ThenSortedAscending)
{
    // given
    std::sort(sorted_sequence.begin(), sorted_sequence.end());
    // when
    alse::bottom_up_merge_sort(sequence);
    // then
    EXPECT_EQ(sorted_sequence, sequence);
}

TEST_F(SortingTest, bottomUpMergeSort_WhenIndices_ThenSubsequenceSortedAscending)
{
    // given
    size_t index_begin = 2, index_end = 7;
    std::sort(sorted_sequence.begin() + index_begin, sorted_sequence.begin() + index_end);
    // when
    alse::bottom_up_merge_sort(sequence, index_begin, index_end);
    // then
    EXPECT_EQ(sorted_sequence, sequence);
}

TEST_F(SortingTest, bottomUpMergeSort_WhenInvalidIndex_ThenSubsequenceSortedAscending)
{
    // when
    auto exec = [&]() { alse::bottom_up_merge_sort(sequence, 20); };
    // then
    EXPECT_THROW(exec(), std::out_of_range);
}

TEST_F(SortingTest, quickSort_ThenSortedAscending)
{
    // given
    std::sort(sorted_sequence.begin(), sorted_sequence.end());
    // when
    alse::quick_sort(sequence);
    // then
    EXPECT_EQ(sorted_sequence, sequence);
}

TEST_F(SortingTest, quickSort_WhenIndices_ThenSubsequenceSortedAscending)
{
    // given
    size_t index_begin = 2, index_end = 7;
    std::sort(sorted_sequence.begin() + index_begin, sorted_sequence.begin() + index_end);
    // when
    alse::quick_sort(sequence, index_begin, index_end);
    // then
    EXPECT_EQ(sorted_sequence, sequence);
}
