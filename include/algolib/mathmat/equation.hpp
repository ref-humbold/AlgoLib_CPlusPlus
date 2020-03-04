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
#include <initializer_list>

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

            double operator[](size_t i);
            equation & operator*=(double constant);
            void combine(const equation<N> & equation, double constant);

            std::array<double, N> coefficients;
            double free;
        };

        template <size_t N>
        equation<N>::equation(const std::array<double, N> & coefficients, double free)
            : coefficients(coefficients), free(free)
        {
        }

        template <size_t N>
        double equation<N>::operator[](size_t i)
        {
            return coefficients.at(i);
        }

        template <size_t N>
        equation<N> & equation<N>::operator*=(double constant)
        {
            if(constant == 0.0)
                throw std::domain_error("Constant cannot be zero");

            for(size_t i = 0; i < N; ++i)
                coefficients[i] *= constant;

            free *= constant;
            return *this;
        }

        template <size_t N>
        void equation<N>::combine(const equation<N> & equation, double constant)
        {
            if(constant == 0.0)
                throw std::domain_error("Constant cannot be zero");

            for(size_t i = 0; i < N; ++i)
                coefficients[i] += equation[i] * constant;

            free *= equation.free * constant;
        }
    }
}

#endif
