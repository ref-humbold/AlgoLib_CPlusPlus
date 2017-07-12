/**
 * @file equation_system.hpp
 * STRUKTURA UKŁADÓW RÓWNAŃ LINIOWYCH Z ALGORYTMEM ELIMINACJI GAUSSA
 */
#ifndef EQUATION_SYSTEM_HPP
#define EQUATION_SYSTEM_HPP

#include <cstdlib>
#include <cmath>
#include <exception>
#include <stdexcept>
#include <algorithm>
#include <initializer_list>
#include <vector>

namespace algolib
{
    namespace structures
    {
        class infinite_solutions_exception : public std::runtime_error
        {
        public:
            explicit infinite_solutions_exception() : std::runtime_error("")
            {
            }

            explicit infinite_solutions_exception(const std::string & what_arg)
                : std::runtime_error(what_arg)
            {
            }

            explicit infinite_solutions_exception(const char * what_arg)
                : std::runtime_error(what_arg)
            {
            }
        };

        class no_solution_exception : public std::runtime_error
        {
        public:
            explicit no_solution_exception() : std::runtime_error("")
            {
            }

            explicit no_solution_exception(const std::string & what_arg)
                : std::runtime_error(what_arg)
            {
            }

            explicit no_solution_exception(const char * what_arg) : std::runtime_error(what_arg)
            {
            }
        };

        class equation_system
        {
        private:
            /// Liczba równań układu.
            size_t equations;

            /// Macierz współczynników równania.
            std::vector<std::vector<double>> coeffs;

            /// Wektor wyrazów wolnych równania.
            std::vector<double> free_terms;

        public:
            explicit equation_system(size_t numeq) : equations{numeq}
            {
                coeffs.resize(equations);
                free_terms.resize(equations, 0.0);

                for(auto & row : coeffs)
                    row.resize(equations, 0.0);
            }

            explicit equation_system(
                std::initializer_list<std::initializer_list<double>> init_list);

            ~equation_system() = default;
            equation_system(const equation_system & eqsys) = default;
            equation_system(equation_system && eqsys) = default;
            equation_system & operator=(const equation_system & eqsys) = default;
            equation_system & operator=(equation_system && eqsys) = default;

            /**
             * @return liczba równań układu
             */
            size_t get_equations_number()
            {
                return equations;
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
             * Zamiana równań miejscami.
             * @param eq1 numer pierwszego równania
             * @param eq2 numer drugiego równania
             */
            void change(int equ1, int equ2);

            /**
             * Przekształcenie równania przez kombinację liniową z innym równaniem.
             * @param eq1 numer równania przekształcanego
             * @param eq2 numer drugiego równania
             * @param cst stała kombinacji liniowej
             */
            void linear_comb(int equ1, int equ2, double cst);
        };
    }
}

#endif
