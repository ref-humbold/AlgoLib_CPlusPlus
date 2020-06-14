//! WYSZUKIWANIE MOSTÓW I PUNKTÓW ARTYKULACJI W GRAFIE
#include "algolib/old_graphs/algorithms/cutting.hpp"

namespace algr = algolib::graph;

std::vector<edge_t> impl::graph_cutting::edge_cut()
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

std::vector<vertex_t> impl::graph_cutting::vertex_cut()
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

bool impl::graph_cutting::has_bridge(vertex_t vertex)
{
    return low_values[vertex] == dfs_depths[vertex] && !is_dfs_root(vertex);
}

bool impl::graph_cutting::is_separator(vertex_t vertex)
{
    return is_dfs_root(vertex)
                   ? dfs_children[vertex].size() > 1
                   : std::any_of(dfs_children[vertex].begin(), dfs_children[vertex].end(),
                                 [&](vertex_t ch) { return low_values[ch] >= dfs_depths[vertex]; });
}

void impl::graph_cutting::dfs(vertex_t vertex, vertex_t parent, int depth)
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
