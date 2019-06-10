/**!
 * \file cutting.hpp
 * \brief WYSZUKIWANIE MOSTÓW I PUNKTÓW ARTYKULACJI W GRAFIE
 */
#ifndef CUTTING_HPP_
#define CUTTING_HPP_

#include <cstdlib>
#include <algorithm>
#include <vector>
#include "undirected_graph.hpp"

namespace impl
{
    class graph_cutting
    {
    public:
        explicit graph_cutting(const algolib::graphs::undirected_graph & graph) : graph{graph}
        {
            dfs_parents.resize(graph.get_vertices_number(), graph.get_vertices_number());
            dfs_children.resize(graph.get_vertices_number(), std::vector<vertex_t>());
            dfs_depths.resize(graph.get_vertices_number(), -1);
            low_values.resize(graph.get_vertices_number(), -1);
        }

        /**!
         * \brief Znajdowanie mostów.
         * \return lista krawędzi będących mostami
         */
        std::vector<edge_t> edge_cut();

        /**!
         * \brief Znajdowanie punktów artykulacji.
         * \return lista punktów artykulacji
         */
        std::vector<vertex_t> vertex_cut();

    private:
        /**!
         * \brief Sprawdzanie, czy od wierzchołka wychodzi krawędź będąca mostem.
         * \param vertex wierzchołek
         * \return czy wierzchołek incydentny z mostem
         */
        bool has_bridge(vertex_t vertex);

        /**!
         * \brief Sprawdzanie, czy wierzchołek jest punktem artykulacji.
         * \param vertex wierzchołek
         * \return czy wierzchołek to punkt artykulacji
         */
        bool is_separator(vertex_t vertex);

        /**!
         * \brief Sprawdzanie, czy wierzchołek jest korzeniem drzewa DFS
         * \param vertex wierzchołek
         * \return czy wierzchołek to korzeń
         */
        bool is_dfs_root(vertex_t vertex)
        {
            return dfs_depths[vertex] == 0;
        }

        /**!
         * \brief Algorytm DFS wyliczający funkcję LOW.
         * \param vertex aktualny wierzchołek
         * \param parent ojciec wierzchołka
         * \param depth głębokość
         */
        void dfs(vertex_t vertex, vertex_t parent, int depth);

        const algolib::graphs::undirected_graph & graph;  //!< Reprezentacja grafu nieskierowanego.
        std::vector<vertex_t> dfs_parents;  //!< Ojciec wierzchołka w drzewie DFS.
        std::vector<std::vector<vertex_t>> dfs_children;  //!< Lista synów w drzewie DFS.
        std::vector<int> dfs_depths;  //!< Głębokość wierzchołka w drzewie DFS.
        std::vector<int> low_values;  //!< Wartości funkcji LOW dla wierzchołków.
    };
}

namespace algolib
{
    namespace graph
    {
        /**!
         * \brief Wyznaczanie mostów w grafie.
         * \param ugraph graf nieskierowany
         * \return lista krawędzi będących mostami
         */
        std::vector<edge_t> find_edge_cut(const algolib::graphs::undirected_graph & ugraph)
        {
            return impl::graph_cutting(ugraph).edge_cut();
        }

        /**!
         * \brief Wyznaczanie punktów artykulacji w grafie.
         * \param ugraph graf nieskierowany
         * \return lista punktów artykulacji
         */
        std::vector<vertex_t> find_vertex_cut(const algolib::graphs::undirected_graph & ugraph)
        {
            return impl::graph_cutting(ugraph).vertex_cut();
        }
    }
}

#endif
