// ALGORYTMY PRZESZUKIWANIA GRAFU
#include "searching.hpp"

void detail::dfsR_step(const algolib::graphs::graph & gr, vertex_type vertex,
    std::vector<bool> & is_visited)
{
    is_visited[vertex] = true;

    for(const auto & neighbour : gr.get_neighbours(vertex))
        if(!is_visited[neighbour])
            dfsR_step(gr, neighbour, is_visited);
}

std::vector<bool> algolib::graphs::bfs(const graph & gr, vertex_type root)
{
    std::vector<bool> is_visited(gr.get_vertices_number(), false);
    std::queue<vertex_type> vertex_queue;

    vertex_queue.push(root);
    is_visited[root] = true;

    while(!vertex_queue.empty())
    {
        vertex_type v = vertex_queue.front();

        vertex_queue.pop();

        for(const auto & nb : gr.get_neighbours(v))
            if(!is_visited[nb])
            {
                is_visited[nb] = true;
                vertex_queue.push(nb);
            }
    }

    return is_visited;
}

std::vector<bool> algolib::graphs::dfsI(const graph & gr, vertex_type root)
{
    std::vector<bool> is_visited(gr.get_vertices_number(), false);
    std::stack<vertex_type> vertex_stack;

    vertex_stack.push(root);

    while(!vertex_stack.empty())
    {
        vertex_type v = vertex_stack.top();

        vertex_stack.pop();

        if(!is_visited[v])
        {
            is_visited[v] = true;

            for(const auto & nb : gr.get_neighbours(v))
                if(!is_visited[nb])
                    vertex_stack.push(nb);
        }
    }

    return is_visited;
}

std::vector<bool> algolib::graphs::dfsR(const graph & gr, vertex_type root)
{
    std::vector<bool> is_visited(gr.get_vertices_number(), false);

    detail::dfsR_step(gr, root, is_visited);

    return is_visited;
}
