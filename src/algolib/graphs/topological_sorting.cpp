// ALGORYTMY SORTOWANIA TOPOLOGICZNEGO
#include "topological_sorting.hpp"

namespace details = algolib::detail;

void details::dfs(int vertex, const graph & digraph, std::vector<int> & order,
    std::vector<bool> & is_visited)
{
    is_visited[vertex] = true;

    for( const int & neighbour : digraph.get_neighbours(vertex) )
        if(!is_visited[neighbour])
            dfs(neighbour, digraph, order, is_visited);

    order.push_back(vertex);
}

std::vector<int> algolib::sort_topological1(const graph & digraph)
{
    std::vector<int> order, indegs(digraph.get_vertices_number(), 0);
    std::queue<int> vertex_queue;

    for(const int & v : digraph.get_vertices())
        for( const int & nb : digraph.get_neighbours(v) )
            ++indegs[nb];

    for(const int & v : digraph.get_vertices())
        if(indegs[v] == 0)
            vertex_queue.push(v);

    while(!vertex_queue.empty())
    {
        int v = vertex_queue.front();

        vertex_queue.pop();
        order.push_back(v);
        indegs[v] = -1;

        for( const int & nb : digraph.get_neighbours(v) )
        {
             --indegs[nb];

            if(indegs[nb] == 0)
                vertex_queue.push(nb);
        }
    }

    if(order.size() != digraph.get_vertices_number())
        throw std::runtime_error("graph contains a cycle, so it cannot be sorted topologically.");

    return order;
}

std::vector<int> algolib::sort_topological2(const graph & digraph)
{
    std::vector<int> order;
    std::vector<bool> is_visited(digraph.get_vertices_number(), false);

    for(const int & v : digraph.get_vertices())
        if(!is_visited[v])
            details::dfs(v, digraph, order, is_visited);

    std::reverse(order.begin(), order.end());

    if(order.size() != digraph.get_vertices_number())
        throw std::runtime_error("graph contains a cycle, so it cannot be sorted topologically.");

    return order;
}
