/*!
 * \file topological_sorting.hpp
 * \brief Algorithms for topological sorting of a directed graph
 */
#ifndef TOPOLOGICAL_SORTING_HPP_
#define TOPOLOGICAL_SORTING_HPP_

#include <cstdlib>
#include <exception>
#include <stdexcept>
#include <algorithm>
#include <queue>
#include <string>
#include <unordered_map>
#include <vector>
#include "algolib/graphs/algorithms/searching.hpp"
#include "algolib/graphs/directed_graph.hpp"

using namespace std::string_literals;

namespace algolib::graphs
{
    class directed_cyclic_graph_error : public std::logic_error
    {
    public:
        explicit directed_cyclic_graph_error(const std::string & what_arg)
            : std::logic_error(what_arg)
        {
        }
    };
}

namespace internal
{
    namespace algr = algolib::graphs;

    template <typename V>
    class topological_strategy : public algr::dfs_strategy<V>
    {
    public:
        ~topological_strategy() override = default;

        void for_root(const V &) override
        {
        }

        void on_entry(const V &) override
        {
        }

        void on_next_vertex(const V &, const V &) override
        {
        }

        void on_exit(const V & vertex) override
        {
            order.push_back(vertex);
        }

        void on_edge_to_visited(const V &, const V &) override
        {
            throw algr::directed_cyclic_graph_error("Given graph contains a cycle"s);
        }

        std::vector<V> order;
    };
}

namespace algolib::graphs
{
    /*!
         * \brief Topological sorting algorithm using predecessors counting.
         * \param graph a directed graph
         * \return topological order of vertices
         * \throws directed_cyclic_graph_error if given graph contains a cycle
         */
    template <typename V, typename VP, typename EP>
    std::vector<typename directed_graph<V, VP, EP>::vertex_type>
            sort_topological_using_inputs(const directed_graph<V, VP, EP> & graph)
    {
        std::vector<typename directed_graph<V, VP, EP>::vertex_type> order;

        if(graph.edges_count() == 0)
            return graph.vertices();

        std::unordered_map<typename directed_graph<V, VP, EP>::vertex_type, int> input_degrees;
        std::priority_queue<typename directed_graph<V, VP, EP>::vertex_type,
                            std::vector<typename directed_graph<V, VP, EP>::vertex_type>,
                            std::greater<typename directed_graph<V, VP, EP>::vertex_type>>
                vertex_queue;

        for(auto && vertex : graph.vertices())
        {
            int degree = graph.input_degree(vertex);

            input_degrees.emplace(vertex, degree);

            if(degree == 0)
                vertex_queue.push(vertex);
        }

        while(!vertex_queue.empty())
        {
            auto vertex = vertex_queue.top();

            vertex_queue.pop();
            order.push_back(vertex);
            input_degrees.erase(vertex);

            for(auto && neighbour : graph.neighbours(vertex))
            {
                --input_degrees[neighbour];

                if(input_degrees[neighbour] == 0)
                    vertex_queue.push(neighbour);
            }
        }

        if(order.size() != graph.vertices_count())
            throw directed_cyclic_graph_error("Given graph contains a cycle"s);

        return order;
    }

    /*!
         * \brief Topological sorting algorithm using DFS.
         * \param graph a directed graph
         * \return topological order of vertices
         * \throws directed_cyclic_graph_error if given graph contains a cycle
         */
    template <typename V, typename VP, typename EP>
    std::vector<typename directed_graph<V, VP, EP>::vertex_type>
            sort_topological_using_dfs(const directed_graph<V, VP, EP> & graph)
    {
        if(graph.edges_count() == 0)
            return graph.vertices();

        internal::topological_strategy<typename directed_graph<V, VP, EP>::vertex_type> strategy;
        dfs_recursive(graph, strategy, graph.vertices());

        std::reverse(strategy.order.begin(), strategy.order.end());
        return strategy.order;
    }
}

#endif
