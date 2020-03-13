/**!
 * \file forest_graph.hpp
 * \brief Tree graph structure
 */
#ifndef TREE_GRAPH_HPP_
#define TREE_GRAPH_HPP_

#include <cstdlib>
#include <exception>
#include <stdexcept>
#include <algorithm>
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
        };

        class not_connected_exception : std::logic_error
        {
        public:
            explicit not_connected_exception(const std::string & what_arg)
                : std::logic_error(what_arg)
            {
            }
        };

        class tree_graph : public undirected_graph
        {
        public:
            explicit tree_graph(int n, std::vector<edge_t> edges);
            virtual ~tree_graph() = default;
            tree_graph(const tree_graph &) = default;
            tree_graph(tree_graph &&) = default;
            tree_graph & operator=(const tree_graph &) = default;
            tree_graph & operator=(tree_graph &&) = default;

            size_t get_vertices_number() const override
            {
                return graph.get_vertices_number();
            }

            std::vector<vertex_t> get_vertices() const override
            {
                return graph.get_vertices();
            }

            vertex_t add_vertex(const std::vector<vertex_t> & neighbours) override;

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

        private:
            undirected_simple_graph graph;
        };
    }
}

#endif
