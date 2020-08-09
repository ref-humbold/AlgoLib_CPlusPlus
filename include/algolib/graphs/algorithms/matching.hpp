/**!
 * \file matching.hpp
 * \brief Hopcroft-Karp algorithm for matching in bipartite graph
 */
#ifndef MATCHING_HPP_
#define MATCHING_HPP_

#include <cstdlib>
#include <queue>
#include <unordered_map>
#include <unordered_set>
#include <vector>
#include <limits>
#include <numeric>
#include "algolib/graphs/multipartite_graph.hpp"

namespace internal
{
    namespace algr = algolib::graphs;

    template <typename V, typename VP, typename EP>
    class match_augmenter
    {
    public:
        using graph_t = algr::multipartite_graph<2, V, VP, EP>;

        explicit match_augmenter(const graph_t & graph) : graph{graph}
        {
        }

        bool augment_match();

        std::unordered_map<typename graph_t::vertex_type, typename graph_t::vertex_type> matching;

    private:
        std::vector<typename graph_t::vertex_type> unmatched_vertices();
        void bfs(std::unordered_map<typename graph_t::vertex_type, double> & distances);
        bool dfs(const typename match_augmenter<V, VP, EP>::graph_t::vertex_type & vertex,
                 std::unordered_set<typename graph_t::vertex_type> & visited,
                 const std::unordered_map<typename graph_t::vertex_type, double> & distances);

        static constexpr double INFINITY = std::numeric_limits<double>::infinity();

        graph_t graph;
    };

    template <typename V, typename VP, typename EP>
    constexpr double match_augmenter<V, VP, EP>::INFINITY;

    template <typename V, typename VP, typename EP>
    bool match_augmenter<V, VP, EP>::augment_match()
    {
        std::unordered_set<typename graph_t::vertex_type> visited;
        std::unordered_map<typename graph_t::vertex_type, double> distances;

        for(auto && vertex : this->graph.vertices())
            distances.emplace(vertex, this->INFINITY);

        this->bfs(distances);

        std::vector<typename graph_t::vertex_type> unmatched = this->unmatched_vertices();

        return std::accumulate(unmatched.begin(), unmatched.end(), false,
                               [&](bool acc, typename graph_t::vertex_type vertex) {
                                   return this->dfs(vertex, visited, distances) || acc;
                               });
    }

    template <typename V, typename VP, typename EP>
    std::vector<typename match_augmenter<V, VP, EP>::graph_t::vertex_type>
            match_augmenter<V, VP, EP>::unmatched_vertices()
    {
        std::vector<typename graph_t::vertex_type> unmatched;
        std::vector<typename graph_t::vertex_type> group = this->graph.vertices_from_group(1);

        std::copy_if(group.begin(), group.end(), std::back_inserter(unmatched),
                     [&](typename graph_t::vertex_type vertex) {
                         return this->matching.find(vertex) == this->matching.end();
                     });

        return unmatched;
    }

    template <typename V, typename VP, typename EP>
    void match_augmenter<V, VP, EP>::bfs(
            std::unordered_map<typename match_augmenter<V, VP, EP>::graph_t::vertex_type, double> &
                    distances)
    {
        std::queue<typename graph_t::vertex_type> vertex_queue;

        for(auto && vertex : this->unmatched_vertices())
        {
            distances.emplace(vertex, 0.0);
            vertex_queue.push(vertex);
        }

        while(!vertex_queue.empty())
        {
            typename graph_t::vertex_type vertex = vertex_queue.front();

            vertex_queue.pop();

            for(auto && neighbour : this->graph.neighbours(vertex))
            {
                auto it = this->matching.find(neighbour);

                if(it != this->matching.end() && distances[it->second] == this->INFINITY)
                {
                    ++distances[vertex];
                    vertex_queue.push(it->second);
                }
            }
        }
    }

    template <typename V, typename VP, typename EP>
    bool match_augmenter<V, VP, EP>::dfs(
            const typename match_augmenter<V, VP, EP>::graph_t::vertex_type & vertex,
            std::unordered_set<typename match_augmenter<V, VP, EP>::graph_t::vertex_type> & visited,
            const std::unordered_map<typename match_augmenter<V, VP, EP>::graph_t::vertex_type,
                                     double> & distances)
    {
        visited.insert(vertex);

        for(auto && neighbour : this->graph.neighbours(vertex))
        {
            auto it = this->matching.find(neighbour);

            if(it == this->matching.end())
            {
                this->matching[vertex] = neighbour;
                this->matching[neighbour] = vertex;
                return true;
            }

            if(visited.find(it->second) == visited.end()
               && distances.at(it->second) == distances.at(vertex) + 1
               && dfs(it->second, visited, distances))
            {
                this->matching[vertex] = neighbour;
                this->matching[neighbour] = vertex;
                return true;
            }
        }

        return false;
    }
}

namespace algolib::graphs
{
    /*!
     * \brief Finds maximal matching in given bipartite graph.
     * \param graph a bipartite graph
     * \return map of matched vertices
     */
    template <typename V = size_t, typename VP = no_prop, typename EP = no_prop>
    std::unordered_map<typename multipartite_graph<2, V, VP, EP>::vertex_type,
                       typename multipartite_graph<2, V, VP, EP>::vertex_type>
            match(const multipartite_graph<2, V, VP, EP> & graph)
    {
        internal::match_augmenter<typename multipartite_graph<2, V, VP, EP>::vertex_type,
                                  typename multipartite_graph<2, V, VP, EP>::vertex_property_type,
                                  typename multipartite_graph<2, V, VP, EP>::edge_property_type>
                augmenter(graph);
        bool was_augmented = true;

        while(was_augmented)
            was_augmented = augmenter.augment_match();

        return augmenter.matching;
    }
}

#endif
