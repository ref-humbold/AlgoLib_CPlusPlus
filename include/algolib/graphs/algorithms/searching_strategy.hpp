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

            virtual void on_enter(const V & vertex) = 0;

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
            empty_strategy() = default;
            ~empty_strategy() override = default;
            empty_strategy(const empty_strategy &) = default;
            empty_strategy(empty_strategy &&) = default;
            empty_strategy & operator=(const empty_strategy &) = default;
            empty_strategy & operator=(empty_strategy &&) = default;

            void for_root(const V & root) override
            {
            }

            void on_enter(const V & vertex) override
            {
            }

            void on_next_vertex(const V & vertex, const V & neighbour) override
            {
            }

            void on_exit(const V & vertex) override
            {
            }

            void on_edge_to_visited(const V & vertex, const V & neighbour) override
            {
            }
        };
    }
}

#endif
