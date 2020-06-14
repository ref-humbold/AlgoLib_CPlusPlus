//! ALGORYTMY WYZNACZAJĄCE MINIMALNE DRZEWO SPINAJĄCE
#include "algolib/old_graphs/algorithms/minimal_spanning_tree.hpp"

namespace algr = algolib::graphs;
namespace alst = algolib::structures;

weight_t algr::kruskal(const undirected_weighted_simple_graph & uwgraph)
{
    weight_t size_MST = 0.0;
    std::vector<vertex_t> vertices = uwgraph.get_vertices();
    std::priority_queue<std::tuple<weight_t, vertex_t, vertex_t>> edge_queue;
    alst::disjoint_sets<vertex_t> vertex_sets(std::make_move_iterator(vertices.begin()),
                                              std::make_move_iterator(vertices.end()));

    for(const auto & we : uwgraph.get_weighted_edges())
        edge_queue.push(std::make_tuple(-std::get<2>(we), std::get<0>(we), std::get<1>(we)));

    while(vertex_sets.size() > 1 && !edge_queue.empty())
    {
        weight_t edge_weight;
        vertex_t edge_vert1, edge_vert2;

        std::tie(edge_weight, edge_vert1, edge_vert2) = edge_queue.top();
        edge_queue.pop();

        if(!vertex_sets.is_same_set(edge_vert1, edge_vert2))
        {
            size_MST -= edge_weight;
            vertex_sets.union_set(edge_vert1, edge_vert2);
        }
    }

    return size_MST;
}

weight_t algr::prim(const undirected_weighted_simple_graph & uwgraph, vertex_t source)
{
    weight_t size_MST = 0.0;
    std::vector<bool> is_visited(uwgraph.get_vertices_number(), false);
    std::priority_queue<std::pair<weight_t, vertex_t>> vertex_queue;

    vertex_queue.push(std::make_pair(0.0, source));

    while(!vertex_queue.empty())
    {
        weight_t edge_weight = -vertex_queue.top().first;
        vertex_t v = vertex_queue.top().second;

        vertex_queue.pop();

        if(!is_visited[v])
        {
            is_visited[v] = true;
            size_MST += edge_weight;

            for(const auto & wnb : uwgraph.get_weighted_neighbours(v))
            {
                vertex_t nb;
                weight_t wg;

                std::tie(nb, wg) = wnb;

                if(!is_visited[nb])
                    vertex_queue.push(std::make_pair(-wg, nb));
            }
        }
    }

    return size_MST;
}
