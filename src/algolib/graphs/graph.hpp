// STRUKTURY GRAFÓW
#ifndef GRAPH_HPP
#define GRAPH_HPP

#include <cstdlib>
#include <tuple>
#include <vector>
#include <limits>
#include <algorithm>

namespace algolib
{
    class graph
    {
        public:
        graph()
        {
        }

        /**
        Getter dla liczby wierzchołków.
        @return liczba wierzchołków
        */
        virtual size_t get_vertices_number() const = 0;

        /**
        Getter dla liczby krawędzi.
        @return liczba krawędzi
        */
        virtual size_t get_edges_number() const = 0;

        /**
        Wszystkie wierzchołki.
        @return wektor wierzchołków
        */
        virtual std::vector<int> get_vertices() const
        {
            std::vector<int> vertices;

            for(size_t i = 0; i < get_vertices_number(); ++i)
                vertices.push_back(i);

            return vertices;
        }

        /**
        Wszystkie krawędzie.
        @return wektor krawędzi
        */
        virtual std::vector< std::tuple<int, int> > get_edges() const = 0;

        /**
        Sąsiedzi wierzchołka.
        @param v numer wierzchołka
        @return wektor sąsiadów wierzchołka
        */
        virtual std::vector<int> get_neighbours(int v) const = 0;

        /**
        Stopień wyjściowy wierzchołka.
        @param v numer wierzchołka
        @return wartość stopnia wyjściowego wierzchołka
        */
        virtual size_t get_outdegree(int v) const = 0;

        /**
        Stopień wejściowy wierzchołka.
        @param v numer wierzchołka
        @return wartość stopnia wejściowego wierzchołka
        */
        virtual size_t get_indegree(int v) const = 0;
    };

    class simple_graph : public graph
    {
        protected:
        /** Lista sąsiedztwa grafu. */
        std::vector< std::vector<int> > graphrepr;

        public:
        simple_graph(int n) : graph()
        {
            graphrepr.resize(n);
        }

        /** @see graph#get_vertices_number */
        size_t get_vertices_number() const override
        {
            return graphrepr.size();
        }

        /** @see graph#neighbours */
        std::vector<int> get_neighbours(int v) const override
        {
            return graphrepr[v];
        }

        /** @see graph#get_outdegree */
        size_t get_outdegree(int v) const override
        {
            return graphrepr[v].size();
        }

        /**
        Wyznaczanie listy sąsiedztwa grafu.
        @return lista sąsiedztwa
        */
        std::vector< std::vector<int> > get_adjacency_list() const
        {
            return graphrepr;
        }

        /**
        Wyznaczanie macierzy sąsiedztwa grafu.
        @return macierz sąsiedztwa
        */
        std::vector< std::vector<bool> > get_adjacency_matrix() const;
    };

    class directed_simple_graph : public simple_graph
    {
        public:
        directed_simple_graph(int n) : simple_graph(n)
        {
        }

        directed_simple_graph(int n, std::vector< std::tuple<int, int> > edges) : simple_graph(n)
        {
            for(const auto & e : edges)
                graphrepr[std::get<0>(e)].push_back( std::get<1>(e) );
        }

        directed_simple_graph(int n, std::vector< std::pair<int, int> > edges) : simple_graph(n)
        {
            for(const auto & e : edges)
                graphrepr[e.first].push_back(e.second);
        }

        /** @see graph#get_edges_number */
        size_t get_edges_number() const override;

        /** @see graph#edges */
        std::vector< std::tuple<int, int> > get_edges() const override;

        /** @see graph#get_indegree */
        size_t get_indegree(int v) const override;
    };

    class undirected_simple_graph : public simple_graph
    {
        public:
        undirected_simple_graph(int n) : simple_graph(n)
        {
        }

        undirected_simple_graph(int n, std::vector< std::tuple<int, int> > edges) :
            simple_graph(n)
        {
            for(const auto & e : edges)
            {
                graphrepr[std::get<0>(e)].push_back( std::get<1>(e) );
                graphrepr[std::get<1>(e)].push_back( std::get<0>(e) );
            }
        }

        undirected_simple_graph(int n, std::vector< std::pair<int, int> > edges) :
            simple_graph(n)
        {
            for(const auto & e : edges)
            {
                graphrepr[e.first].push_back(e.second);
                graphrepr[e.second].push_back(e.first);
            }
        }

        /** @see graph#get_edges_number */
        size_t get_edges_number() const override;

        /** @see graph#edges */
        std::vector< std::tuple<int, int> > get_edges() const override;

        /** @see graph#get_indegree */
        size_t get_indegree(int v) const override
        {
            return get_outdegree(v);
        }
    };

    class weighted_graph : public graph
    {
        protected:
        /** Oznaczenie nieskończoności */
        static constexpr double INF = std::numeric_limits<double>::infinity();

        /** Lista sąsiedztwa grafu ważonego. */
        std::vector< std::vector< std::tuple<int, double> > > graphrepr;

        public:
        weighted_graph(int n) : graph()
        {
            graphrepr.resize(n);
        }

        /** @see graph#get_vertices_number */
        size_t get_vertices_number() const override
        {
            return graphrepr.size();
        }

        /**
        Wszystkie krawędzie wraz z wagami.
        @return lista krawędzi z ich wagami
        */
        virtual std::vector< std::tuple<int, int, double> > get_weighted_edges() const = 0;

        /** @see graph#neighbours */
        std::vector<int> get_neighbours(int v) const override;

        /**
        Sąsiedzi wierzchołka wraz z wagami.
        @param v numer wierzchołka
        @return lista sąsiadów wierzchołka wraz z wagami krawędzi
        */
        std::vector< std::tuple<int, double> > get_weighted_neighbours(int v) const
        {
            return graphrepr[v];
        }

        /** @see graph#get_outdegree */
        size_t get_outdegree(int v) const override
        {
            return graphrepr[v].size();
        }

        /**
        Wyznaczanie listy sąsiedztwa grafu.
        @return lista sąsiedztwa
        */
        std::vector< std::vector< std::tuple<int, double> > > get_adjacency_list() const
        {
            return graphrepr;
        }

        /**
        Wyznaczanie macierzy sąsiedztwa grafu.
        @return macierz sąsiedztwa
        */
        std::vector< std::vector<double> > get_adjacency_matrix() const;
    };

    class directed_weighted_graph : public weighted_graph
    {
        public:
        directed_weighted_graph(int n) : weighted_graph(n)
        {
        }

        directed_weighted_graph(int n, std::vector< std::tuple<int, int, double> > edges) :
            weighted_graph(n)
        {
            for(const auto & e : edges)
                graphrepr[std::get<0>(e)].push_back(
                    std::make_tuple( std::get<1>(e), std::get<2>(e) ) );
        }

        /** @see graph#get_edges_number */
        size_t get_edges_number() const override;

        /** @see graph#get_outdegree */
        size_t get_outdegree(int v) const override
        {
            return graphrepr[v].size();
        }

        /** @see graph#get_indegree */
        size_t get_indegree(int v) const override;

        /** @see graph#edges */
        std::vector< std::tuple<int, int> > get_edges() const override;

        /** @see weighted_graph#weighted_edges */
        std::vector< std::tuple<int, int, double> > get_weighted_edges() const override;
    };

    class undirected_weighted_graph : public weighted_graph
    {
        public:
        undirected_weighted_graph(int n) : weighted_graph(n)
        {
        }

        undirected_weighted_graph(int n, std::vector< std::tuple<int, int, double> > edges) :
            weighted_graph(n)
        {
            for(const auto & e : edges)
            {
                graphrepr[std::get<0>(e)].push_back(
                    std::make_tuple( std::get<1>(e), std::get<2>(e) ) );
                graphrepr[std::get<1>(e)].push_back(
                    std::make_tuple( std::get<0>(e), std::get<2>(e) ) );
            }
        }

        /** @see graph#get_edges_number */
        size_t get_edges_number() const override;

        /** @see graph#get_indegree */
        size_t get_indegree(int v) const override
        {
            return get_outdegree(v);
        }

        /** @see graph#edges */
        std::vector< std::tuple<int, int> > get_edges() const override;

        /** @see weighted_graph#weighted_edges */
        std::vector< std::tuple<int, int, double> > get_weighted_edges() const override;
    };
}

#endif
