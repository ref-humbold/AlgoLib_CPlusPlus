/*!
 * \file equation_system.hpp
 * \brief Structure of system of linear equations.
 */
#ifndef EQUATION_SYSTEM_HPP_
#define EQUATION_SYSTEM_HPP_

#include <cmath>
#include <cstdlib>
#include <algorithm>
#include <array>
#include <exception>
#include <stdexcept>
#include "algolib/maths/equation.hpp"

namespace algolib::maths
{
    template <size_t N>
    class equation_system;

    template <size_t N>
    std::ostream & operator<<(std::ostream & os, const equation_system<N> & eqs);

#pragma region errors

    class infinite_solutions_error : public std::runtime_error
    {
    public:
        explicit infinite_solutions_error(const char * what_arg) : std::runtime_error(what_arg)
        {
        }
    };

    class no_solution_error : public std::runtime_error
    {
    public:
        explicit no_solution_error(const char * what_arg) : std::runtime_error(what_arg)
        {
        }
    };

#pragma endregion
#pragma region equation_system

    template <size_t N>
    class equation_system
    {
    public:
        explicit equation_system(const std::array<equation<N>, N> & equations)
            : equations{equations}
        {
        }

        ~equation_system() = default;
        equation_system(const equation_system & es) = default;
        equation_system(equation_system && es) = default;
        equation_system & operator=(const equation_system & es) = default;
        equation_system & operator=(equation_system && es) = default;

        /*!
         * \brief Gets the equation at given index.
         * \param i the index
         * \return the equation specified by the index
         */
        const equation<N> & operator[](size_t i) const
        {
            return this->equations[i];
        }

        /*!
         * \brief Gets the equation at given index.
         * \param i the index
         * \return the equation specified by the index
         * \throw std::out_of_range if the index is out of range
         */
        const equation<N> & at(size_t i) const
        {
            return this->equations.at(i);
        }

        /*!
         * \brief Computes solution of this equation system.
         * \return the solution
         * \throw infinite_solutions_error if infinitely many solutions
         * \throw no_solution_error if no solution
         */
        std::array<double, N> solve();

        //! \brief Runs the Gaussian elimination algorithm on this equation system.
        void gaussian_reduce();

        /*!
         * \brief Swaps two equations in this system.
         * \param i the index of first equation
         * \param j the index of second equation
         */
        void swap(size_t i, size_t j);

        /*!
         * \brief Checks whether given values solve this equation system.
         * \param solution the values
         * \return \c true if the solution is correct, otherwise \c false
         */
        bool has_solution(const std::array<double, N> & solution) const;

        friend std::ostream & operator<< <N>(std::ostream & os, const equation_system<N> & eqs);

    private:
        std::array<equation<N>, N> equations;

        size_t min_coefficient_index(size_t starting_index);
    };

    template <size_t N>
    std::array<double, N> equation_system<N>::solve()
    {
        gaussian_reduce();

        if(this->equations[N - 1].coefficients()[N - 1] == 0
           && this->equations[N - 1].free_term() == 0)
            throw infinite_solutions_error("Equation system has an infinite number of solutions");

        if(this->equations[N - 1].coefficients()[N - 1] == 0
           && this->equations[N - 1].free_term() != 0)
            throw no_solution_error("Equation system has no solution");

        std::array<double, N> solution;

        solution.back() =
                this->equations[N - 1].free_term() / this->equations[N - 1].coefficients()[N - 1];

        for(int i = N - 2; i >= 0; --i)
        {
            double value = this->equations[i].free_term();

            for(int j = N - 1; j > i; --j)
                value -= this->equations[i].coefficients()[j] * solution[j];

            solution[i] = value / this->equations[i].coefficients()[i];
        }

        return solution;
    }

    template <size_t N>
    void equation_system<N>::gaussian_reduce()
    {
        for(size_t i = 0; i < N - 1; ++i)
        {
            int index_min = i;

            for(size_t j = i + 1; j < N; ++j)
            {
                double min_coefficient = this->equations[index_min].coefficients()[i];
                double current_coefficient = this->equations[j].coefficients()[i];

                if(current_coefficient != 0
                   && (min_coefficient == 0
                       || std::abs(current_coefficient) < std::abs(min_coefficient)))
                    index_min = j;
            }

            if(this->equations[index_min].coefficients()[i] != 0)
            {
                swap(index_min, i);

                for(size_t j = i + 1; j < N; ++j)
                {
                    double param = -this->equations[j].coefficients()[i]
                                   / this->equations[i].coefficients()[i];

                    if(param != 0)
                        this->equations[j] += param * this->equations[i];
                }
            }
        }
    }

    template <size_t N>
    void equation_system<N>::swap(size_t i, size_t j)
    {
        std::swap(this->equations.at(i), this->equations.at(j));
    }

    template <size_t N>
    bool equation_system<N>::has_solution(const std::array<double, N> & solution) const
    {
        return std::all_of(
                this->equations.begin(), this->equations.end(),
                [&](auto && eq) { return eq.has_solution(solution); });
    }

    template <size_t N>
    size_t equation_system<N>::min_coefficient_index(size_t starting_index)
    {
        int index_min = starting_index;

        for(size_t i = starting_index + 1; i < N; ++i)
        {
            double min_coefficient = this->equations[index_min].coefficients()[starting_index];
            double current_coefficient = this->equations[i].coefficients()[starting_index];

            if(current_coefficient != 0
               && (min_coefficient == 0
                   || std::abs(current_coefficient) < std::abs(min_coefficient)))
                index_min = i;
        }

        return index_min;
    }

#pragma endregion

    template <size_t N>
    std::ostream & operator<<(std::ostream & os, const equation_system<N> & eqs)
    {
        os << "{ ";

        for(size_t i = 0; i < N; ++i)
        {
            if(i > 0)
                os << " ; ";

            os << eqs[i];
        }

        os << " }";
        return os;
    }
}

#endif
