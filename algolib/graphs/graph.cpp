// STRUKTURY GRAFÓW
#include "graph.hpp"

namespace algr = algolib::graphs;

// simple_graph

std::vector<vertex_t> algr::simple_graph::get_vertices() const
{
    std::vector<vertex_t> vertices;

    for(size_t i = 0; i < get_vertices_number(); ++i)
        vertices.push_back(i);

    return vertices;
}

vertex_t algr::simple_graph::add_vertex()
{
    graphrepr.emplace_back();

    return graphrepr.size() - 1;
}

std::vector<vertex_t> algr::simple_graph::get_neighbours(vertex_t v) const
{
    std::vector<vertex_t> neibs(graphrepr[v].size());

    std::transform(graphrepr[v].begin(), graphrepr[v].end(), neibs.begin(),
                   [](wvertex_t wv) { return std::get<0>(wv); });

    return neibs;
}
