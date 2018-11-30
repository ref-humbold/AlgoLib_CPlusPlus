// ALGORYTM EDMONDSA-KARPA: MAKSYMALNY PRZEP�YW
#include "algolib/graphs/edmonds.hpp"

constexpr double edmonds_flow_graph::INF;

int edmonds_flow_graph::count_flow(int source, int target)
{
    double max_flow = 0.0;
    bool is_flow_added = true;

    while(is_flow_added)
    {
        augmenting_paths.clear();
        augmenting_paths.resize(num_vertex + 1, std::make_pair(-1, INF));
        is_flow_added = edmonds_flow_graph::bfs(source, target);

        if(is_flow_added)
            max_flow += edmonds_flow_graph::count_path_flow(source, target);
    }

    return max_flow;
}

bool edmonds_flow_graph::bfs(int source, int target)
{
    std::queue<int> vertex_queue;

    vertex_queue.push(source);
    augmenting_paths[source] = std::make_pair(0, INF);

    while(!vertex_queue.empty())
    {
        int w = vertex_queue.front();

        vertex_queue.pop();

        if(w == target)
            return true;

        for(size_t i = 0; i < graphrepr[w].size(); ++i)
        {
            int s = graphrepr[w][i];

            if(capacities[w][s] > 0 && augmenting_paths[s].first == -1)
            {
                augmenting_paths[s] =
                    std::make_pair(w, std::min(capacities[w][s], augmenting_paths[w].second));
                vertex_queue.push(s);
            }
        }
    }

    return false;
}

double edmonds_flow_graph::count_path_flow(int source, int target)
{
    for(int w = target; w != source; w = augmenting_paths[w].first)
    {
        int s = augmenting_paths[w].first;

        capacities[s][w] -= augmenting_paths[target].second;
        capacities[w][s] += augmenting_paths[target].second;
    }

    return augmenting_paths[target].second;
}
