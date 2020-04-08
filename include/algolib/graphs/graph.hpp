/*!
 * \file graph.hpp
 * \brief Struktury grafów
 */
#ifndef GRAPH_HPP_
#define GRAPH_HPP_

#include <cstdlib>
#include <exception>
#include <stdexcept>
#include <algorithm>
#include <set>
#include <tuple>
#include <vector>
#include <limits>
#include <numeric>

using weight_t = double;
using vertex_t = size_t;
using wvertex_t = std::tuple<vertex_t, weight_t>;
using edge_t = std::tuple<vertex_t, vertex_t>;
using wedge_t = std::tuple<vertex_t, vertex_t, weight_t>;

using namespace std::string_literals;

namespace algolib
{
    namespace graphs
    {
        class no_such_vertex_exception : public std::logic_error
        {
        public:
            explicit no_such_vertex_exception(const std::string & vertex)
                : std::logic_error("No vertex "s + vertex)
            {
            }
        };

#pragma region graph

        struct graph
        {
            static constexpr weight_t INF =
                    std::numeric_limits<weight_t>::infinity();  //!< Oznaczenie nieskończoności.

            virtual ~graph() = default;

            //! \return liczba wierzchołków
            virtual size_t get_vertices_number() const = 0;

            //! \return wektor wierzchołków
            virtual std::vector<vertex_t> get_vertices() const = 0;

            /*!
             * \brief Dodawanie nowego wierzchołka
             * \param neighbours sąsiedzi nowego wierzchołka
             * \return oznaczenie wierzchołka
             */
            virtual vertex_t add_vertex(const std::vector<vertex_t> & neighbours) = 0;

            //! \return liczba krawędzi
            virtual size_t get_edges_number() const = 0;

            //! \return wektor krawędzi
            virtual std::vector<edge_t> get_edges() const = 0;

            /*!
             * \brief Dodawanie nowej krawędzi
             * \param v początkowy wierzchołek
             * \param u końcowy wierzchołek
             */
            virtual void add_edge(vertex_t vertex1, vertex_t vertex2) = 0;

            /*!
             * \param v numer wierzchołka
             * \return wektor sąsiadów wierzchołka
             */
            virtual std::vector<vertex_t> get_neighbours(vertex_t vertex) const = 0;

            /*!
             * \param v numer wierzchołka
             * \return stopień wyjściowy wierzchołka
             */
            virtual size_t get_outdegree(vertex_t vertex) const = 0;

            /*!
             * \param v numer wierzchołka
             * \return stopień wejściowy wierzchołka
             */
            virtual size_t get_indegree(vertex_t vertex) const = 0;
        };

#pragma endregion
#pragma region weighted_graph

        struct weighted_graph : public virtual graph
        {
            ~weighted_graph() override = default;

            //! \return wektor krawędzi z wagami
            virtual std::vector<wedge_t> get_weighted_edges() const = 0;

            /*!
             * \brief Dodawanie nowej krawędzi z jej wagą
             * \param v początkowy wierzchołek
             * \param u końcowy wierzchołek
             * \param wg waga krawędzi
             */
            virtual void add_weighted_edge(vertex_t vertex1, vertex_t vertex2, weight_t weight) = 0;

            /*!
             * \param v numer wierzchołka
             * \return wektor sąsiadów wierzchołka z wagami
             */
            virtual std::vector<wvertex_t> get_weighted_neighbours(vertex_t vertex) const = 0;
        };

#pragma endregion
#pragma region simple_graph

        class simple_graph : public virtual graph
        {
        public:
            explicit simple_graph(int n)
            {
                this->graphrepr.resize(n);
            }

            ~simple_graph() override = default;
            simple_graph(const simple_graph &) = default;
            simple_graph(simple_graph &&) = default;
            simple_graph & operator=(const simple_graph &) = default;
            simple_graph & operator=(simple_graph &&) = default;

            size_t get_vertices_number() const override
            {
                return graphrepr.size();
            }

            std::vector<vertex_t> get_vertices() const override;

            vertex_t add_vertex(const std::vector<vertex_t> & neighbours) override;

            std::vector<vertex_t> get_neighbours(vertex_t vertex) const override;

            size_t get_outdegree(vertex_t vertex) const override;

        protected:
            static constexpr weight_t DEFAULT_WEIGHT = 1.0;  //!< Domyślna waga krawędzi.
            std::vector<std::set<wvertex_t>> graphrepr;  //!< Lista sąsiedztwa grafu.
        };

#pragma endregion
    }
}

#endif
