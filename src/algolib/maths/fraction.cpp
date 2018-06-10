#include "fraction.hpp"

void fraction::normalize()
{
    std::pair<int, int> p = std::make_pair(std::min(std::abs(num), std::abs(denom)),
                                           std::max(std::abs(num), std::abs(denom)));

    while(p.first > 0)
        p = std::make_pair(p.second % p.first, p.first);

    num /= p.second;
    denom /= p.second;

    if(num < 0 && denom < 0)
    {
        num = std::abs(num);
        denom = std::abs(denom);
    }
    else if(num >= 0 && denom < 0)
    {
        num = -num;
        denom = std::abs(denom);
    }
}

fraction & fraction::operator+=(const fraction & r)
{
    this->num = this->num * r.denom + r.num * this->denom;
    this->denom *= r.denom;
    this->normalize();

    return *this;
}

fraction & fraction::operator-=(const fraction & r)
{
    this->num = this->num * r.denom - r.num * this->denom;
    this->denom *= r.denom;
    this->normalize();

    return *this;
}

fraction & fraction::operator*=(const fraction & r)
{
    this->num *= r.num;
    this->denom *= r.denom;
    this->normalize();

    return *this;
}

fraction & fraction::operator/=(const fraction & r)
{
    this->num *= r.denom;
    this->denom *= r.num;
    this->normalize();

    return *this;
}

fraction operator+(fraction r1, const fraction & r2)
{
    r1 += r2;

    return r1;
}

fraction operator-(fraction r1, const fraction & r2)
{
    r1 -= r2;

    return r1;
}

fraction operator*(fraction r1, const fraction & r2)
{
    r1 *= r2;

    return r1;
}

fraction operator/(fraction r1, const fraction & r2)
{
    r1 /= r2;

    return r1;
}

fraction operator-(fraction r)
{
    r.num *= -1;

    return r;
}

fraction operator~(fraction r)
{
    if(r == 0)
        throw std::domain_error("Reversing zero.");

    std::swap(r.num, r.denom);

    return r;
}

bool operator==(const fraction & r1, const fraction & r2)
{
    return r1.num == r2.num && r1.denom == r2.denom;
}

bool operator!=(const fraction & r1, const fraction & r2)
{
    return !(r1 == r2);
}

std::ostream & operator<<(std::ostream & os, const fraction & r)
{
    os << r.num << "/" << r.denom;

    return os;
}
