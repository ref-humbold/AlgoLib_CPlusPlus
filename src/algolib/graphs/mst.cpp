// ALGORYTMY WYZNACZAJĄCE MINIMALNE DRZEWO SPINAJĄCE
#include "mst.hpp"

double algolib::kruskal(const weighted_graph & wgraph)
{
    double size_MST = 0.0;
    int components = wgraph.get_vertices_number();
    std::priority_queue< std::tuple<double, int, int> > edge_queue;

    disjoint_sets<int> * vertex_sets = new disjoint_sets<int>(wgraph.get_vertices());

    for(const auto & we : wgraph.get_weighted_edges())
        edge_queue.push( std::make_tuple( -std::get<2>(we), std::get<0>(we), std::get<1>(we) ) );

    while(components > 1 && !edge_queue.empty())
    {
        double edge_weight;
        int edge_vert1, edge_vert2;

        std::tie(edge_weight, edge_vert1, edge_vert2) = edge_queue.top();
        edge_queue.pop();
        edge_weight = -edge_weight;

        if( vertex_sets->is_set_different(edge_vert1, edge_vert2) )
        {
            size_MST += edge_weight;
            --components;
            vertex_sets->union_set(edge_vert1, edge_vert2);
        }
    }

    return size_MST;
}

double algolib::prim(const weighted_graph & wgraph, int source)
{
    double size_MST = 0.0;
    std::vector<bool> is_visited(wgraph.get_vertices_number(), false);
    std::priority_queue< std::pair<double, int> > vertex_queue;

    vertex_queue.push( std::make_pair(0.0, source) );

    while(!vertex_queue.empty())
    {
        double edge_weight = -vertex_queue.top().first;
        int v = vertex_queue.top().second;

        vertex_queue.pop();

        if(!is_visited[v])
        {
            is_visited[v] = true;
            size_MST += edge_weight;

            for( const auto & wnb : wgraph.get_weighted_neighbours(v) )
            {
                int nb;
                double wg;

                std::tie(nb, wg) = wnb;

                if(!is_visited[nb])
                    vertex_queue.push( std::make_pair(-wg, nb) );
            }
        }
    }

    return size_MST;
}
