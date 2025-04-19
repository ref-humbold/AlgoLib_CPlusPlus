/*!
 * \file primes_testing_test.cpp
 * \brief Tests: Algorithms for testing prime numbers.
 */
#include <gtest/gtest.h>
#include "algolib/maths/primes_testing.hpp"

namespace alma = algolib::maths;

class PrimesTestingTest_IntNotPrime : public testing::TestWithParam<int>
{
};

// 1001 = 7 * 11 * 13 ; 3481 = 59 ^ 2
INSTANTIATE_TEST_SUITE_P(, PrimesTestingTest_IntNotPrime, testing::Values(0, 1, 77, 1001, 3481));

class PrimesTestingTest_LongNotPrime : public testing::TestWithParam<long>
{
};

// 41041 = 7 * 11 * 13 * 41 ; 73627 = 17 * 61 * 71
INSTANTIATE_TEST_SUITE_P(, PrimesTestingTest_LongNotPrime, testing::Values(41041L, 73627L));

class PrimesTestingTest_LongLongNotPrime : public testing::TestWithParam<long long>
{
};

INSTANTIATE_TEST_SUITE_P(, PrimesTestingTest_LongLongNotPrime, testing::Values(41041LL, 73627LL));

class PrimesTestingTest_IntPrime : public testing::TestWithParam<int>
{
};

INSTANTIATE_TEST_SUITE_P(, PrimesTestingTest_IntPrime, testing::Values(2, 107, 1013));

class PrimesTestingTest_LongPrime : public testing::TestWithParam<long>
{
};

INSTANTIATE_TEST_SUITE_P(, PrimesTestingTest_LongPrime, testing::Values(2131L, 6199L));

class PrimesTestingTest_LongLongPrime : public testing::TestWithParam<long long>
{
};

INSTANTIATE_TEST_SUITE_P(, PrimesTestingTest_LongLongPrime, testing::Values(2131LL, 6199LL));

#pragma region test_prime_fermat

TEST_P(PrimesTestingTest_IntNotPrime, testPrimeFermat_WhenIntNotPrime_ThenFalse)
{
    // given
    int number = GetParam();

    // when
    bool result = alma::test_prime_fermat(number);

    // then
    EXPECT_FALSE(result);
}

TEST_P(PrimesTestingTest_LongNotPrime, testPrimeFermat_WhenLongNotPrime_ThenFalse)
{
    // given
    long number = GetParam();

    // when
    bool result = alma::test_prime_fermat(number);

    // then
    EXPECT_FALSE(result);
}

TEST_P(PrimesTestingTest_LongLongNotPrime, testPrimeFermat_WhenLongLongNotPrime_ThenFalse)
{
    // given
    long long number = GetParam();

    // when
    bool result = alma::test_prime_fermat(number);

    // then
    EXPECT_FALSE(result);
}

TEST_P(PrimesTestingTest_IntPrime, testPrimeFermat_WhenIntIsPrime_ThenTrue)
{
    // given
    int number = GetParam();

    // when
    bool result = alma::test_prime_fermat(number);

    // then
    EXPECT_TRUE(result);
}

TEST_P(PrimesTestingTest_LongPrime, testPrimeFermat_WhenLongIsPrime_ThenTrue)
{
    // given
    long number = GetParam();

    // when
    bool result = alma::test_prime_fermat(number);

    // then
    EXPECT_TRUE(result);
}

TEST_P(PrimesTestingTest_LongLongPrime, testPrimeFermat_WhenLongLongIsPrime_ThenTrue)
{
    // given
    long long number = GetParam();

    // when
    bool result = alma::test_prime_fermat(number);

    // then
    EXPECT_TRUE(result);
}

#pragma endregion
#pragma region test_prime_miller

TEST_P(PrimesTestingTest_IntNotPrime, testPrimeMiller_WhenIntNotPrime_ThenFalse)
{
    // given
    int number = GetParam();

    // when
    bool result = alma::test_prime_miller(number);

    // then
    EXPECT_FALSE(result);
}

TEST_P(PrimesTestingTest_LongNotPrime, testPrimeMiller_WhenLongNotPrime_ThenFalse)
{
    // given
    long number = GetParam();

    // when
    bool result = alma::test_prime_miller(number);

    // then
    EXPECT_FALSE(result);
}

TEST_P(PrimesTestingTest_LongLongNotPrime, testPrimeMiller_WhenLongLongNotPrime_ThenFalse)
{
    // given
    long long number = GetParam();

    // when
    bool result = alma::test_prime_miller(number);

    // then
    EXPECT_FALSE(result);
}

TEST_P(PrimesTestingTest_IntPrime, testPrimeMiller_WhenIntIsPrime_ThenTrue)
{
    // given
    int number = GetParam();

    // when
    bool result = alma::test_prime_miller(number);

    // then
    EXPECT_TRUE(result);
}

TEST_P(PrimesTestingTest_LongPrime, testPrimeMiller_WhenLongIsPrime_ThenTrue)
{
    // given
    long number = GetParam();

    // when
    bool result = alma::test_prime_miller(number);

    // then
    EXPECT_TRUE(result);
}

TEST_P(PrimesTestingTest_LongLongPrime, testPrimeMiller_WhenLongLongIsPrime_ThenTrue)
{
    // given
    long long number = GetParam();

    // when
    bool result = alma::test_prime_miller(number);

    // then
    EXPECT_TRUE(result);
}

#pragma endregion
