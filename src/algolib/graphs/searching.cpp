// ALGORYTMY PRZESZUKIWANIA GRAFU
#include "searching.hpp"

namespace details = algolib::detail;

void details::dfsR_step(const graph & gr, int vertex, std::vector<bool> & is_visited)
{
    is_visited[vertex] = true;

    for( const int & neighbour : gr.get_neighbours(vertex) )
        if(!is_visited[neighbour])
            dfsR_step(gr, neighbour, is_visited);
}

std::vector<bool> algolib::bfs(const graph & gr, int root)
{
    std::vector<bool> is_visited(gr.get_vertices_number(), false);
    std::queue<int> vertex_queue;

    vertex_queue.push(root);
    is_visited[root] = true;

    while(!vertex_queue.empty())
    {
        int v = vertex_queue.front();

        vertex_queue.pop();

        for( const int & nb : gr.get_neighbours(v) )
            if(!is_visited[nb])
            {
                is_visited[nb] = true;
                vertex_queue.push(nb);
            }
    }

    return is_visited;
}

std::vector<bool> algolib::dfsI(const graph & gr, int root)
{
    std::vector<bool> is_visited(gr.get_vertices_number(), false);
    std::stack<int> vertex_stack;

    vertex_stack.push(root);

    while(!vertex_stack.empty())
    {
        int v = vertex_stack.top();

        vertex_stack.pop();

        if(!is_visited[v])
        {
            is_visited[v] = true;

            for( const int & nb : gr.get_neighbours(v) )
                if(!is_visited[nb])
                    vertex_stack.push(nb);
        }
    }

    return is_visited;
}

std::vector<bool> algolib::dfsR(const graph & gr, int root)
{
    std::vector<bool> is_visited(gr.get_vertices_number(), false);

    details::dfsR_step(gr, root, is_visited);

    return is_visited;
}
