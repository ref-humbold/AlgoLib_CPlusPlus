/**!
 * \file searching.hpp
 * \brief Graph searching algorithms.
 */
#ifndef SEARCHING_HPP_
#define SEARCHING_HPP_

#include <cstdlib>
#include <initializer_list>
#include "graph.hpp"
#include "searching_strategy.hpp"

namespace algolib
{
    namespace graphs
    {
        /**!
         * \brief Algorytm BFS
         * \param gr graf
         * \param strategy strategia odwiedzania
         * \param roots wierzchołki początkowe
         * \return lista odwiedzonych wierzchołków
         */
        std::vector<bool> bfs(const graph & gr, searching_strategy & strategy,
                              std::initializer_list<vertex_t> roots);

        /**!
         * \brief Iteracyjny algorytm DFS
         * \param gr graf
         * \param strategy strategia odwiedzania
         * \param roots wierzchołki początkowe
         * \return lista odwiedzonych wierzchołków
         */
        std::vector<bool> dfsI(const graph & gr, searching_strategy & strategy,
                               std::initializer_list<vertex_t> roots);

        /**!
         * \brief Rekurencyjny algorytm DFS
         * \param gr graf
         * \param strategy strategia odwiedzania
         * \param roots wierzchołki początkowe
         * \return lista odwiedzonych wierzchołków
         */
        std::vector<bool> dfsR(const graph & gr, searching_strategy & strategy,
                               std::initializer_list<vertex_t> roots);
    }
}

#endif
