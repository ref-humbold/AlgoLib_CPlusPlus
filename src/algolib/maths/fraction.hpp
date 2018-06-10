#ifndef _FRACTION_HPP_
#define _FRACTION_HPP_

#include <cstdlib>
#include <cmath>
#include <exception>
#include <iostream>
#include <stdexcept>
#include <string>

class fraction
{
private:
    int num, denom;

public:
    fraction() : fraction(0)
    {
    }

    fraction(int num, int denom = 1) : num{num}, denom{denom}
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

    fraction & operator+=(const fraction & r);
    fraction & operator-=(const fraction & r);
    fraction & operator*=(const fraction & r);
    fraction & operator/=(const fraction & r);
    friend fraction operator+(fraction r1, const fraction & r2);
    friend fraction operator-(fraction r1, const fraction & r2);
    friend fraction operator*(fraction r1, const fraction & r2);
    friend fraction operator/(fraction r1, const fraction & r2);
    friend fraction operator-(fraction r);
    friend fraction operator~(fraction r);

    friend bool operator==(const fraction & r1, const fraction & r2);
    friend bool operator!=(const fraction & r1, const fraction & r2);

    friend std::ostream & operator<<(std::ostream & os, const fraction & r);

private:
    void normalize();
};

fraction operator+(fraction r1, const fraction & r2);
fraction operator-(fraction r1, const fraction & r2);
fraction operator*(fraction r1, const fraction & r2);
fraction operator/(fraction r1, const fraction & r2);
fraction operator-(fraction r);
fraction operator~(fraction r);
bool operator==(const fraction & r1, const fraction & r2);
bool operator!=(const fraction & r1, const fraction & r2);
std::ostream & operator<<(std::ostream & os, const fraction & r);

#endif
