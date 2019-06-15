/**!
 * \file matching.hpp
 * \brief ALGORYTM HOPCROFTA-KARPA WYZNACZANIA SKOJARZEŃ W GRAFIE DWUDZIELNYM
 */
#ifndef MATCHING_HPP_
#define MATCHING_HPP_

#include <cstdlib>
#include <exception>
#include <stdexcept>
#include <queue>
#include <vector>
#include "multipartite_graph.hpp"

namespace impl
{
    class match_augmenter
    {
    public:
        explicit match_augmenter(const algolib::graphs::multipartite_graph<2> & partgraph)
            : graph{partgraph}
        {
            this->matching.resize(this->graph.get_vertices_number(), NO_MATCH);
        }

        //! \return skojarzenia wierzchołków
        std::vector<int> get_matching()
        {
            return this->matching;
        }

        /**!
         * \brief Powiększanie skojarzenia przy pomocy scieżek poiększających.
         * \return czy powiększono skojarzenie
         */
        bool augment_match();

    private:
        //! \brief Algorytm BFS wyliczający odległości wierzchołków.
        void bfs();

        /**!
         * \brief Algorytm DFS powiększający skojarzenie za pomocą ścieżek powiekszających.
         * \param vertex wierzchołek
         * \return czy powiększono skojarzenie
         */
        bool dfs(int vertex);

        static constexpr int NO_MATCH = -1;  //!< Oznaczenie braku skojarzenia.
        const algolib::graphs::multipartite_graph<2> & graph;  //!< Graf dwudzielny.
        std::vector<int> matching;  //!< Skojarzenia wierzchołków.
        std::vector<double> distances;  //!< Odległości wierzchołków.
        std::vector<bool> is_visited;  //!< Lista odwiedzonych wierzchołków.
    };
}

namespace algolib
{
    namespace graphs
    {
        /**!
         * \brief Wyznaczanie maksymalnego skojarzenia.
         * \param partgraph graf wielodzielny
         * \return pary skojarzonych wierzchołków
         */
        std::vector<std::pair<int, int>> match(const multipartite_graph<2> & partgraph);
    }
}

#endif
