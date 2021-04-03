/**!
 * \file fraction.hpp
 * \brief Structure of fraction
 */
#ifndef FRACTION_HPP_
#define FRACTION_HPP_

#include <cmath>
#include <cstdlib>
#include <exception>
#include <iostream>
#include <stdexcept>
#include <string>
#include "maths.hpp"

namespace algolib::mathmat
{
    class fraction;
}

namespace std
{
    template <>
    struct hash<algolib::mathmat::fraction>;
}

namespace algolib::mathmat
{
    class fraction
    {
    public:
        fraction() : fraction(0LL)
        {
        }

        explicit fraction(long long int numerator, long long int denominator = 1LL)
            : numerator{numerator}, denominator{denominator}
        {
            if(denominator == 0LL)
                throw std::domain_error("Denominator cannot be equal to zero");

            normalize();
        }

        ~fraction() = default;
        fraction(const fraction &) = default;
        fraction(fraction &&) = default;
        fraction & operator=(const fraction &) = default;
        fraction & operator=(fraction &&) = default;

        explicit operator double() const
        {
            return (1.0 * numerator) / denominator;
        }

        explicit operator long long int() const
        {
            return numerator / denominator;
        }

        explicit operator int() const
        {
            return static_cast<int>(numerator / denominator);
        }

        fraction & operator+=(const fraction & f);
        fraction & operator-=(const fraction & f);
        fraction & operator*=(const fraction & f);
        fraction & operator/=(const fraction & f);

        friend fraction operator+(fraction f1, const fraction & f2);
        friend fraction operator-(fraction f1, const fraction & f2);
        friend fraction operator*(fraction f1, const fraction & f2);
        friend fraction operator/(fraction f1, const fraction & f2);
        friend fraction operator-(fraction f);
        friend fraction operator~(fraction f);

        friend bool operator==(const fraction & f1, const fraction & f2);
        friend bool operator!=(const fraction & f1, const fraction & f2);

        friend std::ostream & operator<<(std::ostream & os, const fraction & f);

        friend struct std::hash<fraction>;

    private:
        void normalize();

        long long int numerator, denominator;
    };

    fraction operator+(fraction f1, const fraction & f2);
    fraction operator-(fraction f1, const fraction & f2);
    fraction operator*(fraction f1, const fraction & f2);
    fraction operator/(fraction f1, const fraction & f2);
    fraction operator-(fraction f);
    fraction operator~(fraction f);
    bool operator==(const fraction & f1, const fraction & f2);
    bool operator!=(const fraction & f1, const fraction & f2);
    std::ostream & operator<<(std::ostream & os, const fraction & f);
}

namespace std
{
    template <>
    struct hash<algolib::mathmat::fraction>
    {
        using argument_type = algolib::mathmat::fraction;
        using result_type = size_t;

        result_type operator()(const argument_type & f)
        {
            size_t n_hash = hash<double>()(f.numerator);
            size_t y_hash = hash<double>()(f.denominator);

            return n_hash ^ (y_hash + 0x9e3779b9 + (n_hash << 6) + (n_hash >> 2));
        }
    };
}

#endif
