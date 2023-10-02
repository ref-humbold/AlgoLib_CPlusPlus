/**!
 * \file equation.hpp
 * \brief Structure of linear equation.
 */
#ifndef EQUATION_HPP_
#define EQUATION_HPP_

#include <cmath>
#include <cstdlib>
#include <algorithm>
#include <array>
#include <exception>
#include <iostream>
#include <stdexcept>

namespace algolib::maths
{
    template <size_t N>
    class equation;

    /*!
     * \brief Copies equation.
     * \param eq the equation
     * \return the copy of the equation
     */
    template <size_t N>
    equation<N> operator+(equation<N> eq);

    /*!
     * \brief Negates equation.
     * \param eq the equation
     * \return the equation with all coefficients negated
     */
    template <size_t N>
    equation<N> operator-(equation<N> eq);

    /*!
     * \brief Adds two equations.
     * \param eq1 the first euqation
     * \param eq2 the second equation
     * \return the equation with coefficients added
     */
    template <size_t N>
    equation<N> operator+(equation<N> eq1, const equation<N> & eq2);

    /*!
     * \brief Subtracts two equations.
     * \param eq1 the first euqation
     * \param eq2 the second equation
     * \return the equation with coefficients subtracted
     */
    template <size_t N>
    equation<N> operator-(equation<N> eq1, const equation<N> & eq2);

    /*!
     * \brief Multiplies equation by given constant.
     * \param eq the equation
     * \param constant the contant
     * \return the equation with all coefficients multiplied
     * \throw std::domain_error if constant is equal to zero
     */
    template <size_t N>
    equation<N> operator*(equation<N> eq, double constant);

    /*!
     * \brief Multiplies equation by given constant.
     * \param constant the contant
     * \param eq the equation
     * \return the equation with all coefficients multiplied
     * \throw std::domain_error if constant is equal to zero
     */
    template <size_t N>
    equation<N> operator*(double constant, equation<N> eq);

    /*!
     * \brief Divides equation by given constant.
     * \param eq the equation
     * \param constant the contant
     * \return the equation with all coefficients divided
     * \throw std::domain_error if constant is equal to zero
     */
    template <size_t N>
    equation<N> operator/(equation<N> eq, double constant);

    template <size_t N>
    std::ostream & operator<<(std::ostream & os, const equation<N> & eq);
}

namespace std
{
    template <size_t N>
    struct hash<algolib::maths::equation<N>>;
}

namespace algolib::maths
{
#pragma region equation

    template <size_t N>
    class equation
    {
    public:
        equation(const std::array<double, N> & coefficients, double free_term)
            : coefficients{coefficients}, free_term_{free_term}
        {
        }

        ~equation() = default;
        equation(const equation & eq) = default;
        equation(equation && eq) noexcept = default;
        equation & operator=(const equation & eq) = default;
        equation & operator=(equation && eq) noexcept = default;

        /*!
         * Adds another equation to this equation.
         * \param equation the equation
         */
        equation & operator+=(const equation<N> & equation);

        /*!
         * Subtracts another equation from this equation.
         * \param equation the equation
         */
        equation & operator-=(const equation<N> & equation);

        /*!
         * Multiplies equation by a constant.
         * \param constant the constant
         * \throw std::domain_error if constant is equal to zero
         */
        equation & operator*=(double constant);

        /*!
         * Divides equation by a constant.
         * \param constant the constant
         * \throw std::domain_error if constant is equal to zero
         */
        equation & operator/=(double constant);

        /*!
         * \param i the index of variable
         * \return the coefficient specified by the index
         */
        const double & operator[](size_t i) const
        {
            return this->coefficients[i];
        }

        /*!
         * \param i the index of variable
         * \return the coefficient specified by the index
         * \throw std::out_of_range if index is out of range
         */
        const double & at(size_t i) const
        {
            return this->coefficients.at(i);
        }

        /*!
         * \return free term of this equation
         */
        double free_term() const
        {
            return this->free_term_;
        }

        /*!
         * \brief Checks whether given values solve this equation.
         * \param solution the values
         * \return \c true if solution is correct, otherwise \c false
         */
        bool has_solution(const std::array<double, N> & solution) const;

        friend equation<N> operator+ <N>(equation<N> eq);
        friend equation<N> operator- <N>(equation<N> eq);
        friend equation<N> operator+ <N>(equation<N> eq1, const equation<N> & eq2);
        friend equation<N> operator- <N>(equation<N> eq1, const equation<N> & eq2);
        friend equation<N> operator* <N>(equation<N> eq, double constant);
        friend equation<N> operator* <N>(double constant, equation<N> eq);
        friend equation<N> operator/ <N>(equation<N> eq, double constant);
        friend std::ostream & operator<< <N>(std::ostream & os, const equation<N> & eq);

    private:
        std::array<double, N> coefficients;
        double free_term_;
    };

    template <size_t N>
    equation<N> & equation<N>::operator+=(const equation<N> & equation)
    {
        for(size_t i = 0; i < N; ++i)
            this->coefficients[i] += equation[i];

        this->free_term_ += equation.free_term_;
        return *this;
    }

    template <size_t N>
    equation<N> & equation<N>::operator-=(const equation<N> & equation)
    {
        for(size_t i = 0; i < N; ++i)
            this->coefficients[i] -= equation[i];

        this->free_term_ -= equation.free_term_;
        return *this;
    }

    template <size_t N>
    equation<N> & equation<N>::operator*=(double constant)
    {
        if(constant == 0)
            throw std::domain_error("Constant cannot be equal to zero");

        for(size_t i = 0; i < N; ++i)
            this->coefficients[i] *= constant;

        this->free_term_ *= constant;
        return *this;
    }

    template <size_t N>
    equation<N> & equation<N>::operator/=(double constant)
    {
        if(constant == 0)
            throw std::domain_error("Constant cannot be equal to zero");

        for(size_t i = 0; i < N; ++i)
            this->coefficients[i] /= constant;

        this->free_term_ /= constant;
        return *this;
    }

    template <size_t N>
    bool equation<N>::has_solution(const std::array<double, N> & solution) const
    {
        double result = 0;

        for(size_t i = 0; i < N; ++i)
            result += solution[i] * this->coefficients[i];

        return result == this->free_term_;
    }

#pragma endregion

    template <size_t N>
    equation<N> operator+(equation<N> eq)
    {
        return eq;
    }

    template <size_t N>
    equation<N> operator-(equation<N> eq)
    {
        for(size_t i = 0; i < N; ++i)
            eq.coefficients[i] = -eq.coefficients[i];

        eq.free_term_ = -eq.free_term_;
        return eq;
    }

    template <size_t N>
    equation<N> operator+(equation<N> eq1, const equation<N> & eq2)
    {
        eq1 += eq2;
        return eq1;
    }

    template <size_t N>
    equation<N> operator-(equation<N> eq1, const equation<N> & eq2)
    {
        eq1 -= eq2;
        return eq1;
    }

    template <size_t N>
    equation<N> operator*(equation<N> eq, double constant)
    {
        eq *= constant;
        return eq;
    }

    template <size_t N>
    equation<N> operator*(double constant, equation<N> eq)
    {
        return eq * constant;
    }

    template <size_t N>
    equation<N> operator/(equation<N> eq, double constant)
    {
        eq /= constant;
        return eq;
    }

    template <size_t N>
    std::ostream & operator<<(std::ostream & os, const equation<N> & eq)
    {
        for(size_t i = 0; i < eq.coefficients.size(); ++i)
            if(eq.coefficients[i] != 0)
            {
                if(i > 0)
                    os << " + ";

                os << eq.coefficients[i] << " x_" << i;
            }

        os << " = " << eq.free_term_;
        return os;
    }
}

namespace std
{
    template <size_t N>
    struct hash<algolib::maths::equation<N>>
    {
        using argument_type = algolib::maths::equation<N>;
        using result_type = size_t;

        result_type operator()(const argument_type & eq)
        {
            result_type c_hash = std::hash<std::array<double, N>>()(eq.coefficients);
            result_type f_hash = std::hash<double>()(eq.free_term_);

            return c_hash ^ (f_hash + 0x9e3779b9 + (c_hash << 6) + (c_hash >> 2));
        }
    };
}

#endif
