/**!
 * \file equation_system.hpp
 * \brief Structure of linear equation system with Gauss elimination algorithm
 */
#ifndef EQUATION_SYSTEM_HPP_
#define EQUATION_SYSTEM_HPP_

#include <cstdlib>
#include <cmath>
#include <exception>
#include <stdexcept>
#include <algorithm>
#include <array>
#include "equation.hpp"

namespace algolib
{
    namespace mathmat
    {
        class infinite_solutions_exception : public std::runtime_error
        {
        public:
            explicit infinite_solutions_exception(const std::string & what_arg)
                : std::runtime_error(what_arg)
            {
            }

            explicit infinite_solutions_exception(const char * what_arg = "")
                : std::runtime_error(what_arg)
            {
            }
        };

        class no_solution_exception : public std::runtime_error
        {
        public:
            explicit no_solution_exception(const std::string & what_arg)
                : std::runtime_error(what_arg)
            {
            }

            explicit no_solution_exception(const char * what_arg = "")
                : std::runtime_error(what_arg)
            {
            }
        };

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

            /**!
             * \param i index of equation
             * \return equation object
             */
            equation<N> & operator[](size_t i);

            /**!
             * \param i index of equation
             * \return equation object
             */
            const equation<N> & operator[](size_t i) const;

            /**!
             * \brief Computes the solution of this equation system
             * \return solution vector
             * \throw infinite_solutions_exception
             * \throw no_solution_exception
             */
            std::array<double, N> solve();

            /**!
             * \brief Gauss elimination algorithm
             */
            void gaussian_reduce();

            /**!
             * \brief Swaps two equations
             * \param i index of first equation
             * \param j index of second equation
             */
            void swap(size_t i, size_t j);

            /**!
             * \brief Checks whether given values solve this equation system
             * \param solution values to check
             * \return ``true`` if solution is correct, otherwise ``false``
             */
            bool is_solution(const std::array<double, N> & solution) const;

        private:
            std::array<equation<N>, N> equations;
        };

        template <size_t N>
        equation<N> & equation_system<N>::operator[](size_t i)
        {
            return equations.at(i);
        }

        template <size_t N>
        const equation<N> & equation_system<N>::operator[](size_t i) const
        {
            return equations.at(i);
        }

        template <size_t N>
        std::array<double, N> equation_system<N>::solve()
        {
            gaussian_reduce();

            if(equations[N - 1][N - 1] == 0 && equations[N - 1].free == 0)
                throw infinite_solutions_exception("");

            if(equations[N - 1][N - 1] == 0 && equations[N - 1].free != 0)
                throw no_solution_exception("");

            std::array<double, N> solution;

            solution.back() = equations[N - 1].free / equations[N - 1][N - 1];

            for(int i = N - 2; i >= 0; --i)
            {
                double value = equations[i].free;

                for(int j = N - 1; j > i; --j)
                    value -= equations[i][j] * solution[j];

                solution[i] = value / equations[i][i];
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
                    double min_coef = equations[index_min][i];
                    double act_coef = equations[j][i];

                    if(act_coef != 0 && (min_coef == 0 || std::abs(act_coef) < std::abs(min_coef)))
                        index_min = j;
                }

                if(equations[index_min][i] != 0)
                {
                    swap(index_min, i);

                    for(size_t j = i + 1; j < N; ++j){
                        double param = -equations[j][i] / equations[i][i];

                        if(param != 0)
                            equations[j].combine(equations[i], param);
                    }
                }
            }
        }

        template <size_t N>
        void equation_system<N>::swap(size_t i, size_t j)
        {
            std::swap(equations.at(i), equations.at(j));
        }

        template <size_t N>
        bool equation_system<N>::is_solution(const std::array<double, N> & solution) const
        {
            return std::all_of(
                    equations.begin(), equations.end(),
                    [this, solution](const equation<N> & eq) { return eq.is_solution(solution); });
        }
    }
}

#endif
