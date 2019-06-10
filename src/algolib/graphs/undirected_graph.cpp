//! STRUKTURY GRAFÓW SKIEROWANYCH
#include "algolib/graphs/undirected_graph.hpp"

namespace algr = algolib::graphs;

#pragma region undirected_simple_graph

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
            if(u >= v)
                edges.emplace_back(v, u);

    return edges;
}

void algr::undirected_simple_graph::add_edge(vertex_t vertex1, vertex_t vertex2)
{
    if(vertex1 >= get_vertices_number())
        throw no_such_vertex_exception(std::to_string(vertex1));

    if(vertex2 >= get_vertices_number())
        throw no_such_vertex_exception(std::to_string(vertex2));

    graphrepr[vertex1].emplace(vertex2, DEFAULT_WEIGHT);
    graphrepr[vertex2].emplace(vertex1, DEFAULT_WEIGHT);
}

size_t algr::undirected_simple_graph::get_indegree(vertex_t vertex) const
{
    if(vertex >= get_vertices_number())
        throw no_such_vertex_exception(std::to_string(vertex));

    return get_outdegree(vertex);
}

#pragma endregion
#pragma region undirected_weighted_simple_graph

std::vector<wedge_t> algr::undirected_weighted_simple_graph::get_weighted_edges() const
{
    std::vector<wedge_t> wedges;

    for(const auto & v : get_vertices())
        for(const auto & u : get_weighted_neighbours(v))
            if(std::get<0>(u) >= v)
                wedges.emplace_back(v, std::get<0>(u), std::get<1>(u));

    return wedges;
}

void algr::undirected_weighted_simple_graph::add_weighted_edge(vertex_t vertex1, vertex_t vertex2,
                                                               weight_t weight)
{
    if(vertex1 >= get_vertices_number())
        throw no_such_vertex_exception(std::to_string(vertex1));

    if(vertex2 >= get_vertices_number())
        throw no_such_vertex_exception(std::to_string(vertex2));

    graphrepr[vertex1].emplace(vertex2, weight);
    graphrepr[vertex2].emplace(vertex1, weight);
}

std::vector<wvertex_t>
        algr::undirected_weighted_simple_graph::get_weighted_neighbours(vertex_t vertex) const
{
    if(vertex >= get_vertices_number())
        throw no_such_vertex_exception(std::to_string(vertex));

    return std::vector<wvertex_t>(graphrepr[vertex].begin(), graphrepr[vertex].end());
}

#pragma endregion
