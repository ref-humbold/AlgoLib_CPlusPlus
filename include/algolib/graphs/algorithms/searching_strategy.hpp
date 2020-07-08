/*!
 * \file searching_strategy.hpp
 * \brief Strategies for graph searching
 */
#ifndef SEARCHING_STRATEGY_HPP_
#define SEARCHING_STRATEGY_HPP_

namespace algolib
{
    namespace graphs
    {
        template <typename V>
        struct bfs_strategy
        {
            virtual ~bfs_strategy() = default;

            virtual void for_root(const V & root) = 0;

            virtual void on_entry(const V & vertex) = 0;

            virtual void on_next_vertex(const V & vertex, const V & neighbour) = 0;

            virtual void on_exit(const V & vertex) = 0;
        };

        template <typename V>
        struct dfs_strategy : public virtual bfs_strategy<V>
        {
            ~dfs_strategy() override = default;

            virtual void on_edge_to_visited(const V & vertex, const V & neighbour) = 0;
        };

        template <typename V>
        struct empty_strategy : public virtual dfs_strategy<V>
        {
            ~empty_strategy() override = default;

            void for_root(const V &) override
            {
            }

            void on_entry(const V &) override
            {
            }

            void on_next_vertex(const V &, const V &) override
            {
            }

            void on_exit(const V &) override
            {
            }

            void on_edge_to_visited(const V &, const V &) override
            {
            }
        };
    }
}

#endif
