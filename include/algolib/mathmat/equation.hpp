/**!
 * \file equation.hpp
 * \brief Structure of linear equation
 */
#ifndef EQUATION_HPP_
#define EQUATION_HPP_

#include <cstdlib>
#include <cmath>
#include <exception>
#include <stdexcept>
#include <algorithm>
#include <array>

namespace algolib
{
    namespace mathmat
    {
        template <size_t N>
        class equation;
    }
}

namespace std
{
    template <size_t N>
    struct hash<algolib::mathmat::equation<N>>;
}

namespace algolib
{
    namespace mathmat
    {
        template <size_t N>
        class equation
        {
        public:
            explicit equation(const std::array<double, N> & coefficients, double free);

            ~equation() = default;
            equation(const equation & eq) = default;
            equation(equation && eq) noexcept = default;
            equation & operator=(const equation & eq) = default;
            equation & operator=(equation && eq) noexcept = default;

            std::pair<std::array<double, N>, double> values() const;
            double & operator[](size_t i);
            double operator[](size_t i) const;
            equation & operator*=(double constant);
            void combine(const equation<N> & equation, double constant = 1);
            bool is_solution(const std::array<double, N> & solution) const;

            std::array<double, N> coefficients;
            double free;
        };

        template <size_t N>
        equation<N>::equation(const std::array<double, N> & coefficients, double free)
            : coefficients{coefficients}, free{free}
        {
        }

        template <size_t N>
        std::pair<std::array<double, N>, double> equation<N>::values() const
        {
            return std::make_pair(coefficients, free);
        }

        template <size_t N>
        double & equation<N>::operator[](size_t i)
        {
            return coefficients.at(i);
        }

        template <size_t N>
        double equation<N>::operator[](size_t i) const
        {
            return coefficients.at(i);
        }

        template <size_t N>
        equation<N> & equation<N>::operator*=(double constant)
        {
            if(constant == 0)
                throw std::domain_error("Constant cannot be equal to zero");

            for(size_t i = 0; i < N; ++i)
                coefficients[i] *= constant;

            this->free *= constant;
            return *this;
        }

        template <size_t N>
        void equation<N>::combine(const equation<N> & equation, double constant)
        {
            if(constant == 0)
                throw std::domain_error("Constant cannot be equal to zero");

            for(size_t i = 0; i < N; ++i)
                coefficients[i] += equation[i] * constant;

            this->free += equation.free * constant;
        }

        template <size_t N>
        bool equation<N>::is_solution(const std::array<double, N> & solution) const
        {
            double result = 0;

            for(size_t i = 0; i < N; ++i)
                result += solution[i] * coefficients[i];

            return result == free;
        }
    }
}

namespace std
{
    template <size_t N>
    struct hash<algolib::mathmat::equation<N>>
    {
        using argument_type = algolib::mathmat::equation<N>;
        using result_type = size_t;

        result_type operator()(const argument_type & eq)
        {
            return hash<std::array<double, N>>()(eq.coefficients) ^ hash<double>()(eq.free);
        }
    };
}

#endif
