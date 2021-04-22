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
    private:
        using integral_type = long long int;

    public:
        fraction(integral_type numerator = 0LL, integral_type denominator = 1LL);
        ~fraction() = default;
        fraction(const fraction &) = default;
        fraction(fraction &&) = default;
        fraction & operator=(const fraction &) = default;
        fraction & operator=(fraction &&) = default;

        operator double() const
        {
            return (1.0 * numerator) / denominator;
        }

        operator long long int() const
        {
            return numerator / denominator;
        }

        operator bool() const
        {
            return numerator != 0;
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
        friend bool operator<(const fraction & f1, const fraction & f2);
        friend bool operator<=(const fraction & f1, const fraction & f2);
        friend bool operator>(const fraction & f1, const fraction & f2);
        friend bool operator>=(const fraction & f1, const fraction & f2);

        friend std::ostream & operator<<(std::ostream & os, const fraction & f);

        friend struct std::hash<fraction>;

    private:
        void normalize();
        std::pair<integral_type, integral_type> common(const fraction & f) const;

        integral_type numerator, denominator;
    };

    fraction operator+(fraction f1, const fraction & f2);
    fraction operator-(fraction f1, const fraction & f2);
    fraction operator*(fraction f1, const fraction & f2);
    fraction operator/(fraction f1, const fraction & f2);
    fraction operator-(fraction f);
    fraction operator~(fraction f);
    bool operator==(const fraction & f1, const fraction & f2);
    bool operator!=(const fraction & f1, const fraction & f2);
    bool operator<(const fraction & f1, const fraction & f2);
    bool operator<=(const fraction & f1, const fraction & f2);
    bool operator>(const fraction & f1, const fraction & f2);
    bool operator>=(const fraction & f1, const fraction & f2);
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
