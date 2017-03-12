// STRUKTURY GRAFÓW
#include <cstdlib>
#include <tuple>
#include <vector>
#include <limits>

#include "graph.hpp"

constexpr double algolib::weighted_graph::INF;

std::vector< std::vector<bool> > algolib::simple_graph::adjacency_matrix() const
{
    std::vector< std::vector<bool> > matrix(get_vertices_number());

    for(unsigned int i = 0; i < matrix.size(); ++i)
        matrix[i].resize(get_vertices_number(), false);

    for(const auto & v : vertices())
        for( const auto & u : neighbours(v) )
            matrix[v][u] = true;

    return matrix;
}

size_t algolib::directed_simple_graph::get_edges_number() const
{
    size_t edges_number = 0;

    for(const auto & v : vertices())
        edges_number += degree_out(v);

    return edges_number;
}

std::vector< std::tuple<int, int> > algolib::directed_simple_graph::edges() const
{
    std::vector< std::tuple<int, int> > edges;

    for(const auto & v : vertices())
        for( const auto & u : neighbours(v) )
            edges.push_back( std::make_tuple(v, u) );

    return edges;
}

size_t algolib::directed_simple_graph::degree_in(int v) const
{
    size_t indeg = 0;

    for(const int & w : vertices())
        for( const int & u : neighbours(w) )
            if(u == v)
                ++indeg;

    return indeg;
}

size_t algolib::undirected_simple_graph::get_edges_number() const
{
    size_t edges_number = 0;

    for(const auto & v : vertices())
        edges_number += degree_out(v);

    return edges_number>>1;
}

std::vector< std::tuple<int, int> > algolib::undirected_simple_graph::edges() const
{
    std::vector< std::tuple<int, int> > edges;

    for(const auto & v : vertices())
        for( const auto & u : neighbours(v) )
            if(u > v)
                edges.push_back( std::make_tuple(v, u) );

    return edges;
}

std::vector<int> algolib::weighted_graph::neighbours(int v) const
{
    std::vector<int> neighbours;

    for(const auto & e : graphrepr[v])
        neighbours.push_back( std::get<0>(e) );

    return neighbours;
}

std::vector< std::vector<double> > algolib::weighted_graph::adjacency_matrix() const
{
    std::vector< std::vector<double> > matrix(get_vertices_number());

    for(unsigned int i = 0; i < matrix.size(); ++i)
    {
        matrix[i].resize(get_vertices_number(), INF);
        matrix[i][i] = 0.0;
    }

    for(const auto & v : vertices())
        for( const auto & e : weighted_neighbours(v) )
            matrix[v][std::get<0>(e)] = std::get<1>(e);

    return matrix;
}

size_t algolib::directed_weighted_graph::get_edges_number() const
{
    size_t edges_number = 0;

    for(const auto & v : vertices())
        edges_number += degree_out(v);

    return edges_number;
}

std::vector< std::tuple<int, int> > algolib::directed_weighted_graph::edges() const
{
    std::vector< std::tuple<int, int> > edges;

    for(const auto & v : vertices())
        for( const auto & u : neighbours(v) )
            edges.push_back( std::make_tuple(v, u) );

    return edges;
}

std::vector< std::tuple<int, int, double> > algolib::directed_weighted_graph::weighted_edges() const
{
    std::vector< std::tuple<int, int, double> > wedges;

    for(const auto & v : vertices())
        for( const auto & u : weighted_neighbours(v) )
            wedges.push_back( std::make_tuple( v, std::get<0>(u), std::get<1>(u) ) );

    return wedges;
}

size_t algolib::directed_weighted_graph::degree_in(int v) const
{
    size_t indeg = 0;

    for(const int & w : vertices())
        for( const int & u : neighbours(w) )
            if(u == v)
                ++indeg;

    return indeg;
}

size_t algolib::undirected_weighted_graph::get_edges_number() const
{
    size_t edges_number = 0;

    for(const auto & v : vertices())
        edges_number += degree_out(v);

    return edges_number>>1;
}

std::vector< std::tuple<int, int> > algolib::undirected_weighted_graph::edges() const
{
    std::vector< std::tuple<int, int> > edges;

    for(const auto & v : vertices())
        for( const auto & u : neighbours(v) )
            if(u > v)
                edges.push_back( std::make_tuple(v, u) );

    return edges;
}

std::vector< std::tuple<int, int, double> > algolib::undirected_weighted_graph::weighted_edges() const
{
    std::vector< std::tuple<int, int, double> > wedges;

    for(const auto & v : vertices())
        for( const auto & u : weighted_neighbours(v) )
            if(std::get<0>(u) > v)
                wedges.push_back( std::make_tuple(v, std::get<0>(u), std::get<1>(u) ) );

    return wedges;
}
