/**
 * @file cutting.hpp
 * WYSZUKIWANIE MOSTÓW I PUNKTÓW ARTYKULACJI W GRAFIE
 */
#ifndef CUTTING_HPP_
#define CUTTING_HPP_

#include <cstdlib>
#include <algorithm>
#include <vector>
#include "undirected_graph.hpp"

namespace detail
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

        /**
         * Znajdowanie mostów.
         * @return lista krawędzi będących mostami
         */
        std::vector<edge_t> edge_cut();

        /**
         * Znajdowanie punktów artykulacji.
         * @return lista punktów artykulacji
         */
        std::vector<vertex_t> vertex_cut();

    private:
        /**
         * Sprawdzanie, czy od wierzchołka wychodzi krawędź będąca mostem.
         * @param vertex wierzchołek
         * @return czy wierzchołek incydentny z mostem
         */
        bool has_bridge(vertex_t vertex);

        /**
         * Sprawdzanie, czy wierzchołek jest punktem artykulacji.
         * @param vertex wierzchołek
         * @return czy wierzchołek to punkt artykulacji
         */
        bool is_separator(vertex_t vertex);

        /**
         * Sprawdzanie, czy wierzchołek jest korzeniem drzewa DFS
         * @param vertex wierzchołek
         * @return czy wierzchołek to korzeń
         */
        bool is_dfs_root(vertex_t vertex)
        {
            return dfs_depths[vertex] == 0;
        }

        /**
         * Algorytm DFS wyliczający funkcję LOW.
         * @param vertex aktualny wierzchołek
         * @param parent ojciec wierzchołka
         * @param depth głębokość
         */
        void dfs(vertex_t vertex, vertex_t parent, int depth);

        /// Reprezentacja grafu nieskierowanego.
        const algolib::graphs::undirected_graph & graph;

        /// Ojciec wierzchołka w drzewie DFS.
        std::vector<vertex_t> dfs_parents;

        /// Lista synów w drzewie DFS.
        std::vector<std::vector<vertex_t>> dfs_children;

        /// Głębokość wierzchołka w drzewie DFS.
        std::vector<int> dfs_depths;

        /// Wartości funkcji LOW dla wierzchołków.
        std::vector<int> low_values;
    };
}

namespace algolib
{
    namespace graph
    {
        /**
         * Wyznaczanie mostów w grafie.
         * @param ugraph graf nieskierowany
         * @return lista krawędzi będących mostami
         */
        std::vector<edge_t> find_edge_cut(const algolib::graphs::undirected_graph & ugraph)
        {
            return detail::graph_cutting(ugraph).edge_cut();
        }

        /**
         * Wyznaczanie punktów artykulacji w grafie.
         * @param ugraph graf nieskierowany
         * @return lista punktów artykulacji
         */
        std::vector<vertex_t> find_vertex_cut(const algolib::graphs::undirected_graph & ugraph)
        {
            return detail::graph_cutting(ugraph).vertex_cut();
        }
    }
}

#endif
