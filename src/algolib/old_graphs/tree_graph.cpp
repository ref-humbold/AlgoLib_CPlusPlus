//! STRUKTURY GRAFÓW DRZEW
#include "algolib/old_graphs/tree_graph.hpp"

namespace algr = algolib::graphs;

algr::tree_graph::tree_graph(int n, std::vector<edge_t> edges) : graph{undirected_simple_graph(n)}
{
    std::vector<vertex_t> vertices = graph.get_vertices();
    alst::disjoint_sets<vertex_t> components;

    components.insert(std::make_move_iterator(vertices.begin()),
                      std::make_move_iterator(vertices.end()));

    for(const auto & e : edges)
    {
        if(components.is_same_set(std::get<0>(e), std::get<1>(e)))
            throw cycle_exception("Edge from " + std::to_string(std::get<0>(e)) + " to "
                                  + std::to_string(std::get<1>(e)) + " may create a cycle");

        graph.add_edge(std::get<0>(e), std::get<1>(e));
        components.union_set(std::get<0>(e), std::get<1>(e));
    }

    if(components.size() > 1)
        throw not_connected_exception("Tree is not a connected graph");
}

vertex_t algr::tree_graph::add_vertex(const std::vector<vertex_t> & neighbours)
{
    if(neighbours.size() == 0)
        throw not_connected_exception("New vertex won't be connected with the rest of the tree"s);

    if(neighbours.size() > 1)
        throw cycle_exception("More than one edge from new vertex may create a cycle"s);

    return graph.add_vertex(neighbours);
}

void algr::tree_graph::add_edge(vertex_t vertex1, vertex_t vertex2)
{
    if(vertex1 >= get_vertices_number())
        throw no_such_vertex_exception(std::to_string(vertex1));

    if(vertex2 >= get_vertices_number())
        throw no_such_vertex_exception(std::to_string(vertex2));

    throw cycle_exception("Edge from vertex " + std::to_string(vertex1) + " to vertex "
                          + std::to_string(vertex2) + " will create a cycle.");
}
