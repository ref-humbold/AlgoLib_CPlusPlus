/**
 * @file equation_system.hpp
 * STRUKTURA UKŁADÓW RÓWNAŃ LINIOWYCH Z ALGORYTMEM ELIMINACJI GAUSSA
 */
#ifndef _EQUATION_SYSTEM_HPP_
#define _EQUATION_SYSTEM_HPP_

#include <cstdlib>
#include <cmath>
#include <exception>
#include <stdexcept>
#include <algorithm>
#include <initializer_list>
#include <vector>

namespace algolib
{
    namespace math
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
        private:
            /// Macierz współczynników równania.
            double coeffs[N][N];

            /// Wektor wyrazów wolnych równania.
            double free_terms[N];

        public:
            explicit equation_system();
            explicit equation_system(std::initializer_list<std::initializer_list<double>> coef,
                                     std::initializer_list<double> frees);

            ~equation_system() = default;
            equation_system(const equation_system & eqsys) = default;
            equation_system(equation_system && eqsys) = default;
            equation_system & operator=(const equation_system & eqsys) = default;
            equation_system & operator=(equation_system && eqsys) = default;

            /**
             * @return liczba równań układu
             */
            size_t get_N_number()
            {
                return N;
            }

            /**
             * Wyliczanie rozwiązań układu równań liniowych.
             * @return wektor wyniku równania
             */
            std::vector<double> solve();

            /**
             * Algorytm eliminacji Gaussa.
             */
            void gaussian_reduce();

            /**
             * Pomnożenie równania przez niezerową stałą.
             * @param equ numer równania
             * @param constant stała
             */
            void mult(size_t equ, double constant);

            /**
             * Zamiana równań miejscami.
             * @param eq1 numer pierwszego równania
             * @param eq2 numer drugiego równania
             */
            void swap(size_t equ1, size_t equ2);

            /**
             * Przekształcenie równania przez kombinację liniową z innym równaniem.
             * @param eq1 numer równania przekształcanego
             * @param eq2 numer drugiego równania
             * @param constant stała kombinacji liniowej
             */
            void combine(size_t equ1, size_t equ2, double constant);
        };

        template <size_t N>
        equation_system<N>::equation_system()
        {
            for(size_t i = 0; i < N; ++i)
                std::fill(this->coeffs[i], this->coeffs[i] + N, 0);

            std::fill(this->free_terms, this->free_terms + N, 0);
        }

        template <size_t N>
        equation_system<N>::equation_system(
            std::initializer_list<std::initializer_list<double>> coef,
            std::initializer_list<double> frees)
        {
            if(coef.size() != N || frees.size() != N)
                throw std::length_error("Incorrect number of equations.");

            for(auto it : coef)
                if(it.size() != N)
                    throw std::length_error("Initializer matrix is not a square matrix.");

            int i = 0;

            for(auto it1 : coef)
            {
                int j = 0;

                for(auto it2 : it1)
                {
                    this->coeffs[i][j] = it2;
                    ++j;
                }

                ++i;
            }

            i = 0;

            for(auto it : frees)
            {
                this->free_terms[i] = it;
                ++i;
            }
        }

        template <size_t N>
        std::vector<double> equation_system<N>::solve()
        {
            gaussian_reduce();

            if(coeffs[N - 1][N - 1] == 0 && free_terms[N - 1] == 0)
                throw infinite_solutions_exception("");

            if(coeffs[N - 1][N - 1] == 0 && free_terms[N - 1] != 0)
                throw no_solution_exception("");

            std::vector<double> solution(N);

            solution.back() = free_terms[N - 1] / coeffs[N - 1][N - 1];

            for(int equ = N - 2; equ >= 0; --equ)
            {
                double value = free_terms[equ];

                for(int i = N - 1; i > equ; --i)
                    value -= coeffs[equ][i] * solution[i];

                solution[equ] = value / coeffs[equ][equ];
            }

            return solution;
        }

        template <size_t N>
        void equation_system<N>::gaussian_reduce()
        {
            for(size_t equ = 0; equ < N - 1; ++equ)
            {
                int index_min = equ;

                for(size_t i = equ + 1; i < N; ++i)
                {
                    double min_coef = coeffs[index_min][equ];
                    double act_coef = coeffs[i][equ];

                    if(act_coef != 0 && (min_coef == 0 || std::abs(act_coef) < std::abs(min_coef)))
                        index_min = i;
                }

                if(coeffs[index_min][equ] != 0)
                {
                    swap(equ, index_min);

                    for(size_t i = equ + 1; i < N; ++i)
                    {
                        double param = coeffs[i][equ] / coeffs[equ][equ];

                        combine(i, equ, -param);
                    }
                }
            }
        }

        template <size_t N>
        void equation_system<N>::mult(size_t equ, double constant)
        {
            if(constant == 0)
                throw std::domain_error("Constant cannot be zero");

            for(int i = 0; i < N; ++i)
                coeffs[equ][i] *= constant;

            free_terms[equ] *= constant;
        };

        template <size_t N>
        void equation_system<N>::swap(size_t equ1, size_t equ2)
        {
            for(size_t i = 0; i < N; ++i)
                std::swap(coeffs[equ1][i], coeffs[equ2][i]);

            std::swap(free_terms[equ1], free_terms[equ2]);
        }

        template <size_t N>
        void equation_system<N>::combine(size_t equ1, size_t equ2, double constant)
        {
            if(constant == 0)
                throw std::domain_error("Constant cannot be zero");

            for(size_t i = 0; i < N; ++i)
                coeffs[equ1][i] += constant * coeffs[equ2][i];

            free_terms[equ1] += constant * free_terms[equ2];
        }
    }
}

#endif
