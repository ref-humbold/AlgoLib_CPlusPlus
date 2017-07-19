// STRUKTURY GRAFÓW WIELODZIELNYCH
#include "multipartite_graph.hpp"

namespace algr = algolib::graphs;

std::vector<vertex_t> algr::multipartite_graph::get_vertices(size_t group) const
{
    std::vector<vertex_t> vertices;

    if(group == 0)
        return graph.get_vertices();

    for(const auto & v : graph.get_vertices())
        if(groups[v] == group)
            vertices.push_back(v);

    return vertices;
}

vertex_t algr::multipartite_graph::add_vertex(size_t group)
{
    if(group == 0)
        throw std::logic_error("Cannot add vertex to group 0.");

    groups.push_back(group);

    return graph.add_vertex();
}

std::vector<vertex_t> algr::multipartite_graph::get_neighbours(vertex_t vertex, size_t group) const
{
    std::vector<vertex_t> vertices;

    if(group == 0)
        return graph.get_neighbours(vertex);

    for(const auto & v : graph.get_neighbours(vertex))
        if(groups[v] == group)
            vertices.push_back(v);

    return vertices;
}
