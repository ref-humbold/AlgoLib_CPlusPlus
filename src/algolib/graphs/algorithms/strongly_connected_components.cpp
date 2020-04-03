/**!
 * \file scc.hpp
 * \brief ALGORYTM WYZNACZANIA SILNIE SPÓLJNYCH SKŁADOWYCH W GRAFIE SKIEROWANYM
 */
#include "algolib/graphs/algorithms/strongly_connected_components.hpp"

namespace algr = algolib::graphs;

impl::graph_components::graph_components(algr::directed_graph & digr) : digraph{digr}
{
    for(vertex_t v : this->digraph.get_vertices())
    {
        this->components.push_back(-1);
        this->postorder.push_back(std::make_pair(-1, v));
    }
}

std::vector<int> impl::graph_components::find_scc()
{
    int timer = 0, component = 0;

    for(vertex_t v : digraph.get_vertices())
        if(postorder[v].first < 0)
        {
            timer = dfs_order(v, timer);
            ++timer;
        }

    std::sort(postorder.rbegin(), postorder.rend());
    digraph.reverse();

    for(std::pair<int, vertex_t> vt : postorder)
        if(components[vt.second] < 0)
        {
            dfs_scc(vt.second, component);
            ++component;
        }

    return components;
}

int impl::graph_components::dfs_order(vertex_t vertex, int timer)
{
    postorder[vertex].first = 0;
    ++timer;

    for(vertex_t neighbour : digraph.get_neighbours(vertex))
        if(postorder[neighbour].first < 0)
            timer = dfs_order(neighbour, timer);

    postorder[vertex].first = timer;

    return timer + 1;
}

void impl::graph_components::dfs_scc(vertex_t vertex, int component)
{
    components[vertex] = component;

    for(vertex_t neighbour : digraph.get_neighbours(vertex))
        if(components[neighbour] < 0)
            dfs_scc(neighbour, component);
}

std::vector<std::set<vertex_t>> algr::find_scc(directed_graph & digraph)
{
    impl::graph_components gc(digraph);

    std::vector<int> comps = gc.find_scc();
    std::vector<std::set<vertex_t>> components(*std::max_element(comps.begin(), comps.end()) + 1,
                                               std::set<vertex_t>());

    for(vertex_t v : digraph.get_vertices())
        components[comps[v]].insert(v);

    return components;
}
