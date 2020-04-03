//! ALGORYTMY SORTOWANIA TOPOLOGICZNEGO
#include "algolib/graphs/algorithms/topological_sorting.hpp"

namespace algr = algolib::graphs;

using namespace std::string_literals;

namespace
{
    void dfs(vertex_t vertex, vertex_t index, const algr::directed_graph & digraph,
             std::vector<vertex_t> & order, std::vector<std::pair<vertex_t, bool>> & indices)
    {
        indices[vertex] = std::make_pair(index, true);

        for(const auto & neighbour : digraph.get_neighbours(vertex))
            if(indices[neighbour].first == digraph.get_vertices_number())
                dfs(neighbour, index, digraph, order, indices);
            else if(indices[neighbour] == std::make_pair(index, true))
                throw algr::directed_cyclic_graph_exception(
                        "Cannot perform topological sorting on directed cyclic graph"s);

        order.push_back(vertex);
        indices[vertex].second = false;
    }
}

std::vector<vertex_t> algr::sort_topological1(const directed_graph & digraph)
{
    std::vector<vertex_t> order;
    std::vector<size_t> indegs(digraph.get_vertices_number());
    std::priority_queue<vertex_t, std::vector<vertex_t>, std::greater<vertex_t>> vertex_queue;
    const std::vector<vertex_t> vertices = digraph.get_vertices();

    std::transform(vertices.begin(), vertices.end(), indegs.begin(),
                   [&](vertex_t v) { return digraph.get_indegree(v); });

    for(const auto & v : vertices)
        if(indegs[v] == 0)
            vertex_queue.push(v);

    while(!vertex_queue.empty())
    {
        vertex_t v = vertex_queue.top();

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
        throw algr::directed_cyclic_graph_exception(
                "Cannot perform topological sorting on directed cyclic graph"s);

    return order;
}

std::vector<vertex_t> algr::sort_topological2(const directed_graph & digraph)
{
    std::vector<vertex_t> order;
    std::vector<std::pair<vertex_t, bool>> indices(
            digraph.get_vertices_number(), std::make_pair(digraph.get_vertices_number(), false));
    std::vector<vertex_t> vertices = digraph.get_vertices();

    std::sort(vertices.rbegin(), vertices.rend());

    for(const auto & v : vertices)
        if(indices[v].first == digraph.get_vertices_number())
            dfs(v, v, digraph, order, indices);

    std::reverse(order.begin(), order.end());

    return order;
}
