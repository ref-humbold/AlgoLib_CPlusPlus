// ALGORYTMY SORTOWANIA TOPOLOGICZNEGO
#include "topological_sorting.hpp"

void detail::dfs(vertex_type vertex, const algolib::graphs::directed_graph & digraph,
    std::vector<vertex_type> & order, std::vector<bool> & is_visited)
{
    is_visited[vertex] = true;

    for(const auto & neighbour : digraph.get_neighbours(vertex))
        if(!is_visited[neighbour])
            dfs(neighbour, digraph, order, is_visited);

    order.push_back(vertex);
}

std::vector<vertex_type> algolib::graphs::sort_topological1(const directed_graph & digraph)
{
    std::vector<vertex_type> order, indegs(digraph.get_vertices_number(), 0);
    std::queue<vertex_type> vertex_queue;

    for(const auto & e : digraph.get_edges())
        ++indegs[std::get<1>(e)];

    for(const auto & v : digraph.get_vertices())
        if(indegs[v] == 0)
            vertex_queue.push(v);

    while(!vertex_queue.empty())
    {
        vertex_type v = vertex_queue.front();

        vertex_queue.pop();
        order.push_back(v);
        indegs[v] = -1;

        for(const auto & nb : digraph.get_neighbours(v))
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

std::vector<vertex_type> algolib::graphs::sort_topological2(const directed_graph & digraph)
{
    std::vector<vertex_type> order;
    std::vector<bool> is_visited(digraph.get_vertices_number(), false);

    for(const auto & v : digraph.get_vertices())
        if(!is_visited[v])
            detail::dfs(v, digraph, order, is_visited);

    std::reverse(order.begin(), order.end());

    if(order.size() != digraph.get_vertices_number())
        throw std::runtime_error("graph contains a cycle, so it cannot be sorted topologically.");

    return order;
}
