// DATA STRUCTURE FOR FRACTIONS
#ifndef _FRACTION_HPP_
#define _FRACTION_HPP_

#include <cstdlib>
#include <cmath>
#include <exception>
#include <iostream>
#include <stdexcept>
#include <string>

#include "maths.hpp"

namespace algolib
{
    namespace math
    {
        class fraction;
    }
}

namespace std
{
    template <>
    struct hash<algolib::math::fraction>;
}

namespace algolib
{
    namespace math
    {
        class fraction
        {
        private:
            long long int num, denom;

        public:
            fraction() : fraction(0)
            {
            }

            fraction(long long int num, long long int denom = 1) : num{num}, denom{denom}
            {
                if(denom == 0)
                    throw std::domain_error("Denominator equals zero.");

                this->normalize();
            }

            ~fraction() = default;
            fraction(const fraction &) = default;
            fraction(fraction &&) = default;
            fraction & operator=(const fraction &) = default;
            fraction & operator=(fraction &&) = default;

            explicit operator double() const
            {
                return (1.0 * num) / denom;
            }

            explicit operator long long int() const
            {
                return num / denom;
            }

            explicit operator int() const
            {
                return (long long int)(*this);
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
        };

        fraction operator+(fraction f1, const fraction & f2);
        fraction operator-(fraction f1, const fraction & f2);
        fraction operator*(fraction f1, const fraction & f2);
        fraction operator/(fraction f1, const fraction & f2);
        fraction operator-(fraction r);
        fraction operator~(fraction r);
        bool operator==(const fraction & f1, const fraction & f2);
        bool operator!=(const fraction & f1, const fraction & f2);
        std::ostream & operator<<(std::ostream & os, const fraction & f);
    }
}

namespace std
{
    template <>
    struct hash<algolib::math::fraction>
    {
        using argument_type = algolib::math::fraction;
        using result_type = size_t;

        result_type operator()(const argument_type & f)
        {
            return hash<long long int>()(f.num) + hash<long long int>()(f.denom);
        }
    };
}

#endif
