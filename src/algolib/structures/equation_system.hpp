// STRUKTURA UKŁADÓW RÓWNAŃ LINIOWYCH Z ALGORYTMEM ELIMINACJI GAUSSA
#ifndef EQUATION_SYSTEM_HPP
#define EQUATION_SYSTEM_HPP

#include <cstdlib>
#include <exception>
#include <stdexcept>
#include <initializer_list>
#include <vector>

namespace algolib
{
    class equation_system
    {
        private:
        /** liczba równań układu */
        size_t equations;

        /** macierz współczynników równania */
        std::vector< std::vector<double> > coeffs;

        /** wektor wyrazów wolnych równania */
        std::vector<double> free_terms;

        public:
        explicit equation_system(size_t numeq = 0) : equations{numeq}
        {
            coeffs.resize(equations);
            free_terms.resize(equations, 0.0);

            for(auto & i : coeffs)
                i.resize(equations, 0.0);
        }

        explicit equation_system(std::initializer_list< std::initializer_list<double> > init_list) :
            equations{init_list.size()}
        {
            coeffs.reserve(equations);
            free_terms.reserve(equations);

            for(auto it : init_list)
            {
                if(it.size() != equations+1)
                {
                    equations = 0;
                    coeffs.clear();
                    free_terms.clear();
                    throw std::runtime_error("Incorrect initilization of equation system.");
                }

                coeffs.push_back(it);
                free_terms.push_back(coeffs.back().back());
                coeffs.pop_back();
            }
        }

        ~equation_system() = default;
        equation_system(const equation_system & eqsys) = default;
        equation_system(equation_system && eqsys) = default;
        equation_system & operator=(const equation_system & eqsys) = default;
        equation_system & operator=(equation_system && eqsys) = default;

        /**
        Wyliczanie rozwiązań układu równań liniowych.
        @return wektor wyniku równania
        */
        std::vector<double> solve();

        /** Algorytm eliminacji Gaussa. */
        void gaussian_reduce();

        private:
        /**
        Zamiana równań miejscami.
        @param eq1 numer pierwszego równania
        @param eq2 numer drugiego równania
        */
        void change(int equ1, int equ2);

        /**
        Przekształcenie równania przez kombinację liniową z innym równaniem.
        @param eq1 numer równania przekształcanego
        @param eq2 numer drugiego równania
        @param cst stała kombinacji liniowej
        */
        void linear_comb(int equ1, int equ2, double cst);
    };
}

#endif

