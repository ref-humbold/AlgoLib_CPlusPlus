//! NAJNIŻSZY WSPÓLNY PRZODEK DWÓCH WIERZCHOŁKÓW W DRZEWIE
#ifndef LCA_HPP_
#define LCA_HPP_

#include <cstdlib>
#include <cmath>
#include <exception>
#include <stdexcept>
#include <algorithm>
#include <vector>
#include "forest_graph.hpp"

namespace impl
{
    class lca_finder
    {
    public:
        explicit lca_finder(const algolib::graphs::forest_graph & treegraph) : graph{treegraph}
        {
            paths.resize(graph.get_vertices_number());
            pre_post_times.resize(graph.get_vertices_number(), std::make_pair(NO_TIME, NO_TIME));
        }

        /**!
         * \brief Wyszukiwanie najniższego wspólnego przodka.
         * \param vertex1 wierzchołek 1
         * \param vertex2 wierzchołek 2
         * \param root korzeń drzewa
         * \return najniższy wspólny przodek
         */
        int search_lca(int vertex1, int vertex2, int root);

        /**!
         * \brief Wyszukiwanie najniższego wspólnego przodka.
         * \param vertex1 wierzchołek 1
         * \param vertex2 wierzchołek 2
         * \return najniższy wspólny przodek
         */
    private:
        int search(int vertex1, int vertex2);

        /**!
         * \brief Algorytm dfs z licznikiem czasu wyznaczający kolejne wierzchołki na ścieżce do korzenia.
         * \param vertex aktualny wierzchołek
         * \param parent ojciec wierzchołka
         * \param timer aktualny czasu
         * \return nowy czas po przetworzeniu wierzchołka
         */
        int dfs(int vertex, int parent, int timer);

        /**!
         * \brief Sprawdza, czy wierzchołki są potomkami.
         * \param vertex1 wierzchołek 1
         * \param vertex2 wierzchołek 2
         * \return czy wierzchołek 1 jest potomkiem wierzchołka 2
         */
        bool is_offspring(int vertex1, int vertex2)
        {
            return pre_post_times[vertex1].first >= pre_post_times[vertex2].first
                   && pre_post_times[vertex1].second <= pre_post_times[vertex2].second;
        }

        static constexpr int NO_TIME = -1;  //!< Oznaczenie braku nadania czasu wejścia lub wyjścia.
        const algolib::graphs::forest_graph & graph;  //!< Reprezentacja drzewa.
        std::vector<std::vector<int>> paths;  //!< Skompresowane ścieżki do korzenia drzewa.
        std::vector<std::pair<int, int>>
                pre_post_times;  //!< Czas wejścia i wyjścia dla wierzchołka.
    };
}

namespace algolib
{
    namespace graphs
    {
        /**!
         * \brief Wyznaczanie najniższego wspólnego przodka.
         * \param treegraph graf drzewo
         * \param vertex1 wierzchołek 1
         * \param vertex2 wierzchołek 2
         * \param root korzeń drzewa
         * \return najniższy wspólny przodek
         */
        int find_lca(const forest_graph & treegraph, int vertex1, int vertex2, int root = 0);
    }
}

#endif
