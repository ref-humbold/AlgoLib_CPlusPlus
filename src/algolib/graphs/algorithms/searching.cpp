/**!
 * \file searching.cpp
 * \brief Graph searching algorithms.
 */
#include "algolib/graphs/algorithms/searching.hpp"
#include <algorithm>
#include <queue>
#include <stack>
#include <vector>

namespace algr = algolib::graphs;

namespace
{
    struct dfsR_state
    {
        explicit dfsR_state(size_t vertices_number) : iteration{1}
        {
            reached.resize(vertices_number, 0);
        }

        void on_entry(vertex_t v)
        {
            reached[v] = iteration;
        }

        void on_exit(vertex_t v)
        {
            reached[v] = -iteration;
        }

        int iteration;
        std::vector<int> reached;
    };

    void dfsR_step(const algr::graph & gr, algr::searching_strategy & strategy, vertex_t vertex,
                   dfsR_state & state)
    {
        state.on_entry(vertex);
        strategy.preprocess(vertex);

        for(const auto & neighbour : gr.get_neighbours(vertex))
            if(state.reached[neighbour] == 0)
            {
                strategy.for_neighbour(vertex, neighbour);
                dfsR_step(gr, strategy, neighbour, state);
            }
            else
                strategy.on_cycle(vertex, neighbour);

        strategy.postprocess(vertex);
        state.on_exit(vertex);
    }
}

std::vector<bool> algr::bfs(const graph & gr, searching_strategy & strategy,
                            std::initializer_list<vertex_t> roots)
{
    std::vector<bool> visited;
    std::vector<int> reached(gr.get_vertices_number(), 0);
    std::queue<vertex_t> vertex_queue;
    int iteration = 1;

    for(vertex_t root : roots)
        if(reached[root] == 0)
        {
            vertex_queue.push(root);
            reached[root] = iteration;

            while(!vertex_queue.empty())
            {
                vertex_t vertex = vertex_queue.front();

                vertex_queue.pop();
                strategy.preprocess(vertex);

                for(const auto & neighbour : gr.get_neighbours(vertex))
                    if(reached[neighbour] == 0)
                    {
                        strategy.for_neighbour(vertex, neighbour);
                        reached[neighbour] = iteration;
                        vertex_queue.push(neighbour);
                    }
                    else if(reached[neighbour] == iteration)
                        strategy.on_cycle(vertex, neighbour);

                strategy.postprocess(vertex);
                reached[vertex] = -iteration;
            }

            ++iteration;
        }

    std::transform(reached.begin(), reached.end(), std::back_inserter(visited),
                   [](int i) { return i != 0; });

    return visited;
}

std::vector<bool> algr::dfsI(const graph & gr, searching_strategy & strategy,
                             std::initializer_list<vertex_t> roots)
{
    std::vector<bool> visited;
    std::vector<int> reached(gr.get_vertices_number(), 0);
    std::stack<vertex_t> vertex_stack;
    int iteration = 1;

    for(vertex_t root : roots)
        if(reached[root] == 0)
        {
            vertex_stack.push(root);

            while(!vertex_stack.empty())
            {
                vertex_t vertex = vertex_stack.top();

                vertex_stack.pop();

                if(reached[vertex] == 0)
                {
                    reached[vertex] = iteration;
                    strategy.preprocess(vertex);

                    for(const auto & neighbour : gr.get_neighbours(vertex))
                        if(reached[neighbour] == 0)
                        {
                            strategy.for_neighbour(vertex, neighbour);
                            vertex_stack.push(neighbour);
                        }
                        else if(reached[neighbour] == iteration)
                            strategy.on_cycle(vertex, neighbour);
                }

                strategy.postprocess(vertex);
                reached[vertex] = -iteration;
            }

            ++iteration;
        }

    std::transform(reached.begin(), reached.end(), std::back_inserter(visited),
                   [](int i) { return i != 0; });

    return visited;
}

std::vector<bool> algr::dfsR(const graph & gr, searching_strategy & strategy,
                             std::initializer_list<vertex_t> roots)
{
    std::vector<bool> visited;
    dfsR_state state(gr.get_vertices_number());

    for(vertex_t root : roots)
        if(state.reached[root] == 0)
        {
            dfsR_step(gr, strategy, root, state);
            ++state.iteration;
        }

    std::transform(state.reached.begin(), state.reached.end(), std::back_inserter(visited),
                   [](int i) { return i != 0; });

    return visited;
}
