// ALGORYTM SPEŁNIALNOŚCI FORMUŁ 2-CNF
#ifndef TWO_SAT_HPP
#define TWO_SAT_HPP

#include <cstdlib>
#include <algorithm>
#include <numeric>
#include <vector>

#include "algolib/graphs/directed_graph.hpp"

using literal_t = int;
using clause_t = std::pair<literal_t, literal_t>;
using formula_t = std::vector<clause_t>;

namespace detail
{
    /**
     * Wyliczanie liczby zmiennych występujących w formule.
     * @param formula lista klauzul
     * @return liczba zmiennych
     */
    int count_variables(const formula_t & formula);

    /**
     * Wyliczanie numeru wierzchołka literału.
     * @param literal literał
     * @return numer wierzchołka odpowiadający literałowi
     */
    size_t vertex(literal_t literal);

    /**
     * Wyznaczanie grafu implikacji formuły 2-CNF.
     * @param formula lista klauzul
     * @return skierowany graf implikacji
     */
    algolib::graphs::directed_simple_graph make_graph(const formula_t & formula);
}

namespace algolib
{
    /**
     * Sprawdzanie spełnialności formuły 2-CNF.
     * @param formula lista klauzul
     * @return czy formuła spełnialna
     */
    bool is_satisfiable(const formula_t & formula);
}

#endif
