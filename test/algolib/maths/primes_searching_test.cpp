/*!
 * \file primes_searching_test.cpp
 * \brief Tests: Algorithms for searching for prime numbers.
 */
#include <gtest/gtest.h>
#include "algolib/maths/primes_searching.hpp"

namespace alma = algolib::maths;

TEST(PrimesSearchingTest, findPrimes_WhenMinGreaterThanMax_ThenEmpty)
{
    // when
    std::vector<size_t> result = alma::find_primes(100, 30);
    // then
    EXPECT_TRUE(result.empty());
}

TEST(PrimesSearchingTest, findPrimes_WhenSingleArgument_ThenMinIsZero)
{
    // when
    std::vector<size_t> result1 = alma::find_primes(100);
    std::vector<size_t> result2 = alma::find_primes(0, 100);
    // then
    EXPECT_EQ(result1, result2);
}

TEST(PrimesSearchingTest, findPrimes_WhenMaxIsComposite_ThenAllPrimes)
{
    // when
    std::vector<size_t> result = alma::find_primes(100);
    // then
    EXPECT_EQ(
            std::vector<size_t>({2,  3,  5,  7,  11, 13, 17, 19, 23, 29, 31, 37, 41,
                                 43, 47, 53, 59, 61, 67, 71, 73, 79, 83, 89, 97}),
            result);
}

TEST(PrimesSearchingTest, findPrimes_WhenMaxIsPrime_ThenMaxExclusive)
{
    // when
    std::vector<size_t> result = alma::find_primes(67);
    // then
    EXPECT_EQ(
            std::vector<size_t>(
                    {2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37, 41, 43, 47, 53, 59, 61}),
            result);
}

TEST(PrimesSearchingTest, findPrimes_WhenMaxIsTwo_ThenEmpty)
{
    // when
    std::vector<size_t> result = alma::find_primes(2);
    // then
    EXPECT_TRUE(result.empty());
}

TEST(PrimesSearchingTest, findPrimes_WhenMaxIsThree_ThenSingleElement)
{
    // when
    std::vector<size_t> result = alma::find_primes(3);
    // then
    EXPECT_EQ(std::vector<size_t>({2}), result);
}

TEST(PrimesSearchingTest, findPrimes_WhenMaxIsFour_ThenAllPrimes)
{
    // when
    std::vector<size_t> result = alma::find_primes(4);
    // then
    EXPECT_EQ(std::vector<size_t>({2, 3}), result);
}

TEST(PrimesSearchingTest, findPrimes_WhenRange_ThenPrimesBetween)
{
    // when
    std::vector<size_t> result = alma::find_primes(30, 200);
    // then
    EXPECT_EQ(
            std::vector<size_t>({31,  37,  41,  43,  47,  53,  59,  61,  67,  71,  73,  79,
                                 83,  89,  97,  101, 103, 107, 109, 113, 127, 131, 137, 139,
                                 149, 151, 157, 163, 167, 173, 179, 181, 191, 193, 197, 199}),
            result);
}

TEST(PrimesSearchingTest, findPrimes_WhenMinimumIsTwo_ThenTwoIncluded)
{
    // when
    std::vector<size_t> result = alma::find_primes(2, 30);
    // then
    EXPECT_EQ(std::vector<size_t>({2, 3, 5, 7, 11, 13, 17, 19, 23, 29}), result);
}

TEST(PrimesSearchingTest, findPrimes_WhenMinimumIsThree_ThenTwoNotIncluded)
{
    // when
    std::vector<size_t> result = alma::find_primes(3, 30);
    // then
    EXPECT_EQ(std::vector<size_t>({3, 5, 7, 11, 13, 17, 19, 23, 29}), result);
}

TEST(PrimesSearchingTest, findPrimes_WhenMaxIsFourthPowerOfPrime_ThenAllPrimesBetween)
{
    // when
    std::vector<size_t> result = alma::find_primes(9, 81);
    // then
    EXPECT_EQ(
            std::vector<size_t>(
                    {11, 13, 17, 19, 23, 29, 31, 37, 41, 43, 47, 53, 59, 61, 67, 71, 73, 79}),
            result);
}

TEST(PrimesSearchingTest, findPrimes_WhenMinIsLessThanSquareRootOfMax_ThenPrimesBetween)
{
    // when
    std::vector<size_t> result = alma::find_primes(5, 150);
    // then
    EXPECT_EQ(
            std::vector<size_t>({5,  7,   11,  13,  17,  19,  23,  29,  31,  37,  41,
                                 43, 47,  53,  59,  61,  67,  71,  73,  79,  83,  89,
                                 97, 101, 103, 107, 109, 113, 127, 131, 137, 139, 149}),
            result);
}

TEST(PrimesSearchingTest, findPrimes_WhenMinAndMaxArePrimes_ThenMinInclusiveAndMaxExclusive)
{
    // when
    std::vector<size_t> result = alma::find_primes(137, 317);
    // then
    EXPECT_EQ(
            std::vector<size_t>({137, 139, 149, 151, 157, 163, 167, 173, 179, 181, 191,
                                 193, 197, 199, 211, 223, 227, 229, 233, 239, 241, 251,
                                 257, 263, 269, 271, 277, 281, 283, 293, 307, 311, 313}),
            result);
}

TEST(PrimesSearchingTest, findPrimes_WhenMinEqualsMaxAndPrime_ThenEmpty)
{
    // when
    std::vector<size_t> result = alma::find_primes(41, 41);
    // then
    EXPECT_TRUE(result.empty());
}

TEST(PrimesSearchingTest, findPrimes_WhenMinEqualsMaxAndComposite_ThenEmpty)
{
    // when
    std::vector<size_t> result = alma::find_primes(91, 91);
    // then
    EXPECT_TRUE(result.empty());
}
