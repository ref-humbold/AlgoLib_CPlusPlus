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

TEST(PrimesTestingTest, testPrimeFermat_WhenPrimeLong_ThenTrue)
{
    // when
    bool result = alma::test_prime_fermat(2131L);
    // then
    EXPECT_TRUE(result);
}

TEST(PrimesTestingTest, testPrimeFermat_WhenPrimeLongLong_ThenTrue)
{
    // when
    bool result = alma::test_prime_fermat(6199LL);
    // then
    EXPECT_TRUE(result);
}

TEST(PrimesTestingTest, testPrimeFermat_WhenComposite_ThenFalse)
{
    // when
    bool result = alma::test_prime_fermat(1001L);  // 1001 = 7 * 11 * 13
    // then
    EXPECT_FALSE(result);
}

TEST(PrimesTestingTest, testPrimeFermat_WhenCompositeLong_ThenFalse)
{
    // when
    bool result = alma::test_prime_fermat(41041L);  // 41041 = 7 * 11 * 13 * 41
    // then
    EXPECT_FALSE(result);
}

TEST(PrimesTestingTest, testPrimeFermat_WhenCompositeLongLong_ThenFalse)
{
    // when
    bool result = alma::test_prime_fermat(73627LL);  // 73627 = 17 * 61 * 71
    // then
    EXPECT_FALSE(result);
}

TEST(PrimesTestingTest, testPrimeFermat_WhenCompositeSquareOfPrime_ThenFalse)
{
    // when
    bool result = alma::test_prime_fermat(3481);  // 3481 = 59 ^ 2
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

TEST(PrimesTestingTest, testPrimeMiller_WhenPrimeLong_ThenTrue)
{
    // when
    bool result = alma::test_prime_miller(2131L);
    // then
    EXPECT_TRUE(result);
}

TEST(PrimesTestingTest, testPrimeMiller_WhenPrimeLongLong_ThenTrue)
{
    // when
    bool result = alma::test_prime_miller(6199LL);
    // then
    EXPECT_TRUE(result);
}

TEST(PrimesTestingTest, testPrimeMiller_WhenComposite_ThenFalse)
{
    // when
    bool result = alma::test_prime_miller(1001L);
    // then
    EXPECT_FALSE(result);
}

TEST(PrimesTestingTest, testPrimeMiller_WhenCompositeLong_ThenFalse)
{
    // when
    bool result = alma::test_prime_miller(41041L);
    // then
    EXPECT_FALSE(result);
}

TEST(PrimesTestingTest, testPrimeMiller_WhenCompositeLongLong_ThenFalse)
{
    // when
    bool result = alma::test_prime_miller(73627LL);
    // then
    EXPECT_FALSE(result);
}

TEST(PrimesTestingTest, testPrimeMiller_WhenCompositeSquareOfPrime_ThenFalse)
{
    // when
    bool result = alma::test_prime_miller(3481);
    // then
    EXPECT_FALSE(result);
}

#pragma endregion
