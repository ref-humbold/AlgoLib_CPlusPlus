// ALGORYTM HOPCROFTA-KARPA: SKOJARZENIA W GRAFIE DWUDZIELNYM
#ifndef HOPCROFT_HPP
#define HOPCROFT_HPP

#include <cstdlib>
#include <cmath>
#include <exception>
#include <stdexcept>
#include <queue>
#include <vector>

class graph_partition_exception : public std::logic_error
{
public:
    explicit graph_partition_exception() : std::logic_error("")
    {
    }

    explicit graph_partition_exception(const std::string & what_arg) : std::logic_error(what_arg)
    {
    }

    explicit graph_partition_exception(const char * what_arg) : std::logic_error(what_arg)
    {
    }
};

class bipartite_graph
{
private:
    /** Oznaczenie braku skojarzenia. */
    static const int NO_MATCH = -1;

    /** Oznaczenie nieskończoności. */
    static const int INF = 1 << 30;

    /** Czy wierzchołek w pierwszym zbiorze. */
    std::vector<bool> is_first_set;

    /** Odległości wierzchołków pierwszej podgrupy. */
    std::vector<int> distances;

    /** Liczba wierzchołków grafu. */
    int num_vertex;

    /** Lista odwiedzonych wierzchołków. */
    std::vector<bool> is_visited;

    /** Lista sąsiedztwa grafu dwudzielnego. */
    std::vector<std::vector<int>> graphrepr;

    /** Skojarzenia wierzchołków. */
    std::vector<int> matchings;

public:
    bipartite_graph(int n, const std::vector<int> & first_set) : num_vertex{n}
    {
        graphrepr.resize(n + 1);
        matchings.resize(n + 1, NO_MATCH);
        is_visited.resize(n + 1, false);
        is_first_set.resize(n + 1, false);

        for(const auto & it : first_set)
            is_first_set[it] = true;
    }

    /**
    Wyznaczanie maksymalnego skojarzenia.
    @return rozmiar skojarzenia
    */
    int match();

private:
    /** Algorytm BFS wyliczający numery wierzchołków. */
    void bfs();

    /**
    Wyznaczanie skojarzeń na podstawie ścieżek powiększających.
    @return wartość powiększenia skojarzenia
    */
    int augment_match();

    /**
    Algorytm DFS yznaczający mozliwe ściezki powiększające.
    @param vertex wierzchołek
    @return czy powiększono skojarzenie
    */
    bool dfs(int vertex);
};

#endif
