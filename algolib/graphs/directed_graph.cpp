// STRUKTURY GRAFÓW SKIEROWANYCH
#include "directed_graph.hpp"

namespace algr = algolib::graphs;

// directed_simple_graph

size_t algr::directed_simple_graph::get_edges_number() const
{
    size_t edges_number = 0;

    for(const auto & v : get_vertices())
        edges_number += get_outdegree(v);

    return edges_number;
}

std::vector<edge_t> algr::directed_simple_graph::get_edges() const
{
    std::vector<edge_t> edges;

    for(const auto & v : get_vertices())
        for(const auto & u : get_neighbours(v))
            edges.emplace_back(v, u);

    return edges;
}

void algr::directed_simple_graph::add_edge(vertex_t v, vertex_t u)
{
    if(v > get_vertices_number() || u > get_vertices_number())
        throw std::invalid_argument("No such vertex.");

    graphrepr[v].emplace(u, DEFAULT_WEIGHT);
}

size_t algr::directed_simple_graph::get_indegree(vertex_t v) const
{
    std::vector<edge_t> edges = get_edges();

    return std::accumulate(edges.begin(), edges.end(), 0, [&](size_t acc, edge_t e) {
        return std::get<1>(e) == v ? acc + 1 : acc;
    });
}

void algr::directed_simple_graph::reverse()
{
    std::vector<std::set<wvertex_t>> revgraph(get_vertices_number(), std::set<wvertex_t>());

    for(auto e : get_edges())
        revgraph[std::get<1>(e)].emplace(std::get<0>(e), DEFAULT_WEIGHT);

    graphrepr = std::move(revgraph);
}

// directed_weighted_simple_graph

std::vector<wedge_t> algr::directed_weighted_simple_graph::get_weighted_edges() const
{
    std::vector<wedge_t> wedges;

    for(const auto & v : get_vertices())
        for(const auto & u : get_weighted_neighbours(v))
            wedges.emplace_back(v, std::get<0>(u), std::get<1>(u));

    return wedges;
}

void algr::directed_weighted_simple_graph::add_weighted_edge(vertex_t v, vertex_t u,
                                                             weight_t wg)
{
    if(v > get_vertices_number() || u > get_vertices_number())
        throw std::invalid_argument("No such vertex.");

    graphrepr[v].emplace(u, wg);
}

void algr::directed_weighted_simple_graph::reverse()
{
    std::vector<std::set<wvertex_t>> revgraph(get_vertices_number(), std::set<wvertex_t>());

    for(auto e : get_weighted_edges())
        revgraph[std::get<1>(e)].emplace(std::get<0>(e), std::get<2>(e));

    graphrepr = std::move(revgraph);
}
