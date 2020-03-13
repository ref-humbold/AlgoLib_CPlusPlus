/*!
 * \file searching_strategy.cpp
 * \brief
 */
#include "algolib/graphs/searching_strategy.hpp"

namespace algr = algolib::graphs;

algr::timer_strategy::timer_strategy(const graph & graph) : timer{1}
{
    pre_times.resize(graph.get_vertices_number(), 0);
    post_times.resize(graph.get_vertices_number(), 0);
}

void algr::timer_strategy::preprocess(vertex_t vertex)
{
    pre_times[vertex] = timer;
    ++timer;
}

void algr::timer_strategy::postprocess(vertex_t vertex)
{
    post_times[vertex] = timer;
    ++timer;
}
