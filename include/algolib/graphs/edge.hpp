/*!
 * \file edge.hpp
 * \brief Structure of graph edge
 */
#ifndef EDGE_HPP_
#define EDGE_HPP_

#include <cstdlib>
#include <exception>
#include <stdexcept>

namespace algolib
{
    namespace graphs
    {
        template <typename V>
        class edge
        {
        public:
            edge(V source, V destination) : source_{source}, destination_{destination}
            {
            }

            ~edge() = default;
            edge(const edge<V> &) = default;
            edge(edge<V> &&) = default;
            edge<V> & operator=(const edge<V> &) = default;
            edge<V> & operator=(edge<V> &&) = default;

            const V & source() const
            {
                return source_;
            }

            const V & destination() const
            {
                return destination_;
            }

            V get_neighbour(V vertex) const
            {
                if(source_ == vertex)
                    return destination_;

                if(destination_ == vertex)
                    return source_;

                throw std::invalid_argument();
            }

            edge<V> reversed() const
            {
                return edge(destination_, source_);
            }

        private:
            V source_;
            V destination_;
        };

    }
}

#endif
