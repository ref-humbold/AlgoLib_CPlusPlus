//! STRUKTURY GRAFÓW SKIEROWANYCH
#include "refhumbold/algolib/graphs/directed_graph.hpp"

namespace algr = algolib::graphs;

#pragma region directed_simple_graph

algr::directed_simple_graph::directed_simple_graph(const algr::undirected_simple_graph & ugraph)
    : simple_graph(ugraph.get_vertices_number())
{
    for(auto e : ugraph.get_edges())
    {
        add_edge(std::get<0>(e), std::get<1>(e));
        add_edge(std::get<1>(e), std::get<0>(e));
    }
}

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

void algr::directed_simple_graph::add_edge(vertex_t vertex1, vertex_t vertex2)
{
    if(vertex1 >= get_vertices_number())
        throw no_such_vertex_exception(std::to_string(vertex1));

    if(vertex2 >= get_vertices_number())
        throw no_such_vertex_exception(std::to_string(vertex2));

    graphrepr[vertex1].emplace(vertex2, DEFAULT_WEIGHT);
}

size_t algr::directed_simple_graph::get_indegree(vertex_t vertex) const
{
    if(vertex >= get_vertices_number())
        throw no_such_vertex_exception(std::to_string(vertex));

    std::vector<edge_t> edges = get_edges();

    return std::accumulate(edges.begin(), edges.end(), 0, [&](size_t acc, edge_t e) {
        return std::get<1>(e) == vertex ? acc + 1 : acc;
    });
}

void algr::directed_simple_graph::reverse()
{
    std::vector<std::set<wvertex_t>> revgraph(get_vertices_number(), std::set<wvertex_t>());

    for(auto e : get_edges())
        revgraph[std::get<1>(e)].emplace(std::get<0>(e), DEFAULT_WEIGHT);

    graphrepr = std::move(revgraph);
}

#pragma endregion
#pragma region directed_weighted_simple_graph

algr::directed_weighted_simple_graph::directed_weighted_simple_graph(
        const algr::undirected_weighted_simple_graph & uwgraph)
    : directed_simple_graph(uwgraph.get_vertices_number())
{
    for(auto e : uwgraph.get_weighted_edges())
    {
        add_weighted_edge(std::get<0>(e), std::get<1>(e), std::get<2>(e));
        add_weighted_edge(std::get<1>(e), std::get<0>(e), std::get<2>(e));
    }
}

std::vector<wedge_t> algr::directed_weighted_simple_graph::get_weighted_edges() const
{
    std::vector<wedge_t> wedges;

    for(const auto & v : get_vertices())
        for(const auto & u : get_weighted_neighbours(v))
            wedges.emplace_back(v, std::get<0>(u), std::get<1>(u));

    return wedges;
}

void algr::directed_weighted_simple_graph::add_weighted_edge(vertex_t vertex1, vertex_t vertex2,
                                                             weight_t weight)
{
    if(vertex1 >= get_vertices_number())
        throw no_such_vertex_exception(std::to_string(vertex1));

    if(vertex2 >= get_vertices_number())
        throw no_such_vertex_exception(std::to_string(vertex2));

    graphrepr[vertex1].emplace(vertex2, weight);
}

std::vector<wvertex_t>
        algr::directed_weighted_simple_graph::get_weighted_neighbours(vertex_t vertex) const
{
    if(vertex >= get_vertices_number())
        throw no_such_vertex_exception(std::to_string(vertex));

    return std::vector<wvertex_t>(graphrepr[vertex].begin(), graphrepr[vertex].end());
}

void algr::directed_weighted_simple_graph::reverse()
{
    std::vector<std::set<wvertex_t>> revgraph(get_vertices_number(), std::set<wvertex_t>());

    for(auto e : get_weighted_edges())
        revgraph[std::get<1>(e)].emplace(std::get<0>(e), std::get<2>(e));

    graphrepr = std::move(revgraph);
}

#pragma endregion
