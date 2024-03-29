/**!
 * \file fraction.cpp
 * \brief Structure of fraction.
 */
#include "algolib/maths/fraction.hpp"

namespace alma = algolib::maths;

#pragma region fraction

alma::fraction::fraction(intmax_t numerator, intmax_t denominator)
    : numerator{numerator}, denominator{denominator}
{
    if(denominator == 0)
        throw std::domain_error("Division by zero");

    normalize();
}

alma::fraction & alma::fraction::operator+=(const alma::fraction & f)
{
    this->numerator = this->numerator * f.denominator + f.numerator * this->denominator;
    this->denominator *= f.denominator;
    normalize();
    return *this;
}

alma::fraction & alma::fraction::operator-=(const alma::fraction & f)
{
    this->numerator = this->numerator * f.denominator - f.numerator * this->denominator;
    this->denominator *= f.denominator;
    normalize();
    return *this;
}

alma::fraction & alma::fraction::operator*=(const alma::fraction & f)
{
    this->numerator *= f.numerator;
    this->denominator *= f.denominator;
    normalize();
    return *this;
}

alma::fraction & alma::fraction::operator/=(const alma::fraction & f)
{
    if(f.numerator == 0)
        throw std::domain_error("Division by zero");

    this->numerator *= f.denominator;
    this->denominator *= f.numerator;
    normalize();
    return *this;
}

void alma::fraction::normalize()
{
    if(denominator < 0)
    {
        numerator = -numerator;
        denominator = -denominator;
    }

    intmax_t gcd_val = gcd(numerator, denominator);

    numerator /= gcd_val;
    denominator /= gcd_val;
}

std::pair<intmax_t, intmax_t> alma::fraction::common(const alma::fraction & f) const
{
    intmax_t common_denominator = lcm(denominator, f.denominator);
    intmax_t this_numerator = common_denominator / denominator * numerator,
             other_numerator = common_denominator / f.denominator * f.numerator;

    return {this_numerator, other_numerator};
}

#pragma endregion
#pragma region comparison operators

bool alma::operator==(const alma::fraction & f1, const alma::fraction & f2)
{
    return f1.numerator == f2.numerator && f1.denominator == f2.denominator;
}

bool alma::operator!=(const alma::fraction & f1, const alma::fraction & f2)
{
    return !(f1 == f2);
}

bool alma::operator<(const alma::fraction & f1, const alma::fraction & f2)
{
    std::pair<intmax_t, intmax_t> numerators = f1.common(f2);

    return numerators.first < numerators.second;
}

bool alma::operator<=(const alma::fraction & f1, const alma::fraction & f2)
{
    std::pair<intmax_t, intmax_t> numerators = f1.common(f2);

    return numerators.first <= numerators.second;
}

bool alma::operator>(const alma::fraction & f1, const alma::fraction & f2)
{
    std::pair<intmax_t, intmax_t> numerators = f1.common(f2);

    return numerators.first > numerators.second;
}

bool alma::operator>=(const alma::fraction & f1, const alma::fraction & f2)
{
    std::pair<intmax_t, intmax_t> numerators = f1.common(f2);

    return numerators.first >= numerators.second;
}

bool alma::operator==(const alma::fraction & f, int i)
{
    return f == static_cast<alma::fraction>(i);
}

bool alma::operator==(int i, const alma::fraction & f)
{
    return static_cast<alma::fraction>(i) == f;
}

bool alma::operator!=(const alma::fraction & f, int i)
{
    return f != static_cast<alma::fraction>(i);
}

bool alma::operator!=(int i, const alma::fraction & f)
{
    return static_cast<alma::fraction>(i) != f;
}

bool alma::operator<(const alma::fraction & f, int i)
{
    return f < static_cast<alma::fraction>(i);
}

bool alma::operator<(int i, const alma::fraction & f)
{
    return static_cast<alma::fraction>(i) < f;
}

bool alma::operator<=(const alma::fraction & f, int i)
{
    return f <= static_cast<alma::fraction>(i);
}

bool alma::operator<=(int i, const alma::fraction & f)
{
    return static_cast<alma::fraction>(i) <= f;
}

bool alma::operator>(const alma::fraction & f, int i)
{
    return f > static_cast<alma::fraction>(i);
}

bool alma::operator>(int i, const alma::fraction & f)
{
    return static_cast<alma::fraction>(i) > f;
}

bool alma::operator>=(const alma::fraction & f, int i)
{
    return f >= static_cast<alma::fraction>(i);
}

bool alma::operator>=(int i, const alma::fraction & f)
{
    return static_cast<alma::fraction>(i) >= f;
}

bool alma::operator==(const alma::fraction & f, long i)
{
    return f == static_cast<alma::fraction>(i);
}

bool alma::operator==(long i, const alma::fraction & f)
{
    return static_cast<alma::fraction>(i) == f;
}

bool alma::operator!=(const alma::fraction & f, long i)
{
    return f != static_cast<alma::fraction>(i);
}

bool alma::operator!=(long i, const alma::fraction & f)
{
    return static_cast<alma::fraction>(i) != f;
}

bool alma::operator<(const alma::fraction & f, long i)
{
    return f < static_cast<alma::fraction>(i);
}

bool alma::operator<(long i, const alma::fraction & f)
{
    return static_cast<alma::fraction>(i) < f;
}

bool alma::operator<=(const alma::fraction & f, long i)
{
    return f <= static_cast<alma::fraction>(i);
}

bool alma::operator<=(long i, const alma::fraction & f)
{
    return static_cast<alma::fraction>(i) <= f;
}

bool alma::operator>(const alma::fraction & f, long i)
{
    return f > static_cast<alma::fraction>(i);
}

bool alma::operator>(long i, const alma::fraction & f)
{
    return static_cast<alma::fraction>(i) > f;
}

bool alma::operator>=(const alma::fraction & f, long i)
{
    return f >= static_cast<alma::fraction>(i);
}

bool alma::operator>=(long i, const alma::fraction & f)
{
    return static_cast<alma::fraction>(i) >= f;
}

bool alma::operator==(const alma::fraction & f, long long i)
{
    return f == static_cast<alma::fraction>(i);
}

bool alma::operator==(long long i, const alma::fraction & f)
{
    return static_cast<alma::fraction>(i) == f;
}

bool alma::operator!=(const alma::fraction & f, long long i)
{
    return f != static_cast<alma::fraction>(i);
}

bool alma::operator!=(long long i, const alma::fraction & f)
{
    return static_cast<alma::fraction>(i) != f;
}

bool alma::operator<(const alma::fraction & f, long long i)
{
    return f < static_cast<alma::fraction>(i);
}

bool alma::operator<(long long i, const alma::fraction & f)
{
    return static_cast<alma::fraction>(i) < f;
}

bool alma::operator<=(const alma::fraction & f, long long i)
{
    return f <= static_cast<alma::fraction>(i);
}

bool alma::operator<=(long long i, const alma::fraction & f)
{
    return static_cast<alma::fraction>(i) <= f;
}

bool alma::operator>(const alma::fraction & f, long long i)
{
    return f > static_cast<alma::fraction>(i);
}

bool alma::operator>(long long i, const alma::fraction & f)
{
    return static_cast<alma::fraction>(i) > f;
}

bool alma::operator>=(const alma::fraction & f, long long i)
{
    return f >= static_cast<alma::fraction>(i);
}

bool alma::operator>=(long long i, const alma::fraction & f)
{
    return static_cast<alma::fraction>(i) >= f;
}

#pragma endregion
#pragma region unary operators

alma::fraction alma::operator+(alma::fraction f)
{
    f.numerator = +f.numerator;
    f.denominator = +f.denominator;
    return f;
}

alma::fraction alma::operator-(alma::fraction f)
{
    f.numerator = -f.numerator;
    return f;
}

alma::fraction alma::operator~(alma::fraction f)
{
    if(f.numerator == 0)
        throw std::domain_error("Inverting zero");

    std::swap(f.numerator, f.denominator);
    f.normalize();
    return f;
}

#pragma endregion
#pragma region binary operators

alma::fraction alma::operator+(alma::fraction f1, const alma::fraction & f2)
{
    f1 += f2;
    return f1;
}

alma::fraction alma::operator-(alma::fraction f1, const alma::fraction & f2)
{
    f1 -= f2;
    return f1;
}

alma::fraction alma::operator*(alma::fraction f1, const alma::fraction & f2)
{
    f1 *= f2;
    return f1;
}

alma::fraction alma::operator/(alma::fraction f1, const alma::fraction & f2)
{
    f1 /= f2;
    return f1;
}

alma::fraction alma::operator+(alma::fraction f, int i)
{
    f += i;
    return f;
}

alma::fraction alma::operator+(int i, const alma::fraction & f)
{
    return static_cast<alma::fraction>(i) + f;
}

alma::fraction alma::operator-(alma::fraction f, int i)
{
    f -= i;
    return f;
}

alma::fraction alma::operator-(int i, const alma::fraction & f)
{
    return static_cast<alma::fraction>(i) - f;
}

alma::fraction alma::operator*(alma::fraction f, int i)
{
    f *= i;
    return f;
}

alma::fraction alma::operator*(int i, const alma::fraction & f)
{
    return static_cast<alma::fraction>(i) * f;
}

alma::fraction alma::operator/(alma::fraction f, int i)
{
    f /= i;
    return f;
}

alma::fraction alma::operator/(int i, const alma::fraction & f)
{
    return static_cast<alma::fraction>(i) / f;
}

alma::fraction alma::operator+(alma::fraction f, long i)
{
    f += i;
    return f;
}

alma::fraction alma::operator+(long i, const alma::fraction & f)
{
    return static_cast<alma::fraction>(i) + f;
}

alma::fraction alma::operator-(alma::fraction f, long i)
{
    f -= i;
    return f;
}

alma::fraction alma::operator-(long i, const alma::fraction & f)
{
    return static_cast<alma::fraction>(i) - f;
}

alma::fraction alma::operator*(alma::fraction f, long i)
{
    f *= i;
    return f;
}

alma::fraction alma::operator*(long i, const alma::fraction & f)
{
    return static_cast<alma::fraction>(i) * f;
}

alma::fraction alma::operator/(alma::fraction f, long i)
{
    f /= i;
    return f;
}

alma::fraction alma::operator/(long i, const alma::fraction & f)
{
    return static_cast<alma::fraction>(i) / f;
}

alma::fraction alma::operator+(alma::fraction f, long long i)
{
    f += i;
    return f;
}

alma::fraction alma::operator+(long long i, const alma::fraction & f)
{
    return static_cast<alma::fraction>(i) + f;
}

alma::fraction alma::operator-(alma::fraction f, long long i)
{
    f -= i;
    return f;
}

alma::fraction alma::operator-(long long i, const alma::fraction & f)
{
    return static_cast<alma::fraction>(i) - f;
}

alma::fraction alma::operator*(alma::fraction f, long long i)
{
    f *= i;
    return f;
}

alma::fraction alma::operator*(long long i, const alma::fraction & f)
{
    return static_cast<alma::fraction>(i) * f;
}

alma::fraction alma::operator/(alma::fraction f, long long i)
{
    f /= i;
    return f;
}

alma::fraction alma::operator/(long long i, const alma::fraction & f)
{
    return static_cast<alma::fraction>(i) / f;
}

#pragma endregion

std::ostream & alma::operator<<(std::ostream & os, const alma::fraction & f)
{
    os << f.numerator << "/" << f.denominator;
    return os;
}
