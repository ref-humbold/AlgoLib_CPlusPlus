// NAJNIŻSZY WSPÓLNY PRZODEK DWÓCH WIERZCHOŁKÓW W DRZEWIE
#include "algolib/graphs/lca.hpp"

namespace algr = algolib::graphs;

constexpr int impl::lca_finder::NO_TIME;

int impl::lca_finder::search_lca(int vertex1, int vertex2, int root)
{
    dfs(root, root, 0);

    for(int i = 0; i < log(graph.get_vertices_number()) / log(2) + 3; ++i)
        for(int v : graph.get_vertices())
            if(!paths[v].empty())
                paths[v].push_back(paths[paths[v][i]][i]);

    return search(vertex1, vertex2);
}

int impl::lca_finder::search(int vertex1, int vertex2)
{
    if(is_offspring(vertex1, vertex2))
        return vertex2;

    if(is_offspring(vertex2, vertex1))
        return vertex1;

    std::vector<int> candidates = paths[vertex1];

    std::reverse(candidates.begin(), candidates.end());

    for(int candidate : candidates)
        if(!is_offspring(vertex2, candidate))
            return search(candidate, vertex2);

    return search(paths[vertex1][0], vertex2);
}

int impl::lca_finder::dfs(int vertex, int parent, int timer)
{
    pre_post_times[vertex].first = timer;
    paths[vertex].push_back(parent);
    ++timer;

    for(int neighbour : graph.get_neighbours(vertex))
        if(pre_post_times[neighbour].first == NO_TIME)
            timer = dfs(neighbour, vertex, timer);

    pre_post_times[vertex].second = timer;

    return timer + 1;
}

int algr::find_lca(const forest_graph & treegraph, int vertex1, int vertex2, int root)
{
    if(!treegraph.is_same_tree(vertex1, vertex2))
        throw std::invalid_argument("Vertices are not in the same tree.");

    if(!treegraph.is_same_tree(vertex1, root) || !treegraph.is_same_tree(vertex2, root))
        throw std::invalid_argument("Root vertex does not belong to the tree.");

    impl::lca_finder finder(treegraph);

    return finder.search_lca(vertex1, vertex2, root);
}
