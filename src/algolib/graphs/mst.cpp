// ALGORYTMY WYZNACZAJĄCE MINIMALNE DRZEWO SPINAJĄCE
#include "mst.hpp"

namespace str = algolib::structures;

weight_type algolib::graphs::kruskal(const weighted_graph & wgraph)
{
    weight_type size_MST = 0.0;
    int components = wgraph.get_vertices_number();
    std::priority_queue< std::tuple<weight_type, vertex_type, vertex_type> > edge_queue;

    str::disjoint_sets<vertex_type> vertex_sets(wgraph.get_vertices());

    for(const auto & we : wgraph.get_weighted_edges())
        edge_queue.push(std::make_tuple(-std::get<2>(we), std::get<0>(we), std::get<1>(we)));

    while(components > 1 && !edge_queue.empty())
    {
        weight_type edge_weight;
        vertex_type edge_vert1, edge_vert2;

        std::tie(edge_weight, edge_vert1, edge_vert2) = edge_queue.top();
        edge_queue.pop();
        edge_weight = -edge_weight;

        if(vertex_sets.is_set_different(edge_vert1, edge_vert2))
        {
            size_MST += edge_weight;
            --components;
            vertex_sets.union_set(edge_vert1, edge_vert2);
        }
    }

    return size_MST;
}

weight_type algolib::graphs::prim(const weighted_graph & wgraph, vertex_type source)
{
    weight_type size_MST = 0.0;
    std::vector<bool> is_visited(wgraph.get_vertices_number(), false);
    std::priority_queue< std::pair<weight_type, vertex_type> > vertex_queue;

    vertex_queue.push(std::make_pair(0.0, source));

    while(!vertex_queue.empty())
    {
        weight_type edge_weight = -vertex_queue.top().first;
        vertex_type v = vertex_queue.top().second;

        vertex_queue.pop();

        if(!is_visited[v])
        {
            is_visited[v] = true;
            size_MST += edge_weight;

            for(const auto & wnb : wgraph.get_weighted_neighbours(v))
            {
                vertex_type nb;
                weight_type wg;

                std::tie(nb, wg) = wnb;

                if(!is_visited[nb])
                    vertex_queue.push(std::make_pair(-wg, nb));
            }
        }
    }

    return size_MST;
}
