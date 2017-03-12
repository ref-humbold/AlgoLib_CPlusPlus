// WYSZUKIWANIE MOSTÓW W GRAFIE
#ifndef MOSTY_HPP
#define MOSTY_HPP

#include <cstdlib>
#include <vector>
#include <algorithm>

class graph
{
    private:
    /** onaczenie braku głębokości (nieodwiedzenia) w drzewie DFS */
    static const int NO_DEPTH = -1;

    /** ojciec wierzchołka w drzewie DFS */
    std::vector<int> dfs_parents;

    /** głębokość wierzchołka w drzewie DFS */
    std::vector<int> dfs_depths;

    /** wartości funkcji LOW dla wierzchołków */
    std::vector<int> low_values;

    /** liczba wierzchołków grafu */
    int num_vertex;

    /** lista sąsiedztwa grafu */
    std::vector< std::vector<int> > graphrepr;

    public:
    /**
    KONSTRUKTOR PARAMETRYCZNY
    @param n liczba wierzchołków
    */
    graph(int n) : num_vertex{n}
    {
        graphrepr.resize(n+1);
    }

    /**
    WYZNACZA MOSTY W GRAFIE
    @return lista krawędzi będących mostami
    */
    std::vector< std::pair<int, int> > find_bridges();

    private:
    /**
    ALGORYTM DFS WYLICZAJĄCY FUNKCJĘ LOW
    @param vertex aktualny wierzchołek
    */
    void dfs(int vertex);
};

#endif

