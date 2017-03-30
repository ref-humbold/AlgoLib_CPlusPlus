// NAJNIŻSZY WSPÓLNY PRZODEK DWÓCH WIERZCHOŁKÓW W DRZEWIE
#ifndef LCA_HPP
#define LCA_HPP

#include <cstdlib>
#include <cmath>
#include <vector>
#include <algorithm>

class tree_graph
{
private:
    /** skompresowane ścieżki do korzenia drzewa */
    std::vector< std::vector<int> > paths;

    /** tablica czasów wejścia i wyjścia dla wierzchołka */
    std::vector< std::pair<int, int> > pre_post_times;

    /** liczba wierzchołków grafu */
    int num_vertex;

    /** czy wierzchołek odwiedzony */
    std::vector<bool> is_visited;

    /** lista sąsiedztwa grafu */
    std::vector< std::vector<int> > graphrepr;

public:
    /**
    KONSTRUKTOR PARAMETRYCZNY
    @param n liczba wierzchołków
    */
    tree_graph(int n) :
        num_vertex{n}
    {
        is_visited.resize(n+1, false);
        graphrepr.resize(n+1);
    }

    /**
    ZNAJDUJE NAJNIŻSZEGO WSPÓLNEGO PRZODKA
    @param vertex1 wierzchołek 1
    @param vertex2 wierzchołek 2
    @param root korzeń drzewa
    @return najniższy wspólny przodek
    */
    int find_lca(int vertex1, int vertex2, int root = 1);

private:
    /**
    ALGORYTM DFS Z LICZNIKIEM CZASU WYZNACZAJĄCY KOLEJNE WIERZCHOŁKI NA ŚCIEŻCE DO KORZENIA
    @param vertex aktualny wierzchołek
    @param parent ojciec wierzchołka
    @param timer aktualny czasu
    @return nowy czas po przetworzeniu wierzchołka
    */
    int dfs(int vertex, int parent, int timer);

    /**
    WYSZUKUJE NAJNIŻSZEGO WSPÓLNEGO PRZODKA
    @param vertex1 wierzchołek 1
    @param vertex2 wierzchołek 2
    @return najniższy wspólny przodek
    */
    int search_lca(int vertex1, int vertex2);
};

#endif

