// STRUKTURY GRAFÓW
#include "graph.hpp"

constexpr double algolib::graphs::weighted_graph::INF;

// graph

std::vector<vertex_t> algolib::graphs::graph::get_vertices() const
{
    std::vector<vertex_t> vertices;

    for(size_t i = 0; i < get_vertices_number(); ++i)
        vertices.push_back(i);

    return vertices;
}

// simple_graph

std::vector< std::vector<bool> > algolib::graphs::simple_graph::get_adjacency_matrix() const
{
    std::vector< std::vector<bool> > matrix(get_vertices_number());

    for(unsigned int i = 0; i < matrix.size(); ++i)
        matrix[i].resize(get_vertices_number(), false);

    for(const auto & v : get_vertices())
        for(const auto & u : get_neighbours(v))
            matrix[v][u] = true;

    return matrix;
}

// weighted graph

std::vector<vertex_t> algolib::graphs::weighted_graph::get_neighbours(vertex_t v) const
{
    std::vector<vertex_t> neighbours;

    for(const auto & e : graphrepr[v])
        neighbours.push_back(std::get<0>(e));

    return neighbours;
}

std::vector< std::vector<double> > algolib::graphs::weighted_graph::get_adjacency_matrix() const
{
    std::vector< std::vector<double> > matrix(get_vertices_number());

    for(unsigned int i = 0; i < matrix.size(); ++i)
    {
        matrix[i].resize(get_vertices_number(), INF);
        matrix[i][i] = 0.0;
    }

    for(const auto & v : get_vertices())
        for(const auto & uwg : get_weighted_neighbours(v))
            matrix[v][std::get<0>(uwg)] = std::get<1>(uwg);

    return matrix;
}

// directed_simple_graph

size_t algolib::graphs::directed_simple_graph::get_edges_number() const
{
    size_t edges_number = 0;

    for(const auto & v : get_vertices())
        edges_number += get_outdegree(v);

    return edges_number;
}

std::vector<edge_t> algolib::graphs::directed_simple_graph::get_edges() const
{
    std::vector<edge_t> edges;

    for(const auto & v : get_vertices())
        for(const auto & u : get_neighbours(v))
            edges.push_back(std::make_tuple(v, u));

    return edges;
}

size_t algolib::graphs::directed_simple_graph::get_indegree(vertex_t v) const
{
    size_t indeg = 0;

    for(const int & w : get_vertices())
        for(const int & u : get_neighbours(w))
            if(u == v)
                ++indeg;

    return indeg;
}

// undirected_simple_graph

size_t algolib::graphs::undirected_simple_graph::get_edges_number() const
{
    size_t edges_number = 0;

    for(const auto & v : get_vertices())
        edges_number += get_outdegree(v);

    return edges_number>>1;
}

std::vector<edge_t> algolib::graphs::undirected_simple_graph::get_edges() const
{
    std::vector<edge_t> edges;

    for(const auto & v : get_vertices())
        for(const auto & u : get_neighbours(v))
            if(u > v)
                edges.push_back(std::make_tuple(v, u));

    return edges;
}

// directed_weighted_graph

size_t algolib::graphs::directed_weighted_graph::get_edges_number() const
{
    size_t edges_number = 0;

    for(const auto & v : get_vertices())
        edges_number += get_outdegree(v);

    return edges_number;
}

std::vector<edge_t> algolib::graphs::directed_weighted_graph::get_edges() const
{
    std::vector<edge_t> edges;

    for(const auto & v : get_vertices())
        for(const auto & u : get_neighbours(v))
            edges.push_back(std::make_tuple(v, u));

    return edges;
}

std::vector<wedge_t> algolib::graphs::directed_weighted_graph::get_weighted_edges() const
{
    std::vector<wedge_t> wedges;

    for(const auto & v : get_vertices())
        for(const auto & u : get_weighted_neighbours(v))
            wedges.push_back(std::make_tuple(v, std::get<0>(u), std::get<1>(u)));

    return wedges;
}

size_t algolib::graphs::directed_weighted_graph::get_indegree(vertex_t v) const
{
    size_t indeg = 0;

    for(const int & w : get_vertices())
        for(const int & u : get_neighbours(w))
            if(u == v)
                ++indeg;

    return indeg;
}

// undirected_weighted_graph

size_t algolib::graphs::undirected_weighted_graph::get_edges_number() const
{
    size_t edges_number = 0;

    for(const auto & v : get_vertices())
        edges_number += get_outdegree(v);

    return edges_number>>1;
}

std::vector<edge_t> algolib::graphs::undirected_weighted_graph::get_edges() const
{
    std::vector<edge_t> edges;

    for(const auto & v : get_vertices())
        for(const auto & u : get_neighbours(v))
            if(u > v)
                edges.push_back(std::make_tuple(v, u));

    return edges;
}

std::vector<wedge_t> algolib::graphs::undirected_weighted_graph::get_weighted_edges() const
{
    std::vector<wedge_t> wedges;

    for(const auto & v : get_vertices())
        for(const auto & u : get_weighted_neighbours(v))
            if(std::get<0>(u) > v)
                wedges.push_back(std::make_tuple(v, std::get<0>(u), std::get<1>(u)));

    return wedges;
}
