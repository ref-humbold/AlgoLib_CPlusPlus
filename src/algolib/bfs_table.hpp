// BFS DLA TABLICY
#ifndef BFS_TABLE_HPP
#define BFS_TABLE_HPP

#include <cstdlib>
#include <queue>
#include <algorithm>

class table
{
    private:
    /** oznaczenie pustej komórki */
    static const int EMPTY_CELL = -1;

    /** liczba wierszy */
    int num_rows;

    /** liczba kolumn */
    int num_columns;

    /** tablica */
    std::vector< std::vector<int> > celltable;

    public:
    /**
    KONSTRUKTOR PARAMTERYCZNY
    @param n liczba wierszy
    @param m liczba kolumn
    */
    table(int n, int m) : num_rows{n}, num_columns{m}
    {
        celltable.resize(n);

        for(size_t i = 0; i < celltable.size(); ++i)
            celltable[i].resize(m, EMPTY_CELL);
    }

    /**
    ALGORYTM BFS
    @param source współrzędne początkowej komórki
    */
    void bfs(std::pair<int, int> source);
};

#endif

