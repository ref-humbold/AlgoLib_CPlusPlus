/**
 * @file graph.hpp
 * STRUKTURY GRAFÓW
 */
#ifndef _GRAPH_HPP_
#define _GRAPH_HPP_

#include <cstdlib>
#include <exception>
#include <stdexcept>
#include <algorithm>
#include <numeric>
#include <set>
#include <tuple>
#include <vector>
#include <limits>

using weight_t = double;
using vertex_t = size_t;
using wvertex_t = std::tuple<vertex_t, weight_t>;
using edge_t = std::tuple<vertex_t, vertex_t>;
using wedge_t = std::tuple<vertex_t, vertex_t, weight_t>;

namespace algolib
{
    namespace graphs
    {
        class no_such_vertex_exception : public std::logic_error
        {
        public:
            explicit no_such_vertex_exception(const std::string & what_arg)
                : std::logic_error(what_arg)
            {
            }

            explicit no_such_vertex_exception(const char * what_arg = "")
                : std::logic_error(what_arg)
            {
            }
        };

        class graph
        {
        public:
            /// Oznaczenie nieskończoności.
            static constexpr weight_t INF = std::numeric_limits<weight_t>::infinity();

            graph() = default;
            virtual ~graph() = default;
            graph(const graph &) = default;
            graph(graph &&) = default;
            graph & operator=(const graph &) = default;
            graph & operator=(graph &&) = default;

            /**
             * @return liczba wierzchołków
             */
            virtual size_t get_vertices_number() const = 0;

            /**
             * @return wektor wierzchołków
             */
            virtual std::vector<vertex_t> get_vertices() const = 0;

            /**
             * Dodawanie nowego wierzchołka.
             * @return oznaczenie wierzchołka
             */
            virtual vertex_t add_vertex() = 0;

            /**
             * @return liczba krawędzi
             */
            virtual size_t get_edges_number() const = 0;

            /**
             * @return wektor krawędzi
             */
            virtual std::vector<edge_t> get_edges() const = 0;

            /**
             * Dodawanie nowej krawędzi.
             * @param v początkowy wierzchołek
             * @param u końcowy wierzchołek
             */
            virtual void add_edge(vertex_t vertex1, vertex_t vertex2) = 0;

            /**
             * @param v numer wierzchołka
             * @return wektor sąsiadów wierzchołka
             */
            virtual std::vector<vertex_t> get_neighbours(vertex_t vertex) const = 0;

            /**
             * @param v numer wierzchołka
             * @return stopień wyjściowy wierzchołka
             */
            virtual size_t get_outdegree(vertex_t vertex) const = 0;

            /**
             * @param v numer wierzchołka
             * @return stopień wejściowy wierzchołka
             */
            virtual size_t get_indegree(vertex_t vertex) const = 0;
        };

        class weighted_graph : public virtual graph
        {
        public:
            weighted_graph() = default;
            virtual ~weighted_graph() = default;
            weighted_graph(const weighted_graph &) = default;
            weighted_graph(weighted_graph &&) = default;
            weighted_graph & operator=(const weighted_graph &) = default;
            weighted_graph & operator=(weighted_graph &&) = default;

            /**
             * @return wektor krawędzi z wagami
             */
            virtual std::vector<wedge_t> get_weighted_edges() const = 0;

            /**
             * Dodawanie nowej krawędzi z jej wagą.
             * @param v początkowy wierzchołek
             * @param u końcowy wierzchołek
             * @param wg waga krawędzi
             */
            virtual void add_weighted_edge(vertex_t vertex1, vertex_t vertex2, weight_t weight) = 0;

            /**
             * @param v numer wierzchołka
             * @return wektor sąsiadów wierzchołka z wagami
             */
            virtual std::vector<wvertex_t> get_weighted_neighbours(vertex_t vertex) const = 0;
        };

        class simple_graph : public virtual graph
        {
        protected:
            /// Domyślna waga krawędzi.
            static constexpr weight_t DEFAULT_WEIGHT = 1.0;

            /// Lista sąsiedztwa grafu.
            std::vector<std::set<wvertex_t>> graphrepr;

        public:
            explicit simple_graph(int n)
            {
                this->graphrepr.resize(n);
            }

            virtual ~simple_graph() = default;
            simple_graph(const simple_graph &) = default;
            simple_graph(simple_graph &&) = default;
            simple_graph & operator=(const simple_graph &) = default;
            simple_graph & operator=(simple_graph &&) = default;

            size_t get_vertices_number() const override
            {
                return graphrepr.size();
            }

            std::vector<vertex_t> get_vertices() const override;

            vertex_t add_vertex() override;

            std::vector<vertex_t> get_neighbours(vertex_t vertex) const override;

            size_t get_outdegree(vertex_t vertex) const override;
        };
    }
}

#endif