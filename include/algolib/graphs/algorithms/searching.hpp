/**!
 * \file searching.hpp
 * \brief Graph searching algorithms
 */
#ifndef SEARCHING_HPP_
#define SEARCHING_HPP_

#include <cstdlib>
#include <algorithm>
#include <optional>
#include <queue>
#include <stack>
#include <unordered_map>
#include <unordered_set>
#include <vector>
#include "algolib/graphs/algorithms/searching_strategy.hpp"
#include "algolib/graphs/graph.hpp"

namespace internal
{
    namespace algr = algolib::graphs;

    template <typename Vertex>
    struct dfs_recursive_state
    {
        void on_entry(Vertex vertex_)
        {
            reached[vertex_] = iteration;
        }

        void on_exit(Vertex vertex_)
        {
            reached[vertex_] = -iteration;
        }

        std::optional<Vertex> vertex = std::nullopt;
        int iteration = 1;
        std::unordered_map<Vertex, int> reached = {};
    };

    // Single step of recursive DFS.
    template <typename VertexId, typename VertexProperty, typename EdgeProperty>
    void dfs_recursive_step(
            const algr::graph<VertexId, VertexProperty, EdgeProperty> & graph_,
            algr::dfs_strategy<typename algr::graph<VertexId, VertexProperty,
                                                    EdgeProperty>::vertex_type> & strategy,
            dfs_recursive_state<typename algr::graph<VertexId, VertexProperty,
                                                     EdgeProperty>::vertex_type> & state)
    {
        typename algr::graph<VertexId, VertexProperty, EdgeProperty>::vertex_type vertex =
                state.vertex.value();

        state.on_entry(vertex);
        strategy.on_entry(vertex);

        for(auto && neighbour : graph_.neighbours(vertex))
        {
            auto it = state.reached.find(neighbour);

            if(it == state.reached.end())
            {
                strategy.on_next_vertex(vertex, neighbour);
                state.vertex = std::make_optional(neighbour);
                dfs_recursive_step(graph_, strategy, state);
            }
            else if(it->second == state.iteration)
                strategy.on_edge_to_visited(vertex, neighbour);
        }

        strategy.on_exit(vertex);
        state.on_exit(vertex);
    }
}

namespace algolib::graphs
{
    /*!
     * \brief Breadth-first search algorithm.
     * \param graph_ a graph
     * \param strategy a searching strategy
     * \param roots starting vertices
     * \return vector of visited vertices
     */
    template <typename VertexId, typename VertexProperty, typename EdgeProperty>
    std::vector<typename graph<VertexId, VertexProperty, EdgeProperty>::vertex_type> bfs(
            const graph<VertexId, VertexProperty, EdgeProperty> & graph_,
            bfs_strategy<typename graph<VertexId, VertexProperty, EdgeProperty>::vertex_type> &
                    strategy,
            std::vector<typename graph<VertexId, VertexProperty, EdgeProperty>::vertex_type> roots)
    {
        std::unordered_set<typename graph<VertexId, VertexProperty, EdgeProperty>::vertex_type>
                reached;
        std::queue<typename graph<VertexId, VertexProperty, EdgeProperty>::vertex_type>
                vertex_queue;

        for(auto && root : roots)
            if(reached.find(root) == reached.end())
            {
                strategy.for_root(root);
                vertex_queue.push(root);
                reached.insert(root);

                while(!vertex_queue.empty())
                {
                    typename graph<VertexId, VertexProperty, EdgeProperty>::vertex_type vertex =
                            vertex_queue.front();

                    vertex_queue.pop();
                    strategy.on_entry(vertex);

                    for(auto && neighbour : graph_.neighbours(vertex))
                        if(reached.find(neighbour) == reached.end())
                        {
                            strategy.on_next_vertex(vertex, neighbour);
                            reached.insert(neighbour);
                            vertex_queue.push(neighbour);
                        }

                    strategy.on_exit(vertex);
                }
            }

        return std::vector<typename graph<VertexId, VertexProperty, EdgeProperty>::vertex_type>(
                reached.begin(), reached.end());
    }

    /*!
     * \brief Iterative depth-first search algorithm.
     * \param graph_ a graph
     * \param strategy a searching strategy
     * \param roots starting vertices
     * \return vector of visited vertices
     */
    template <typename VertexId, typename VertexProperty, typename EdgeProperty>
    std::vector<typename graph<VertexId, VertexProperty, EdgeProperty>::vertex_type> dfs_iterative(
            const graph<VertexId, VertexProperty, EdgeProperty> & graph_,
            dfs_strategy<typename graph<VertexId, VertexProperty, EdgeProperty>::vertex_type> &
                    strategy,
            std::vector<typename graph<VertexId, VertexProperty, EdgeProperty>::vertex_type> roots)
    {
        std::vector<typename graph<VertexId, VertexProperty, EdgeProperty>::vertex_type> visited;
        std::unordered_map<typename graph<VertexId, VertexProperty, EdgeProperty>::vertex_type, int>
                reached;
        std::stack<typename graph<VertexId, VertexProperty, EdgeProperty>::vertex_type>
                vertex_stack;
        int iteration = 1;

        for(auto && root : roots)
            if(reached.find(root) == reached.end())
            {
                strategy.for_root(root);
                vertex_stack.push(root);

                while(!vertex_stack.empty())
                {
                    typename graph<VertexId, VertexProperty, EdgeProperty>::vertex_type vertex =
                            vertex_stack.top();

                    vertex_stack.pop();

                    auto insert_result = reached.emplace(vertex, iteration);

                    if(insert_result.second)
                    {
                        strategy.on_entry(vertex);

                        for(auto && neighbour : graph_.neighbours(vertex))
                        {
                            auto it = reached.find(neighbour);

                            if(it == reached.end())
                            {
                                strategy.on_next_vertex(vertex, neighbour);
                                vertex_stack.push(neighbour);
                            }
                            else if(it->second == iteration)
                                strategy.on_edge_to_visited(vertex, neighbour);
                        }

                        strategy.on_exit(vertex);
                        reached[vertex] = -iteration;
                    }
                }

                ++iteration;
            }

        std::transform(reached.begin(), reached.end(), std::back_inserter(visited),
                       [](auto && p) { return p.first; });

        return visited;
    }

    /*!
     * \brief Recursive depth-first search algorithm.
     * \param graph_ a graph
     * \param strategy a searching strategy
     * \param roots starting vertices
     * \return vector of visited vertices
     */
    template <typename VertexId, typename VertexProperty, typename EdgeProperty>
    std::vector<typename graph<VertexId, VertexProperty, EdgeProperty>::vertex_type> dfs_recursive(
            const graph<VertexId, VertexProperty, EdgeProperty> & graph_,
            dfs_strategy<typename graph<VertexId, VertexProperty, EdgeProperty>::vertex_type> &
                    strategy,
            std::vector<typename graph<VertexId, VertexProperty, EdgeProperty>::vertex_type> roots)
    {
        std::vector<typename graph<VertexId, VertexProperty, EdgeProperty>::vertex_type> visited;
        internal::dfs_recursive_state<
                typename graph<VertexId, VertexProperty, EdgeProperty>::vertex_type>
                state;

        for(auto && root : roots)
            if(state.reached.find(root) == state.reached.end())
            {
                strategy.for_root(root);
                state.vertex = std::make_optional(root);
                internal::dfs_recursive_step(graph_, strategy, state);
                ++state.iteration;
            }

        std::transform(state.reached.begin(), state.reached.end(), std::back_inserter(visited),
                       [](auto && p) { return p.first; });

        return visited;
    }
}

#endif
