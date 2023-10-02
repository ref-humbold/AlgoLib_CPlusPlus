/*!
 * \file searching_strategy.hpp
 * \brief Strategies for algorithms for graph searching.
 */
#ifndef SEARCHING_STRATEGY_HPP_
#define SEARCHING_STRATEGY_HPP_

namespace algolib::graphs
{
    template <typename Vertex>
    struct bfs_strategy
    {
        virtual ~bfs_strategy() = default;

        virtual void for_root(const Vertex & root) = 0;

        virtual void on_entry(const Vertex & vertex) = 0;

        virtual void on_next_vertex(const Vertex & vertex, const Vertex & neighbour) = 0;

        virtual void on_exit(const Vertex & vertex) = 0;
    };

    template <typename Vertex>
    struct dfs_strategy : public virtual bfs_strategy<Vertex>
    {
        ~dfs_strategy() override = default;

        virtual void on_edge_to_visited(const Vertex & vertex, const Vertex & neighbour) = 0;
    };

    template <typename Vertex>
    struct empty_strategy : public virtual dfs_strategy<Vertex>
    {
        void for_root(const Vertex &) override
        {
        }

        void on_entry(const Vertex &) override
        {
        }

        void on_next_vertex(const Vertex &, const Vertex &) override
        {
        }

        void on_exit(const Vertex &) override
        {
        }

        void on_edge_to_visited(const Vertex &, const Vertex &) override
        {
        }
    };
}

#endif
