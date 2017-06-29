// NAJNIŻSZY WSPÓLNY PRZODEK DWÓCH WIERZCHOŁKÓW W DRZEWIE
#include "lca.hpp"

int tree_graph::find_lca(int vertex1, int vertex2, int root)
{
    paths.resize(num_vertex + 1);
    pre_post_times.resize(num_vertex + 1);
    dfs(root, root, 0);

    for(int i = 1; i <= log2(num_vertex) + 2; ++i)
        for(int v = 1; v <= num_vertex; ++v)
            paths[v].push_back(paths[paths[v][i - 1]][i - 1]);

    return search_lca(vertex1, vertex2);
}

int tree_graph::dfs(int vertex, int parent, int timer)
{
    int pre_time = timer;

    is_visited[vertex] = true;
    paths[vertex].push_back(parent);
    ++timer;

    for(size_t i = 0; i < graphrepr[vertex].size(); ++i)
    {
        int neighbour = graphrepr[vertex][i];

        if(!is_visited[neighbour])
            timer = dfs(neighbour, vertex, timer);
    }

    pre_post_times[vertex] = std::make_pair(pre_time, timer);

    return timer + 1;
}

int tree_graph::search_lca(int vertex1, int vertex2)
{
    auto is_offspring = [&](int vertex1, int vertex2) {
        return pre_post_times[vertex1].first >= pre_post_times[vertex2].first
               && pre_post_times[vertex1].second <= pre_post_times[vertex2].second;
    };

    if(is_offspring(vertex1, vertex2))
        return vertex2;

    if(is_offspring(vertex2, vertex1))
        return vertex1;

    for(int i = paths[vertex1].size() - 1; i > 0; --i)
    {
        int candidate = paths[vertex1][i];

        if(!is_offspring(vertex2, candidate))
            return search_lca(candidate, vertex2);
    }

    return search_lca(paths[vertex1][0], vertex2);
}
