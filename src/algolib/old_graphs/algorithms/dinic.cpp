//! ALGORYTM DINICA: MAKSYMALNY PRZEPŁYW
#include "algolib/old_graphs/algorithms/dinic.hpp"

double dinic_flow_graph::count_flow(int source, int target)
{
    double max_flow = 0.0;
    bool is_flow_added = true;

    while(is_flow_added)
    {
        layer_graph.clear();
        layer_graph.resize(num_vertex + 1);
        is_flow_added = dinic_flow_graph::bfs(source, target);

        if(is_flow_added)
            max_flow += dinic_flow_graph::dfs(source, target, INF);
    }

    return max_flow;
}

bool dinic_flow_graph::bfs(int source, int target)
{
    std::vector<int> vertex_layer(num_vertex + 1, -1);
    std::queue<int> vertex_queue;

    vertex_layer[source] = 0;
    vertex_queue.push(source);

    while(!vertex_queue.empty())
    {
        int v = vertex_queue.front();

        vertex_queue.pop();

        if(v == target)
            return true;

        for(size_t i = 0; i < graphrepr[v].size(); ++i)
        {
            int nb = graphrepr[v][i];

            if(capacities[v][nb] > 0.0)
            {
                if(vertex_layer[nb] == -1)
                {
                    vertex_layer[nb] = vertex_layer[v] + 1;
                    vertex_queue.push(nb);
                }

                if(vertex_layer[nb] == vertex_layer[v] + 1)
                    layer_graph[v].push_back(nb);
            }
        }
    }

    return false;
}

double dinic_flow_graph::dfs(int vertex, int target, double blocking_flow)
{
    if(vertex == target || blocking_flow == 0.0)
        return blocking_flow;

    double new_blocking_flow = 0.0;

    for(size_t i = 0; i < layer_graph[vertex].size() && blocking_flow != 0.0; ++i)
    {
        int neighbour = layer_graph[vertex][i];
        double flow_add =
                dfs(neighbour, target, std::min(capacities[vertex][neighbour], blocking_flow));

        blocking_flow -= flow_add;
        new_blocking_flow += flow_add;
        capacities[vertex][neighbour] -= flow_add;
        capacities[neighbour][vertex] += flow_add;
    }

    return new_blocking_flow;
}
