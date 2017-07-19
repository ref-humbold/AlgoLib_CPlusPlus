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

void algr::multipartite_graph::add_edge(vertex_t vertex1, vertex_t vertex2)
{
    if(vertex1 >= get_vertices_number())
        throw no_such_vertex_exception(std::to_string(vertex1));

    if(vertex2 >= get_vertices_number())
        throw no_such_vertex_exception(std::to_string(vertex2));

    if(is_same_group(vertex1, vertex2))
        throw graph_partition_exception();

    graph.add_edge(vertex1, vertex2);
}

std::vector<vertex_t> algr::multipartite_graph::get_neighbours(vertex_t vertex, size_t group) const
{
    std::vector<vertex_t> vertices;

    if(vertex >= get_vertices_number())
        throw no_such_vertex_exception(std::to_string(vertex));

    if(group == 0)
        return graph.get_neighbours(vertex);

    for(const auto & v : graph.get_neighbours(vertex))
        if(groups[v] == group)
            vertices.push_back(v);

    return vertices;
}

bool algr::multipartite_graph::is_in_group(vertex_t vertex, size_t group) const
{
    if(vertex >= get_vertices_number())
        throw no_such_vertex_exception(std::to_string(vertex));

    return groups[vertex] == group;
}

bool algr::multipartite_graph::is_same_group(vertex_t vertex1, vertex_t vertex2) const
{
    if(vertex1 >= get_vertices_number())
        throw no_such_vertex_exception(std::to_string(vertex1));

    if(vertex2 >= get_vertices_number())
        throw no_such_vertex_exception(std::to_string(vertex2));

    return groups[vertex1] == groups[vertex2];
}
