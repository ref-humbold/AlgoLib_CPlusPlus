// STRUKTURA UKŁADÓW RÓWNAŃ LINIOWYCH Z ALGORYTMEM ELIMINACJI GAUSSA
#include "equation_system.hpp"

namespace alst = algolib::structures;

alst::equation_system::equation_system(
    std::initializer_list<std::initializer_list<double>> init_list)
    : equations{init_list.size()}
{
    coeffs.reserve(equations);
    free_terms.reserve(equations);

    for(auto it : init_list)
        if(it.size() != equations + 1)
            throw std::length_error("Initializer matrix is not a square matrix.");

    for(auto it : init_list)
    {
        coeffs.push_back(it);
        free_terms.push_back(coeffs.back().back());
        coeffs.pop_back();
    }
}

std::vector<double> alst::equation_system::solve()
{
    gaussian_reduce();

    if(coeffs.back().back() == 0 && free_terms.back() == 0)
        throw infinite_solutions_exception("");

    if(coeffs.back().back() == 0 && free_terms.back() != 0)
        throw no_solution_exception("");

    std::vector<double> solution(equations);

    solution.back() = free_terms.back() / coeffs.back().back();

    for(int equ = equations - 2; equ >= 0; --equ)
    {
        double value = free_terms[equ];

        for(int i = equations - 1; i > equ; --i)
            value -= coeffs[equ][i] * solution[i];

        solution[equ] = value / coeffs[equ][equ];
    }

    return solution;
}

void alst::equation_system::gaussian_reduce()
{
    for(size_t equ = 0; equ < equations - 1; ++equ)
    {
        int index_min = equ;

        for(size_t i = equ + 1; i < equations; ++i)
        {
            double min_coef = coeffs[index_min][equ];
            double act_coef = coeffs[i][equ];

            if(act_coef != 0 && (min_coef == 0 || std::abs(act_coef) < std::abs(min_coef)))
                index_min = i;
        }

        if(coeffs[index_min][equ] != 0)
        {
            change(equ, index_min);

            for(size_t i = equ + 1; i < equations; ++i)
            {
                double param = coeffs[i][equ] / coeffs[equ][equ];

                linear_comb(i, equ, -param);
            }
        }
    }
}

void alst::equation_system::change(int equ1, int equ2)
{
    for(size_t i = 0; i < equations; ++i)
        std::swap(coeffs[equ1][i], coeffs[equ2][i]);

    std::swap(free_terms[equ1], free_terms[equ2]);
}

void alst::equation_system::linear_comb(int equ1, int equ2, double cst)
{
    for(size_t i = 0; i < equations; ++i)
        coeffs[equ1][i] += cst * coeffs[equ2][i];

    free_terms[equ1] += cst * free_terms[equ2];
}
