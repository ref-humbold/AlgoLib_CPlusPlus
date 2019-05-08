// ALGORYTM EDMONDSA-KARPA: MAKSYMALNY PRZEPŁYW
#ifndef EDMONDS_HPP_
#define EDMONDS_HPP_

#include <cstdlib>
#include <algorithm>
#include <queue>
#include <vector>

class edmonds_flow_graph
{
private:
    /** oznaczenie nieskończoności */
    static constexpr double INF = 1 << 30;

    /** tablica poprzedników i minimalnych przepustowości ze źródła */
    std::vector<std::pair<int, double>> augmenting_paths;

    /** liczba wierzchołków grafu */
    int num_vertex;

    /** lista sąsiedztwa grafu przepływowego */
    std::vector<std::vector<int>> graphrepr;

    /** macierz przeputowości */
    std::vector<std::vector<double>> capacities;

public:
    /**
    @param n liczba wierzchołków
    */
    explicit edmonds_flow_graph(int n) : num_vertex{n}
    {
        graphrepr.resize(n + 1);
        capacities.resize(n + 1);

        for(size_t i = 0; i < capacities.size(); ++i)
            capacities[i].resize(n + 1, INF);
    }

    /**
    WYLICZANIE CAŁOŚCIOWEGO PRZEPŁYWU W GRAFIE
    @param source źródło
    @param target ujście
    @return maksymalny przepływ sieci
    */
    int count_flow(int source, int target);

private:
    /**
    ALGORYTM BFS ZNAJDUJĄCY ŚCIEŻKĘ POWIĘKSZAJĄCĄ
    @param source źródło
    @param target ujście
    @return czy uda się powiększyć przepływ
    */
    bool bfs(int source, int target);

    /**
    WYLICZANIE PRZEPŁYWU NA ŚCIEŻCE POWIĘKSZAJĄCEJ
    @param source źródło
    @param target ujście
    @return przepływ na ścieżce
    */
    double count_path_flow(int source, int target);
};

#endif
