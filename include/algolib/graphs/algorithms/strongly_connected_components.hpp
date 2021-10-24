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

    template <typename Vertex>
    struct post_order_strategy : public algr::dfs_strategy<Vertex>
    {
        post_order_strategy() : timer{0}
        {
        }

        void for_root(const Vertex &) override
        {
        }

        void on_entry(const Vertex &) override
        {
        }

        void on_next_vertex(const Vertex &, const Vertex &) override
        {
        }

        void on_exit(const Vertex & vertex) override
        {
            this->post_times.emplace(vertex, timer);
            ++this->timer;
        }

        void on_edge_to_visited(const Vertex &, const Vertex &) override
        {
        }

        std::unordered_map<Vertex, int> post_times;
        int timer;
    };

#pragma endregion
#pragma region scc_strategy

    template <typename Vertex>
    struct scc_strategy : public algr::dfs_strategy<Vertex>
    {
        void for_root(const Vertex &) override
        {
            this->components.push_back(std::unordered_set<Vertex>());
        }

        void on_entry(const Vertex & vertex) override
        {
            this->components.back().insert(vertex);
        }

        void on_next_vertex(const Vertex &, const Vertex &) override
        {
        }

        void on_exit(const Vertex &) override
        {
        }

        void on_edge_to_visited(const Vertex &, const Vertex &) override
        {
        }

        std::vector<std::unordered_set<Vertex>> components;
    };

#pragma endregion
}

namespace algolib::graphs
{
    /*!
     * \brief Finds strongly connected components in given directed graph.
     * \param graph a directed graph
     * \return vector of vertices in strongly connected components
     */
    template <typename VertexId, typename VertexProperty, typename EdgeProperty>
    std::vector<std::unordered_set<
            typename directed_graph<VertexId, VertexProperty, EdgeProperty>::vertex_type>>
            find_scc(const directed_simple_graph<VertexId, VertexProperty, EdgeProperty> & graph)
    {
        internal::post_order_strategy<
                typename directed_graph<VertexId, VertexProperty, EdgeProperty>::vertex_type>
                post_order_strategy;

        dfs_recursive(graph, post_order_strategy, graph.vertices());

        std::vector<std::pair<
                typename directed_graph<VertexId, VertexProperty, EdgeProperty>::vertex_type, int>>
                entries;
        std::vector<typename directed_graph<VertexId, VertexProperty, EdgeProperty>::vertex_type>
                vertices;

        std::copy(post_order_strategy.post_times.begin(), post_order_strategy.post_times.end(),
                  std::back_inserter(entries));
        std::sort(entries.begin(), entries.end(),
                  [](auto && entry1, auto && entry2) { return entry2.second < entry1.second; });
        std::transform(entries.begin(), entries.end(), std::back_inserter(vertices),
                       [](auto && entry) { return entry.first; });

        directed_simple_graph<VertexId, VertexProperty, EdgeProperty> reversed_graph =
                graph.reversed_copy();
        internal::scc_strategy<
                typename directed_graph<VertexId, VertexProperty, EdgeProperty>::vertex_type>
                scc_strategy;

        dfs_recursive(reversed_graph, scc_strategy, vertices);
        return scc_strategy.components;
    }
}

#endif
