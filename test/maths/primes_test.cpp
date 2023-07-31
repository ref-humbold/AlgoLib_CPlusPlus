/*!
 * \file primes_test.cpp
 * \brief TEST: Algorithms for prime numbers
 */
#include <gtest/gtest.h>
#include "algolib/maths/primes.hpp"

namespace alma = algolib::maths;

#pragma region findPrimes

TEST(PrimesTest, findPrimes_WhenMinGreaterThanMax_ThenEmpty)
{
    // when
    std::vector<size_t> result = alma::find_primes(100, 30);
    // then
    EXPECT_TRUE(result.empty());
}

TEST(PrimesTest, findPrimes_WhenSingleArgument_ThenMinIsZero)
{
    // when
    std::vector<size_t> result1 = alma::find_primes(100);
    std::vector<size_t> result2 = alma::find_primes(0, 100);
    // then
    EXPECT_EQ(result1, result2);
}

TEST(PrimesTest, findPrimes_WhenMaxIsComposite_ThenAllPrimes)
{
    // when
    std::vector<size_t> result = alma::find_primes(100);
    // then
    EXPECT_EQ(std::vector<size_t>({2,  3,  5,  7,  11, 13, 17, 19, 23, 29, 31, 37, 41,
                                   43, 47, 53, 59, 61, 67, 71, 73, 79, 83, 89, 97}),
              result);
}

TEST(PrimesTest, findPrimes_WhenMaxIsPrime_ThenMaxExclusive)
{
    // when
    std::vector<size_t> result = alma::find_primes(67);
    // then
    EXPECT_EQ(std::vector<size_t>(
                      {2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37, 41, 43, 47, 53, 59, 61}),
              result);
}

TEST(PrimesTest, findPrimes_WhenMaxIsTwo_ThenEmpty)
{
    // when
    std::vector<size_t> result = alma::find_primes(2);
    // then
    EXPECT_TRUE(result.empty());
}

TEST(PrimesTest, findPrimes_WhenMaxIsThree_ThenSingleElement)
{
    // when
    std::vector<size_t> result = alma::find_primes(3);
    // then
    EXPECT_EQ(std::vector<size_t>({2}), result);
}

TEST(PrimesTest, findPrimes_WhenMaxIsFour_ThenAllPrimes)
{
    // when
    std::vector<size_t> result = alma::find_primes(4);
    // then
    EXPECT_EQ(std::vector<size_t>({2, 3}), result);
}

TEST(PrimesTest, findPrimes_WhenRange_ThenPrimesBetween)
{
    // when
    std::vector<size_t> result = alma::find_primes(30, 200);
    // then
    EXPECT_EQ(std::vector<size_t>({31,  37,  41,  43,  47,  53,  59,  61,  67,  71,  73,  79,
                                   83,  89,  97,  101, 103, 107, 109, 113, 127, 131, 137, 139,
                                   149, 151, 157, 163, 167, 173, 179, 181, 191, 193, 197, 199}),
              result);
}

TEST(PrimesTest, findPrimes_WhenMinimumIsTwo_ThenTwoIncluded)
{
    // when
    std::vector<size_t> result = alma::find_primes(2, 30);
    // then
    EXPECT_EQ(std::vector<size_t>({2, 3, 5, 7, 11, 13, 17, 19, 23, 29}), result);
}

TEST(PrimesTest, findPrimes_WhenMinimumIsThree_ThenTwoNotIncluded)
{
    // when
    std::vector<size_t> result = alma::find_primes(3, 30);
    // then
    EXPECT_EQ(std::vector<size_t>({3, 5, 7, 11, 13, 17, 19, 23, 29}), result);
}

TEST(PrimesTest, findPrimes_WhenMaxIsFourthPowerOfPrime_ThenAllPrimesBetween)
{
    // when
    std::vector<size_t> result = alma::find_primes(9, 81);
    // then
    EXPECT_EQ(std::vector<size_t>(
                      {11, 13, 17, 19, 23, 29, 31, 37, 41, 43, 47, 53, 59, 61, 67, 71, 73, 79}),
              result);
}

TEST(PrimesTest, findPrimes_WhenMinIsLessThanSquareRootOfMax_ThenPrimesBetween)
{
    // when
    std::vector<size_t> result = alma::find_primes(5, 150);
    // then
    EXPECT_EQ(std::vector<size_t>({5,  7,   11,  13,  17,  19,  23,  29,  31,  37,  41,
                                   43, 47,  53,  59,  61,  67,  71,  73,  79,  83,  89,
                                   97, 101, 103, 107, 109, 113, 127, 131, 137, 139, 149}),
              result);
}

TEST(PrimesTest, findPrimes_WhenMinAndMaxArePrimes_ThenMinInclusiveAndMaxExclusive)
{
    // when
    std::vector<size_t> result = alma::find_primes(137, 317);
    // then
    EXPECT_EQ(std::vector<size_t>({137, 139, 149, 151, 157, 163, 167, 173, 179, 181, 191,
                                   193, 197, 199, 211, 223, 227, 229, 233, 239, 241, 251,
                                   257, 263, 269, 271, 277, 281, 283, 293, 307, 311, 313}),
              result);
}

TEST(PrimesTest, findPrimes_WhenMinEqualsMaxAndPrime_ThenEmpty)
{
    // when
    std::vector<size_t> result = alma::find_primes(41, 41);
    // then
    EXPECT_TRUE(result.empty());
}

TEST(PrimesTest, findPrimes_WhenMinEqualsMaxAndComposite_ThenEmpty)
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
    bool result = alma::test_fermat(1001L);
    // then
    EXPECT_FALSE(result);
}

TEST(PrimesTest, testFermat_WhenCarmichaelNumber_ThenFalse)
{
    // when
    bool result = alma::test_fermat(1105LL);  // 1105 = 5 * 13 * 17 is a Carmichael number
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
    bool result = alma::test_miller(1001L);
    // then
    EXPECT_FALSE(result);
}

TEST(PrimesTest, testMiller_WhenComposite2_ThenFalse)
{
    // when
    bool result = alma::test_miller(1105LL);
    // then
    EXPECT_FALSE(result);
}

#pragma endregion
