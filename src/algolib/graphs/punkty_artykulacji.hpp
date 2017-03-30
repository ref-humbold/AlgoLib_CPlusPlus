// WYSZUKIWANIE PUNKTÓW ARTYKULACJI W GRAFIE
#ifndef PUNKTY_ARTYKULACJI_HPP
#define PUNKTY_ARTYKULACJI_HPP

#include <cstdlib>
#include <vector>
#include <algorithm>

class graph
{
private:
    /** onaczenie braku głębokości (nieodwiedzenia) w drzewie DFS */
    static const int NO_DEPTH = -1;

    /** lista synów wierzchołka w drzewie DFS */
    std::vector< std::vector<int> > dfs_childs;

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
    graph(int n) :
        num_vertex{n}
    {
        graphrepr.resize(n+1);
    }

    /**
    WYZNACZANIE PUNKTÓW ARTYKULACJI
    @return lista punktów artykulacji
    */
    std::vector<int> find_vertex_separator();

private:
    /**
    ALGORYTM DFS WYLICZAJĄCY FUNKCJĘ LOW
    @param vertex aktualny wierzchołek
    @param parent ojciec wierzchołka
    */
    void dfs(int vertex, int parent);
};

#endif

