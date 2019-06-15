/*!
 * \file avl_tree_test.cpp
 * \brief TEST: Algorithms for prime numbers
 */
#include <gtest/gtest.h>
#include "algolib/mathmat/primes.hpp"

namespace alma = algolib::mathmat;

#pragma region testFindPrimes

TEST(PrimesTest, testFindPrimesTwoArgsDescending)
{
    EXPECT_THROW(alma::find_primes(100, 30), std::invalid_argument);
}

TEST(PrimesTest, testFindPrimesOneArgIsTwoArgs_with_zero_asMin)
{
    std::vector<size_t> result1 = alma::find_primes(100);
    std::vector<size_t> result2 = alma::find_primes(0, 100);

    EXPECT_EQ(result1, result2);
}

TEST(PrimesTest, testFindPrimesOneArg)
{
    std::vector<size_t> result = alma::find_primes(100);

    EXPECT_EQ(std::vector<size_t>({2,  3,  5,  7,  11, 13, 17, 19, 23, 29, 31, 37, 41,
                                   43, 47, 53, 59, 61, 67, 71, 73, 79, 83, 89, 97}),
              result);
}

TEST(PrimesTest, testFindPrimesOneArgWhenMaxIsPrime)
{
    std::vector<size_t> result = alma::find_primes(67);

    EXPECT_EQ(std::vector<size_t>(
                      {2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37, 41, 43, 47, 53, 59, 61, 67}),
              result);
}

TEST(PrimesTest, testFindPrimesOneArgWhenLessThanTwo)
{
    std::vector<size_t> result = alma::find_primes(1);

    EXPECT_EQ(std::vector<size_t>(), result);
}

TEST(PrimesTest, testFindPrimesTwoArgs)
{
    std::vector<size_t> result = alma::find_primes(30, 200);

    EXPECT_EQ(std::vector<size_t>({31,  37,  41,  43,  47,  53,  59,  61,  67,  71,  73,  79,
                                   83,  89,  97,  101, 103, 107, 109, 113, 127, 131, 137, 139,
                                   149, 151, 157, 163, 167, 173, 179, 181, 191, 193, 197, 199}),
              result);
}

TEST(PrimesTest, testFindPrimesTwoArgsWhenMinLessThanSqrtOfMax)
{
    std::vector<size_t> result = alma::find_primes(5, 150);

    EXPECT_EQ(std::vector<size_t>({5,  7,   11,  13,  17,  19,  23,  29,  31,  37,  41,
                                   43, 47,  53,  59,  61,  67,  71,  73,  79,  83,  89,
                                   97, 101, 103, 107, 109, 113, 127, 131, 137, 139, 149}),
              result);
}

TEST(PrimesTest, testFindPrimesTwoArgsWhenMinAndMaxArePrimes)
{
    std::vector<size_t> result = alma::find_primes(137, 317);

    EXPECT_EQ(std::vector<size_t>({137, 139, 149, 151, 157, 163, 167, 173, 179, 181, 191, 193,
                                   197, 199, 211, 223, 227, 229, 233, 239, 241, 251, 257, 263,
                                   269, 271, 277, 281, 283, 293, 307, 311, 313, 317}),
              result);
}

TEST(PrimesTest, testFindPrimesTwoArgsWhenMinEqualsMaxAndPrime)
{
    std::vector<size_t> result = alma::find_primes(41, 41);

    EXPECT_EQ(std::vector<size_t>({41}), result);
}

TEST(PrimesTest, testFindPrimesTwoArgsWhenMinEqualsMaxAndComposite)
{
    std::vector<size_t> result = alma::find_primes(91, 91);

    EXPECT_EQ(std::vector<size_t>(), result);
}

#pragma endregion
#pragma region testTestFermat

TEST(PrimesTest, testTestFermatWhenZero)
{
    bool result = alma::test_fermat(0);

    EXPECT_FALSE(result);
}

TEST(PrimesTest, testTestFermatWhenOne)
{
    bool result = alma::test_fermat(1);

    EXPECT_FALSE(result);
}

TEST(PrimesTest, testTestFermatWhenTwo)
{
    bool result = alma::test_fermat(2);

    EXPECT_TRUE(result);
}

TEST(PrimesTest, testTestFermatWhenPrime)
{
    bool result = alma::test_fermat(1013);

    EXPECT_TRUE(result);
}

TEST(PrimesTest, testTestFermatWhenComposite)
{
    bool result = alma::test_fermat(1001);

    EXPECT_FALSE(result);
}

TEST(PrimesTest, testTestFermatWhenCarmichaelNumber)
{
    bool result = alma::test_fermat(1105);  // 1105 = 5 * 13 * 17 is a Carmichael number

    EXPECT_FALSE(result);
}

#pragma endregion
#pragma region testTestMiller

TEST(PrimesTest, testTestMillerWhenZero)
{
    bool result = alma::test_miller(0);

    EXPECT_FALSE(result);
}

TEST(PrimesTest, testTestMillerWhenOne)
{
    bool result = alma::test_miller(1);

    EXPECT_FALSE(result);
}

TEST(PrimesTest, testTestMillerWhenTwo)
{
    bool result = alma::test_miller(2);

    EXPECT_TRUE(result);
}

TEST(PrimesTest, testTestMillerWhenPrime)
{
    bool result = alma::test_miller(1013);

    EXPECT_TRUE(result);
}

TEST(PrimesTest, testTestMillerWhenComposite1)
{
    bool result = alma::test_miller(1001);

    EXPECT_FALSE(result);
}

TEST(PrimesTest, testTestMillerWhenComposite2)
{
    bool result = alma::test_miller(1105);

    EXPECT_FALSE(result);
}

#pragma endregion
