/**!
 * \file fraction.cpp
 * \brief Structure of fraction
 */
#include "algolib/mathmat/fraction.hpp"

namespace alma = algolib::mathmat;

void alma::fraction::normalize()
{
    if(denominator < 0)
    {
        numerator = -numerator;
        denominator = -denominator;
    }

    long long int gcd_val = gcd(numerator, denominator);

    numerator /= gcd_val;
    denominator /= gcd_val;
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

alma::fraction alma::operator-(alma::fraction f)
{
    f.numerator = -f.numerator;

    return f;
}

alma::fraction alma::operator~(alma::fraction f)
{
    if(f.numerator == 0)
        throw std::domain_error("Inversing zero.");

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

std::ostream & alma::operator<<(std::ostream & os, const alma::fraction & f)
{
    os << f.numerator << "/" << f.denominator;

    return os;
}
