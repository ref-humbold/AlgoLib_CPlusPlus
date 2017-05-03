// STRUKTURY GRAFÓW
#include "graph.hpp"

namespace algr = algolib::graphs;

//
// simple_graph
//

std::vector<vertex_type> algr::simple_graph::get_vertices() const
{
    std::vector<vertex_type> vertices;

    for(size_t i = 0; i < get_vertices_number(); ++i)
        vertices.push_back(i);

    return vertices;
}

vertex_type algr::simple_graph::add_vertex()
{
    graphrepr.emplace_back();

    return graphrepr.size() - 1;
}

std::vector<vertex_type> algr::simple_graph::get_neighbours(vertex_type v) const
{
    std::vector<vertex_type> neibs(graphrepr[v].size());

    std::transform(graphrepr[v].begin(), graphrepr[v].end(), neibs.begin(),
                   [](wvertex_type wv){ return std::get<0>(wv); });

    return neibs;
}

//
// directed_graph
//

size_t algr::directed_graph::get_edges_number() const
{
    size_t edges_number = 0;

    for(const auto & v : get_vertices())
        edges_number += get_outdegree(v);

    return edges_number;
}

std::vector<edge_type> algr::directed_graph::get_edges() const
{
    std::vector<edge_type> edges;

    for(const auto & v : get_vertices())
        for(const auto & u : get_neighbours(v))
            edges.emplace_back(v, u);

    return edges;
}

void algr::directed_graph::add_edge(vertex_type v, vertex_type u)
{
    if(v > get_vertices_number() || u > get_vertices_number())
        throw std::invalid_argument("No such vertex.");

    graphrepr[v].emplace(u, DEFAULT_WEIGHT);
}

size_t algr::directed_graph::get_indegree(vertex_type v) const
{
    std::vector<edge_type> edges = get_edges();

    return std::accumulate(edges.begin(), edges.end(), 0,
        [=](size_t total, edge_type e){ return std::get<1>(e) == v ? total + 1 : total; });
}

void algr::directed_graph::reverse()
{
    std::vector<std::set<wvertex_type>> revgraph(get_vertices_number(), std::set<wvertex_type>());

    for(auto e : get_edges())
        revgraph[std::get<1>(e)].emplace(std::get<0>(e), DEFAULT_WEIGHT);

    graphrepr = std::move(revgraph);
}

//
// directed_weighted_graph
//

std::vector<wedge_type> algr::directed_weighted_graph::get_weighted_edges() const
{
    std::vector<wedge_type> wedges;

    for(const auto & v : get_vertices())
        for(const auto & u : get_weighted_neighbours(v))
            wedges.emplace_back(v, std::get<0>(u), std::get<1>(u));

    return wedges;
}

void algr::directed_weighted_graph::add_weighted_edge(vertex_type v, vertex_type u, weight_type wg)
{
    if(v > get_vertices_number() || u > get_vertices_number())
        throw std::invalid_argument("No such vertex.");

    graphrepr[v].emplace(u, wg);
}

void algr::directed_weighted_graph::reverse()
{
    std::vector<std::set<wvertex_type>> revgraph(get_vertices_number(), std::set<wvertex_type>());

    for(auto e : get_weighted_edges())
        revgraph[std::get<1>(e)].emplace(std::get<0>(e), std::get<2>(e));

    graphrepr = std::move(revgraph);
}

//
// undirected_graph
//

size_t algr::undirected_graph::get_edges_number() const
{
    size_t edges_number = 0;

    for(const auto & v : get_vertices())
        edges_number += get_outdegree(v);

    return edges_number >> 1;
}

std::vector<edge_type> algr::undirected_graph::get_edges() const
{
    std::vector<edge_type> edges;

    for(const auto & v : get_vertices())
        for(const auto & u : get_neighbours(v))
            if(u > v)
                edges.emplace_back(v, u);

    return edges;
}

void algr::undirected_graph::add_edge(vertex_type v, vertex_type u)
{
    if(v > get_vertices_number() || u > get_vertices_number())
        throw std::invalid_argument("No such vertex.");

    graphrepr[v].emplace(u, DEFAULT_WEIGHT);
    graphrepr[u].emplace(v, DEFAULT_WEIGHT);
}

algr::undirected_graph::operator directed_graph() const
{
    std::vector<edge_type> diedges = get_edges();

    for(auto e : get_edges())
        diedges.emplace_back(std::get<1>(e), std::get<0>(e), DEFAULT_WEIGHT);

    return directed_graph(get_vertices_number(), diedges);
}

//
// undirected_weighted_graph
//

std::vector<wedge_type> algr::undirected_weighted_graph::get_weighted_edges() const
{
    std::vector<wedge_type> wedges;

    for(const auto & v : get_vertices())
        for(const auto & u : get_weighted_neighbours(v))
            if(std::get<0>(u) > v)
                wedges.emplace_back(v, std::get<0>(u), std::get<1>(u));

    return wedges;
}

void algr::undirected_weighted_graph::add_weighted_edge(vertex_type v, vertex_type u, weight_type wg)
{
    if(v > get_vertices_number() || u > get_vertices_number())
        throw std::invalid_argument("No such vertex.");

    graphrepr[v].emplace(u, wg);
    graphrepr[u].emplace(v, wg);
}

algr::undirected_weighted_graph::operator directed_weighted_graph() const
{
    std::vector<wedge_type> diwedges = get_weighted_edges();

    for(auto e : get_weighted_edges())
        diwedges.emplace_back(std::get<1>(e), std::get<0>(e), std::get<2>(e));

    return directed_weighted_graph(get_vertices_number(), diwedges);
}
