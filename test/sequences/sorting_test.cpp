
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

TEST_F(SortingTest, heapSort_thenSortedAscending)
{
    // given
    std::sort(sorted_sequence.begin(), sorted_sequence.end());
    // when
    alse::heap_sort(sequence);
    // then
    EXPECT_EQ(sorted_sequence, sequence);
}

TEST_F(SortingTest, heapSort_whenIndices_thenSubsequenceSortedAscending)
{
    // given
    size_t index_begin = 2, index_end = 7;
    std::sort(sorted_sequence.begin() + index_begin, sorted_sequence.begin() + index_end);
    // when
    alse::heap_sort(sequence, index_begin, index_end);
    // then
    EXPECT_EQ(sorted_sequence, sequence);
}

TEST_F(SortingTest, topDownMergeSort_thenSortedAscending)
{
    // given
    std::sort(sorted_sequence.begin(), sorted_sequence.end());
    // when
    alse::top_down_merge_sort(sequence);
    // then
    EXPECT_EQ(sorted_sequence, sequence);
}

TEST_F(SortingTest, topDownMergeSort_whenIndices_thenSubsequenceSortedAscending)
{
    // given
    size_t index_begin = 2, index_end = 7;
    std::sort(sorted_sequence.begin() + index_begin, sorted_sequence.begin() + index_end);
    // when
    alse::top_down_merge_sort(sequence, index_begin, index_end);
    // then
    EXPECT_EQ(sorted_sequence, sequence);
}

TEST_F(SortingTest, topDownMergeSort_whenInvalidIndex_thenSubsequenceSortedAscending)
{
    // when
    auto exec = [&]() { alse::top_down_merge_sort(sequence, 0, 20); };
    // then
    EXPECT_THROW(exec(), std::out_of_range);
}

TEST_F(SortingTest, bottomUpMergeSort_thenSortedAscending)
{
    // given
    std::sort(sorted_sequence.begin(), sorted_sequence.end());
    // when
    alse::bottom_up_merge_sort(sequence);
    // then
    EXPECT_EQ(sorted_sequence, sequence);
}

TEST_F(SortingTest, bottomUpMergeSort_whenIndices_thenSubsequenceSortedAscending)
{
    // given
    size_t index_begin = 2, index_end = 7;
    std::sort(sorted_sequence.begin() + index_begin, sorted_sequence.begin() + index_end);
    // when
    alse::bottom_up_merge_sort(sequence, index_begin, index_end);
    // then
    EXPECT_EQ(sorted_sequence, sequence);
}

TEST_F(SortingTest, bottomUpMergeSort_whenInvalidIndex_thenSubsequenceSortedAscending)
{
    // when
    auto exec = [&]() { alse::bottom_up_merge_sort(sequence, 20); };
    // then
    EXPECT_THROW(exec(), std::out_of_range);
}

TEST_F(SortingTest, quickSort_thenSortedAscending)
{
    // given
    std::sort(sorted_sequence.begin(), sorted_sequence.end());
    // when
    alse::quick_sort(sequence);
    // then
    EXPECT_EQ(sorted_sequence, sequence);
}

TEST_F(SortingTest, quickSort_whenIndices_thenSubsequenceSortedAscending)
{
    // given
    size_t index_begin = 2, index_end = 7;
    std::sort(sorted_sequence.begin() + index_begin, sorted_sequence.begin() + index_end);
    // when
    alse::quick_sort(sequence, index_begin, index_end);
    // then
    EXPECT_EQ(sorted_sequence, sequence);
}
