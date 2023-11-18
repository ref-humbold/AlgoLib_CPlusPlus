/*!
 * \file primes_testing_test.cpp
 * \brief Tests: Algorithms for testing prime numbers.
 */
#include <gtest/gtest.h>
#include "algolib/maths/primes_testing.hpp"

namespace alma = algolib::maths;

#pragma region test_prime_fermat

TEST(PrimesTestingTest, testPrimeFermat_WhenZero_ThenFalse)
{
    // when
    bool result = alma::test_prime_fermat(0);
    // then
    EXPECT_FALSE(result);
}

TEST(PrimesTestingTest, testPrimeFermat_WhenOne_ThenFalse)
{
    // when
    bool result = alma::test_prime_fermat(1);
    // then
    EXPECT_FALSE(result);
}

TEST(PrimesTestingTest, testPrimeFermat_WhenTwo_ThenTrue)
{
    // when
    bool result = alma::test_prime_fermat(2);
    // then
    EXPECT_TRUE(result);
}

TEST(PrimesTestingTest, testPrimeFermat_WhenPrime_ThenTrue)
{
    // when
    bool result = alma::test_prime_fermat(1013);
    // then
    EXPECT_TRUE(result);
}

TEST(PrimesTestingTest, testPrimeFermat_WhenComposite1_ThenFalse)
{
    // when
    bool result = alma::test_prime_fermat(1001L);
    // then
    EXPECT_FALSE(result);
}

TEST(PrimesTestingTest, testPrimeFermat_WhenComposite2_ThenFalse)
{
    // when
    bool result =
            alma::test_prime_fermat(41041LL);  // 41041 = 7 * 11 * 13 * 41 is a Carmichael number
    // then
    EXPECT_FALSE(result);
}

#pragma endregion
#pragma region test_prime_miller

TEST(PrimesTestingTest, testPrimeMiller_WhenZero_ThenFalse)
{
    // when
    bool result = alma::test_prime_miller(0);
    // then
    EXPECT_FALSE(result);
}

TEST(PrimesTestingTest, testPrimeMiller_WhenOne_ThenFalse)
{
    // when
    bool result = alma::test_prime_miller(1);
    // then
    EXPECT_FALSE(result);
}

TEST(PrimesTestingTest, testPrimeMiller_WhenTwo_ThenTrue)
{
    // when
    bool result = alma::test_prime_miller(2);
    // then
    EXPECT_TRUE(result);
}

TEST(PrimesTestingTest, testPrimeMiller_WhenPrime_ThenTrue)
{
    // when
    bool result = alma::test_prime_miller(1013);
    // then
    EXPECT_TRUE(result);
}

TEST(PrimesTestingTest, testPrimeMiller_WhenComposite1_ThenFalse)
{
    // when
    bool result = alma::test_prime_miller(1001L);
    // then
    EXPECT_FALSE(result);
}

TEST(PrimesTestingTest, testPrimeMiller_WhenComposite2_ThenFalse)
{
    // when
    bool result = alma::test_prime_miller(41041LL);
    // then
    EXPECT_FALSE(result);
}

#pragma endregion
