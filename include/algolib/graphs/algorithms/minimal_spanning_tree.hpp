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
    namespace algr = algolib::graphs;

    template <typename VertexId, typename VertexProperty, typename EdgeProperty>
    struct kruskal_cmp
    {
        using graph_type = algr::undirected_graph<VertexId, VertexProperty, EdgeProperty>;

        explicit kruskal_cmp(const graph_type & graph) : graph{graph}
        {
        }

        bool operator()(const typename graph_type::edge_type & edge1,
                        const typename graph_type::edge_type & edge2) const
        {
            return graph.properties().at(edge2).weight() < graph.properties().at(edge1).weight();
        }

        const graph_type & graph;
    };

    template <typename VertexId, typename VertexProperty, typename EdgeProperty>
    struct prim_cmp
    {
        using graph_type = algr::undirected_graph<VertexId, VertexProperty, EdgeProperty>;
        using argument_type =
                std::pair<typename graph_type::edge_type, typename graph_type::vertex_type>;

        explicit prim_cmp(const graph_type & graph) : graph{graph}
        {
        }

        bool operator()(const argument_type & pair1, const argument_type & pair2) const
        {
            return graph.properties().at(pair2.first).weight()
                   < graph.properties().at(pair1.first).weight();
        }

        const graph_type & graph;
    };
}

namespace algolib::graphs
{
    namespace alst = algolib::structures;

    /*!
     * \brief Kruskal algorithm.
     * \param graph an undirected weighted graph
     * \return the minimal spanning tree
     */
    template <typename VertexId, typename VertexProperty, typename EdgeProperty>
    undirected_simple_graph<VertexId, VertexProperty, EdgeProperty>
            kruskal(const undirected_graph<VertexId, VertexProperty, EdgeProperty> & graph)
    {
        using cmp = internal::kruskal_cmp<
                typename undirected_graph<VertexId, VertexProperty, EdgeProperty>::vertex_id_type,
                typename undirected_graph<VertexId, VertexProperty,
                                          EdgeProperty>::vertex_property_type,
                typename undirected_graph<VertexId, VertexProperty,
                                          EdgeProperty>::edge_property_type>;

        std::vector<typename undirected_graph<VertexId, VertexProperty, EdgeProperty>::vertex_type>
                vertices = graph.vertices();
        alst::disjoint_sets<
                typename undirected_graph<VertexId, VertexProperty, EdgeProperty>::vertex_type>
                vertex_sets(vertices.begin(), vertices.end());
        std::vector<
                typename undirected_graph<VertexId, VertexProperty, EdgeProperty>::vertex_id_type>
                vertex_ids;

        std::transform(vertices.begin(), vertices.end(), std::back_inserter(vertex_ids),
                       [](auto && vertex) { return vertex.id(); });

        undirected_simple_graph<VertexId, VertexProperty, EdgeProperty> mst(vertex_ids);
        auto edge_queue = std::priority_queue<
                typename undirected_graph<VertexId, VertexProperty, EdgeProperty>::edge_type,
                std::vector<typename undirected_graph<VertexId, VertexProperty,
                                                      EdgeProperty>::edge_type>,
                cmp>(cmp(graph));

        for(auto && edge : graph.edges())
            edge_queue.push(edge);

        while(vertex_sets.size() > 1 && !edge_queue.empty())
        {
            auto edge = edge_queue.top();

            edge_queue.pop();

            if(!vertex_sets.is_same_set(edge.source(), edge.destination()))
                mst.add_edge(edge, graph.properties().at(edge));

            vertex_sets.union_set(edge.source(), edge.destination());
        }

        return mst;
    }

    /*!
     * \brief Prim algorithm.
     * \param graph an undirected weighted graph
     * \param source starting vertex
     * \return the minimal spanning tree
     */
    template <typename VertexId, typename VertexProperty, typename EdgeProperty>
    undirected_simple_graph<VertexId, VertexProperty, EdgeProperty> prim(
            const undirected_graph<VertexId, VertexProperty, EdgeProperty> & graph,
            typename undirected_graph<VertexId, VertexProperty, EdgeProperty>::vertex_type source)
    {
        using ev_pair = std::pair<
                typename undirected_graph<VertexId, VertexProperty, EdgeProperty>::edge_type,
                typename undirected_graph<VertexId, VertexProperty, EdgeProperty>::vertex_type>;
        using cmp = internal::prim_cmp<
                typename undirected_graph<VertexId, VertexProperty, EdgeProperty>::vertex_id_type,
                typename undirected_graph<VertexId, VertexProperty,
                                          EdgeProperty>::vertex_property_type,
                typename undirected_graph<VertexId, VertexProperty,
                                          EdgeProperty>::edge_property_type>;

        std::vector<typename undirected_graph<VertexId, VertexProperty, EdgeProperty>::vertex_type>
                vertices = graph.vertices();
        std::vector<
                typename undirected_graph<VertexId, VertexProperty, EdgeProperty>::vertex_id_type>
                vertex_ids;

        std::transform(vertices.begin(), vertices.end(), std::back_inserter(vertex_ids),
                       [](auto && vertex) { return vertex.id(); });

        undirected_simple_graph<VertexId, VertexProperty, EdgeProperty> mst(vertex_ids);
        std::unordered_set<
                typename undirected_graph<VertexId, VertexProperty, EdgeProperty>::vertex_type>
                visited;
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
                mst.add_edge(edge, graph.properties().at(edge));

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

#endif
