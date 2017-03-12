// STRUKTURA UKŁADÓW RÓWNAŃ LINIOWYCH Z ALGORYTMEM ELIMINACJI GAUSSA
#include <cstdlib>
#include <cmath>
#include <exception>
#include <stdexcept>
#include <vector>
#include <algorithm>

#include "equation_system.hpp"

std::vector<double> algolib::equation_system::solve()
{
    gaussian_reduce();

    if(coeffs.back().back() == 0 && free_terms.back() == 0)
        throw std::runtime_error("System of equations has got infinitely many solutions.\n");

    if(coeffs.back().back() == 0 && free_terms.back() != 0)
        throw std::runtime_error("System of equations has got no solution.\n");

    std::vector<double> solution;

    solution.push_back(free_terms.back()/coeffs.back().back());

    for(int equ = equations-2; equ >= 0; --equ)
    {
        double value = free_terms[equ];

        for(size_t i = 0; i < solution.size(); ++i)
        {
            int pos = equations-1-i;

            value -= coeffs[equ][pos]*solution[i];
        }

        solution.push_back(value/coeffs[equ][equ]);
    }

    reverse(solution.begin(), solution.end());

    return solution;
}

void algolib::equation_system::gaussian_reduce()
{
    for(size_t equ = 0; equ < equations-1; ++equ)
    {
        int index_min = equ;

        for(size_t i = equ+1; i < equations; ++i)
        {
            double min_coef = coeffs[index_min][equ];
            double act_coef = coeffs[i][equ];

            if( act_coef != 0 && ( min_coef == 0 || std::abs(act_coef) < std::abs(min_coef) ) )
                index_min = i;
        }

        if(coeffs[index_min][equ] != 0)
        {
            change(equ, index_min);

            for(size_t i = equ+1; i < equations; ++i)
            {
                double param = coeffs[i][equ]/coeffs[equ][equ];

                linear_comb(i, equ, -param);
            }
        }
    }
}

void algolib::equation_system::change(int equ1, int equ2)
{
    for(size_t i = 0; i < equations; ++i)
        std::swap(coeffs[equ1][i], coeffs[equ2][i]);

    std::swap(free_terms[equ1], free_terms[equ2]);
}

void algolib::equation_system::linear_comb(int equ1, int equ2, double cst)
{
    for(size_t i = 0; i < equations; ++i)
        coeffs[equ1][i] += cst*coeffs[equ2][i];

    free_terms[equ1] += cst*free_terms[equ2];
}
