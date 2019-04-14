/**
 * @file fraction.hpp
 * STRUCTURE FOR FRACTIONS
 */
#include "algolib/mathmat/fraction.hpp"

namespace alma = algolib::mathmat;

void alma::fraction::normalize()
{
    if(denom < 0)
    {
        num = -num;
        denom = -denom;
    }

    long long int gcd_val = gcd(std::abs(num), denom);

    num /= gcd_val;
    denom /= gcd_val;
}

alma::fraction & alma::fraction::operator+=(const alma::fraction & f)
{
    this->num = this->num * f.denom + f.num * this->denom;
    this->denom *= f.denom;
    normalize();

    return *this;
}

alma::fraction & alma::fraction::operator-=(const alma::fraction & f)
{
    this->num = this->num * f.denom - f.num * this->denom;
    this->denom *= f.denom;
    normalize();

    return *this;
}

alma::fraction & alma::fraction::operator*=(const alma::fraction & f)
{
    this->num *= f.num;
    this->denom *= f.denom;
    normalize();

    return *this;
}

alma::fraction & alma::fraction::operator/=(const alma::fraction & f)
{
    this->num *= f.denom;
    this->denom *= f.num;
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
    f.num = -f.num;

    return f;
}

alma::fraction alma::operator~(alma::fraction f)
{
    if(f.num == 0)
        throw std::domain_error("Inversing zero.");

    std::swap(f.num, f.denom);
    f.normalize();

    return f;
}

bool alma::operator==(const alma::fraction & f1, const alma::fraction & f2)
{
    return f1.num == f2.num && f1.denom == f2.denom;
}

bool alma::operator!=(const alma::fraction & f1, const alma::fraction & f2)
{
    return !(f1 == f2);
}

std::ostream & alma::operator<<(std::ostream & os, const alma::fraction & f)
{
    os << f.num << "/" << f.denom;

    return os;
}
