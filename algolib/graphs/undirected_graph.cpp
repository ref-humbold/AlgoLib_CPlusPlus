// STRUKTURY GRAFÓW SKIEROWANYCH
#include "undirected_graph.hpp"

namespace algr = algolib::graphs;

// undirected_simple_graph

size_t algr::undirected_simple_graph::get_edges_number() const
{
    size_t edges_number = 0;

    for(const auto & v : get_vertices())
    {
        edges_number += get_outdegree(v);

        auto neighbours = get_neighbours(v);
        auto pos = std::find(neighbours.begin(), neighbours.end(), v);

        if(pos != neighbours.end())
            ++edges_number;
    }

    return edges_number / 2;
}

std::vector<edge_t> algr::undirected_simple_graph::get_edges() const
{
    std::vector<edge_t> edges;

    for(const auto & v : get_vertices())
        for(const auto & u : get_neighbours(v))
            if(u > v)
                edges.emplace_back(v, u);

    return edges;
}

void algr::undirected_simple_graph::add_edge(vertex_t v, vertex_t u)
{
    if(v >= get_vertices_number() || u >= get_vertices_number())
        throw std::invalid_argument("No such vertex.");

    graphrepr[v].emplace(u, DEFAULT_WEIGHT);
    graphrepr[u].emplace(v, DEFAULT_WEIGHT);
}

algr::directed_simple_graph * algr::undirected_simple_graph::as_directed() const
{
    std::vector<edge_t> diedges = get_edges();

    for(auto e : get_edges())
        diedges.emplace_back(std::get<1>(e), std::get<0>(e));

    return new algr::directed_simple_graph(get_vertices_number(), diedges);
}

// undirected_weighted_simple_graph

std::vector<wedge_t> algr::undirected_weighted_simple_graph::get_weighted_edges() const
{
    std::vector<wedge_t> wedges;

    for(const auto & v : get_vertices())
        for(const auto & u : get_weighted_neighbours(v))
            if(std::get<0>(u) > v)
                wedges.emplace_back(v, std::get<0>(u), std::get<1>(u));

    return wedges;
}

void algr::undirected_weighted_simple_graph::add_weighted_edge(vertex_t v, vertex_t u, weight_t wg)
{
    if(v >= get_vertices_number() || u >= get_vertices_number())
        throw std::invalid_argument("No such vertex.");

    graphrepr[v].emplace(u, wg);
    graphrepr[u].emplace(v, wg);
}

algr::directed_weighted_simple_graph * algr::undirected_weighted_simple_graph::as_directed() const
{
    std::vector<wedge_t> diwedges = get_weighted_edges();

    for(auto e : get_weighted_edges())
        diwedges.emplace_back(std::get<1>(e), std::get<0>(e), std::get<2>(e));

    return new algr::directed_weighted_simple_graph(get_vertices_number(), diwedges);
}
