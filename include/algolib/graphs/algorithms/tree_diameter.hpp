/*!
 * \file tree_diameter.hpp
 * \brief Algorithm for computing diameter of a tree.
 */
#ifndef TREE_DIAMETER_HPP_
#define TREE_DIAMETER_HPP_

#include <cmath>
#include <cstdlib>
#include <algorithm>
#include <vector>
#include "algolib/graphs/tree_graph.hpp"

namespace internal
{
    namespace algr = algolib::graphs;

    template <typename VertexId, typename VertexProperty, typename EdgeProperty>
    std::pair<double, double> dfs(
            const algr::tree_graph<VertexId, VertexProperty, EdgeProperty> & tree,
            const typename algr::tree_graph<VertexId, VertexProperty, EdgeProperty>::vertex_type &
                    vertex,
            const typename algr::tree_graph<VertexId, VertexProperty, EdgeProperty>::vertex_type &
                    parent)
    {
        double path_from = 0.0, path_subtree = 0.0, path_through = 0.0;

        for(auto && edge : tree.adjacent_edges(vertex))
        {
            typename algr::tree_graph<VertexId, VertexProperty, EdgeProperty>::vertex_type
                    neighbour = edge.get_neighbour(vertex);

            if(neighbour != parent)
            {
                double weight = tree.properties().at(edge).weight();
                std::pair<double, double> result = dfs(tree, neighbour, vertex);

                path_through = std::max(path_through, path_from + result.first + weight);
                path_subtree = std::max(path_subtree, result.second);
                path_from = std::max(path_from, result.first + weight);
            }
        }

        return std::make_pair(path_from, std::max(path_through, path_subtree));
    }
}

namespace algolib::graphs
{
    /*!
     * \brief Computes length of diameter of given tree graph.
     * \param tree the tree graph
     * \return the length of the tree diameter
     */
    template <typename VertexId, typename VertexProperty, typename EdgeProperty>
    double count_diameter(const tree_graph<VertexId, VertexProperty, EdgeProperty> & tree)
    {
        std::vector<typename tree_graph<VertexId, VertexProperty, EdgeProperty>::vertex_type>
                vertices = tree.vertices();
        auto root_it = std::max_element(
                vertices.begin(), vertices.end(),
                [&](auto && v1, auto && v2)
                { return tree.output_degree(v1) < tree.output_degree(v2); });

        return root_it == vertices.end() ? 0.0 : internal::dfs(tree, *root_it, *root_it).second;
    }
}

#endif
