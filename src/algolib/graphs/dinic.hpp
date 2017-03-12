// ALGORYTM DINICA: MAKSYMALNY PRZEPŁYW
#ifndef DINIC_HPP
#define DINIC_HPP

#include <cstdlib>
#include <vector>
#include <queue>
#include <algorithm>

class flow_graph
{
    private:
    /**oznaczenie nieskończoności */
    static const double INF = 1<<30;

    /** lista sąsiedztwa grafu warstwowego */
    std::vector< std::vector<int> > layer_graph;

    /** liczba wierzchołków grafu */
    int num_vertex;

    /** lista sąsiedztwa grafu przepływowego */
    std::vector< std::vector<int> > graphrepr;

    /** macierz przeputowości */
    std::vector< std::vector<double> > capacities;

    public:
    /**
    KONSTRUKTOR PARAMETRYCZNY
    @param n liczba wierzchołków
    */
    flow_graph(int n) : num_vertex{n}
    {
        graphrepr.resize(n+1);
        capacities.resize(n+1);

        for(int i = 0; i < capacities.size(); ++i)
            capacities_[i].resize(n+1, INF);
    }

    /**
    WYLICZANIE CAŁOŚCIOWEGO PRZEPŁYWU W GRAFIE
    @param source źródło
    @param target ujście
    @return maksymalny przepływ sieci
    */
    double count_flow(int source, int target);

    private:
    /**
    ALGORYTM BFS TWORZĄCY GRAF WARSTWOWY
    @param source źródło
    @param target ujście
    @return czy uda się powiększyć przepływ
    */
    bool bfs(int source, int target)

    /**
    ALGORYTM DFS NA GRAFIE WARSTWOWYM WYZNACZAJĄCY PRZEPŁYW BLOKUJĄCY DLA ŚCIEŻEK
    @param vertex aktualny wierzchołek
    @param target ujście
    @param blocking_flow stary przepływ blokujący
    @return nowy przepływ blokujący
    */
    double dfs(int vertex, int target, double blocking_flow)
};

#endif

