/*!
 * \file searching_strategy.hpp
 * \brief
 */
#ifndef SEARCHING_STRATEGY_HPP_
#define SEARCHING_STRATEGY_HPP_

#include "algolib/old_graphs/graph.hpp"

namespace algolib
{
    namespace graphs
    {
        struct searching_strategy
        {
            virtual ~searching_strategy() = default;

            virtual void preprocess(vertex_t vertex) = 0;

            virtual void for_neighbour(vertex_t vertex, vertex_t neighbour) = 0;

            virtual void postprocess(vertex_t vertex) = 0;

            virtual void on_cycle(vertex_t vertex, vertex_t neighbour) = 0;
        };

        struct empty_strategy : public virtual searching_strategy
        {
            empty_strategy() = default;
            ~empty_strategy() override = default;
            empty_strategy(const empty_strategy &) = default;
            empty_strategy(empty_strategy &&) = default;
            empty_strategy & operator=(const empty_strategy &) = default;
            empty_strategy & operator=(empty_strategy &&) = default;

            void preprocess(vertex_t) override
            {
            }

            void for_neighbour(vertex_t, vertex_t) override
            {
            }

            void postprocess(vertex_t) override
            {
            }

            void on_cycle(vertex_t, vertex_t) override
            {
            }
        };

        class timer_strategy : public virtual searching_strategy
        {
        public:
            explicit timer_strategy(const graph & graph);

            ~timer_strategy() override = default;
            timer_strategy(const timer_strategy &) = default;
            timer_strategy(timer_strategy &&) = default;
            timer_strategy & operator=(const timer_strategy &) = default;
            timer_strategy & operator=(timer_strategy &&) = default;

            size_t pre_time(vertex_t vertex)
            {
                return pre_times[vertex];
            }

            size_t post_time(vertex_t vertex)
            {
                return post_times[vertex];
            }

            void preprocess(vertex_t vertex) override;

            void for_neighbour(vertex_t, vertex_t) override
            {
            }

            void postprocess(vertex_t vertex) override;

            void on_cycle(vertex_t, vertex_t) override
            {
            }

        private:
            size_t timer;
            std::vector<size_t> pre_times;
            std::vector<size_t> post_times;
        };
    }
}

#endif
