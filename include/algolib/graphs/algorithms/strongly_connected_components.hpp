/**!
 * \file strongly_connected_components.hpp
 * \brief Algorithm for strongly connected components
 */
#ifndef STRONGLY_CONNECTED_COMPONENTS_HPP_
#define STRONGLY_CONNECTED_COMPONENTS_HPP_

#include <cstdlib>
#include <algorithm>
#include <unordered_map>
#include <unordered_set>
#include <vector>
#include "algolib/graphs/algorithms/searching.hpp"
#include "algolib/graphs/directed_graph.hpp"

namespace internal
{
    namespace algr = algolib::graphs;

#pragma region post_order_strategy

    template <typename V>
    struct post_order_strategy : public algr::dfs_strategy<V>
    {
        post_order_strategy() : timer{0}
        {
        }

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
            this->post_times.emplace(vertex, timer);
            ++this->timer;
        }

        void on_edge_to_visited(const V &, const V &) override
        {
        }

        std::unordered_map<V, int> post_times;
        int timer;
    };

#pragma endregion
#pragma region scc_strategy

    template <typename V>
    struct scc_strategy : public algr::dfs_strategy<V>
    {
        void for_root(const V &) override
        {
            this->components.push_back(std::unordered_set<V>());
        }

        void on_entry(const V & vertex) override
        {
            this->components.back().insert(vertex);
        }

        void on_next_vertex(const V &, const V &) override
        {
        }

        void on_exit(const V &) override
        {
        }

        void on_edge_to_visited(const V &, const V &) override
        {
        }

        std::vector<std::unordered_set<V>> components;
    };

#pragma endregion
}

namespace algolib
{
    namespace graphs
    {
        /*!
         * \brief Finds strongly connected components in given directed graph.
         * \param graph a directed graph
         * \return list of vertices in strongly connected components
         */
        template <typename V, typename VP, typename EP>
        std::vector<std::unordered_set<typename directed_graph<V, VP, EP>::vertex_type>>
                find_scc(const directed_simple_graph<V, VP, EP> & graph)
        {
            internal::post_order_strategy<typename directed_graph<V, VP, EP>::vertex_type>
                    post_order_strategy;

            dfs_recursive(graph, post_order_strategy, graph.vertices());

            std::vector<std::pair<typename directed_graph<V, VP, EP>::vertex_type, int>> entries;
            std::vector<typename directed_graph<V, VP, EP>::vertex_type> vertices;

            std::copy(std::begin(post_order_strategy.post_times),
                      std::end(post_order_strategy.post_times), std::back_inserter(entries));
            std::sort(
                    entries.begin(), entries.end(),
                    [](const std::pair<typename directed_graph<V, VP, EP>::vertex_type, int> & e1,
                       const std::pair<typename directed_graph<V, VP, EP>::vertex_type, int> & e2) {
                        return e2.second < e1.second;
                    });
            std::transform(entries.begin(), entries.end(), std::back_inserter(vertices),
                           [](const std::pair<typename directed_graph<V, VP, EP>::vertex_type,
                                              int> & entry) { return entry.first; });

            directed_simple_graph<V, VP, EP> reversed_graph = graph.reversed_copy();
            internal::scc_strategy<typename directed_graph<V, VP, EP>::vertex_type> scc_strategy;

            dfs_recursive(reversed_graph, scc_strategy, vertices);

            return scc_strategy.components;
        }
    }
}

#endif
