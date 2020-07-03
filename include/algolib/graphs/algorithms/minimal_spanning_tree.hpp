/**!
 * \file minimal_spanning_tree.hpp
 * \brief Algorithms for minimal spanning tree
 */
#ifndef MINIMAL_SPANNING_TREE_HPP_
#define MINIMAL_SPANNING_TREE_HPP_

#include <cstdlib>
#include <algorithm>
#include <queue>
#include <unordered_set>
#include <vector>
#include "algolib/graphs/undirected_graph.hpp"
#include "algolib/structures/disjoint_sets.hpp"

namespace internal
{
    template <typename V, typename E, typename VP, typename EP>
    struct kruskal_cmp
    {
        explicit kruskal_cmp(const algolib::graphs::undirected_simple_graph<V, VP, EP> & graph)
            : graph{graph}
        {
        }

        bool operator()(const E & edge1, const E & edge2) const
        {
            return graph[edge2].weight() < graph[edge1].weight();
        }

        const algolib::graphs::undirected_simple_graph<V, VP, EP> & graph;
    };

    template <typename V, typename E, typename VP, typename EP>
    struct prim_cmp
    {
        explicit prim_cmp(const algolib::graphs::undirected_simple_graph<V, VP, EP> & graph)
            : graph{graph}
        {
        }

        bool operator()(const std::pair<E, V> & pair1, const std::pair<E, V> & pair2) const
        {
            return graph[pair2.first].weight() < graph[pair1.first].weight();
        }

        const algolib::graphs::undirected_simple_graph<V, VP, EP> & graph;
    };
}

namespace algolib
{
    namespace graphs
    {
        namespace alst = algolib::structures;

        /**!
         * \brief Kruskal algorithm.
         * \param graph an undirected weighted graph
         * \return the minimal spanning tree
         */
        template <typename V, typename VP, typename EP>
        undirected_simple_graph<V, VP, EP> kruskal(const undirected_simple_graph<V, VP, EP> & graph)
        {
            using cmp = internal::kruskal_cmp<
                    typename undirected_simple_graph<V, VP, EP>::vertex_type,
                    typename undirected_simple_graph<V, VP, EP>::edge_type,
                    typename undirected_simple_graph<V, VP, EP>::vertex_property_type,
                    typename undirected_simple_graph<V, VP, EP>::edge_property_type>;

            undirected_simple_graph<V, VP, EP> mst(graph.vertices());
            std::vector<typename undirected_simple_graph<V, VP, EP>::vertex_type> vertices =
                    graph.vertices();
            alst::disjoint_sets<typename undirected_simple_graph<V, VP, EP>::vertex_type>
                    vertex_sets(vertices.begin(), vertices.end());
            auto edge_queue = std::priority_queue<
                    typename undirected_simple_graph<V, VP, EP>::edge_type,
                    std::vector<typename undirected_simple_graph<V, VP, EP>::edge_type>, cmp>(
                    cmp(graph));

            for(auto && edge : graph.edges())
                edge_queue.push(edge);

            while(vertex_sets.size() > 1 && !edge_queue.empty())
            {
                auto edge = edge_queue.top();

                edge_queue.pop();

                if(!vertex_sets.is_same_set(edge.source(), edge.destination()))
                    mst.add_edge(edge, graph[edge]);

                vertex_sets.union_set(edge.source(), edge.destination());
            }

            return mst;
        }

        /**!
         * \brief Prim algorithm.
         * \param graph an undirected weighted graph
         * \param source starting vertex
         * \return the minimal spanning tree
         */
        template <typename V, typename VP, typename EP>
        undirected_simple_graph<V, VP, EP>
                prim(const undirected_simple_graph<V, VP, EP> & graph,
                     typename undirected_simple_graph<V, VP, EP>::vertex_type source)
        {
            using ev_pair = std::pair<typename undirected_simple_graph<V, VP, EP>::edge_type,
                                      typename undirected_simple_graph<V, VP, EP>::vertex_type>;
            using cmp = internal::prim_cmp<
                    typename undirected_simple_graph<V, VP, EP>::vertex_type,
                    typename undirected_simple_graph<V, VP, EP>::edge_type,
                    typename undirected_simple_graph<V, VP, EP>::vertex_property_type,
                    typename undirected_simple_graph<V, VP, EP>::edge_property_type>;

            undirected_simple_graph<V, VP, EP> mst(graph.vertices());
            std::unordered_set<typename undirected_simple_graph<V, VP, EP>::vertex_type> visited;
            auto queue = std::priority_queue<ev_pair, std::vector<ev_pair>, cmp>(cmp(graph));

            visited.insert(source);

            for(auto && adjacent_edge : graph.adjacent_edges(source))
            {
                auto neighbour = adjacent_edge.get_neighbour(source);

                if(neighbour != source)
                    queue.push(std::make_pair(adjacent_edge, neighbour));
            }

            while(!queue.empty())
            {
                auto edge = queue.top().first;
                auto vertex = queue.top().second;

                queue.pop();

                auto insert_result = visited.insert(vertex);

                if(insert_result.second)
                {
                    mst.add_edge(edge, graph[edge]);

                    for(auto && adjacent_edge : graph.adjacent_edges(vertex))
                    {
                        auto neighbour = adjacent_edge.get_neighbour(vertex);

                        if(visited.find(neighbour) == visited.end())
                            queue.push(std::make_pair(adjacent_edge, neighbour));
                    }
                }
            }

            return mst;
        }
    }
}

#endif
