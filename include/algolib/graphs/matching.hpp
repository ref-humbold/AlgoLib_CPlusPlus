/**
 * @file matching.hpp
 * ALGORYTM HOPCROFTA-KARPA WYZNACZANIA SKOJARZEŃ W GRAFIE DWUDZIELNYM
 */
#ifndef _MATCHING_HPP_
#define _MATCHING_HPP_

#include <cstdlib>
#include <exception>
#include <stdexcept>
#include <queue>
#include <vector>
#include "multipartite_graph.hpp"

namespace detail
{
    class match_augmenter
    {
    public:
        explicit match_augmenter(const algolib::graphs::multipartite_graph<2> & partgraph)
            : graph{partgraph}
        {
            this->matching.resize(this->graph.get_vertices_number(), NO_MATCH);
        }

        /// @return skojarzenia wierzchołków
        std::vector<int> get_matching()
        {
            return this->matching;
        }

        /**
         * Powiększanie skojarzenia przy pomocy scieżek poiększających.
         * @return czy powiększono skojarzenie
         */
        bool augment_match();

    private:
        /// Algorytm BFS wyliczający odległości wierzchołków.
        void bfs();

        /**
         * Algorytm DFS powiększający skojarzenie za pomocą ścieżek powiekszających.
         * @param vertex wierzchołek
         * @return czy powiększono skojarzenie
         */
        bool dfs(int vertex);

        /// Oznaczenie braku skojarzenia.
        static constexpr int NO_MATCH = -1;

        /// Graf dwudzielny.
        const algolib::graphs::multipartite_graph<2> & graph;

        /// Skojarzenia wierzchołków.
        std::vector<int> matching;

        /// Odległości wierzchołków.
        std::vector<double> distances;

        /// Lista odwiedzonych wierzchołków.
        std::vector<bool> is_visited;
    };
}

namespace algolib
{
    namespace graphs
    {
        /**
         * Wyznaczanie maksymalnego skojarzenia.
         * @param partgraph graf wielodzielny
         * @return pary skojarzonych wierzchołków
         */
        std::vector<std::pair<int, int>> match(const multipartite_graph<2> & partgraph);
    }
}

#endif
