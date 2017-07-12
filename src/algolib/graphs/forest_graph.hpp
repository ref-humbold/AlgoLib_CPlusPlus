/**
 * @file forest_graph.hpp
 * STRUKTURY GRAFÓW DRZEW
 */
#ifndef FOREST_GRAPH_HPP
#define FOREST_GRAPH_HPP

#include <cstdlib>
#include <exception>
#include <stdexcept>
#include <algorithm>
#include <tuple>
#include <vector>

#include "../structures/disjoint_sets.hpp"
#include "graph.hpp"
#include "undirected_graph.hpp"

namespace alst = algolib::structures;

namespace algolib
{
    namespace graphs
    {
        class cycle_exception : std::runtime_error
        {
        public:
            explicit cycle_exception() : std::runtime_error("")
            {
            }

            explicit cycle_exception(const std::string & what_arg) : std::runtime_error(what_arg)
            {
            }

            explicit cycle_exception(const char * what_arg) : std::runtime_error(what_arg)
            {
            }
        };

        class forest_graph : public undirected_graph
        {
        private:
            undirected_graph & graph;

            alst::disjoint_sets<vertex_t> components;

        public:
            explicit forest_graph(undirected_graph & ugraph,
                                  std::vector<edge_t> edges = std::vector<edge_t>())
                : graph{ugraph}, components{alst::disjoint_sets<vertex_t>(ugraph.get_vertices())}
            {
                for(const auto & e : edges)
                    this->add_edge(std::get<0>(e), std::get<1>(e));
            }

            size_t get_trees_number() const
            {
                return this->components.size();
            }

            size_t get_vertices_number() const override
            {
                return this->graph.get_vertices_number();
            }

            std::vector<vertex_t> get_vertices() const override
            {
                return this->graph.get_vertices();
            }

            vertex_t add_vertex();

            size_t get_edges_number() const override
            {
                return this->graph.get_edges_number();
            }

            std::vector<edge_t> get_edges() const override
            {
                return this->graph.get_edges();
            }

            void add_edge(vertex_t vertex1, vertex_t vertex2);

            std::vector<vertex_t> get_neighbours(vertex_t vertex) const override
            {
                return this->graph.get_neighbours(vertex);
            }

            size_t get_outdegree(vertex_t vertex) const override
            {
                return this->graph.get_outdegree(vertex);
            }

            size_t get_indegree(vertex_t vertex) const override
            {
                return this->graph.get_indegree(vertex);
            }

            directed_graph * as_directed() const override
            {
                return graph.as_directed();
            }
            /**
             * Sprawdzanie, czy wierzchołki należą do tego samego drzewa.
             * @param vertex1 pierwszy wierzchołek
             * @param vertex2 drugi wierzchołek
             * @return czy wierzchołki są w jednym drzewie
             */
            bool is_same_tree(vertex_t vertex1, vertex_t vertex2) const
            {
                return components.is_same_set(vertex1, vertex2);
            }
        };
    }
}

#endif
