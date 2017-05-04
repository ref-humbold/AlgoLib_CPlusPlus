// SPEŁNIALNOŚĆ FORMUŁ 2-CNF
#ifndef TWO_SAT_HPP
#define TWO_SAT_HPP

#include <cstdlib>
#include <algorithm>
#include <numeric>
#include <vector>

#include "graphs/graph.hpp"

using literal_type = int;
using clause_type = std::pair<literal_type, literal_type>;
using formula_type = std::vector<clause_type>;

namespace detail
{
    /**
     * Wyliczanie liczby zmiennych występujących w formule.
     * @param formula lista klauzul
     * @return liczba zmiennych
     */
    int count_variables(const formula_type & formula);

    /**
     * Wyliczanie numeru wierzchołka literału.
     * @param literal literał
     * @return numer wierzchołka odpowiadający literałowi
     */
    size_t vertex(literal_type literal);

    /**
     * Wyznaczanie grafu implikacji formuły 2-CNF.
     * @param formula lista klauzul
     * @return skierowany graf implikacji
     */
    algolib::graphs::directed_graph make_graph(const formula_type & formula);
}

namespace algolib
{
    /**
     * Sprawdzanie spełnialności formuły 2-CNF.
     * @param formula lista klauzul
     * @return czy formuła spełnialna
     */
    bool is_satisfiable(const formula_type & formula);
}

#endif
