// ALGORYTM SPEŁNIALNOŚCI FORMUŁ 2-CNF
#include "algolib/two_sat.hpp"

namespace algr = algolib::graphs;

int detail::count_variables(const formula_t & formula)
{
    return std::accumulate(formula.begin(), formula.end(), 0, [](int maximum, clause_t clause) {
        return std::max(maximum, std::max(std::abs(clause.first), std::abs(clause.second)));
    });
}

size_t detail::vertex(literal_t literal)
{
    return literal > 0 ? 2 * literal - 2 : 2 * (-literal) - 1;
}

algr::directed_simple_graph detail::make_graph(const formula_t & formula)
{
    algr::directed_simple_graph digraph(2 * count_variables(formula));

    for(clause_t clause : formula)
    {
        digraph.add_edge(vertex(-clause.first), vertex(clause.second));
        digraph.add_edge(vertex(-clause.second), vertex(clause.first));
    }

    return digraph;
}

bool algolib::is_satisfiable(const formula_t & formula)
{
    algolib::graphs::directed_simple_graph digraph = detail::make_graph(formula);

    // TODO algorytm 2sat i silnie spójne składowe

    return false;
}
