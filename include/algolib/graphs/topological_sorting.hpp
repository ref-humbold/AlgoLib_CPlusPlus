/*!
 * \file topological_sorting.hpp
 * \brief ALGORYTMY SORTOWANIA TOPOLOGICZNEGO
 */
#ifndef TOPOLOGICAL_SORTING_HPP_
#define TOPOLOGICAL_SORTING_HPP_

#include <cstdlib>
#include <exception>
#include <stdexcept>
#include <algorithm>
#include <queue>
#include <string>
#include <vector>
#include <functional>
#include "directed_graph.hpp"

namespace algolib
{
    namespace graphs
    {
        class directed_cyclic_graph_exception : public std::logic_error
        {
        public:
            explicit directed_cyclic_graph_exception(const std::string & what_arg)
                : std::logic_error(what_arg)
            {
            }
        };

        /*!
         * \brief Sortowanie topologiczne przez liczenie poprzedników
         * \param digraph graf skierowany
         * \return porządek topologiczny wierzchołków
         */
        std::vector<vertex_t> sort_topological1(const directed_graph & digraph);

        /*!
         * \brief Sortowanie topologiczne z użyciem DFS
         * \param digraph graf skierowany
         * \return porządek topologiczny wierzchołków
         */
        std::vector<vertex_t> sort_topological2(const directed_graph & digraph);
    }
}

#endif
