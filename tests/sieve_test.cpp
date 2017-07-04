// TESTY DLA ALGORYTMU SITA ERASTOTENESA"""
#include <gtest/gtest.h>
#include "../algolib/maths/sieve.hpp"

namespace alma = algolib::maths;

TEST(SieveTest, test_find_primes_when_two_args_descending)
{
    EXPECT_THROW(alma::find_primes(100, 30), std::invalid_argument);
}

TEST(SieveTest, test_find_primes_one_arg_is_two_args_with_zero_as_min)
{
    std::vector<size_t> result1 = alma::find_primes(100);
    std::vector<size_t> result2 = alma::find_primes(0, 100);

    EXPECT_EQ(result1, result2);
}

TEST(SieveTest, test_find_primes_one_arg)
{
    std::vector<size_t> result = alma::find_primes(100);

    EXPECT_EQ(std::vector<size_t>({2,  3,  5,  7,  11, 13, 17, 19, 23, 29, 31, 37, 41,
                                   43, 47, 53, 59, 61, 67, 71, 73, 79, 83, 89, 97}),
              result);
}

TEST(SieveTest, test_find_primes_one_arg_when_max_is_prime)
{
    std::vector<size_t> result = alma::find_primes(67);

    EXPECT_EQ(std::vector<size_t>(
                  {2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37, 41, 43, 47, 53, 59, 61, 67}),
              result);
}

TEST(SieveTest, test_find_primes_one_arg_when_less_than_two)
{
    std::vector<size_t> result = alma::find_primes(1);

    EXPECT_EQ(std::vector<size_t>(), result);
}

TEST(SieveTest, test_find_primes_two_args)
{
    std::vector<size_t> result = alma::find_primes(30, 200);

    EXPECT_EQ(std::vector<size_t>({31,  37,  41,  43,  47,  53,  59,  61,  67,  71,  73,  79,
                                   83,  89,  97,  101, 103, 107, 109, 113, 127, 131, 137, 139,
                                   149, 151, 157, 163, 167, 173, 179, 181, 191, 193, 197, 199}),
              result);
}

TEST(SieveTest, test_find_primes_two_args_when_min_less_than_sqrt_of_max)
{
    std::vector<size_t> result = alma::find_primes(5, 150);

    EXPECT_EQ(std::vector<size_t>({5,  7,   11,  13,  17,  19,  23,  29,  31,  37,  41,
                                   43, 47,  53,  59,  61,  67,  71,  73,  79,  83,  89,
                                   97, 101, 103, 107, 109, 113, 127, 131, 137, 139, 149}),
              result);
}

TEST(SieveTest, test_find_primes_two_args_when_min_and_max_are_primes)
{
    std::vector<size_t> result = alma::find_primes(137, 317);

    EXPECT_EQ(std::vector<size_t>({137, 139, 149, 151, 157, 163, 167, 173, 179, 181, 191, 193,
                                   197, 199, 211, 223, 227, 229, 233, 239, 241, 251, 257, 263,
                                   269, 271, 277, 281, 283, 293, 307, 311, 313, 317}),
              result);
}

TEST(SieveTest, test_find_primes_two_args_when_min_equals_max_and_prime)
{
    std::vector<size_t> result = alma::find_primes(41, 41);

    EXPECT_EQ(std::vector<size_t>({41}), result);
}

TEST(SieveTest, test_find_primes_two_args_when_min_equals_max_and_composite)
{
    std::vector<size_t> result = alma::find_primes(91, 91);

    EXPECT_EQ(std::vector<size_t>(), result);
}
