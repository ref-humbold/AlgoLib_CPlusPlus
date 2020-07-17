/*!
 * \file lowest_common_ancestor.hpp
 * \brief Algorithm for lowest common ancestor
 */
#ifndef LOWEST_COMMON_ANCESTOR_HPP_
#define LOWEST_COMMON_ANCESTOR_HPP_

#include <cstdlib>
#include <cmath>
#include <algorithm>
#include <unordered_map>
#include <vector>
#include "algolib/graphs/algorithms/searching.hpp"
#include "algolib/graphs/tree_graph.hpp"

namespace algolib
{
    namespace graphs
    {
#pragma region lowest_common_ancestor

        template <typename V = size_t, typename VP = no_prop, typename EP = no_prop>
        class lowest_common_ancestor
        {
        public:
            using vertex_type = typename tree_graph<V, VP, EP>::vertex_type;

        private:
            struct lca_strategy;

        public:
            lowest_common_ancestor(const tree_graph<V, VP, EP> & graph, const vertex_type & root)
                : graph{graph}, root_{root}, empty{true}
            {
            }

            const vertex_type & root()
            {
                return this->root_;
            }

            /*!
             * \brief Finds a lowest common ancestor of two vertices in a rooted tree.
             * \param vertex1 first vertex
             * \param vertex2 second vertex
             * \return lowest common ancestor of given vertices
             */
            int find(const vertex_type & vertex1, const vertex_type & vertex2)
            {
                if(this->empty)
                    this->initialize();

                return this->do_find(vertex1, vertex2);
            }

            const tree_graph<V, VP, EP> & graph;

        private:
            void initialize();
            int do_find(const vertex_type & vertex1, const vertex_type & vertex2);
            bool is_offspring(const vertex_type & vertex1, const vertex_type & vertex2);

            vertex_type root_;
            bool empty;
            std::unordered_map<vertex_type, std::vector<vertex_type>> paths;
            lca_strategy strategy;
        };

        template <typename V, typename VP, typename EP>
        int lowest_common_ancestor<V, VP, EP>::do_find(
                const lowest_common_ancestor<V, VP, EP>::vertex_type & vertex1,
                const lowest_common_ancestor<V, VP, EP>::vertex_type & vertex2)
        {
            if(this->is_offspring(vertex1, vertex2))
                return vertex2;

            if(this->is_offspring(vertex2, vertex1))
                return vertex1;

            std::vector<vertex_type> candidates = paths[vertex1];

            auto it = std::find_if(candidates.rbegin(), candidates.rend(),
                                   [&](const vertex_type & candidate) {
                                       return !this->is_offspring(vertex2, candidate);
                                   });

            return it != candidates.rend() ? do_find(*it, vertex2)
                                           : do_find(paths[vertex1][0], vertex2);
        }

        template <typename V, typename VP, typename EP>
        void lowest_common_ancestor<V, VP, EP>::initialize()
        {
            dfs_recursive(this->graph, this->strategy, {this->root_});

            for(auto && vertex : this->graph.vertices())
                this->paths.emplace(vertex,
                                    std::vector<vertex_type>({this->strategy.parents[vertex]}));

            for(int i = 0; i < std::log2(this->graph.vertices_count()) + 3; ++i)
                for(auto && vertex : this->graph.vertices())
                    this->paths[vertex].push_back(this->paths[this->paths[vertex][i]][i]);

            this->empty = false;
        }

        template <typename V, typename VP, typename EP>
        bool lowest_common_ancestor<V, VP, EP>::is_offspring(
                const typename lowest_common_ancestor<V, VP, EP>::vertex_type & vertex1,
                const typename lowest_common_ancestor<V, VP, EP>::vertex_type & vertex2)
        {
            return this->strategy.pre_times[vertex1] >= this->strategy.pre_times[vertex2]
                   && this->strategy.post_times[vertex1] <= this->strategy.post_times[vertex2];
        }

#pragma endregion
#pragma region lca_strategy

        template <typename V, typename VP, typename EP>
        struct lowest_common_ancestor<V, VP, EP>::lca_strategy
            : public dfs_strategy<typename lowest_common_ancestor<V, VP, EP>::vertex_type>
        {
            using vertex_type = typename lowest_common_ancestor<V, VP, EP>::vertex_type;

            lca_strategy() : timer{0}
            {
            }

            void for_root(const vertex_type & root) override
            {
                this->parents.emplace(root, root);
            }

            void on_entry(const vertex_type & vertex) override
            {
                this->pre_times.emplace(vertex, this->timer);
                ++this->timer;
            }

            void on_next_vertex(const vertex_type & vertex, const vertex_type & neighbour) override
            {
                this->parents.emplace(neighbour, vertex);
            }

            void on_exit(const vertex_type & vertex) override
            {
                this->post_times.emplace(vertex, this->timer);
                ++this->timer;
            }

            void on_edge_to_visited(const vertex_type &, const vertex_type &) override
            {
            }

            std::unordered_map<vertex_type, vertex_type> parents;
            std::unordered_map<vertex_type, int> pre_times;
            std::unordered_map<vertex_type, int> post_times;
            int timer;
        };

#pragma endregion
    }
}

#endif
