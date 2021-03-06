/*!
 * \file primes_test.cpp
 * \brief TEST: Algorithms for prime numbers
 */
#include <gtest/gtest.h>
#include "algolib/mathmat/primes.hpp"

namespace alma = algolib::mathmat;

#pragma region findPrimes

TEST(PrimesTest, findPrimes_WhenRangeIsDescending_ThenEmptyResult)
{
    // when
    std::vector<size_t> result = alma::find_primes(100, 30);
    // then
    EXPECT_TRUE(result.empty());
}

TEST(PrimesTest, findPrimes_WhenSingleMaximumAndRangeFromZero_ThenSameResult)
{
    // when
    std::vector<size_t> result1 = alma::find_primes(100);
    std::vector<size_t> result2 = alma::find_primes(0, 100);
    // then
    EXPECT_EQ(result1, result2);
}

TEST(PrimesTest, findPrimes_WhenSingleMaximum_ThenPrimesFromZero)
{
    // when
    std::vector<size_t> result = alma::find_primes(100);
    // then
    EXPECT_EQ(std::vector<size_t>({2,  3,  5,  7,  11, 13, 17, 19, 23, 29, 31, 37, 41,
                                   43, 47, 53, 59, 61, 67, 71, 73, 79, 83, 89, 97}),
              result);
}

TEST(PrimesTest, findPrimes_WhenMaximumIsPrime_ThenMaximumIsNotContained)
{
    // when
    std::vector<size_t> result = alma::find_primes(67);
    // then
    EXPECT_EQ(std::vector<size_t>(
                      {2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37, 41, 43, 47, 53, 59, 61}),
              result);
}

TEST(PrimesTest, findPrimes_WhenMaximumIsLessThanTwo_ThenEmptyResult)
{
    // when
    std::vector<size_t> result = alma::find_primes(1);
    // then
    EXPECT_TRUE(result.empty());
}

TEST(PrimesTest, findPrimes_WhenRange_ThenPrimesInsideRange)
{
    // when
    std::vector<size_t> result = alma::find_primes(30, 200);
    // then
    EXPECT_EQ(std::vector<size_t>({31,  37,  41,  43,  47,  53,  59,  61,  67,  71,  73,  79,
                                   83,  89,  97,  101, 103, 107, 109, 113, 127, 131, 137, 139,
                                   149, 151, 157, 163, 167, 173, 179, 181, 191, 193, 197, 199}),
              result);
}

TEST(PrimesTest, findPrimes_WhenMinimumLessThanSquareRootOfMaximum_ThenPrimesInsideRange)
{
    // when
    std::vector<size_t> result = alma::find_primes(5, 150);
    // then
    EXPECT_EQ(std::vector<size_t>({5,  7,   11,  13,  17,  19,  23,  29,  31,  37,  41,
                                   43, 47,  53,  59,  61,  67,  71,  73,  79,  83,  89,
                                   97, 101, 103, 107, 109, 113, 127, 131, 137, 139, 149}),
              result);
}

TEST(PrimesTest, findPrimes_WhenRangeBoundariesArePrimes_ThenLeftBoundaryIsIncluded)
{
    // when
    std::vector<size_t> result = alma::find_primes(137, 317);
    // then
    EXPECT_EQ(std::vector<size_t>({137, 139, 149, 151, 157, 163, 167, 173, 179, 181, 191,
                                   193, 197, 199, 211, 223, 227, 229, 233, 239, 241, 251,
                                   257, 263, 269, 271, 277, 281, 283, 293, 307, 311, 313}),
              result);
}

TEST(PrimesTest, findPrimes_WhenRangeBoundariesAreSameAndPrime_ThenEmptyResult)
{
    // when
    std::vector<size_t> result = alma::find_primes(41, 41);
    // then
    EXPECT_TRUE(result.empty());
}

TEST(PrimesTest, findPrimes_WhenRangeBoundariesAreSameAndComposite_ThenEmptyResult)
{
    // when
    std::vector<size_t> result = alma::find_primes(91, 91);
    // then
    EXPECT_TRUE(result.empty());
}

#pragma endregion
#pragma region testFermat

TEST(PrimesTest, testFermat_WhenZero_ThenFalse)
{
    // when
    bool result = alma::test_fermat(0);
    // then
    EXPECT_FALSE(result);
}

TEST(PrimesTest, testFermat_WhenOne_ThenFalse)
{
    // when
    bool result = alma::test_fermat(1);
    // then
    EXPECT_FALSE(result);
}

TEST(PrimesTest, testFermat_WhenTwo_ThenTrue)
{
    // when
    bool result = alma::test_fermat(2);
    // then
    EXPECT_TRUE(result);
}

TEST(PrimesTest, testFermat_WhenPrime_ThenTrue)
{
    // when
    bool result = alma::test_fermat(1013);
    // then
    EXPECT_TRUE(result);
}

TEST(PrimesTest, testFermat_WhenComposite_ThenFalse)
{
    // when
    bool result = alma::test_fermat(1001);
    // then
    EXPECT_FALSE(result);
}

TEST(PrimesTest, testFermat_WhenCarmichaelNumber_ThenFalse)
{
    // when
    bool result = alma::test_fermat(1105);  // 1105 = 5 * 13 * 17 is a Carmichael number
    // then
    EXPECT_FALSE(result);
}

#pragma endregion
#pragma region testMiller

TEST(PrimesTest, testMiller_WhenZero_ThenFalse)
{
    // when
    bool result = alma::test_miller(0);
    // then
    EXPECT_FALSE(result);
}

TEST(PrimesTest, testMiller_WhenOne_ThenFalse)
{
    // when
    bool result = alma::test_miller(1);
    // then
    EXPECT_FALSE(result);
}

TEST(PrimesTest, testMiller_WhenTwo_ThenTrue)
{
    // when
    bool result = alma::test_miller(2);
    // then
    EXPECT_TRUE(result);
}

TEST(PrimesTest, testMiller_WhenPrime_ThenTrue)
{
    // when
    bool result = alma::test_miller(1013);
    // then
    EXPECT_TRUE(result);
}

TEST(PrimesTest, testMiller_WhenComposite1_ThenFalse)
{
    // when
    bool result = alma::test_miller(1001);
    // then
    EXPECT_FALSE(result);
}

TEST(PrimesTest, testMiller_WhenComposite2_ThenFalse)
{
    // when
    bool result = alma::test_miller(1105);
    // then
    EXPECT_FALSE(result);
}

#pragma endregion
