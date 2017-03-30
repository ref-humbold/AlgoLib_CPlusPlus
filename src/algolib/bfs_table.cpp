// BFS DLA TABLICY
#include <cstdlib>
#include <queue>
#include <algorithm>

#include "bfs_table.hpp"

void table::bfs(std::pair<int, int> source)
{
    std::queue< std::pair<int, int> > cell_queue;

    celltable[source.first][source.second] = 0;
    cell_queue.push(source);

    while(!cell_queue.empty())
    {
        int cellX = cell_queue.front().first;
        int cellY = cell_queue.front().second;

        cell_queue.pop();

        if(cellX > 0 && celltable[cellX-1][cellY] == EMPTY_CELL)
        {
            celltable[cellX-1][cellY] = celltable[cellX][cellY]+1;
            cell_queue.push(std::make_pair(cellX-1, cellY));
        }

        if(cellX < num_rows-1 && celltable[cellX+1][cellY] == EMPTY_CELL)
        {
            celltable[cellX+1][cellY] = celltable[cellX][cellY]+1;
            cell_queue.push(std::make_pair(cellX+1, cellY));
        }

        if(cellY > 0 && celltable[cellX][cellY-1] == EMPTY_CELL)
        {
            celltable[cellX][cellY-1] = celltable[cellX][cellY]+1;
            cell_queue.push(std::make_pair(cellX, cellY-1));
        }

        if(cellY < num_columns-1 && celltable[cellX][cellY+1] == EMPTY_CELL)
        {
            celltable[cellX][cellY+1] = celltable[cellX][cellY]+1;
            cell_queue.push(std::make_pair(cellX, cellY+1));
        }
    }
}

