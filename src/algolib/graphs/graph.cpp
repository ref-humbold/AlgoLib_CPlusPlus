//! STRUKTURY GRAFÓW
#include "algolib/graphs/graph.hpp"

namespace algr = algolib::graphs;

//region graph

constexpr weight_t algr::graph::INF;

//endregion
//region simple_graph

constexpr weight_t algr::simple_graph::DEFAULT_WEIGHT;

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

std::vector<vertex_t> algr::simple_graph::get_neighbours(vertex_t vertex) const
{
    if(vertex >= get_vertices_number())
        throw no_such_vertex_exception(std::to_string(vertex));

    std::vector<vertex_t> neibs(graphrepr[vertex].size());

    std::transform(graphrepr[vertex].begin(), graphrepr[vertex].end(), neibs.begin(),
                   [](wvertex_t wv) { return std::get<0>(wv); });

    return neibs;
}

size_t algr::simple_graph::get_outdegree(vertex_t vertex) const
{
    if(vertex >= get_vertices_number())
        throw no_such_vertex_exception(std::to_string(vertex));

    return graphrepr[vertex].size();
}

//endregion
