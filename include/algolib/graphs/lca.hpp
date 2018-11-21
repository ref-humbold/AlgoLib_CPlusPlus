// NAJNIŻSZY WSPÓLNY PRZODEK DWÓCH WIERZCHOŁKÓW W DRZEWIE
#include <cstdlib>
#include <cmath>
#include <exception>
#include <stdexcept>
#include <algorithm>
#include <vector>
#include "forest_graph.hpp"

namespace detail
{
    class lca_finder
    {
    private:
        /// Oznaczenie braku nadania czasu wejścia lub wyjścia.
        static constexpr int NO_TIME = -1;

        /// Reprezentacja drzewa.
        const algolib::graphs::forest_graph & graph;

        /// Skompresowane ścieżki do korzenia drzewa.
        std::vector<std::vector<int>> paths;

        /// Czas wejścia i wyjścia dla wierzchołka.
        std::vector<std::pair<int, int>> pre_post_times;

    public:
        explicit lca_finder(const algolib::graphs::forest_graph & treegraph) : graph{treegraph}
        {
            this->paths.resize(graph.get_vertices_number());
            this->pre_post_times.resize(graph.get_vertices_number(),
                                        std::make_pair(NO_TIME, NO_TIME));
        }

        /**
         * Wyszukiwanie najniższego wspólnego przodka.
         * @param vertex1 wierzchołek 1
         * @param vertex2 wierzchołek 2
         * @param root korzeń drzewa
         * @return najniższy wspólny przodek
         */
        int search_lca(int vertex1, int vertex2, int root);

        /**
         * Wyszukiwanie najniższego wspólnego przodka.
         * @param vertex1 wierzchołek 1
         * @param vertex2 wierzchołek 2
         * @return najniższy wspólny przodek
         */
    private:
        int search(int vertex1, int vertex2);

        /**
         * Algorytm dfs z licznikiem czasu wyznaczający kolejne wierzchołki na ścieżce do korzenia.
         * @param vertex aktualny wierzchołek
         * @param parent ojciec wierzchołka
         * @param timer aktualny czasu
         * @return nowy czas po przetworzeniu wierzchołka
         */
        int dfs(int vertex, int parent, int timer);

        /**
         * Sprawdza, czy wierzchołki są potomkami.
         * @param vertex1 wierzchołek 1
         * @param vertex2 wierzchołek 2
         * @return czy wierzchołek 1 jest potomkiem wierzchołka 2
         */
        bool is_offspring(int vertex1, int vertex2)
        {
            return pre_post_times[vertex1].first >= pre_post_times[vertex2].first
                   && pre_post_times[vertex1].second <= pre_post_times[vertex2].second;
        }
    };
}

namespace algolib
{
    namespace graphs
    {
        /**
         * Wyznaczanie najniższego wspólnego przodka.
         * @param treegraph graf drzewo
         * @param vertex1 wierzchołek 1
         * @param vertex2 wierzchołek 2
         * @param root korzeń drzewa
         * @return najniższy wspólny przodek
         */
        int find_lca(const forest_graph & treegraph, int vertex1, int vertex2, int root = 0);
    }
}
