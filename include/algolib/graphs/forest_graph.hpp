/**!
 * \file forest_graph.hpp
 * \brief STRUKTURY GRAFÓW DRZEW
 */
#ifndef FOREST_GRAPH_HPP_
#define FOREST_GRAPH_HPP_

#include <cstdlib>
#include <algorithm>
#include <exception>
#include <stdexcept>
#include <tuple>
#include <vector>
#include "algolib/structures/disjoint_sets.hpp"
#include "graph.hpp"
#include "undirected_graph.hpp"

namespace alst = algolib::structures;

namespace algolib
{
    namespace graphs
    {
        class cycle_exception : std::logic_error
        {
        public:
            explicit cycle_exception(const std::string & what_arg) : std::logic_error(what_arg)
            {
            }

            explicit cycle_exception(const char * what_arg = "") : std::logic_error(what_arg)
            {
            }
        };

        class forest_graph : public undirected_graph
        {
        public:
            explicit forest_graph(int n, std::vector<edge_t> edges = std::vector<edge_t>());
            virtual ~forest_graph() = default;
            forest_graph(const forest_graph &) = default;
            forest_graph(forest_graph &&) = default;
            forest_graph & operator=(const forest_graph &) = default;
            forest_graph & operator=(forest_graph &&) = default;

            size_t get_trees_number() const
            {
                return components.size();
            }

            size_t get_vertices_number() const override
            {
                return graph.get_vertices_number();
            }

            std::vector<vertex_t> get_vertices() const override
            {
                return graph.get_vertices();
            }

            vertex_t add_vertex() override;

            size_t get_edges_number() const override
            {
                return graph.get_edges_number();
            }

            std::vector<edge_t> get_edges() const override
            {
                return graph.get_edges();
            }

            void add_edge(vertex_t vertex1, vertex_t vertex2) override;

            std::vector<vertex_t> get_neighbours(vertex_t vertex) const override
            {
                return graph.get_neighbours(vertex);
            }

            size_t get_outdegree(vertex_t vertex) const override
            {
                return graph.get_outdegree(vertex);
            }

            size_t get_indegree(vertex_t vertex) const override
            {
                return graph.get_indegree(vertex);
            }

            /**!
             * \brief Sprawdzanie, czy wierzchołki należą do tego samego drzewa.
             * \param vertex1 pierwszy wierzchołek
             * \param vertex2 drugi wierzchołek
             * \return czy wierzchołki są w jednym drzewie
             */
            bool is_same_tree(vertex_t vertex1, vertex_t vertex2) const;

        private:
            undirected_simple_graph graph;

            alst::disjoint_sets<vertex_t> components;
        };
    }
}

#endif
