/**!
 * \file searching.hpp
 * \brief ALGORYTMY PRZESZUKIWANIA GRAFU
 */
#ifndef SEARCHING_HPP_
#define SEARCHING_HPP_

#include <cstdlib>
#include <algorithm>
#include <queue>
#include <stack>
#include <vector>
#include "graph.hpp"

namespace algolib
{
    namespace graphs
    {
        /**!
         * \brief Algorytm BFS
         * \param gr graf
         * \param root wierzchołek początkowy
         * \return lista odwiedzonych wierzchołków
         */
        std::vector<bool> bfs(const graph & gr, vertex_t root);

        /**!
         * \brief Iteracyjny algorytm DFS
         * \param gr graf
         * \param root wierzchołek początkowy
         * \return lista odwiedzonych wierzchołków
         */
        std::vector<bool> dfsI(const graph & gr, vertex_t root);

        /**!
         * \brief Rekurencyjny algorytm DFS
         * \param gr graf
         * \param root wierzchołek początkowy
         * \return lista odwiedzonych wierzchołków
         */
        std::vector<bool> dfsR(const graph & gr, vertex_t root);
    }
}

#endif
