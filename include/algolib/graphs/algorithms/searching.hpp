/**!
 * \file searching.hpp
 * \brief Graph searching algorithms
 */
#ifndef SEARCHING_HPP_
#define SEARCHING_HPP_

#include <cstdlib>
#include <algorithm>
#include <queue>
#include <stack>
#include <unordered_map>
#include <unordered_set>
#include <vector>
#include "algolib/graphs/graph.hpp"
#include "searching_strategy.hpp"

namespace internal
{
    namespace algr = algolib::graphs;

    template <typename V>
    struct dfs_recursive_state
    {
        void on_entry(V vertex_)
        {
            reached[vertex_] = iteration;
        }

        void on_exit(V vertex_)
        {
            reached[vertex_] = -iteration;
        }

        V vertex;
        int iteration;
        std::unordered_map<V, int> reached;
    };

    // Single step of recursive DFS.
    template <typename V, typename VP, typename EP>
    void dfs_recursive_step(const algr::graph<V, VP, EP> & graph_, algr::dfs_strategy<V> & strategy,
                            dfs_recursive_state<V> & state)
    {
        V vertex = state.vertex;

        state.on_entry(vertex);
        strategy.on_entry(vertex);

        for(auto && neighbour : graph_.neighbours(vertex))
        {
            auto it = state.reached.find(neighbour);

            if(it == state.reached.end())
            {
                strategy.on_next_vertex(vertex, neighbour);
                state.vertex = neighbour;
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
    /**!
         * \brief Breadth-first search algorithm.
         * \param graph_ a graph
         * \param strategy a searching strategy
         * \param roots starting vertices
         * \return vector of visited vertices
         */
    template <typename V, typename VP, typename EP>
    std::vector<V> bfs(const graph<V, VP, EP> & graph_,
                       bfs_strategy<typename graph<V, VP, EP>::vertex_type> & strategy,
                       std::vector<typename graph<V, VP, EP>::vertex_type> roots)
    {
        std::unordered_set<V> reached;
        std::queue<V> vertex_queue;

        for(auto && root : roots)
            if(reached.find(root) == reached.end())
            {
                strategy.for_root(root);
                vertex_queue.push(root);
                reached.insert(root);

                while(!vertex_queue.empty())
                {
                    V vertex = vertex_queue.front();

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

        return std::vector<V>(reached.begin(), reached.end());
    }

    /**!
         * \brief Iterative depth-first search algorithm.
         * \param graph_ a graph
         * \param strategy a searching strategy
         * \param roots starting vertices
         * \return vector of visited vertices
         */
    template <typename V, typename VP, typename EP>
    std::vector<V> dfs_iterative(const graph<V, VP, EP> & graph_, dfs_strategy<V> & strategy,
                                 std::vector<V> roots)
    {
        std::vector<V> visited;
        std::unordered_map<V, int> reached;
        std::stack<V> vertex_stack;
        int iteration = 1;

        for(auto && root : roots)
            if(reached.find(root) == reached.end())
            {
                strategy.for_root(root);
                vertex_stack.push(root);

                while(!vertex_stack.empty())
                {
                    V vertex = vertex_stack.top();

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
                       [](std::pair<V, int> p) { return p.first; });

        return visited;
    }

    /**!
         * \brief Recursive depth-first search algorithm.
         * \param graph_ a graph
         * \param strategy a searching strategy
         * \param roots starting vertices
         * \return vector of visited vertices
         */
    template <typename V, typename VP, typename EP>
    std::vector<V> dfs_recursive(const graph<V, VP, EP> & graph_, dfs_strategy<V> & strategy,
                                 std::vector<V> roots)
    {
        std::vector<V> visited;
        internal::dfs_recursive_state<V> state;

        for(auto && root : roots)
            if(state.reached.find(root) == state.reached.end())
            {
                strategy.for_root(root);
                state.vertex = root;
                internal::dfs_recursive_step(graph_, strategy, state);
                ++state.iteration;
            }

        std::transform(state.reached.begin(), state.reached.end(), std::back_inserter(visited),
                       [](std::pair<V, int> p) { return p.first; });

        return visited;
    }
}

#endif
