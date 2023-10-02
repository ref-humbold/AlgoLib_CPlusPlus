/**!
 * \file matching.hpp
 * \brief Hopcroft-Karp algorithm for matching in a bipartite graph.
 */
#ifndef MATCHING_HPP_
#define MATCHING_HPP_

#include <cstdlib>
#include <limits>
#include <numeric>
#include <optional>
#include <queue>
#include <unordered_map>
#include <unordered_set>
#include <vector>
#include "algolib/graphs/multipartite_graph.hpp"

namespace internal
{
    namespace algr = algolib::graphs;

    template <typename VertexId, typename VertexProperty, typename EdgeProperty>
    class match_augmenter
    {
    public:
        using graph_t = algr::multipartite_graph<2, VertexId, VertexProperty, EdgeProperty>;

        explicit match_augmenter(const graph_t & graph) : graph{graph}
        {
        }

        bool augment_match();

        std::unordered_map<
                typename graph_t::vertex_type,
                std::optional<typename graph_t::vertex_type>>
                matching;

    private:
        std::vector<typename graph_t::vertex_type> unmatched_vertices();
        void bfs(std::unordered_map<typename graph_t::vertex_type, double> & distances);
        bool
                dfs(const typename match_augmenter<VertexId, VertexProperty, EdgeProperty>::
                            graph_t::vertex_type & vertex,
                    std::unordered_set<typename graph_t::vertex_type> & visited,
                    const std::unordered_map<typename graph_t::vertex_type, double> & distances);

        static constexpr double infinity = std::numeric_limits<double>::infinity();

        graph_t graph;
    };

    template <typename VertexId, typename VertexProperty, typename EdgeProperty>
    constexpr double match_augmenter<VertexId, VertexProperty, EdgeProperty>::infinity;

    template <typename VertexId, typename VertexProperty, typename EdgeProperty>
    bool match_augmenter<VertexId, VertexProperty, EdgeProperty>::augment_match()
    {
        std::unordered_set<typename graph_t::vertex_type> visited;
        std::unordered_map<typename graph_t::vertex_type, double> distances;

        for(auto && vertex : this->graph.vertices())
            distances.emplace(vertex, this->infinity);

        this->bfs(distances);
        std::vector<typename graph_t::vertex_type> unmatched = this->unmatched_vertices();
        return std::accumulate(
                unmatched.begin(), unmatched.end(), false,
                [&](bool acc, typename graph_t::vertex_type vertex)
                { return this->dfs(vertex, visited, distances) || acc; });
    }

    template <typename VertexId, typename VertexProperty, typename EdgeProperty>
    std::vector<
            typename match_augmenter<VertexId, VertexProperty, EdgeProperty>::graph_t::vertex_type>
            match_augmenter<VertexId, VertexProperty, EdgeProperty>::unmatched_vertices()
    {
        std::vector<typename graph_t::vertex_type> unmatched;
        std::vector<typename graph_t::vertex_type> group = this->graph.vertices_from_group(1);

        std::copy_if(
                group.begin(), group.end(), std::back_inserter(unmatched),
                [&](typename graph_t::vertex_type vertex)
                { return this->matching.find(vertex) == this->matching.end(); });
        return unmatched;
    }

    template <typename VertexId, typename VertexProperty, typename EdgeProperty>
    void match_augmenter<VertexId, VertexProperty, EdgeProperty>::bfs(
            std::unordered_map<
                    typename match_augmenter<VertexId, VertexProperty, EdgeProperty>::graph_t::
                            vertex_type,
                    double> & distances)
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

                if(it != this->matching.end() && distances[it->second.value()] == this->infinity)
                {
                    ++distances[vertex];
                    vertex_queue.push(*it->second);
                }
            }
        }
    }

    template <typename VertexId, typename VertexProperty, typename EdgeProperty>
    bool match_augmenter<VertexId, VertexProperty, EdgeProperty>::dfs(
            const typename match_augmenter<VertexId, VertexProperty, EdgeProperty>::graph_t::
                    vertex_type & vertex,
            std::unordered_set<typename match_augmenter<VertexId, VertexProperty, EdgeProperty>::
                                       graph_t::vertex_type> & visited,
            const std::unordered_map<
                    typename match_augmenter<VertexId, VertexProperty, EdgeProperty>::graph_t::
                            vertex_type,
                    double> & distances)
    {
        visited.insert(vertex);

        for(auto && neighbour : this->graph.neighbours(vertex))
        {
            auto it = this->matching.find(neighbour);

            if(it == this->matching.end())
            {
                this->matching[vertex] = std::make_optional(neighbour);
                this->matching[neighbour] = std::make_optional(vertex);
                return true;
            }

            auto matched = it->second.value();

            if(visited.find(matched) == visited.end()
               && distances.at(matched) == distances.at(vertex) + 1
               && dfs(matched, visited, distances))
            {
                this->matching[vertex] = std::make_optional(neighbour);
                this->matching[neighbour] = std::make_optional(vertex);
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
     * \param graph the bipartite graph
     * \return the map of matched vertices
     */
    template <
            typename VertexId = size_t,
            typename VertexProperty = std::nullptr_t,
            typename EdgeProperty = std::nullptr_t>
    std::unordered_map<
            typename multipartite_graph<2, VertexId, VertexProperty, EdgeProperty>::vertex_type,
            typename multipartite_graph<2, VertexId, VertexProperty, EdgeProperty>::vertex_type>
            match(const multipartite_graph<2, VertexId, VertexProperty, EdgeProperty> & graph)
    {
        internal::match_augmenter<
                typename multipartite_graph<
                        2, VertexId, VertexProperty, EdgeProperty>::vertex_id_type,
                typename multipartite_graph<
                        2, VertexId, VertexProperty, EdgeProperty>::vertex_property_type,
                typename multipartite_graph<
                        2, VertexId, VertexProperty, EdgeProperty>::edge_property_type>
                augmenter(graph);
        std::unordered_map<
                typename multipartite_graph<2, VertexId, VertexProperty, EdgeProperty>::vertex_type,
                typename multipartite_graph<2, VertexId, VertexProperty, EdgeProperty>::vertex_type>
                matching;
        bool was_augmented = true;

        while(was_augmented)
            was_augmented = augmenter.augment_match();

        std::transform(
                augmenter.matching.begin(), augmenter.matching.end(),
                std::inserter(matching, matching.end()),
                [&](auto && entry) { return std::make_pair(entry.first, entry.second.value()); });
        return matching;
    }
}

#endif
