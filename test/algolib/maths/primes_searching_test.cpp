/*!
 * \file primes_searching_test.cpp
 * \brief Tests: Algorithms for searching for prime numbers.
 */
#include <algorithm>
#include <tuple>
#include <gtest/gtest.h>
#include "algolib/maths/primes_searching.hpp"

namespace alma = algolib::maths;

std::vector<size_t> primes = {2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37, 41, 43, 47, 53, 59, 61,
    67, 71, 73, 79, 83, 89, 97, 101, 103, 107, 109, 113, 127, 131, 137, 139, 149, 151, 157, 163,
    167, 173, 179, 181, 191, 193, 197, 199, 211, 223, 227, 229, 233, 239, 241, 251, 257, 263, 269,
    271, 277, 281, 283, 293, 307, 311, 313, 317, 331, 337, 347, 349, 353, 359, 367, 373, 379, 383,
    389, 397, 401, 409, 419, 421, 431, 433, 439, 443, 449, 457, 461, 463, 467, 479, 487, 491, 499,
    503, 509, 521, 523, 541, 547, 557, 563, 569, 571, 577, 587, 593, 599, 601, 607, 613, 617, 619,
    631, 641, 643, 647, 653, 659, 661, 673, 677, 683, 691, 701, 709, 719, 727, 733, 739, 743, 751,
    757, 761, 769, 773, 787, 797, 809, 811, 821, 823, 827, 829, 839, 853, 857, 859, 863, 877, 881,
    883, 887, 907, 911, 919, 929, 937, 941, 947, 953, 967, 971, 977, 983, 991, 997};

class PrimesSearchingTest_Max : public testing::TestWithParam<size_t>
{
};

INSTANTIATE_TEST_SUITE_P(
        , PrimesSearchingTest_Max, testing::Values(2, 3, 4, 67, 100, 155, 400, 499, 701, 911));

class PrimesSearchingTest_MinMax : public testing::TestWithParam<std::tuple<size_t, size_t>>
{
};

INSTANTIATE_TEST_SUITE_P(,
        PrimesSearchingTest_MinMax,
        testing::Combine(testing::Values(2, 3, 8, 25, 54, 71, 101, 243),
                testing::Values(54, 150, 243, 481, 625, 827, 1000)));

TEST(PrimesSearchingTest, findPrimes_WhenSingleArgument_ThenMinIsZero)

{
    // when
    std::vector<size_t> result1 = alma::find_primes(100);
    std::vector<size_t> result2 = alma::find_primes(0, 100);

    // then
    EXPECT_EQ(result1, result2);
}

TEST_P(PrimesSearchingTest_Max, findPrimes_WhenMaximalNumber_ThenMaxExclusive)
{
    // given
    size_t number = GetParam();
    std::cout << "NUMBER: " << number << "\n";

    // when
    std::vector<size_t> result = alma::find_primes(number);

    // then
    std::vector<size_t> expected;

    std::copy_if(primes.begin(), primes.end(), std::back_inserter(expected),
            [&](auto && p) { return p < number; });

    EXPECT_EQ(expected, result);
}

TEST_P(PrimesSearchingTest_MinMax, findPrimes_WhenRange_ThenMinInclusiveAndMaxExclusive)
{
    // given
    size_t minimum, maximum;

    std::tie(minimum, maximum) = GetParam();

    // when
    std::vector<size_t> result = alma::find_primes(minimum, maximum);

    // then
    std::vector<size_t> expected;

    std::copy_if(primes.begin(), primes.end(), std::back_inserter(expected),
            [&](auto && p) { return p >= minimum && p < maximum; });

    EXPECT_EQ(expected, result);
}
