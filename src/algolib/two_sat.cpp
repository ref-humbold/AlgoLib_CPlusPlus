#include "two_sat.hpp"

int detail::count_variables(const formula_type & formula)
{
    return std::accumulate(formula.begin(), formula.end(), 0,
                           [](int maximum, clause_type clause)
                           {
                               return std::max(maximum, std::max(std::abs(clause.first),
                                                                 std::abs(clause.second)));
                           });
}

size_t detail::vertex(literal_type literal)
{
    return literal > 0 ? 2 * literal - 2 : 2 * (-literal) - 1;
}

algolib::graphs::directed_graph detail::make_graph(const formula_type & formula)
{
    algolib::graphs::directed_graph digraph(2 * count_variables(formula));

    for(clause_type clause : formula)
    {
        digraph.add_edge(vertex(-clause.first), vertex(clause.second));
        digraph.add_edge(vertex(-clause.second), vertex(clause.first));
    }

    return digraph;
}

bool algolib::is_satisfiable(const formula_type & formula)
{
    algolib::graphs::directed_graph digraph = detail::make_graph(formula);

    return false;
}
