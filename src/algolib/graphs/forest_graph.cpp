// STRUKTURY GRAFÓW DRZEW
#include "forest_graph.hpp"

namespace algr = algolib::graphs;

vertex_t algr::forest_graph::add_vertex()
{
    vertex_t vertex = graph.add_vertex();
    components.make_set(vertex);

    return vertex;
}

void algr::forest_graph::add_edge(vertex_t vertex1, vertex_t vertex2)
{
    if(is_same_tree(vertex1, vertex2))
        throw cycle_exception();

    components.union_set(vertex1, vertex2);
    graph.add_edge(vertex1, vertex2);
}
