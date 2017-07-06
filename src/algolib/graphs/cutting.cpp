// WYSZUKIWANIE MOSTÓW I PUNKTÓW ARTYKULACJI W GRAFIE
#include "cutting.hpp"

namespace algr = algolib::graph;

std::vector<edge_t> detail::graph_cutting::bridges()
{
    std::vector<edge_t> bridges;

    for(auto v : graph.get_vertices())
        if(dfs_depths[v] == -1)
            dfs(v, graph.get_vertices_number(), 0);

    for(auto v : graph.get_vertices())
        if(has_bridge(v))
            bridges.emplace_back(std::min(v, dfs_parents[v]), std::max(v, dfs_parents[v]));

    return bridges;
}

std::vector<vertex_t> detail::graph_cutting::separators()
{
    std::vector<vertex_t> separators;

    for(auto v : graph.get_vertices())
        if(dfs_depths[v] == -1)
            dfs(v, graph.get_vertices_number(), 0);

    for(auto v : graph.get_vertices())
        if(is_separator(v))
            separators.push_back(v);

    return separators;
}

void detail::graph_cutting::dfs(vertex_t vertex, vertex_t parent, int depth)
{
    dfs_parents[vertex] = parent;
    dfs_depths[vertex] = depth;
    low_values[vertex] = depth;

    for(auto neighbour : graph.get_neighbours(vertex))
        if(dfs_depths[neighbour] == -1)
        {
            dfs_children[vertex].push_back(neighbour);
            dfs(neighbour, vertex, depth + 1);
            low_values[vertex] = std::min(low_values[vertex], low_values[neighbour]);
        }
        else if(neighbour != parent)
            low_values[vertex] = std::min(low_values[vertex], dfs_depths[neighbour]);
}

std::vector<edge_t> algr::find_bridges(const algolib::graphs::undirected_graph & ugraph)
{
    return detail::graph_cutting(ugraph).bridges();
}

std::vector<vertex_t> algr::find_vertex_separators(const algolib::graphs::undirected_graph & ugraph)
{
    return detail::graph_cutting(ugraph).separators();
}
