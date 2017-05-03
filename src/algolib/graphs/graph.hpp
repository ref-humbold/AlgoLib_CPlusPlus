// STRUKTURY GRAFÓW
#ifndef GRAPH_HPP
#define GRAPH_HPP

#include <cstdlib>
#include <exception>
#include <stdexcept>
#include <algorithm>
#include <numeric>
#include <set>
#include <tuple>
#include <vector>
#include <limits>

using weight_type = double;
using vertex_type = size_t;
using wvertex_type = std::tuple<vertex_type, weight_type>;
using edge_type = std::tuple<vertex_type, vertex_type>;
using wedge_type = std::tuple<vertex_type, vertex_type, weight_type>;

namespace algolib
{
    namespace graphs
    {
        class graph
        {
        public:
            /**
             * Getter dla liczby wierzchołków.
             * @return liczba wierzchołków
             */
            virtual size_t get_vertices_number() const = 0;

            /**
             * Getter dla liczby krawędzi.
             * @return liczba krawędzi
             */
            virtual size_t get_edges_number() const = 0;

            /**
             * Wszystkie wierzchołki.
             * @return wektor wierzchołków
             */
            virtual std::vector<vertex_type> get_vertices() const = 0;

            /**
             * Wszystkie krawędzie.
             * @return wektor krawędzi
             */
            virtual std::vector<edge_type> get_edges() const = 0;

            /**
             * Dodawanie nowego wierzchołka.
             * @return oznaczenie wierzchołka
             */
            virtual vertex_type add_vertex() = 0;

            /**
             * Dodawanie nowej krawędzi.
             * @param v początkowy wierzchołek
             * @param u końcowy wierzchołek
             */
            virtual void add_edge(vertex_type v, vertex_type u) = 0;

            /**
             * Sąsiedzi wierzchołka.
             * @param v numer wierzchołka
             * @return wektor sąsiadów wierzchołka
             */
            virtual std::vector<vertex_type> get_neighbours(vertex_type v) const = 0;

            /**
             * Stopień wyjściowy wierzchołka.
             * @param v numer wierzchołka
             * @return wartość stopnia wyjściowego wierzchołka
             */
            virtual size_t get_outdegree(vertex_type v) const = 0;

            /**
             * Stopień wejściowy wierzchołka.
             * @param v numer wierzchołka
             * @return wartość stopnia wejściowego wierzchołka
             */
            virtual size_t get_indegree(vertex_type v) const = 0;
        };

        class weighted_graph : public virtual graph
        {
        public:
            /**
             * Wszystkie krawędzie z ich wagami.
             * @return lista krawędzi z wagami
             */
            virtual std::vector<wedge_type> get_weighted_edges() const = 0;

            /**
             * Dodawanie nowej krawędzi z jej wagą.
             * @param v początkowy wierzchołek
             * @param u końcowy wierzchołek
             * @param wg waga krawędzi
             */
            virtual void add_weighted_edge(vertex_type v, vertex_type u, weight_type wg) = 0;

            /**
             * Sąsiedzi wierzchołka z wagami krawędzi do nich.
             * @param v numer wierzchołka
             * @return lista sąsiadów wierzchołka z wagami
             */
            virtual std::vector<wvertex_type> get_weighted_neighbours(vertex_type v) const = 0;
        };

        class simple_graph : public virtual graph
        {
        public:
            /** Oznaczenie nieskończoności. */
            static constexpr weight_type INF = std::numeric_limits<weight_type>::infinity();

        protected:
            /** Domyślna waga krawędzi. */
            static constexpr weight_type DEFAULT_WEIGHT = 1.0;

            /** Lista sąsiedztwa grafu. */
            std::vector<std::set<wvertex_type>> graphrepr;

        public:
            simple_graph(int n)
            {
                graphrepr.resize(n);
            }

            ~simple_graph() = default;
            simple_graph(const simple_graph & g) = default;
            simple_graph(simple_graph && g) = default;
            simple_graph & operator =(const simple_graph & g) = default;
            simple_graph & operator =(simple_graph && g) = default;

            /** @see graph#get_vertices_number */
            size_t get_vertices_number() const override
            {
                return graphrepr.size();
            }

            /** @see graph#get_vertices */
            std::vector<vertex_type> get_vertices() const override;

            /** @see graph#add_vertex */
            vertex_type add_vertex() override;

            /** @see graph#neighbours */
            std::vector<vertex_type> get_neighbours(vertex_type v) const override;

            /** @see graph#get_outdegree */
            size_t get_outdegree(vertex_type v) const override
            {
                return graphrepr[v].size();
            }
        };

        class directed_graph : public simple_graph
        {
        public:
            directed_graph(int n) :
                simple_graph(n)
            {
            }

            directed_graph(int n, std::vector<edge_type> edges) :
                simple_graph(n)
            {
                for(const auto & e : edges)
                    graphrepr[std::get<0>(e)].emplace(std::get<1>(e), DEFAULT_WEIGHT);
            }

            directed_graph(int n, std::vector<std::pair<int, int>> edges) :
                simple_graph(n)
            {
                for(const auto & e : edges)
                    graphrepr[e.first].emplace(e.second, DEFAULT_WEIGHT);
            }

            ~directed_graph() = default;
            directed_graph(const directed_graph & g) = default;
            directed_graph(directed_graph && g) = default;
            directed_graph & operator =(const directed_graph & g) = default;
            directed_graph & operator =(directed_graph && g) = default;

            /** @see graph#get_edges_number */
            size_t get_edges_number() const override;

            /** @see graph#edges */
            std::vector<edge_type> get_edges() const override;

            /** @see graph#add_edge */
            void add_edge(vertex_type v, vertex_type u) override;

            /** @see graph#get_indegree */
            size_t get_indegree(vertex_type v) const override;

            /** Odwracanie skierowania grafu */
            virtual void reverse();
        };

        class directed_weighted_graph : public directed_graph, public virtual weighted_graph
        {
        public:
            directed_weighted_graph(int n) :
                directed_graph(n)
            {
            }

            directed_weighted_graph(int n, std::vector<edge_type> edges) :
                directed_graph(n, edges)
            {
            }

            directed_weighted_graph(int n, std::vector<wedge_type> edges) :
                directed_graph(n)
            {
                for(const auto & e : edges)
                    graphrepr[std::get<0>(e)].emplace(std::get<1>(e), std::get<2>(e));
            }

            ~directed_weighted_graph() = default;
            directed_weighted_graph(const directed_weighted_graph & g) = default;
            directed_weighted_graph(directed_weighted_graph && g) = default;
            directed_weighted_graph & operator =(const directed_weighted_graph & g) = default;
            directed_weighted_graph & operator =(directed_weighted_graph && g) = default;

            /** @see weighted_graph#weighted_edges */
            std::vector<wedge_type> get_weighted_edges() const override;

            /** @see weighted_graph#add_weighted_edge */
            void add_weighted_edge(vertex_type v, vertex_type u, weight_type wg) override;

            /** @see weighted_graph#weighted_neighbours */
            std::vector<wvertex_type> get_weighted_neighbours(vertex_type v) const override
            {
                return std::vector<wvertex_type>(graphrepr[v].begin(), graphrepr[v].end());
            }

            /** @see directed_graph#reverse */
            void reverse() override;
        };

        class undirected_graph : public simple_graph
        {
        public:
            undirected_graph(int n) :
                simple_graph(n)
            {
            }

            undirected_graph(int n, std::vector<edge_type> edges) :
                simple_graph(n)
            {
                for(const auto & e : edges)
                {
                    graphrepr[std::get<0>(e)].emplace(std::get<1>(e), DEFAULT_WEIGHT);
                    graphrepr[std::get<1>(e)].emplace(std::get<0>(e), DEFAULT_WEIGHT);
                }
            }

            ~undirected_graph() = default;
            undirected_graph(const undirected_graph & g) = default;
            undirected_graph(undirected_graph && g) = default;
            undirected_graph & operator =(const undirected_graph & g) = default;
            undirected_graph & operator =(undirected_graph && g) = default;

            /** @see graph#get_edges_number */
            size_t get_edges_number() const override;

            /** @see graph#edges */
            std::vector<edge_type> get_edges() const override;

            /** @see graph#add_edge */
            void add_edge(vertex_type v, vertex_type u) override;

            /** @see graph#get_indegree */
            size_t get_indegree(vertex_type v) const override
            {
                return get_outdegree(v);
            }

            /**
             * Zamiana krawędzi nieskierowanych na skierowane.
             * @return graf ze skierowanymi krawędziami
             */
            operator directed_graph() const;
        };

        class undirected_weighted_graph : public undirected_graph, public virtual weighted_graph
        {
        public:
            undirected_weighted_graph(int n) :
                undirected_graph(n)
            {
            }

            undirected_weighted_graph(int n, std::vector<edge_type> edges) :
                undirected_graph(n, edges)
            {
            }

            undirected_weighted_graph(int n, std::vector<wedge_type> edges) :
                undirected_graph(n)
            {
                for(const auto & e : edges)
                {
                    graphrepr[std::get<0>(e)].emplace(std::get<1>(e), std::get<2>(e));
                    graphrepr[std::get<1>(e)].emplace(std::get<0>(e), std::get<2>(e));
                }
            }

            ~undirected_weighted_graph() = default;
            undirected_weighted_graph(const undirected_weighted_graph & g) = default;
            undirected_weighted_graph(undirected_weighted_graph && g) = default;
            undirected_weighted_graph & operator =(const undirected_weighted_graph & g) = default;
            undirected_weighted_graph & operator =(undirected_weighted_graph && g) = default;

            /** @see weighted_weighted_graph#get_weighted_edges */
            std::vector<wedge_type> get_weighted_edges() const override;

            /** @see weighted_graph#add_weighted_edge */
            void add_weighted_edge(vertex_type v, vertex_type u, weight_type wg) override;

            /** @see weighted_graph#weighted_neighbours */
            std::vector<wvertex_type> get_weighted_neighbours(vertex_type v) const override
            {
                return std::vector<wvertex_type>(graphrepr[v].begin(), graphrepr[v].end());
            }

            /**
             * Zamiana krawędzi nieskierowanych na skierowane z zachowaniem wag.
             * @return graf ze skierowanymi krawędziami ważonymi
             */
            operator directed_weighted_graph() const;
        };
    }
}

#endif
