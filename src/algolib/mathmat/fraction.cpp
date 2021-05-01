/**!
 * \file fraction.cpp
 * \brief Structure of fraction
 */
#include "algolib/mathmat/fraction.hpp"

namespace alma = algolib::mathmat;

#pragma region fraction

alma::fraction::fraction(long long numerator, long long denominator)
    : numerator{numerator}, denominator{denominator}
{
    if(denominator == 0LL)
        throw std::domain_error("Denominator is zero");

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
    this->numerator *= f.denominator;
    this->denominator *= f.numerator;
    this->normalize();

    return *this;
}

void alma::fraction::normalize()
{
    if(denominator < 0)
    {
        numerator = -numerator;
        denominator = -denominator;
    }

    long long gcd_val = gcd(numerator, denominator);

    numerator /= gcd_val;
    denominator /= gcd_val;
}

std::pair<long long, long long> alma::fraction::common(const alma::fraction & f) const
{
    long common_denominator = lcm(denominator, f.denominator);
    long this_numerator = common_denominator / denominator * numerator;
    long other_numerator = common_denominator / f.denominator * f.numerator;

    return {this_numerator, other_numerator};
}

#pragma endregion

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

alma::fraction alma::operator+(alma::fraction f)
{
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
    std::pair<long long, long long> numerators = f1.common(f2);

    return numerators.first < numerators.second;
}

bool alma::operator<=(const alma::fraction & f1, const alma::fraction & f2)
{
    std::pair<long long, long long> numerators = f1.common(f2);

    return numerators.first <= numerators.second;
}

bool alma::operator>(const alma::fraction & f1, const alma::fraction & f2)
{
    std::pair<long long, long long> numerators = f1.common(f2);

    return numerators.first > numerators.second;
}

bool alma::operator>=(const alma::fraction & f1, const alma::fraction & f2)
{
    std::pair<long long, long long> numerators = f1.common(f2);

    return numerators.first >= numerators.second;
}

std::ostream & alma::operator<<(std::ostream & os, const alma::fraction & f)
{
    os << f.numerator << "/" << f.denominator;
    return os;
}
