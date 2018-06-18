// STRUKTURY GRAFÓW DRZEW
#include "algolib/graphs/forest_graph.hpp"

namespace algr = algolib::graphs;

vertex_t algr::forest_graph::add_vertex()
{
    vertex_t vertex = graph.add_vertex();
    components.add_elem(vertex);

    return vertex;
}

void algr::forest_graph::add_edge(vertex_t vertex1, vertex_t vertex2)
{
    if(vertex1 >= get_vertices_number())
        throw no_such_vertex_exception(std::to_string(vertex1));

    if(vertex2 >= get_vertices_number())
        throw no_such_vertex_exception(std::to_string(vertex2));

    if(is_same_tree(vertex1, vertex2))
        throw cycle_exception();

    components.union_set(vertex1, vertex2);
    graph.add_edge(vertex1, vertex2);
}

bool algr::forest_graph::is_same_tree(vertex_t vertex1, vertex_t vertex2) const
{
    if(vertex1 >= get_vertices_number())
        throw no_such_vertex_exception(std::to_string(vertex1));

    if(vertex2 >= get_vertices_number())
        throw no_such_vertex_exception(std::to_string(vertex2));

    return components.is_same_set(vertex1, vertex2);
}
